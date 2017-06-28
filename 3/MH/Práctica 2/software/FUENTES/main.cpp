#include <chrono>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include "greedy.h"
#include "hillclimbing.h"
#include "simulatedannealing.h"
#include "bmb.h"
#include "grasp.h"
#include "ils.h"

/** @brief Contiene los casos aplicados al QAP
 */
struct QAP {
    /** @brief Vector con todos los archivos de los distintos casos **/
    const static std::vector<std::string> files;
};

const std::vector<std::string> QAP::files { "chr20b.dat", "chr22a.dat", "els19.dat", "esc32b.dat",
        "kra30b.dat", "lipa90b.dat", "nug25.dat", "sko56.dat", "sko64.dat", "sko72.dat",
        "sko100a.dat", "sko100b.dat", "sko100c.dat", "sko100d.dat", "sko100e.dat",
         "tai30b.dat", "tai50b.dat", "tai60a.dat", "tai256c.dat", "tho150.dat" };

template<class Solver>
void apply(const InputData& input, std::ostream& os = std::cout) {
    Solver solver(input);
    os << "Archivo evaluado: " << input.getFileName() << '\n';
    os << "Método de evaluación: " << solver.getSolverName() << '\n';
    auto beforeTime = std::chrono::high_resolution_clock::now();
    solver.apply();
    auto afterTime  = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time = afterTime - beforeTime;
    os << "Tiempo: " << time.count() << '\n';
    os << solver.getSolution() << "\n\n";
}

template<class Solver>
void applyToAll(std::ostream& os = std::cout) {
    for (const auto& fileName : QAP::files) {
        try {
            InputData input;
            input.read(fileName);
            apply<Solver>(input, os);
        }
        catch (const std::invalid_argument& exp) {
            std::cout << "No se ha encontrado el archivo " << exp.what() << " en el directorio de trabajo.\n";
        }
    }

}

void displayHelp() {
    std::cout << "Uso: <algoritmo> <archivo=ALL> <seed = 18>  \n"
              << "Para ALL todos los .dat han de encontrarse en el directorio de trabajo.\n"
              << "Los códigos de los algoritmos son: \n"
              << "Greedy: greedy\n"
              << "Búsqueda local: bl\n"
              << "Enfriamiento simulado: es\n"
              << "Búsqueda multiarranque básica: bmb\n"
              << "GRASP: grasp\n"
              << "No se distingue entre mayúsculas y minúsculas\n";
}

int forAllSelectAlgorithm(const std::string& algoritmo) {
    if (algoritmo == "greedy")
        applyToAll<Greedy>();
    else if (algoritmo == "es")
        applyToAll<SimulatedAnnealing>();
    else if (algoritmo == "bl")
        applyToAll<HillClimbing<>>();
    else if (algoritmo == "bmb")
        applyToAll<BMB>();
    else if (algoritmo == "grasp")
        applyToAll<GRASP>();
    else if (algoritmo == "ils")
        applyToAll<ILS<HillClimbing<>>>();
    else if (algoritmo == "ils-es")
        applyToAll<ILS<SimulatedAnnealing>>();
    else {
        displayHelp();
        return -2;
    }
    return 0;
}

 long QAPRepresentation::seed = 18;
int main(int argc, char* argv[])
{

    if (argc < 2 || argc > 5) {
       displayHelp();
       return -1;
    }


    std::string statMode;
    if (argc == 5)
        statMode = argv[4];
    if (argc > 3)
        QAPRepresentation::seed = std::atoi(argv[3]);

    if (argc == 2) {
        std::string algoritmo = argv[1];
        std::transform(algoritmo.begin(), algoritmo.end(), algoritmo.begin(), ::tolower);
        auto exito = forAllSelectAlgorithm(algoritmo);
        if (exito == -2)
            return -2;
    }
    else if (argc == 5 && statMode == "on") {

                std::string algoritmo = argv[1];
                std::transform(algoritmo.begin(), algoritmo.end(), algoritmo.begin(), ::tolower);
                std::string archivo = argv[2];
                if (archivo == "ALL") {
                    if (algoritmo == "greedy")
                        applyToAll<Greedy>();
                    else if (algoritmo == "es")
                        applyToAll<SimulatedAnnealing>();
                    else if (algoritmo == "bl")
                        applyToAll<HillClimbing<>>();
                    else if (algoritmo == "bmb")
                        applyToAll<BMB>();
                    else if (algoritmo == "grasp")
                        applyToAll<GRASP>();
                    else if (algoritmo == "ils")
                        applyToAll<ILS<HillClimbing<>>>();
                    else if (algoritmo == "ils-es")
                        applyToAll<ILS<SimulatedAnnealing>>();
                    else {
                        displayHelp();
                        return -2;
                    }
                    return 0;
                }
                else {
                    try {
                        InputData input;
                        input.read(archivo);
                        if (algoritmo == "greedy")
                            apply<Greedy>(input);
                        else if (algoritmo == "es")
                            apply<SimulatedAnnealing>(input);
                        else if (algoritmo == "bl")
                            apply<HillClimbing<>>(input);
                        else if (algoritmo == "bmb")
                            apply<BMB>(input);
                        else if (algoritmo == "grasp")
                            apply<GRASP>(input);
                        else if (algoritmo == "ils")
                            apply<ILS<HillClimbing<>>>(input);
                        else if (algoritmo == "ils-es")
                            apply<ILS<SimulatedAnnealing>>(input);
                    }
                    catch (const std::invalid_argument& exp) {
                        std::cout << "No se ha encontrado el archivo " << exp.what() << " en el directorio de trabajo.\n";
                    }
                }
            }

    else  {

        std::string algoritmo = argv[1];
        std::transform(algoritmo.begin(), algoritmo.end(), algoritmo.begin(), ::tolower);
        std::string archivo = argv[2];
        if (archivo == "ALL") {
            return forAllSelectAlgorithm(algoritmo);
        }
        try {
            InputData input;
            input.read(archivo);
            if (algoritmo == "greedy")
                apply<Greedy>(input);
            else if (algoritmo == "es")
                apply<SimulatedAnnealing>(input);
            else if (algoritmo == "bmb")
                apply<BMB>(input);
            else if (algoritmo == "es")
                apply<SimulatedAnnealing>(input);
            else if (algoritmo == "bl")
                apply<HillClimbing<>>(input);
            else if (algoritmo == "bmb")
                apply<BMB>(input);
            else if (algoritmo == "grasp")
                apply<GRASP>(input);
            else if (algoritmo == "ils")
                apply<ILS<HillClimbing<>>>(input);
            else if (algoritmo == "ils-es")
                apply<ILS<SimulatedAnnealing>>(input);


        }
        catch (const std::invalid_argument& exp) {
            std::cout << "No se ha encontrado el archivo " << exp.what() << " en el directorio de trabajo.\n";
        }
    }

}
