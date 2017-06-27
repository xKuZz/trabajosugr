/*********************************************************************
*
* Software License Agreement (BSD License)
*
*  Copyright (c) 2008, Willow Garage, Inc.
*  All rights reserved.
*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*   * Redistributions of source code must retain the above copyright
*     notice, this list of conditions and the following disclaimer.
*   * Redistributions in binary form must reproduce the above
*     copyright notice, this list of conditions and the following
*     disclaimer in the documentation and/or other materials provided
*     with the distribution.
*   * Neither the name of Willow Garage, Inc. nor the names of its
*     contributors may be used to endorse or promote products derived
*     from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
*  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
*  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
*  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
*  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
*  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
*  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
*  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
*  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
*  POSSIBILITY OF SUCH DAMAGE.
*
* Authors: Eitan Marder-Eppstein, Sachin Chitta
*********************************************************************/
#include "../include/my_astar_planner/myAstarPlanner.h"
#include <pluginlib/class_list_macros.h>

//para pintar puntos
#include <visualization_msgs/Marker.h>

// para debugging
#include <sstream>
#include <string>







//register this planner as a BaseGlobalPlanner plugin
PLUGINLIB_EXPORT_CLASS(myastar_planner::MyastarPlanner, nav_core::BaseGlobalPlanner)

namespace myastar_planner {

  list<coupleOfCells>::iterator getPositionInList(list<coupleOfCells> & list1, unsigned int cellID);
  bool isContains(list<coupleOfCells> & list1, int cellID);

  MyastarPlanner::MyastarPlanner()
  : costmap_ros_(NULL), initialized_(false){}

  MyastarPlanner::MyastarPlanner(std::string name, costmap_2d::Costmap2DROS* costmap_ros)
  : costmap_ros_(NULL), initialized_(false){
    initialize(name, costmap_ros);
  }

  void MyastarPlanner::initialize(std::string name, costmap_2d::Costmap2DROS* costmap_ros){
    if(!initialized_){
      costmap_ros_ = costmap_ros;
      costmap_ = costmap_ros_->getCostmap();

      ros::NodeHandle private_nh("~/" + name);

      //vamos a asumir estos parámetros, que no es necesario enviar desde el launch.
      private_nh.param("step_size", step_size_, costmap_->getResolution());
      private_nh.param("min_dist_from_robot", min_dist_from_robot_, 0.10);
      //world_model_ = new base_local_planner::CostmapModel(*costmap_);

      //el plan se va a publicar en el topic "planTotal"
      plan_pub_ = private_nh.advertise<nav_msgs::Path>("planTotal",1);
      //los puntos del espacio de búsqueda se visualizan en "visualization_marker"
      marker_Open_publisher = private_nh.advertise<visualization_msgs::Marker>("open_list", 1000);
      marker_Closed_publisher = private_nh.advertise<visualization_msgs::Marker>("closed_list", 1000);
      marker_Goals_publisher = private_nh.advertise<visualization_msgs::Marker>("goals_markers", 1000);
      costmapLimit = costmapLimitStart = 10;

      initialized_ = true;
    }
    else
      ROS_WARN("This planner has already been initialized... doing nothing");
  }

  //we need to take the footprint of the robot into account when we calculate cost to obstacles
  unsigned char MyastarPlanner::footprintCost(double x_i, double y_i, double theta_i){
    std::vector<geometry_msgs::Point> footprint = costmap_ros_->getRobotFootprint();

    unsigned char maximo = 0;
    for(std::vector<geometry_msgs::Point>::iterator it = footprint.begin(); it != footprint.end(); ++it)
        maximo = std::max(maximo, costmap_->getCost(x_i+it->x, y_i+it->y));

    //check if the footprint is legal
    //double footprint_cost = world_model_->footprintCost(x_i, y_i, theta_i, footprint);
    return maximo;
  }


