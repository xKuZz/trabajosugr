#include "steadystategenetic.h"

#ifndef STEADYSTATEGENETIC_CPP
#define STEADYSTATEGENETIC_CPP

template<class CrossOperator, bool statMode>
void SteadyStateGenetic<CrossOperator, statMode>::apply()
{
    long evaluaciones = 0;
    int frecuencyMutation = std::ceil(1/(mutationProbability * input.size() * poblationSize));
    //std::cout << frecuencyMutation;
    genToMutate = std::floor(mutationProbability * input.size() * poblationSize);
    std::vector<int> parents(2);
    std::vector<QAPRepresentation> sons(4);
    std::uniform_int_distribution<int> poblation_dist(0, poblationSize-1);
    std::uniform_int_distribution<int> chromosome_dist(0, 1);
    std::uniform_int_distribution<int> gen_dist(0, input.size()-1);
    // Bucle principal
    while (evaluaciones < 50000){
        // Ordenamos la población
        std::sort(std::begin(poblation), std::end(poblation));

        for (int i = 0; i < 2; ++i) {
            int parent1, parent2;
            do {
                parent1 = poblation_dist(engine);
                parent2 = poblation_dist(engine);
            } while (parent1 == parent2);

            parents[i] = std::min(parent1, parent2);
        }

        // b) CRUCE
        // Preparo nueva población
        // Cruzamos ordenadamente las parejas según han sido obtenidas.
        sons[0] = CrossOperator()(poblation[parents[0]], poblation[parents[1]], input,engine);
        sons[1] = CrossOperator()(poblation[parents[1]], poblation[parents[0]], input,engine);
        evaluaciones +=2;


        // c) MUTACIÓN
        if (generacion % frecuencyMutation == 0)
          for (int i = 0; i < genToMutate; ++i) {
            QAPRepresentation& selected = sons[chromosome_dist(engine)];
            int gen1, gen2;
            do {
                gen1 = gen_dist(engine);
                gen2 = gen_dist(engine);
            } while (gen1 == gen2);

           selected = selected.twoOpt(gen1, gen2, input);
           ++evaluaciones;
        }

        sons[2] = poblation[poblationSize-2];
        sons[3] = poblation[poblationSize-1];

        std::sort(std::begin(sons), std::end(sons));

        poblation[poblationSize - 2] = sons[0];
        poblation[poblationSize - 1] = sons[1];

        // Aumento el número de la generación
        ++generacion;
//        std::cout << "GENERACIÓN " << generacion << '\n';

    }


    std::cout << "Número evaluaciones objetivo: " << evaluaciones << '\n';
    std::cout << "Número de generaciones: " << generacion  << '\n';
//            for (auto representacion: poblation)
//                std::cout << representacion << '\n';
}

template<class CrossOperator, bool statMode>
QAPRepresentation SteadyStateGenetic<CrossOperator, statMode>::getSolution()
{
    return poblation.front();
}

template<class CrossOperator, bool statMode>
std::string SteadyStateGenetic<CrossOperator, statMode>::getSolverName()
{
    return "AGE-" + CrossOperator().name;
}

template<class CrossOperator, bool statMode>
int SteadyStateGenetic<CrossOperator, statMode>::binaryTournament(const int first, const int second) const
{
   return (poblation[first] < poblation[second]) ? first : second;
}

template<class CrossOperator, bool statMode>
SteadyStateGenetic<CrossOperator, statMode>::SteadyStateGenetic(const InputData &input) : input(input)
{
    poblation = QAPRepresentation::randomPoblation(poblationSize, input);

    engine.seed(QAPRepresentation::seed);

}

#endif
