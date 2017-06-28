#ifndef ILS_H
#define ILS_H
#include "qaprepresentation.h"

template<class TrayectorySearch>
class ILS
{
public:
    ILS(const InputData& input) : input(input) {}

    void apply() {
        solution.permutation.resize(input.size());
        // Generamos una solución aleatoria
        for (int i = 0; i < input.size(); ++i)
            solution.assign(i,i);

        solution.randomShuffle(QAPRepresentation::seed);
        solution.calculateCost(input);

        generator.seed(QAPRepresentation::seed);

        // Aplicamos una primera búsqueda por trayectorias
        TrayectorySearch firstSearch(solution, input);
        firstSearch.apply();
        best_solution = solution = firstSearch.getSolution();
        for (int i = 0; i < 24; ++i) {
            QAPRepresentation solution_ = best_solution.mutation(generator, input);
            // Búsqueda por trayectoria
            TrayectorySearch search(solution_, input);
            search.apply();
            QAPRepresentation solution__ = search.getSolution();
            //std::cout << "Mutada: " << solution_ << '\n';
           // std::cout << "BL: " << solution__ << '\n';
            // Criterio de aceptación REVISAR!!
            solution = std::min(solution, solution__);
            // Actualizar mejor solución
            best_solution = std::min(best_solution, solution);
           // std::cout << best_solution << '\n';
        }
    }

    std::string getSolverName() const {
        std::string nombre = TrayectorySearch(input).getSolverName();
        return "ILS-" + nombre;
    }
    QAPRepresentation getSolution() const {
        return best_solution;
    }
private:
    std::default_random_engine generator;
    QAPRepresentation solution;
    QAPRepresentation best_solution;
    const InputData& input;
    std::string nombre;
};

#endif // ILS_H
