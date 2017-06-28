#ifndef STEADYSTATEGENETIC_H
#define STEADYSTATEGENETIC_H

#include "qaprepresentation.h"
#include <algorithm>

template<class CrossOperator, bool statMode = false>
class SteadyStateGenetic
{
private:
    /** @brief Referencia a los datos leidos.
     */
    const InputData& input;

    /** @brief Población actual
     */
    std::vector<QAPRepresentation> poblation;

    /** @brief Mejor de la población en la iteración anterior **/
    QAPRepresentation lastBest;

    /** @brief Número de generación actual **/
    long generacion = 0;


    /** @brief Probabilidad de mutación */
    float mutationProbability = 0.001;

    /** @brief Genes a mutar */
    int genToMutate;

    /** @brief Tamaño de la población **/
    constexpr static int poblationSize = 50;

    /** @brief Generador de números pseudoaletorios */
    std::default_random_engine engine;


public:
    SteadyStateGenetic(const InputData& input);

    void setCrossProbability(float value);
    void apply();

    /** @brief Devuelve la solución encontrada por el algoritmo Greedy.
     */
    QAPRepresentation getSolution();

    /** @brief Devuelve el nombre de la heurística aplicada **/
    std::string getSolverName();

    int binaryTournament(const int first, const int second) const;

};

#include "steadystategenetic.cpp"
#endif // STEADYSTATEGENETIC_H
