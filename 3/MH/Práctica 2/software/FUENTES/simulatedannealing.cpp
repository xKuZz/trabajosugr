#include "simulatedannealing.h"


std::string SimulatedAnnealing::getSolverName() const {
    return "Enfriamiento Simulado";
}

QAPRepresentation SimulatedAnnealing::getSolution() const {
    return bestSolution;
}
