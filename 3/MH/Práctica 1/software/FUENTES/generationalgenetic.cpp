#ifndef GENERATIONALGENETIC_H
#include "generationalgenetic.h"
#endif

#ifndef GENERATIONALGENETIC_CPP
#define GENERATIONALGENETIC_CPP


template <class CrossOperator, bool statMode, int memeticGenerations, int memeticPercentage, Memetic memType, int LS_iters>
GenerationalGenetic<CrossOperator, statMode, memeticGenerations, memeticPercentage, memType, LS_iters>::GenerationalGenetic(const InputData &input) : input(input)
{
    poblation = QAPRepresentation::randomPoblation(poblationSize, input);
    std::sort(std::begin(poblation), std::end(poblation));
    if constexpr (memType == Memetic::None)
            solverName = "AGG-";
    else {
            solverName  = "AM-(";
            solverName += std::to_string(memeticGenerations);
            solverName += ", ";
            solverName += std::to_string(memeticPercentage *1.0/100).substr(0,3);
            if constexpr (memType == Memetic::Best && memeticPercentage != 100)
                solverName += "mej";
            solverName += ") Cruce: ";
    }
    solverName += CrossOperator().name;
    engine.seed(QAPRepresentation::seed);

}


template <class CrossOperator, bool statMode, int memeticGenerations, int memeticPercentage, Memetic memType, int LS_iters>
void GenerationalGenetic<CrossOperator, statMode, memeticGenerations, memeticPercentage, memType, LS_iters>::setCrossProbability(float value)
{
    crossProbability = value;
}


template <class CrossOperator, bool statMode, int memeticGenerations, int memeticPercentage, Memetic memType, int LS_iters>
void GenerationalGenetic<CrossOperator, statMode, memeticGenerations, memeticPercentage, memType, LS_iters>::apply()
{
    long evaluaciones = 0;
    crossPairs = std::ceil(crossProbability * poblationSize/2);
    genToMutate = std::floor(mutationProbability * input.size() * poblationSize);
    std::uniform_int_distribution<int> poblation_dist(0, poblationSize -1);
    std::uniform_int_distribution<int> gen_dist(0, input.size() -1);
    std::vector<int> parents(poblation.size());
    std::vector<QAPRepresentation> sons(poblation.size());

    // Bucle principal
    while (evaluaciones < 50000){
        if constexpr (memType == Memetic::Best) {
            if (generacion % memeticGenerations == 0 && generacion != 0) {
                double percent = memeticPercentage/100.0;
                for (int i = 0; i < percent * poblationSize; ++i) {
                    HillClimbing<> hc(poblation[i], input);
                    evaluaciones += hc.apply(LS_iters);
                    poblation[i] = hc.getSolution();
                }
             }
             std::sort(std::begin(poblation), std::end(poblation));
        }
        else if constexpr (memType == Memetic::Random) {
                if (generacion % memeticGenerations == 0 && generacion != 0) {
                    std::vector<int> toHC(poblationSize);
                    std::iota(std::begin(toHC), std::end(toHC), 0);
                    std::shuffle(std::begin(toHC), std::end(toHC), engine);
                    for (int i = 0; i < (memeticPercentage*1.0/100) * poblationSize;  ++i) {
                        HillClimbing<> hc(poblation[toHC[i]], input);
                        evaluaciones += hc.apply(LS_iters);
                        poblation[toHC[i]] = hc.getSolution();
                    }
                }
                std::sort(std::begin(poblation), std::end(poblation));
        }


        // ** INICIO GENÉTICO **/


        // Selección

        for (int i = 0; i < poblationSize; ++i) {
            int parent1, parent2;
         do {
                parent1 = poblation_dist(engine);
                parent2 = poblation_dist(engine);
         } while (parent1 == parent2);

            parents[i] = std::min(parent1, parent2);
        }

        // Cruce

        for (int i = 0; i < crossPairs; ++i) {
            sons[2*i] = CrossOperator()(poblation[parents[2*i]], poblation[parents[2*i+1]], input, engine);
            sons[2*i+1] = CrossOperator()(poblation[parents[2*i+1]], poblation[parents[2*i]], input, engine);
        }

        for (int i = 2*crossPairs; i < poblationSize; ++i) // Completamos con el resto de seleccionados
            sons[i] = poblation[parents[i]];

        // Mutación
        for (int i = 0; i < genToMutate; ++i) {
            QAPRepresentation& selected =  sons[poblation_dist(engine)];
            int gen1, gen2;
            do {
                gen1 = gen_dist(engine);
                gen2 = gen_dist(engine);
            } while (gen1 == gen2);

           selected = selected.twoOpt(gen1, gen2, input);
        }

        // Ordenamos los hijos de mejor solución a peor
        std::sort(std::begin(sons), std::end(sons));

        // Elitismo
        const QAPRepresentation& lastBest = poblation.front();
        bool remains = std::find(std::begin(sons), std::end(sons), lastBest) != std::end(sons);

        if (!remains)
            sons.back() = std::min(sons.back(), lastBest);



        std::sort(std::begin(sons), std::end(sons));

        if constexpr (statMode)
                if (sons.front() < poblation.front())
                   bestReachedIteration = generacion;
        poblation.swap(sons);



        if constexpr (statMode) {
                std::set<QAPRepresentation> test(std::begin(poblation), std::end(poblation));
                //std::cout << "[DEBUG] Convergence Level: " << test.size() << '\n';
                if ((int) test.size() < convergenceLevel) {
                    convergenceLevel = test.size();
                    convergenceIteration = evaluaciones;
                    convergenceGeneration = generacion;
                }


        }

        // Aumento el número de la generación
        ++generacion;
        evaluaciones += crossPairs * 2 + genToMutate;
        //        std::cout << "GENERACIÓN " << generacion << '\n';

    }


    std::cout << "Número evaluaciones objetivo: " << evaluaciones << '\n';
    std::cout << "Número de generaciones: " << generacion << '\n';
    if constexpr (statMode) {
        std::cout << "[STAT] Esperanza de mutaciones: " << genToMutate << '\n';
        std::cout << "[STAT] Nivel de convergencia: " << convergenceLevel << '\n';
        std::cout << "[STAT] Generación de convergencia: " << convergenceGeneration << '\n';
        std::cout << "[STAT] Evaluaciones en convergencia: " << convergenceIteration << '\n';
        std::cout << "[STAT] Generación de aparación de la solución: " << bestReachedIteration << '\n';
    }
}


template <class CrossOperator, bool statMode, int memeticGenerations, int memeticPercentage, Memetic memType, int LS_iters>
QAPRepresentation GenerationalGenetic<CrossOperator, statMode, memeticGenerations, memeticPercentage, memType, LS_iters>::getSolution()
{
    return poblation.front();
}


template <class CrossOperator, bool statMode, int memeticGenerations, int memeticPercentage, Memetic memType, int LS_iters>
std::string GenerationalGenetic<CrossOperator, statMode, memeticGenerations, memeticPercentage, memType, LS_iters>::getSolverName()
{
    return solverName;
}


#endif
