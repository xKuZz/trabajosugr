
#ifndef RANDOM_WALK_H_
#define RANDOM_WALK_H_
#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"

class RandomWalk {
public:
    // Parámetros que se pueden ajustar
    /** @brief Velocidad de movimiento en caso de avanzar (m/s). */
    const static double FORWARD_SPEED = 0.3;
    /** @brief Ángulo mínimo de escaneo para el láser asociado al robot.
     *  (modificar el número antes de /180 * M_PI para introducirlo en grados).
     */
    const static double MIN_SCAN_ANGLE = -30.0/180*M_PI;
    
    const static double MAX_SCAN_ANGLE = +30.0/180*M_PI;
    /** @brief Distancia mínima con respecto a un obstáculo en la que el robot debería dejar de avanzar.
     *  @pre Debería ser más pequeña que sensor_msgs::LaserScan::range_max.
     */
    float MIN_DIST_FROM_OBSTACLE;
    
    /** @brief Velocidad del giro robot (º/s -> rad/s).
     *  (modificar el número antes de /180 * M_PI para introducirlo en grados).
     */
    const static double TURN_SPEED = 72.0/180*M_PI;
    /** @brief Inicializa el objeto suscribiéndose a los topic necesarios y los callbacks. */
    RandomWalk();
    /** @brief Método principal de interacción con ROS para controlar el robot. */
    void start();

private:
    /** @brief Manejador del nodo */
    ros::NodeHandle node;
    /** @brief Publicador al topic de velocidad del robot */
    ros::Publisher commandPub;
    /** @brief Suscriptor al láser del robot **/
    ros::Subscriber laserSub;
    /** @brief Indicia si el robot debe seguir avanzando */
    bool keepMoving;
    /** @brief Verdadero si gira a la derecha, si no gira a la izquierda */
    bool turnDirection;
    /** @brief Indica si el robot está girando */
    bool turning;

    /** @brief Método que se encarga de hacer al robot avanzar en línea recta */
    void moveForward();
    /** @brief Método que se encarga de hacer al robot girar durante un tiempo aleatorio. */
    void turn();
    /** @brief Método que se encarga de iterpretar la información del laser.
     *  @param scan Mensaje del láser.
     */
    void scanCallback(const sensor_msgs::LaserScan::ConstPtr& scan);
};

#endif // RANDOM_WALK_H_