  bool MyastarPlanner::makePlan(const geometry_msgs::PoseStamped& start,
      const geometry_msgs::PoseStamped& goal, std::vector<geometry_msgs::PoseStamped>& plan){

    //***********************************************************
    // Inicio de gestion de ROS
    //***********************************************************
    if(!initialized_){
      ROS_ERROR("The astar planner has not been initialized, please call initialize() to use the planner");
      return false;
    }

    ROS_DEBUG("MyastarPlanner: Got a start: %.2f, %.2f, and a goal: %.2f, %.2f", start.pose.position.x, start.pose.position.y, goal.pose.position.x, goal.pose.position.y);

    plan.clear();
    closedList.clear();
    abiertos.clear();

    //obtenemos el costmap global  que está publicado por move_base.
    costmap_ = costmap_ros_->getCostmap();


    //Obligamos a que el marco de coordenadas del goal enviado y del costmap sea el mismo.
    //esto es importante para evitar errores de transformaciones de coordenadas.
    if(goal.header.frame_id != costmap_ros_->getGlobalFrameID()){
      ROS_ERROR("This planner as configured will only accept goals in the %s frame, but a goal was sent in the %s frame.",
          costmap_ros_->getGlobalFrameID().c_str(), goal.header.frame_id.c_str());
      return false;
    }

    tf::Stamped<tf::Pose> goal_tf;
    tf::Stamped<tf::Pose> start_tf;

    poseStampedMsgToTF(goal,goal_tf);
    poseStampedMsgToTF(start,start_tf);

    //obtenemos la orientación start y goal en start_yaw y goal_yaw.
    double useless_pitch, useless_roll, goal_yaw, start_yaw;
    start_tf.getBasis().getEulerYPR(start_yaw, useless_pitch, useless_roll);
    goal_tf.getBasis().getEulerYPR(goal_yaw, useless_pitch, useless_roll);


    /**************************************************************************/
    /*************** HASTA AQUÍ GESTIÓN DE ROS *********************************/
    /****************************************************************************/

    //pasamos el goal y start a estructura coupleOfCells
    coupleOfCells cpstart, cpgoal;
    double goal_x = goal.pose.position.x;
    double goal_y = goal.pose.position.y;
    unsigned int mgoal_x, mgoal_y;
    costmap_->worldToMap(goal_x,goal_y,mgoal_x, mgoal_y);
    cpgoal.index = MyastarPlanner::costmap_->getIndex(mgoal_x, mgoal_y);
    cpgoal.parent=0;
    cpgoal.gCost=0;
    cpgoal.hCost=0;
    cpgoal.fCost=0;

    if (cpgoal.index != lastGoal.index)
      costmapLimit = costmapLimitStart;

    lastGoal = cpgoal;
    double start_x = start.pose.position.x;
    double start_y = start.pose.position.y;
    unsigned int mstart_x, mstart_y;
    costmap_->worldToMap(start_x,start_y, mstart_x, mstart_y);
    cpstart.index = MyastarPlanner::costmap_->getIndex(mstart_x, mstart_y);
    cpstart.parent =cpstart.index;
    cpstart.gCost = 0;
    cpstart.hCost = MyastarPlanner::calculateHCost(cpstart.index,cpgoal.index);
    cpstart.costmapValue = costmap_->getCost(mstart_x, mstart_y);

    //insertamos la casilla inicial en abiertos
    //MyastarPlanner::openList.push_back(cpstart);
    abiertos.push(cpstart);
    ROS_INFO("Inserto en Abiertos: %d", cpstart.index );
    ROS_INFO("Index del goal: %d", cpgoal.index );



    /**************************************************************************/
    /*************** GESTIÓN VISUALIZACIÓN PUNTOS DE ABIERTOS Y CERRADOS********/
    /****************************************************************************/

    //visualization_msgs::Marker points;// definida en la clase como markers_OpenList
    inicializaMarkersPoints(markers_OpenList,"openList", 0,0.0f,1.0f,0.0f);
    inicializaMarkersPoints(markers_ClosedList,"closedList", 1,1.0f,0.0f,0.0f);
    inicializaMarkersLine_List(markers_Goals, "goals", 2, 0.0f, 0.0f,1.0f);

    limpiaMarkers(marker_Open_publisher, markers_ClosedList);
    limpiaMarkers(marker_Closed_publisher, markers_OpenList);




    /**************************************************************************/
    /*************** FIN GESTIÓN VISUALIZACIÓN PUNTOS DE ABIERTOS Y CERRADOS********/
    /****************************************************************************/


    //visualizamos start.
    visualizaCelda(marker_Open_publisher, markers_OpenList, cpstart.index);


    unsigned int explorados = 0;
    unsigned int currentIndex = cpstart.index;



    while (!abiertos.empty()) //while the open list is not empty continuie the search
    {
       // ROS_INFO("Abiertos tam:  %lu", abiertos.size());
        //ROS_INFO("Cerrados tam:  %lu", closedList.size());
        // Exploramos la casilla con mejor f
          // La sacamos de la cola con prioridad
          coupleOfCells casillaActual = abiertos.pop();
          currentIndex = casillaActual.index;
        //ROS_INFO("Expandiendo: %u", casillaActual.index);
          // La metemos en cerrados
          
          //closedList.sort();
          //closedList.push_back(casillaActual);
          pair<unsigned, coupleOfCells> toInsert;
          toInsert.first = currentIndex;
          toInsert.second = casillaActual;
          closedList.insert(toInsert);
          // La mostramos en rviz
          visualizaCelda(marker_Closed_publisher, markers_ClosedList, currentIndex);

          // if the currentCell is the goalCell: success: path found

          if(currentIndex==cpgoal.index)
          {
            //el plan lo construimos partiendo del goal, del parent del goal y saltando en cerrados "de parent en parent"
            //vamos insertando al final los waypoints (los nodos de cerrados), por tanto, cuando finaliza el bucle hay que darle la vuelta al plan
             ROS_INFO("Se han explorado %u nodos y cerrados tiene %u nodos", explorados, (unsigned int)closedList.size());
              //ros::Duration(10).sleep();
            //convertimos goal a poseStamped nueva
              geometry_msgs::PoseStamped pose;
              pose.header.stamp =  ros::Time::now();
              pose.header.frame_id = goal.header.frame_id;//debe tener el mismo frame que el de la entrada
              pose.pose.position.x = goal_x;
              pose.pose.position.y = goal_y;
              pose.pose.position.z = 0.0;
              pose.pose.orientation.x = 0.0;
              pose.pose.orientation.y = 0.0;
              pose.pose.orientation.z = 0.0;
              pose.pose.orientation.w = 1.0;

              //lo añadimos al plan
              plan.push_back(pose);


              coupleOfCells currentCouple = cpgoal;
              unsigned int currentParent = casillaActual.index;
              ROS_INFO("Inserta en Plan GOAL: %f, %f PADRE: %u", pose.pose.position.x, pose.pose.position.y, currentParent);
              //ros::Duration(1).sleep();

              while (currentParent != cpstart.index) //e.d. mientras no lleguemos al nodo start
              {
                //encontramos la posición de currentParent en cerrados
                map<unsigned, coupleOfCells>::iterator it=closedList.find(currentParent);
                //list<coupleOfCells>::iterator it = getPositionInList(closedList, currentParent);
                //visualizaCelda(marker_Closed_publisher,markers_ClosedList, currentParent);
                //hacemos esa posición que sea el currentCouple
                coupleOfCells currentCouple;
                currentCouple.index=currentParent;
                currentCouple.parent=it->second.parent;
                currentCouple.gCost=it->second.gCost;
                currentCouple.hCost=it->second.hCost;
                currentCouple.fCost=it->second.fCost;


                //creamos una PoseStamped con la informaciuón de currentCouple.index

                        //primero hay que convertir el currentCouple.index a world coordinates
                unsigned int mpose_x, mpose_y;
                double wpose_x, wpose_y;

                costmap_->indexToCells(it->second.index, mpose_x, mpose_y);
                costmap_->mapToWorld(mpose_x, mpose_y, wpose_x, wpose_y);

                //ROS_INFO("Las coordenadas de El PADRE de %u son (%u, %u) -> (%f, %f). Y su PADRE es %u.", currentParent, mpose_x,mpose_y,wpose_x, wpose_y, (*it).parent);
                //ros::Duration(1).sleep();

                        //después creamos la pose
                geometry_msgs::PoseStamped pose;
                pose.header.stamp =  ros::Time::now();
                pose.header.frame_id = goal.header.frame_id;//debe tener el mismo frame que el de la entrada
                pose.pose.position.x = wpose_x;
                pose.pose.position.y = wpose_y;
                pose.pose.position.z = 0.0;
                pose.pose.orientation.x = 0.0;
                pose.pose.orientation.y = 0.0;
                pose.pose.orientation.z = 0.0;
                pose.pose.orientation.w = 1.0;
                //insertamos la pose en el plan
                plan.push_back(pose);
                //ROS_INFO("Inserta en Plan: %f, %f", pose.pose.position.x, pose.pose.position.y);
                //hacemos que currentParent sea el parent de currentCouple
                currentParent = it->second.parent;
              }

              unsigned int mpose_x, mpose_y;
              double wpose_x, wpose_y;

              costmap_->indexToCells(cpstart.index, mpose_x, mpose_y);
              costmap_->mapToWorld(mpose_x, mpose_y, wpose_x, wpose_y);
              
              pose.header.stamp =  ros::Time::now();
              pose.header.frame_id = goal.header.frame_id;//debe tener el mismo frame que el de la entrada
              pose.pose.position.x = wpose_x;
              pose.pose.position.y = wpose_y;
              pose.pose.position.z = 0.0;
              pose.pose.orientation.x = 0.0;
              pose.pose.orientation.y = 0.0;
              pose.pose.orientation.z = 0.0;
              pose.pose.orientation.w = 1.0;
              //insertamos la pose en el plan
              plan.push_back(pose);
              //ROS_INFO("Inserta en Plan: %f, %f", pose.pose.position.x, pose.pose.position.y);


              
            ROS_INFO("Sale del bucle de generación del plan.");
            std::reverse(plan.begin(),plan.end());
           // completePath(plan, goal);

            //lo publica en el topic "planTotal"
            publishPlan(plan);
            return true;
          }

          
         // closedList.insert(casillaActual);
          
          //search the neighbors of the current Cell
          //vector <unsigned int> neighborCells=findFreeNeighborCell(currentIndex);
          //ROS_INFO("Ha encontrado %u vecinos", (unsigned int)neighborCells.size());
          JPSobtainSuccessors(casillaActual.index != casillaActual.parent, casillaActual.parent,
            casillaActual.index, casillaActual.gCost, cpgoal.index);
          // //neighbors that exist in the closedList are ignored
          // vector <unsigned int> neighborNotInClosedList;
          // for(uint i=0; i<neighborCells.size(); i++)
          // {
          //   if(!isContains(closedList,neighborCells[i]))
          //   {
          //     neighborNotInClosedList.push_back(neighborCells[i]);
          //   }
          // }
          // ROS_INFO("Ha encontrado %u vecinos que no están en cerrados", (unsigned int)neighborNotInClosedList.size());

          // //search the neighbors that already exist in the open List
          // vector <unsigned int> neighborsNotInOpenList;
          // for(uint i=0; i<neighborNotInClosedList.size(); i++)
          // {
          //   if(!abiertos.contains(neighborNotInClosedList[i])) {
              
          //   }
          // }


         //add the neighbors that are not in the open list to the open list and mark the current cell as their parent

         //addNeighborCellsToOpenList(neighborsNotInOpenList, currentIndex, casillaActual.gCost, cpgoal.index); //,tBreak);


         explorados++;

         //PINTO ABIERTOS
         //Anyadir neighborCells a points. pushback()
         
        // visualizaCelda(marker_Closed_publisher,markers_ClosedList, currentIndex);

          //Para los nodos que ya están en abiertos, comprobar en cerrados su coste y actualizarlo si fuera necesario

    }

    if(abiertos.empty())  // if the openList is empty: then failure to find a path
        {
            ROS_INFO("No ha sido posible trazar un camino!");

            if (costmapLimit + 10  <= 127)
              costmapLimit += 10;
            else {
              costmapLimit +=1;
            }
            ROS_INFO("[COSTMAP] Permitimos hasta limite %u", costmapLimit);
            return false;
           
        }

  }

