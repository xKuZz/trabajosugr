#ifndef GENERATIONALGENETIC_H
#define GENERATIONALGENETIC_H

#include "qaprepresentation.h"
#include "hillclimbing.h"
#include <algorithm>
#include <cassert>
#include <set>

enum class Memetic {None, Random, Best};

template <class CrossOperator, bool statMode = false, int memeticGenerations = 10, int memeticPercentage= 10, Memetic memType = Memetic::None, int LS_iters = 400>
class GenerationalGenetic
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

    /** @brief Probabilidad de cruce */
    float crossProbability = 0.7;

    /** @brief Parejas a cruzar */
    int crossPairs;

    /** @brief Probabilidad de mutación */
    float mutationProbability = 0.001;

    /** @brief Genes a mutar */
    int genToMutate;

    /** @brief Tamaño de la población **/
    constexpr static int poblationSize = 50;

    /** @brief Generador de números pseudoaletorios */
    std::default_random_engine engine;

    int convergenceIteration = -1;
    int convergenceGeneration = -1;
    int convergenceLevel = 50;
    int bestReachedIteration = 0;
public:
    GenerationalGenetic(const InputData& input);

    void setCrossProbability(float value);
    void apply();

    /** @brief Devuelve la solución encontrada por el algoritmo Greedy.
     */
    QAPRepresentation getSolution();

    /** @brief Devuelve el nombre de la heurística aplicada **/
    std::string getSolverName();

    std::string solverName;

};

#include "generationalgenetic.cpp"

#endif // GENERATIONALGENETIC_H
