#ifndef HILLCLIMBING_H
#include "hillclimbing.h"
#endif

#ifndef HILLCLIMBING_CPP
#define HILLCLIMBING_CPP
template<bool statMode>
HillClimbing<statMode>::HillClimbing(const InputData &input) : input(input), solution(input.size()),
                                                     dlb(input.size(), false)
{
    for (int i = 0; i < input.size(); ++i)
        solution.assign(i,i);

    solution.randomShuffle(QAPRepresentation::seed);
    solution.calculateCost(input);
}
template<bool statMode>
HillClimbing<statMode>::HillClimbing(const QAPRepresentation &solution, const InputData &input)
                            : input(input), solution(solution), dlb(input.size(), false)
{

}
template<bool statMode>
int HillClimbing<statMode>::apply(int REPS_MAX) {
    long coste_anterior = std::numeric_limits<long>::max();
    int reps = 0;
    mejorado = false;
    while(solution.getCost() < coste_anterior) {
      coste_anterior = solution.getCost();
      for (int i = 0; i < input.size() && reps < REPS_MAX; ++i)
        if (bool isBetter = false; !dlb[i]) {
            for (int j = 0; j < input.size(); ++j, ++reps)
                if (auto neighbor = solution.twoOpt(i,j, input); neighbor < solution) {
                    solution = neighbor;
                    mejorado = true;
                    dlb[i] = dlb[j] = 0;
                    isBetter = true;
                }
            if (!isBetter)
                dlb[i] = 1;
        }
    }

    if constexpr (statMode) {
            if (mejorado)
                std::cout << "BL útil\n";
            else
                std::cout << "BL inútil\n";
            std::cout << "Número evaluaciones objetivo: " << reps << '\n';
    }
    return reps;
}
template<bool statMode>
QAPRepresentation HillClimbing<statMode>::getSolution()
{
    return solution;
}

template<bool statMode>
std::string HillClimbing<statMode>::getSolverName() {
    return "Búsqueda local del primer mejor";
}

#endif