  bool MyastarPlanner::isValidCell(unsigned cx, unsigned cy) {
      return cx >= 0 && cx < costmap_->getSizeInCellsX() &&
              cy >= 0 && cy < costmap_->getSizeInCellsY();
  }

  vector<unsigned> MyastarPlanner::JPSfindNeighbours(bool hasParent, unsigned parent, unsigned currentNode) {
      vector<unsigned> neighborhood;
      if (hasParent) { // Si el nodo actual tiene padre
          // 1. Determinamos la dirección de la que venimos
          unsigned cx, cy, px, py;
          costmap_->indexToCells(parent, px, py);
          costmap_->indexToCells(currentNode, cx, cy);
          // ROS_INFO("TEST DX: %d", cx-px);
          // ROS_INFO("TEST DY: %d", cy-py);
          int dx = (cx*1.0-px*1-0)/max(abs(cx*1.0-px*1.0), 1.0);
          int dy = (cy*1.0-py*1.0)/max(abs(cy*1.0-py*1.0), 1.0);
          // ROS_INFO("[JPS] Padre en %u, %u", px, py);
          // ROS_INFO("[JPS] Nuevo %u, %u", cx, cy);
          // ROS_INFO("Dirección dx: %d dy: %d", dx, dy);


          if (dx != 0 && dy != 0) { // Vamos en diagonal
              // ROS_INFO("[JPS] Movimiento en diagonal");
              bool moveX = false, moveY = false;
              // Vecinos naturales
              if (isValidMoveCell(cx, cy+dy)) {
                  unsigned index = costmap_->getIndex(cx, cy+dy);

                  neighborhood.push_back(index);
                  moveY = true;

              }
              if (isValidMoveCell(cx+dx, cy)) {
                  unsigned index = costmap_->getIndex(cx+dx, cy);

                  neighborhood.push_back(index);
                  moveX = true;

              }
              if (moveX || moveY) {
                  unsigned index = costmap_->getIndex(cx+dx, cy+dy);

                  neighborhood.push_back(index);
              }
              // Vecinos forzados
              if (!isValidMoveCell(cx-dx,cy) && moveY) {
                  unsigned index = costmap_->getIndex(cx-dx, cy+dy);

                  neighborhood.push_back(index);
              }
              if (!isValidMoveCell(cx,cy-dy) && moveX) {
                  unsigned index = costmap_->getIndex(cx+dx, cy-dy);

                  neighborhood.push_back(index);
              }
          }
          else if (dx == 0) { // Movimiento en Y
              // ROS_INFO("[JPS] Movimiento en Y");
              // Vecinos naturales
              if (isValidMoveCell(cx, cy + dy)) {
                  unsigned index = costmap_->getIndex(cx, cy+dy);

                  neighborhood.push_back(index);
              }
              // Vecinos forzados
              if (!isValidMoveCell(cx+1, cy)) {
                  unsigned index = costmap_->getIndex(cx+1, cy+dy);

                  neighborhood.push_back(index);
              }
              if (!isValidMoveCell(cx-1, cy)) {
                  unsigned index = costmap_->getIndex(cx-1, cy+dy);

                  neighborhood.push_back(index);
              }

          }
          else if (dy == 0) { // Movimiento en X
              // ROS_INFO("[JPS] Movimiento en X");
              // Vecinos naturales
              if (isValidMoveCell(cx + dx, cy)) {
                  unsigned index = costmap_->getIndex(cx+dx, cy);

                  neighborhood.push_back(index);
              }
              // Vecinos forzados
              if (!isValidMoveCell(cx, cy+1)) {
                  unsigned index = costmap_->getIndex(cx+dx, cy+1);

                  neighborhood.push_back(index);
              }
              if (!isValidMoveCell(cx, cy-1)) {
                  unsigned index = costmap_->getIndex(cx+dx, cy-1);

                  neighborhood.push_back(index);
              }

          }
      }
      else { // No tengo padre, genero los vecinos iniciales
          // ROS_INFO("[JPS] Generando vecinos iniciales");
          return findFreeNeighborCell(currentNode);
      }
      return neighborhood;
  }

