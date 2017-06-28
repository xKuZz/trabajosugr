#include "qaprepresentation.h"
#include <cassert>

long QAPRepresentation::getCost() const
{
    return costo;
}

QAPRepresentation::QAPRepresentation(int n)
{
    permutation.resize(n);
}

void QAPRepresentation::assign(int unitID, int locationID)
{
    permutation[unitID] = locationID;
}

void QAPRepresentation::calculateCost(const InputData &input) {
    costo = 0;
    for (int i = 0; i < input.size(); ++i)
        for (int j = 0; j < input.size(); ++j)
            costo += input.getDistance(permutation[i], permutation[j]) *
                    input.getStream(i,j);

}

QAPRepresentation QAPRepresentation::positionalCrossover(const QAPRepresentation &father, const QAPRepresentation &mother, const InputData& input, std::default_random_engine &engine)
{
    // 1. Creamos la representación del hijo con el mismo tamaño que los padres.
    QAPRepresentation son;
    std::vector<int> sonPermutation(father.permutation.size(), -1);

    // 2. Asignamos las posiciones que son iguales para ambos padres
    std::vector<int> restos;
    for (auto i = 0u; i < sonPermutation.size(); ++i)
        if (father.permutation[i] == mother.permutation[i])
            sonPermutation[i] = mother.permutation[i];
        else
            restos.push_back(mother.permutation[i]);

    std::shuffle(std::begin(restos), std::end(restos), engine);
    auto it = std::begin(restos);
    for (auto& d :sonPermutation)
        if (d == -1)
            d = *(it++);

    // 4. Devolvemos la representación de la nueva solución.
    son.permutation = sonPermutation;
    son.calculateCost(input);
    return son;

}

QAPRepresentation QAPRepresentation::OXCrossover(const QAPRepresentation& father, const QAPRepresentation &mother, const InputData &input, std::default_random_engine &engine)
{
    // 1 Creamos la representación del hijo con el mismo tamaño que los padres
    QAPRepresentation son;
    std::vector<int> sonPermutation(father.permutation.size(), -1);

    // Obtenemos un tamaño aleatorio para la subcadena central entre N/8 y N/6
    std::uniform_int_distribution<int> sizeDist(father.permutation.size()/8, father.permutation.size()/6);
    auto midSize = sizeDist(engine);
    std::uniform_int_distribution<int> startDist(0,father.permutation.size() - 1 - midSize);


    // 2. Asignamos la subcadena central del padre
    int centerStart = startDist(engine);
    int centerEnd = centerStart + midSize;

    for (auto i = centerStart; i < centerEnd; ++i)
        sonPermutation[i] = father.permutation[i];

    // 3. Cogemos el resto en orden de la madre
    std::vector<int> motherData;

    for (auto d: mother.permutation)
        if (std::find(std::begin(sonPermutation), std::end(sonPermutation), d) == std::end(sonPermutation))
            motherData.push_back(d);


    auto begin = std::begin(motherData);
    for (auto i = 0; i <  centerStart; ++i, ++begin)
        sonPermutation[i] = *begin;

    for (auto i = centerEnd; i < (int) father.permutation.size(); ++i, ++begin)
        sonPermutation[i] = *begin;

    son.permutation = sonPermutation;
    son.calculateCost(input);

    return son;
}

