#include "greedy.h"

Greedy::Greedy(const InputData &input) : input(input), solution(input.size()) {
    streamPotential.resize(input.size(), 0);
    distancePotential.resize(input.size(), 0);
}

void Greedy::apply()
{
    // 1. Calculamos el potencial de flujo
    for (int i = 0; i < input.size(); ++i)
        for (int j = 0; j < input.size(); ++j)
            streamPotential[i] += input.getStream(i,j);

    // 2. Calculamos el potencial de distancia
    for (int i = 0; i < input.size(); ++i)
        for (int j = 0; j < input.size(); ++j)
            distancePotential[i] += input.getDistance(i,j);

    // 3. Los metemos en un multimap para tenerlos directamente ordenados.
    // La clave es el flujo/distancia y la descripción el identificador de unidad/localización.
    std::multimap<int, int, std::greater<int>> streamMap;
    std::multimap<int, int> distanceMap;

    for (int i = 0; i < input.size(); ++i)
        streamMap.insert({streamPotential[i],i});

    for (int i = 0; i < input.size(); ++i)
        distanceMap.insert({distancePotential[i], i});

    // 4. Asignamos en orden unidades con localizaciones
    auto itStream = streamMap.begin();
    auto itDistance = distanceMap.begin();

    while (itStream != streamMap.end()) {
        solution.assign(itStream->second, itDistance->second);
        ++itStream;
        ++itDistance;
    }

    // 5. Calculamos el costo de la solución
    solution.calculateCost(input);
}

QAPRepresentation Greedy::getSolution()
{
    return solution;
}

std::string Greedy::getSolverName()
{
    return "Greedy";
}
