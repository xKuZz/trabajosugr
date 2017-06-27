#include "RandomWalk.h"
#include <cstdlib>

int main(int argc, char **argv) {
    double distance = atof(argv[1]);
    // Inicio un nodo de ROS y le llamo random_walk
    ros::init(argc, argv, "random_walk");

    // Creo un objeto de la clase RandomWalk
    RandomWalk random_walk;
    random_walk.MIN_DIST_FROM_OBSTACLE = distance;

    // Inicio el método principal del objeto para controlar el robot
    random_walk.start();
}