  pair<bool, unsigned> MyastarPlanner::JPSJump(bool hasNode, unsigned currentNode, unsigned parent, unsigned endNode) {
      pair<bool,unsigned> p;
      p.first = false;
      if (!hasNode) return p;

      // Obtenemos casilla de nodo actual y dirección de la que venimos
      unsigned cx, cy, px, py;
      costmap_->indexToCells(parent, px, py);
      costmap_->indexToCells(currentNode, cx, cy);
      // ROS_INFO("[JPS] Padre en %u, %u", px, py);
      // ROS_INFO("[JPS] Nuevo %u, %u", cx, cy);
      int dx = cx-px;
      int dy = cy-py;
      // ROS_INFO("[JPS-JUMP] Dirección dx: %d dy: %d", dx, dy);

      // Si la celda actual no es válida paramos
      if (isValidCell(cx,cy) && !isValidMoveCell(cx,cy)) return p;
      // Si la celda actual es el objetivo devolverlo
      if (currentNode == endNode) {
          p.first = true;
          p.second = currentNode;
          return p;
      }
      if (dx != 0 && dy != 0) { // Caso diagonal
          // Es un punto de salto si alguno de sus vecinos a los lados es forzado
          if ((isValidMoveCell(cx-dx, cy+dy) && isValidCell(cx-dx,cy) && !isValidMoveCell(cx-dx,cy)) ||
                  (isValidMoveCell(cx+dx, cy-dy) && isValidCell(cx,cy-dy) && !isValidMoveCell(cx,cy-dy))) {
              p.first = true;
              p.second = currentNode;
              return p;
          }
      }
      else if (dx != 0) { // Buscamos en el eje X
          // Comprobamos los vecinos forzados
          if ((isValidMoveCell(cx+dx, cy+1) && isValidCell(cx,cy+1) && !isValidMoveCell(cx,cy+1)) ||
                  (isValidMoveCell(cx+dx, cy-1) && isValidCell(cx,cy-1) && !isValidMoveCell(cx,cy-1))) {
              p.first = true;
              p.second = currentNode;
              return p;
          }
      }
      else { // Buscamos en el eje Y
          // Comprobamos los vecinos forzados
          if ((isValidMoveCell(cx+1, cy+dy) && isValidCell(cx+1,cy) && !isValidMoveCell(cx+1,cy)) ||
                  (isValidMoveCell(cx-1, cy+dy) && isValidCell(cx-1,cy) && !isValidMoveCell(cx-1,cy))) {
              p.first = true;
              p.second = currentNode;
              return p;
          }
      }
      // Aplicamos recursividad para traza
      if (dx != 0 && dy != 0) {
          p.first = true;
          p.second = currentNode;
          pair<bool, unsigned> check;
          if (isValidCell(cx+dx,cy)) {
              unsigned newNode = costmap_->getIndex(cx+dx, cy);
              check = JPSJump(hasNode, newNode, currentNode, endNode);
              if (check.first) return p;
          }
          if (isValidCell(cx, cy+dy)) {
              unsigned newNode = costmap_->getIndex(cx, cy+dy);
              check = JPSJump(hasNode, newNode, currentNode, endNode);
              if (check.first) return p;
          }
      }

      if (isValidMoveCell(cx+dx,cy) || isValidMoveCell(cx, cy+dy)) {
          unsigned newNode = costmap_->getIndex(cx+dx, cy+dy);
          return JPSJump(hasNode, newNode, currentNode, endNode);
      }

      return p;
  }

