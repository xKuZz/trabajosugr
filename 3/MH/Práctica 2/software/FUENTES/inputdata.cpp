#include "inputdata.h"

void InputData::read(const std::string &fileName)
{
    // 1. Abrimos un flujo para leer el archivo y leeemos el tamaño del problema
    this->fileName = fileName;
    std::ifstream file(fileName);
    if (!file.is_open())
        throw std::invalid_argument(fileName);
    file >> n;

    // 2. Reajustamos los tamaños de los vectores de vectores para manejar el tamaño del problema.
    stream.resize(n);
    for (auto& row : stream)
        row.resize(n);

    distance.resize(n);
    for (auto& row : distance)
        row.resize(n);

    // 3. Procedemos a la lectura de las matrices
    for (auto& row : stream)
        for (auto& data : row)
            file >> data;

    for (auto& row : distance)
        for (auto& data : row)
            file >> data;

}

InputData::Type InputData::getStream(int origin, int destination) const
{
    return stream[origin][destination];
}

InputData::Type InputData::getDistance(int origin, int destination) const
{
    return distance[origin][destination];
}

int InputData::size() const
{
    return n;
}

std::string InputData::getFileName() const
{
    return fileName;
}

std::ostream& operator<<(std::ostream& os, const InputData& input) {
    os << "Archivo leído: " << input.getFileName() << '\n';

    int tam = input.size();
    os << "Tamaño del problema: " << tam << '\n';

    os << "\n\nMatriz de flujo:\n\n";
    for (auto row : input.stream) {
        for (auto data : row)
            os << data << " ";
        os << '\n';
    }

    os << "\n\nMatriz de distancias:\n\n";
    for (auto row : input.distance) {
        for (auto data : row)
            os << data << " ";
        os << '\n';
    }

    return os;
}
