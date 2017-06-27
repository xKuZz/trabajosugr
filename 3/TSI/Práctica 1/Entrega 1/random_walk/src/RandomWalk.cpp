
#include "RandomWalk.h"
#include "geometry_msgs/Twist.h"
#include <cstdlib>
#include <cmath>

RandomWalk::RandomWalk()
{
    keepMoving = true;
    turning = false;

    // Advertise a new publisher for the robot's velocity command topic
    commandPub = node.advertise<geometry_msgs::Twist>("/cmd_vel_mux/input/teleop", 10);

    // Subscribe to the simulated robot's laser scan topic
    laserSub = node.subscribe("scan", 1, &RandomWalk::scanCallback, this);
    time_t time;
    srand(time);
}

// Send a velocity command
void RandomWalk::moveForward() {
    geometry_msgs::Twist msg; // The default constructor will set all commands to 0
    msg.linear.x = FORWARD_SPEED;
    commandPub.publish(msg);
}

void RandomWalk::turn()
{
    geometry_msgs::Twist msg;
    ROS_INFO("Girando");
    
    double myTime =  ((double) rand()/RAND_MAX) * 3; // Giro entre 0 y 3 segundos
    ROS_INFO("Tiempo de giro aleatorio: %f", myTime);
    ros::Duration turnTime(myTime); // Guardo el aleatorio como duración

    if (turnDirection)
        msg.angular.z = -TURN_SPEED;
    else
        msg.angular.z = TURN_SPEED;
    
    ros::Time before = ros::Time::now();
    ros::Time after = before;
    while (after-before < turnTime) {
    	commandPub.publish(msg);
    	after = ros::Time::now();
    }
  
    ROS_INFO("Giro Completado");
}


// Process the incoming laser scan message
void RandomWalk::scanCallback(const sensor_msgs::LaserScan::ConstPtr& scan)
{
    if (turning) return;
    bool isObstacleInFront = false;
    
    // Find the closest range between the defined minimum and maximum angles
    int minIndex = ceil((MIN_SCAN_ANGLE - scan->angle_min) / scan->angle_increment);
    int maxIndex = floor((MAX_SCAN_ANGLE - scan->angle_min) / scan->angle_increment);

    for (int currIndex = minIndex + 1; currIndex <= maxIndex; currIndex++) {
        if (scan->ranges[currIndex] < MIN_DIST_FROM_OBSTACLE) {
        	isObstacleInFront = true;
            break;
        }
    }

    int halfIndex = (maxIndex - minIndex )/ 2 + minIndex;

    double izquierda = 0.0;
    double derecha = 0.0;
    ROS_INFO("%lf", scan->range_min);
    for (int i = minIndex+1; i < halfIndex; ++i)
        if (scan->ranges[i] >= scan->range_min && scan->ranges[i] <= scan->range_max)
            derecha += 1;
        
    

    for (int i = halfIndex + 1; i <= maxIndex; ++i)
        if (scan->ranges[i] >= scan->range_min && scan->ranges[i] <= scan->range_max)
            izquierda += 1;

    if (isObstacleInFront) {
        ROS_INFO("Obstaculo detectado.");
        ROS_INFO("A la izquierda: %lf", izquierda);
        ROS_INFO("A la derecha: %lf", derecha);
        turning = true;
        if (derecha < izquierda) {
            ROS_INFO("Girando a la derecha.");
            turnDirection= true;
        }
        else {
            ROS_INFO("Girando a la izquierda.");
            turnDirection = false;
        }
        keepMoving = false;
        turning = false;
    }
    else {
        keepMoving = true;
    }
}

void RandomWalk::start()
{
    ros::Rate rate(10);
    ROS_INFO("Iniciando el robot.");

    while (ros::ok()) {
        if (keepMoving) {
            moveForward();
            ros::spinOnce();
            rate.sleep();
        }
        else
            turn();

    }
}