  void MyastarPlanner::JPSobtainSuccessors(bool hasParent, unsigned parent, unsigned currentNode, float gCostParent, unsigned endNode) {
      // ROS_INFO("[JPS] Generando vecindario");
      vector<unsigned> neighborhood = JPSfindNeighbours(hasParent, parent, currentNode);
      //gCostParent = gCostParent + getMoveCost(parent, currentNode);
      for (unsigned i = 0; i < neighborhood.size(); ++i) {
          // Buscamos los puntos de salto de cada vecino
          pair<bool,unsigned> myJump = JPSJump(true,neighborhood[i],currentNode, endNode);
          if (myJump.first) {
              unsigned jumpNode = myJump.second;
              if (closedList.find(jumpNode)==closedList.end()) {
                  //if (!isContains(closedList, jumpNode)) {
                  vector<unsigned> toAdd;
                  toAdd.push_back(jumpNode);
                  // unsigned cx, cy, px, py;
                  // costmap_->indexToCells(parent, px, py);
                  // costmap_->indexToCells(neighborhood[i], cx, cy);
                  // ROS_INFO("[JPS] Ubicado en %u, %u", px, py);
                  // ROS_INFO("[JPS] Nuevo vecino: %u en %u, %u", jumpNode, cx, cy);
                  addNeighborCellsToOpenList(toAdd, currentNode, gCostParent, endNode);
              }
          }

      }
  }

