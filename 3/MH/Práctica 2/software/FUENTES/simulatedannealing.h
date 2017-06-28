#ifndef SIMULATEDAHEALING_H
#define SIMULATEDAHEALING_H
#include "qaprepresentation.h"
#include <cassert>

class SimulatedAnnealing
{
public:
    SimulatedAnnealing(const InputData& input) : input(input) {
        probability = std::uniform_real_distribution<float>(0,1);
        currentSolution.permutation.resize(input.size());
        // Inicalización de solución inicial y generador de aleatorios
        for (int i = 0; i < input.size(); ++i)
            currentSolution.assign(i,i);
        generator.seed(QAPRepresentation::seed);
        std::shuffle(std::begin(currentSolution.permutation), std::end(currentSolution.permutation), generator);
        currentSolution.calculateCost(input);
        bestSolution = currentSolution;
    }

    SimulatedAnnealing(const QAPRepresentation& qap, const InputData& input) : input(input) {
        probability = std::uniform_real_distribution<float>(0,1);
        bestSolution = currentSolution = qap;
    }

    int apply(const int MAX_EVALUACIONES = 50000) {
        int evaluaciones = 0;
        initialize();
        countSuccess = 1;
        while (temperature > endTemperature && countSuccess > 0 &&
               evaluaciones < MAX_EVALUACIONES) {

         //   std::cout << "ITERACIÓN " << k << '\n';
            countSuccess = 0;
            countNeighbours = 0;
            while (countSuccess < max_success && countNeighbours < max_neighbours) {
                auto neighbour = randomNeighbour();
                updateCurrentSolution(neighbour);
                ++evaluaciones;
            }
            Cooling();
           // std::cout << "TEMPERATURA ACTUAL" << temperature << '\n';
        }
//        std::cout << "ENFRIAMIENTOS REALIZADOS " << k << '\n';
//        if (temperature > endTemperature)
//            std::cout << "PARADA POR TEMPERATURA\n";
//        else if (countSuccess > 0)
//            std::cout << "PARADA POR ÉXITOS 0\n";
        return evaluaciones;
    }

    std::string getSolverName() const;

    QAPRepresentation getSolution() const;

private:
    const InputData& input;
    std::default_random_engine generator;
    QAPRepresentation currentSolution, bestSolution;
    std::uniform_int_distribution<int> twoOptDistribution;
    std::uniform_real_distribution<float> probability;
    double temperature;
    double startTemperature;
    double endTemperature;
    double beta;
    int countSuccess = 0;
    int countNeighbours = 0;
    int max_neighbours;
    int max_success;
    int max_coolings;

    // Funciones para organizar el funcionamiento del algoritmo
    void initialize() {
        twoOptDistribution = std::uniform_int_distribution<int>(0, input.size()-1);
        // Inicialización de parámetros del algoritmo
        calculateStartTemperature(0.3, 0.3);
        max_neighbours = 10 * input.size();
        max_success = 0.1 * max_neighbours;
        max_coolings = std::round(50000/max_neighbours);
        endTemperature = 0.001;

        beta = (startTemperature - endTemperature) / (max_coolings*1.0 * startTemperature * endTemperature);
       // k = 0;
        assert(startTemperature > endTemperature);
        temperature = startTemperature;
    }

    void calculateStartTemperature(float mu, float fi) {
        startTemperature = mu * currentSolution.getCost();
        startTemperature /= - std::log(fi);
    }

    void updateCurrentSolution(const QAPRepresentation& neighbour) {
        long deltaF = neighbour.getCost() - currentSolution.getCost();
        if (deltaF < 0 || probability(generator) <= std::exp(-deltaF/temperature)) {
            currentSolution = neighbour;
            ++countSuccess;
            bestSolution = std::min(bestSolution, currentSolution);
        }
    }

    QAPRepresentation randomNeighbour() {
        ++countNeighbours;
        auto pos1 = twoOptDistribution(generator);
        auto pos2 = twoOptDistribution(generator);
        return currentSolution.twoOpt(pos1, pos2, input);
    }

    void Cooling() {
        //std::cout << beta << '\n';
        temperature= temperature/(1+beta*temperature);
    }



};

#endif // SIMULATEDANNEALING_H
