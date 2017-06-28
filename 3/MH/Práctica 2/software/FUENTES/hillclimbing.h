#ifndef HILLCLIMBING_H
#define HILLCLIMBING_H


#include "qaprepresentation.h"

template<bool statMode = false>
/** @brief Solucionador con búsqueda local el primer mejor */
class HillClimbing
{
    /** @brief Referencia a los datos leidos. */
    const InputData& input;

    /** @brief Mejor solución encontrada hasta ahora. Inicalizado aleatoriamente. */
    QAPRepresentation solution;

    /** @brief Máscara para el Don't Look Bits */
    std::vector<bool> dlb;

public:
    /** @brief Inicializa una solución aleatorio (basando en la semilla) para el caso actual y inicia a 0
     *  la máscara Don't Look Bits.
     */
    HillClimbing(const InputData& input);
    HillClimbing(const QAPRepresentation& solution, const InputData& input);

    int apply(int REPS_MAX = 50000);
    bool mejorado;

    /** @brief Devuelve la solución encontrada por el algoritmo.
     */
    QAPRepresentation getSolution();

    std::string getSolverName();
};

#include "hillclimbing.cpp"
#endif // HILLCLIMBING_H