  bool MyastarPlanner::checkConditions(double currentX, double currentY, double nx, double ny, const list<geometry_msgs::PoseStamped>::iterator &it) {

      bool checkX;
      if (nx > 0)
          checkX = currentX < it->pose.position.x;
      else if (nx == 0)
          checkX = true;
      else
          checkX = currentX > it->pose.position.x;

      bool checkY;
      if (ny > 0)
          checkY = currentY < it->pose.position.y;
      else if (ny == 0)
          checkY = true;
      else
          checkY = currentY > it->pose.position.y;

      return checkX && checkY;

  }


  //calculamos H como la distancia euclídea hasta el goal
  double MyastarPlanner::calculateHCost(unsigned int start, unsigned int goal) {
      unsigned int mstart_x, mstart_y, mgoal_x, mgoal_y;
      double wstart_x, wstart_y, wgoal_x, wgoal_y;

      //trasformamos el indice de celdas a coordenadas del mundo.
      //ver http://docs.ros.org/indigo/api/costmap_2d/html/classcostmap__2d_1_1Costmap2D.html

      costmap_->indexToCells(start, mstart_x, mstart_y);
      costmap_->mapToWorld(mstart_x, mstart_y, wstart_x, wstart_y);
      costmap_->indexToCells(goal, mgoal_x, mgoal_y);
      costmap_->mapToWorld(mgoal_x, mgoal_y, wgoal_x, wgoal_y);

      return sqrt((pow(wstart_x - wgoal_x,2))+pow(wstart_y - wgoal_y, 2));
  }


  //comparamos F para dos nodos.
  bool MyastarPlanner::compareFCost(coupleOfCells const &c1, coupleOfCells const &c2)
  {
      return c1.fCost < c2.fCost;
  }

  /*******************************************************************************/
  //Function Name: getPositnionInList
  //Inputs:the cellID, the list
  //Output: index of the cell in the list
  //Description: it is used to search the index of a cell in a list
  /*********************************************************************************/
  list<coupleOfCells>::iterator getPositionInList(list<coupleOfCells> & list1, unsigned int cellID)
  {
      for (list<coupleOfCells>::iterator it = list1.begin(); it != list1.end(); it++){
          if (it->index == cellID)
              return it;

      }
  }