QAPRepresentation QAPRepresentation::PMXCrossover(const QAPRepresentation &father, const QAPRepresentation &mother, const InputData &input, std::default_random_engine &engine) {
    // 1 Creamos la representación del hijo con el mismo tamaño que los padres
    QAPRepresentation son;
    std::vector<int> sonPermutation(father.permutation.size(), -1);


    // Obtenemos un tamaño aleatorio para la subcadena central entre N/8 y N/6
    std::uniform_int_distribution<int> sizeDist(father.permutation.size()/8, father.permutation.size()/6);
    auto midSize = sizeDist(engine);
    std::uniform_int_distribution<int> startDist(0,father.permutation.size() - 1 - midSize);


    // 2. Asignamos la subcadena central del padre
    int centerStart = startDist(engine);
    int centerEnd = centerStart + midSize;

    std::map<int, int> corresponds;
    for (auto i = centerStart; i < centerEnd; ++i) {
        sonPermutation[i] = father.permutation[i];
        if (father.permutation[i] != mother.permutation[i])
            corresponds.insert({father.permutation[i], mother.permutation[i]});
    }


    for(auto& p_current : corresponds) {
        std::vector<int> cicleNumbers;
        cicleNumbers.push_back(p_current.first);
        auto it = corresponds.find(p_current.second);
        while (it != corresponds.end())
            if (std::find(std::begin(cicleNumbers), std::end(cicleNumbers), it->second) == std::end(cicleNumbers)) {
                p_current.second = it->second;
                cicleNumbers.push_back(it->second);
                it = corresponds.find(p_current.second);
            }
            else
                break;
    }

    for (auto i = 0; i < centerStart; ++i)
        if (auto it = corresponds.find(mother.permutation[i]); it != corresponds.end())
            sonPermutation[i] = it->second;
        else
            sonPermutation[i] = mother.permutation[i];

    for (unsigned i = centerEnd; i < sonPermutation.size(); ++i)
        if (auto it = corresponds.find(mother.permutation[i]); it != corresponds.end())
            sonPermutation[i] = it->second;
        else
            sonPermutation[i] = mother.permutation[i];


    son.permutation = sonPermutation;
    son.calculateCost(input);

    return son;
}

std::vector<QAPRepresentation> QAPRepresentation::randomPoblation(int poblationSize, const InputData& input)
{
    std::vector<QAPRepresentation> toReturn(poblationSize);
    std::vector<int> toPermute(input.size());

    for (int i = 0; i < input.size(); ++i)
        toPermute[i] = i;

    auto engine = std::default_random_engine{};
    engine.seed(seed);

    std::set<QAPRepresentation> noDuplicates;
    while ((int) noDuplicates.size() < poblationSize) {
        std::shuffle(std::begin(toPermute), std::end(toPermute), engine);
        QAPRepresentation qap;
        qap.permutation = toPermute;
        qap.calculateCost(input);
        noDuplicates.insert(qap);
    }
    toReturn.assign(std::begin(noDuplicates), std::end(noDuplicates));





    return toReturn;
}

void QAPRepresentation::randomShuffle(int seed) {
    auto engine = std::default_random_engine{};
    engine.seed(seed);
    std::shuffle(std::begin(permutation), std::end(permutation), engine);
}

QAPRepresentation QAPRepresentation::twoOpt(int r, int s, const InputData& input)
{
    QAPRepresentation neighbor(*this);

    // 1. Cambiamos las posiciones
    std::swap(neighbor.permutation[r], neighbor.permutation[s]);

    // 2. Calculamos el costo factorizado
    auto& p = permutation;
    for (int k = 0; k < input.size(); ++k) {
        if (k != r && k != s) // Diapositiva 20 - Seminario 2
            neighbor.costo += input.getStream(r,k) * (input.getDistance(p[s], p[k]) - input.getDistance(p[r], p[k])) +
                    input.getStream(s,k) * (input.getDistance(p[r], p[k]) - input.getDistance(p[s], p[k])) +
                    input.getStream(k,r) * (input.getDistance(p[k], p[s]) - input.getDistance(p[k], p[r])) +
                    input.getStream(k,s) * (input.getDistance(p[k], p[r]) - input.getDistance(p[k], p[s]));
    }


    return neighbor;
}

bool QAPRepresentation::operator<(const QAPRepresentation &qapr) const
{
    return costo < qapr.costo;
}

bool QAPRepresentation::operator==(const QAPRepresentation &qapr) const
{
    return permutation == qapr.permutation && costo == qapr.costo;
}


std::ostream &operator<<(std::ostream &os, const QAPRepresentation &rep)
{
    // OJO: En la solución empezamos por el 1 aunque al procesar empiezo por el 0
    os << "Solución: ";
    for (const auto& location: rep.permutation)
        os << location + 1<< ' ';
    os << "\nCosto: " << rep.costo << '\n';

    return os;
}
