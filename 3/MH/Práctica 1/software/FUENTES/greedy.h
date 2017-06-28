#ifndef GREEDY_H
#define GREEDY_H
#include "inputdata.h"
#include "qaprepresentation.h"

#include <functional>
#include <map>
#include <vector>

/** @brief Solucionador greedy para el QAP **/
class Greedy
{
private:
    /** @brief Referencia a los datos leidos.
     */
    const InputData& input;
    /** @brief Representación de la solución obtenida mediante el algoritmo Greedy.
     */
    QAPRepresentation solution;

    /** @brief Potencial de flujo.
     */
    std::vector<InputData::Type> streamPotential;
    /** @brief Potencial de distancia.
     */
    std::vector<InputData::Type> distancePotential;
public:
    /** @brief Inicializa un objeto preparado para aplicar el algoritmo Greedy.
     */
    Greedy(const InputData& input);
    /** @brief Ejecuta el algoritmo Greedy sobre los datos de entrada.
     */
    void apply();
    /** @brief Devuelve la solución encontrada por el algoritmo Greedy.
     */
    QAPRepresentation getSolution();

    /** @brief Devuelve el nombre de la heurística aplicada **/
    std::string getSolverName();
};

#endif // GREEDY_H