  /*******************************************************************************
 * Function Name: findFreeNeighborCell
  * Inputs: the row and columun of the current Cell
  * Output: a vector of free neighbor cells of the current cell
  * Description:it is used to find the free neighbors Cells of a the current Cell in the grid
  * Check Status: Checked by Anis, Imen and Sahar
*********************************************************************************/
  vector <unsigned int> MyastarPlanner::findFreeNeighborCell (unsigned int CellID){

      unsigned int mx, my;
      double  wx, wy;
      costmap_->indexToCells(CellID,mx,my);
      ROS_INFO("Viendo vecinos de index: %u, Map coords: (%u,%u)", CellID, mx,my);

      vector <unsigned int>  freeNeighborCells;

      for (int x=-1;x<=1;x++)
          for (int y=-1; y<=1;y++){
              //check whether the index is valid
              //ROS_INFO("A ver: X = %u, Size_X = %u, Y = %u Size_Y = %u",mx+x, (unsigned int)costmap_->getSizeInCellsX(),my+y, (unsigned int)costmap_->getSizeInCellsY());
              if ((mx+x>=0)&&(mx+x < costmap_->getSizeInCellsX())&&(my+y >=0 )&&(my+y < costmap_->getSizeInCellsY())){
                  costmap_->mapToWorld( (unsigned int) mx+x, (unsigned int) my+y, wx, wy);

                  //ROS_INFO("Comprobando casilla con Map coords(%u,%u), World coords (%f,%f)", mx+x, my+y ,wx,wy);
                  if(costmap_->getCost(mx+x,my+y) < costmapLimit  && (!(x==0 && y==0))){
                      unsigned int index = costmap_->getIndex(mx+x,my+y);


                      // ROS_INFO("Vecina (%f, %f)", wx,wy);

                      freeNeighborCells.push_back(index);
                  }
              }


          }
      return  freeNeighborCells;
  }




  double MyastarPlanner::getMoveCost(unsigned int here, unsigned int there) {
      //calculo el coste de moverme entre celdas adyacentes como la distancia euclídea.
      return calculateHCost(here,there);

  }

  /*******************************************************************************/
  //Function Name: addNeighborCellsToOpenList
  //Inputs: the open list, the neighbors Cells and the parent Cell
  //Output:
  //Description: it is used to add the neighbor Cells to the open list
  /*********************************************************************************/
  void MyastarPlanner::addNeighborCellsToOpenList(vector <unsigned int>& neighborCells, unsigned int parent, float gCostParent, unsigned int goalCell) //,float tBreak)
  {
      vector <coupleOfCells> neighborsCellsOrdered;
        for(uint i=0; i< neighborCells.size(); i++)
        {
          coupleOfCells CP;
          CP.index=neighborCells[i]; //insert the neighbor cell
          CP.parent = parent; //insert the parent cell
          CP.gCost = gCostParent + getMoveCost(parent, CP.index);
          CP.hCost = getMoveCost(CP.index, goalCell);
         
          unsigned mx, my;
          costmap_->indexToCells(CP.index, mx, my);
          if (isValidCell(mx,my))
            CP.costmapValue = costmap_->getCost(mx,my);
          else
            CP.costmapValue = 500;

           CP.fCost = CP.gCost + CP.hCost;
 
          if (closedList.find(CP.index)==closedList.end()) {
          //if (!isContains(closedList,CP.index)) {
            abiertos.push(CP);
            visualizaCelda(marker_Open_publisher, markers_OpenList, CP.index);
          }

        }
      }


