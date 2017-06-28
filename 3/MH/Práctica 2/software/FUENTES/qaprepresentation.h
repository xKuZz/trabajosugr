#ifndef QAPREPRESENTATION_H
#define QAPREPRESENTATION_H

#include <algorithm>
#include <iostream>
#include <random>
#include <map>
#include <set>
#include <utility>
#include <vector>

#include "inputdata.h"


/** @brief Contiene la representación de una posible solución al problema y algunos operadores sobre ella.
 */
class QAPRepresentation
{
public:
    // La representación se basa en un vector que representa una permutación donde
    // los índices es el identificador de la unidad a colocar y los datos la localización a asignar
    std::vector<int> permutation;

    // Costo de la solución actual.
    long int costo;
public:
    static long seed;
    QAPRepresentation() {}
    /** @brief Crea una representación de una posible solución al problema.
     *  @param n Tamaño del problema que se está resolviendo.
     */
    QAPRepresentation(int n);

    /** @brief Asigna en la solución actual el identificador de la unidad al identificador de la localización propuesta
     *  @param unitID Unidad a asignar.
     *  @param locationID localización a asignar.
     *  @pre Se considera que ambos identificadores son estrictamente menores que el tamaño del problema.
     */

    QAPRepresentation(const std::vector<int>& permutation) : permutation(permutation) {}

    void assign(int unitID, int locationID);

    /** @brief Calcula el costo de la permutación completa actual.
     *  @param input Datos de entrada del problema.
     *  @pre input no debe haber sido modificado desde la llamada al constructor (al menos en tamaño).
     *
     */
    void calculateCost(const InputData& input);

    /** @brief Obtiene una permutación aleatoria a partir de la actual.
     *  @param seed Semilla para la generación aleatoria.
     */

    /** @brief Cruza la solución actual con otra pasada por parámetro para obtener un hijo.
     *  @param qap Solución con la que cruzarse.
     *  @param input Datos de entrada del problema.
     *  @return Representación del hijo.
     */
    static QAPRepresentation positionalCrossover(const QAPRepresentation& father, const QAPRepresentation& mother, const InputData& input,
                                                 std::default_random_engine& engine);

    static QAPRepresentation OXCrossover(const QAPRepresentation& father, const QAPRepresentation& mother, const InputData& input,
                                         std::default_random_engine& engine);

    static QAPRepresentation PMXCrossover(const QAPRepresentation& father, const QAPRepresentation& mother, const InputData& input,
                                          std::default_random_engine& engine);

    /** @brief Genera una población aleatoria para el problema actual.
     *  @param poblationSize Tamaño de la población a crear.
     *  @param input Datos de entrada del problema.
     */
    static std::vector<QAPRepresentation> randomPoblation(int poblationSize, const InputData &input);

    void randomShuffle(int seed);

    /** @brief Operador de intercambio de dos posiciones de la permutación (calcula el nuevo costo).
     *  @param r Primera posición a intercambiar.
     *  @param s Segunda posición a intercambiar.
     * @param input Datos de entrada del problema.
     *  @pre r y s han de ser índices válidos de la permutación.
     *  @return Representación (solución y costo) tras aplicar el operador.
     */
    QAPRepresentation twoOpt(int r, int s, const InputData& input);

    /** @brief Determina si una solución es mejor que otra (tiene menos costo).
     *  @param qapr Solución con la que comparar la actual.
     *  @return Si el coste de la primera es menor que el de la segunda.
     */
    bool operator<(const QAPRepresentation& qapr) const;

    /** @brief Sobrecarga del operador de salida para flujos de una posible solución.
     *  @param os Flujo a utilizar.
     *  @param input Datos leídos.
     *  @return Referencia al flujo tras ser modificado.
     */

    bool operator==(const QAPRepresentation& qapr) const;

    bool operator!=(const QAPRepresentation& qapr) const {
        return permutation != qapr.permutation;
    }
    friend std::ostream& operator<<(std::ostream& os, const QAPRepresentation& rep);

    /** @brief Devuelve el costo de la solución actual.
     *  @return Costo de la solución actual.
     */
    long getCost() const;

    long getCostGRASP(const InputData& input, const int stream, const int distance);

    QAPRepresentation mutation(std::default_random_engine& generator, const InputData& input) {
        int tam = input.size()/4;
        std::uniform_int_distribution<int> startPositionDist(0, input.size()-tam-1);
        int startPosition = startPositionDist(generator);
        std::vector<int> toShuffle(std::begin(permutation)+startPosition,
                                   std::begin(permutation)+startPosition+tam);
        std::shuffle(std::begin(toShuffle), std::end(toShuffle), generator);

        QAPRepresentation toReturn(*this);
        for (int i = 0; i < startPosition; ++i)
            toReturn.permutation[i] = permutation[i];

        for (int i = startPosition; i < startPosition + tam; ++i)
            toReturn.permutation[i] = toShuffle[i-startPosition];

        for (unsigned i = startPosition + tam; i < permutation.size(); ++i)
            toReturn.permutation[i] = permutation[i];

        toReturn.calculateCost(input);
        return toReturn;
    }
};

/** @brief Sobrecarga del operador de salida para flujos de una posible solución.
 *  @param os Flujo a utilizar.
 *  @param input Datos leídos.
 *  @return Referencia al flujo tras ser modificado.
 */
std::ostream& operator<<(std::ostream& os, const QAPRepresentation& rep);


struct PositionalCross {
    QAPRepresentation operator()(const QAPRepresentation& father, const QAPRepresentation& mother, const InputData& input,
                                 std::default_random_engine& engine) const {
        return QAPRepresentation::positionalCrossover(father, mother, input, engine);
    }
    std::string name = "Posición";
};

struct OXCross {
    QAPRepresentation operator()(const QAPRepresentation& father, const QAPRepresentation& mother, const InputData& input,
                                 std::default_random_engine& engine) {
        (void)engine;
        return QAPRepresentation::OXCrossover(father,mother,input,engine);
    }
    std::string name = "OX";
};

struct PMXCross {
    QAPRepresentation operator()(const QAPRepresentation& father, const QAPRepresentation& mother, const InputData& input,
                                 std::default_random_engine& engine) {
        (void)engine;
        return QAPRepresentation::PMXCrossover(father,mother,input, engine);
    }
    std::string name = "PMX";
};

#endif // QAPREPRESENTATION_H

