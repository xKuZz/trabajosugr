#include <chrono>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include "greedy.h"
#include "hillclimbing.h"
#include "generationalgenetic.h"
#include "steadystategenetic.h"

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
              << "Búsqueda local del primer mejor: bl \n"
              << "Genético generacional posición: agg-pos\n"
              << "Genético generacional OX: agg-ox\n"
              << "Genético generacional PMX: agg-pmx\n"
              << "Genético estacionario posición: age-pos\n"
              << "Genético estacionario OX: age-ox\n"
              << "Genético estacionario PMX: age-pmx\n"
              << "Memético AM(10, 1.0): mem-todos\n"
              << "Memético AM(10, 0.1): mem-random\n"
              << "Memético AM(10, 0.1mej): mem-mejor\n"
              << "No se distingue entre mayúsculas y minúsculas\n";
}

int forAllSelectAlgorithm(const std::string& algoritmo) {
    if (algoritmo == "greedy")
        applyToAll<Greedy>();
    else if (algoritmo == "bl")
        applyToAll<HillClimbing<true>>();
    else if (algoritmo == "agg-pos")
        applyToAll<GenerationalGenetic<PositionalCross>>();
    else if (algoritmo == "agg-ox")
        applyToAll<GenerationalGenetic<OXCross>>();
    else if (algoritmo == "agg-pmx")
        applyToAll<GenerationalGenetic<PMXCross>>();
    else if (algoritmo == "age-pos")
        applyToAll<SteadyStateGenetic<PositionalCross>>();
    else if (algoritmo == "age-ox")
        applyToAll<SteadyStateGenetic<OXCross>>();
    else if (algoritmo == "age-pmx")
        applyToAll<SteadyStateGenetic<PMXCross>>();
    else if (algoritmo == "mem-todos")
        applyToAll<GenerationalGenetic<PMXCross, false, 10, 100, Memetic::Best, 400>>();
    else if (algoritmo == "mem-random")
        applyToAll<GenerationalGenetic<PMXCross, false, 10, 10, Memetic::Random, 400>>();
    else if (algoritmo == "mem-mejor")
        applyToAll<GenerationalGenetic<PMXCross, false, 10, 10, Memetic::Best, 400>>();
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
                    else if (algoritmo == "bl")
                        applyToAll<HillClimbing<true>>();
                    else if (algoritmo == "agg-pos")
                        applyToAll<GenerationalGenetic<PositionalCross, true>>();
                    else if (algoritmo == "agg-ox")
                        applyToAll<GenerationalGenetic<OXCross, true>>();
                    else if (algoritmo == "agg-pmx")
                        applyToAll<GenerationalGenetic<PMXCross, true>>();
                    else if (algoritmo == "age-pos")
                        applyToAll<SteadyStateGenetic<PositionalCross, true>>();
                    else if (algoritmo == "age-ox")
                        applyToAll<SteadyStateGenetic<OXCross, true>>();
                    else if (algoritmo == "age-pmx")
                        applyToAll<SteadyStateGenetic<PMXCross, true>>();
                    else if (algoritmo == "mem-todos")
                        applyToAll<GenerationalGenetic<PMXCross, true, 10, 100, Memetic::Best, 400>>();
                    else if (algoritmo == "mem-random")
                        applyToAll<GenerationalGenetic<PMXCross, true, 10, 10, Memetic::Random, 400>>();
                    else if (algoritmo == "mem-mejor")
                        applyToAll<GenerationalGenetic<PMXCross, true, 10, 10, Memetic::Best, 400>>();
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
                        else if (algoritmo == "bl")
                            apply<HillClimbing<true>>(input);
                        else if (algoritmo == "agg-pos")
                            apply<GenerationalGenetic<PositionalCross, true>>(input);
                        else if (algoritmo == "agg-ox")
                            apply<GenerationalGenetic<OXCross, true>>(input);
                        else if (algoritmo == "agg-pmx")
                            apply<GenerationalGenetic<PMXCross, true>>(input);
                        else if (algoritmo == "age-pos")
                            apply<SteadyStateGenetic<PositionalCross, true>>(input);
                        else if (algoritmo == "age-ox")
                            apply<SteadyStateGenetic<OXCross, true>>(input);
                        else if (algoritmo == "age-pmx")
                            apply<SteadyStateGenetic<PMXCross, true>>(input);
                        else if (algoritmo == "mem-todos")
                            apply<GenerationalGenetic<PMXCross, true, 10, 100, Memetic::Best, 400>>(input);
                        else if (algoritmo == "mem-random")
                            apply<GenerationalGenetic<PMXCross, true, 10, 10, Memetic::Random, 400>>(input);
                        else if (algoritmo == "mem-mejor")
                            apply<GenerationalGenetic<PMXCross, true, 10, 10, Memetic::Best, 400>>(input);
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
            else if (algoritmo == "bl")
                apply<HillClimbing<true>>(input);
            else if (algoritmo == "agg-pos")
                apply<GenerationalGenetic<PositionalCross>>(input);
            else if (algoritmo == "agg-ox")
                apply<GenerationalGenetic<OXCross>>(input);
            else if (algoritmo == "agg-pmx")
                apply<GenerationalGenetic<PMXCross>>(input);
            else if (algoritmo == "age-pos")
                apply<SteadyStateGenetic<PositionalCross>>(input);
            else if (algoritmo == "age-ox")
                apply<SteadyStateGenetic<OXCross>>(input);
            else if (algoritmo == "age-pmx")
                apply<SteadyStateGenetic<PMXCross>>(input);
            else if (algoritmo == "mem-todos")
                apply<GenerationalGenetic<PMXCross, false, 10, 100, Memetic::Best, 400>>(input);
            else if (algoritmo == "mem-random")
                apply<GenerationalGenetic<PMXCross, false, 10, 10, Memetic::Random, 400>>(input);
            else if (algoritmo == "mem-mejor")
                apply<GenerationalGenetic<PMXCross, false, 10, 10, Memetic::Best, 400>>(input);
        }
        catch (const std::invalid_argument& exp) {
            std::cout << "No se ha encontrado el archivo " << exp.what() << " en el directorio de trabajo.\n";
        }
    }

}