  /********VISUALIZAR ESPACIO DE BUSQUEDA *************************/

void MyastarPlanner::inicializaMarkersPoints(visualization_msgs::Marker &marker, string ns, int id, float r, float g, float b) {
        marker.header.frame_id = costmap_ros_->getGlobalFrameID().c_str();
        marker.header.stamp =  ros::Time::now();
        marker.ns = ns;

        marker.action = visualization_msgs::Marker::ADD; //la otra es DELETE
        marker.pose.orientation.w = 0.0;



        marker.id = id;



        marker.type = visualization_msgs::Marker::POINTS;




        // POINTS markers use x and y scale for width/height respectively
        marker.scale.x = costmap_->getResolution();
        marker.scale.y = costmap_->getResolution();


        // Points are green
        marker.color.g = g;
        marker.color.r = r;
        marker.color.b = b;
        marker.color.a = 1.0;

    }

void MyastarPlanner::inicializaMarkersLine_List(visualization_msgs::Marker &marker, string ns, int id, float r, float g, float b) {
        marker.header.frame_id = costmap_ros_->getGlobalFrameID().c_str();
        marker.header.stamp =  ros::Time::now();
        marker.ns = ns;

        marker.action = visualization_msgs::Marker::ADD; //la otra es DELETE
        marker.pose.orientation.w = 0.0;
        marker.pose.position.x = 0.0;
        marker.pose.position.y = 0.0;



        marker.id = id;



        marker.type = visualization_msgs::Marker::SPHERE;




        //Line lists also have some special handling for scale: only scale.x is used and it controls the width of the line segments.
        marker.scale.x = marker.scale.y = 0.5;
       // marker.scale.y = costmap_->getResolution();


        // Points are green
        marker.color.g = g;
        marker.color.r = r;
        marker.color.b = b;
        marker.color.a = 1.0;

    }

void MyastarPlanner::visualizaCoords(ros::Publisher where, visualization_msgs::Marker &marker, double x, double y) {
        //PINTO: cpstart.x, cpstart.y, scale == costmap_->getResolution
        geometry_msgs::Point p;
        p.x = x;
        p.y = y;
        p.z = 0; //¿?

        marker.points.push_back(p); //anyado el punto inicial
        marker.action = visualization_msgs::Marker::ADD;
        where.publish(marker); //lo publico
        //marker.points.pop_back(); //quito el punto de la lista de puntos, lo borro con DELETE cuando lo saque de abiertos.
        }

void MyastarPlanner::visualizaCoordsLineUp(ros::Publisher where, visualization_msgs::Marker &marker, double x, double y, double z) {
        //PINTO: cpstart.x, cpstart.y, scale == costmap_->getResolution

        marker.pose.position.x = x;
        marker.pose.position.y = y;
        where.publish(marker); //lo publico
        //points.points.pop_back(); //quito el punto de la lista de puntos, lo borro con DELETE cuando lo saque de abiertos.
        }

void MyastarPlanner::visualizaCelda(ros::Publisher where, visualization_msgs::Marker &marker, unsigned int index) {
        unsigned int mpose_x, mpose_y;
        double wpose_x, wpose_y;
        costmap_->indexToCells(index, mpose_x, mpose_y);
        costmap_->mapToWorld(mpose_x, mpose_y, wpose_x, wpose_y);
        visualizaCoords(where, marker, wpose_x, wpose_y);

    }

 void MyastarPlanner::visualizaLista(ros::Publisher where, visualization_msgs::Marker &marker, vector<unsigned int> lista) {
     for(vector<unsigned int>::iterator i = lista.begin(); i != lista.end(); ++i)
       {
         unsigned int mpose_x, mpose_y;
         double wpose_x, wpose_y;
         costmap_->indexToCells(*i, mpose_x, mpose_y);
         costmap_->mapToWorld(mpose_x, mpose_y, wpose_x, wpose_y);
         //PINTO: cpstart.x, cpstart.y, scale == costmap_->getResolution
         geometry_msgs::Point p;
         p.x = wpose_x;
         p.y = wpose_y;
         p.z = 0; //¿?

         marker.points.push_back(p);
        }
      where.publish(marker);
 //quitar neighborCells de points .popback
 }



 void MyastarPlanner::limpiaMarkers(ros::Publisher where, visualization_msgs::Marker &marker) {
    if (!marker.points.empty()){
        marker.action = visualization_msgs::Marker::DELETE;
        where.publish(marker);
        marker.action = visualization_msgs::Marker::ADD;
    }
    marker.points.clear();


 }

 bool operator<(const coupleOfCells &c1, const coupleOfCells &c2) {
     if (c1.fCost == c2.fCost)
         return c1.costmapValue < c2.costmapValue;
     // else
     //   return c1.gCost < c2.gCost;
     // else
     return c1.fCost < c2.fCost;
 }

 void MyPriorityQueue::push(const coupleOfCells &c) {
     abiertosIndex.insert(c.index);
     abiertos.push(c);
 }

 coupleOfCells MyPriorityQueue::pop() {
     coupleOfCells mejor = abiertos.top();
     abiertosIndex.erase(mejor.index);
     abiertos.pop();

     return mejor;
 }

 void MyPriorityQueue::clear() {
     abiertosIndex.clear();
     abiertos = priority_queue<coupleOfCells, vector<coupleOfCells>, greater<coupleOfCells> >();
 }

 bool MyPriorityQueue::empty() {
     // bool keepChecking = true;
     // while (keepChecking && !abiertosIndex.empty()) {
     //   coupleOfCells mejor = abiertos.top();
     //   if (!contains(mejor.index))
     //     abiertos.pop();
     //   else
     //     keepChecking = false;
     // }
     return abiertosIndex.empty();
 }


}
