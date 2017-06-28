#ifndef GRASP_H
#define GRASP_H

#include "qaprepresentation.h"
#include "hillclimbing.h"
#include <tuple>
class GRASP
{
public:
    GRASP(const InputData& input) : input(input) {
        generator.seed(QAPRepresentation::seed);
    }

    void initializeGRASP(int poblationSize = 25, float threshold = 0.3) {
      poblation.resize(poblationSize);

      for (int i = 0; i < poblationSize; ++i) {
        // std::cout << "KEEP TRACK SOL " << i << '\n';
        auto& solution = poblation[i];
        solution.permutation.resize(input.size(), -1);
        streamPotential.resize(input.size(), 0);
        distancePotential.resize(input.size(), 0);
        // Calculamos potenciales de flujo y distancia y buscamos el mayor y el menor
        // 1. Calculamos el potencial de flujo
        for (int i = 0; i < input.size(); ++i)
            for (int j = 0; j < input.size(); ++j)
                streamPotential[i] += input.getStream(i,j);

        // 2. Calculamos el potencial de distancia
        for (int i = 0; i < input.size(); ++i)
            for (int j = 0; j < input.size(); ++j)
                distancePotential[i] += input.getDistance(i,j);

        // Buscamos el más pequeño y el más chico
        auto max_stream = *std::max_element(std::begin(streamPotential), std::end(streamPotential));
        auto min_stream = *std::min_element(std::begin(streamPotential), std::end(streamPotential));
        auto max_distance = *std::max_element(std::begin(distancePotential), std::end(distancePotential));
        auto min_distance = *std::min_element(std::begin(distancePotential), std::end(distancePotential));

        // Añadimos un par para indicar la posición correspondiente
        std::vector<std::pair<int, int>> streams(streamPotential.size());
        std::vector<std::pair<int, int>> distances(distancePotential.size());

        for (unsigned i = 0; i < streams.size(); ++i)
            streams[i] = {streamPotential[i], i};

        for (unsigned i = 0; i < distances.size(); ++i)
            distances[i] = {distancePotential[i], i};


        std::vector<std::pair<int,int>> toChoose_stream(streamPotential.size());
        std::vector<std::pair<int,int>> toChoose_distance(distancePotential.size());

        // ETAPA 1
        // Ponemos la lista de candidatos para la etapa 1
        auto it = std::copy_if(std::begin(streams), std::end(streams), std::begin(toChoose_stream),
                     [&](const auto& stream) {
            return stream.first >= max_stream - threshold * (max_stream - min_stream);
        });
        toChoose_stream.resize(std::distance(std::begin(toChoose_stream),it));

        it = std::copy_if(std::begin(distances), std::end(distances), std::begin(toChoose_distance),
                     [&](const auto& dist) {
            return dist.first <= min_distance + threshold * (max_distance - min_distance);
        });
        toChoose_distance.resize(std::distance(std::begin(toChoose_distance),it));

        // Sacamos dos elementos aleatorios de cada lista restringida
        std::uniform_int_distribution<int> chooseStep1Stream(0, toChoose_stream.size()-1);
        std::uniform_int_distribution<int> chooseStep1Distance(0, toChoose_distance.size()-1);

        int selectedDistance = toChoose_distance[chooseStep1Distance(generator)].second;
        int selectedStream = toChoose_stream[chooseStep1Stream(generator)].second;

        int d1 = selectedDistance, s1 = selectedStream;
        solution.assign(selectedStream, selectedDistance);

     auto eraseSelected = [&]() {
        streams.erase(std::find_if(std::begin(streams), std::end(streams), [&](const auto& stream) {
            return stream.second == selectedStream;
        }));

        toChoose_stream.erase(std::find_if(std::begin(toChoose_stream), std::end(toChoose_stream), [&](const auto& stream) {
            return stream.second == selectedStream;
        }));

        distances.erase(std::find_if(std::begin(distances), std::end(distances), [&](const auto& dist) {
            return dist.second == selectedDistance;
        }));

        toChoose_distance.erase(std::find_if(std::begin(toChoose_distance), std::end(toChoose_distance), [&](const auto& dist) {
            return dist.second == selectedDistance;
        }));
    };

        eraseSelected();
        chooseStep1Stream = std::uniform_int_distribution<int>(0, toChoose_stream.size()-1);
        chooseStep1Distance = std::uniform_int_distribution<int>(0, toChoose_distance.size()-1);

        selectedDistance = toChoose_distance[chooseStep1Distance(generator)].second;
        selectedStream = toChoose_stream[chooseStep1Stream(generator)].second;

        solution.assign(selectedStream, selectedDistance);
        eraseSelected();

        // ETAPA 2
        // Creamos todas las posibles asignaciones
        std::vector<std::tuple<int,int,long>> candidates;
        for (int i = 0; i < input.size(); ++i)
            for (int j = 0; j < input.size(); ++j)
                if (i != s1 && i != selectedStream &&
                    j != d1 && j != selectedDistance)
                candidates.push_back(std::make_tuple(i,j,0));

        for (auto reps = 0; reps < input.size() -2; ++reps) {
            solution.calculateCost(input);
            // Actualizamos los costes de las posibilidades
            for (auto& element: candidates)
                std::get<2>(element) = solution.getCostGRASP(input, std::get<0>(element), std::get<1>(element));

            // Creamos la lista restringida de candidatos
            auto order_cost = [&] (const auto& t1, const auto& t2) {
                return std::get<2>(t1) < std::get<2>(t2);
            };

            std::vector<std::tuple<int,int,long>> restrictedCandidates(candidates.size());


            auto max_cost = std::get<2>(*std::max_element(std::begin(candidates), std::end(candidates),
                                         order_cost));
            auto min_cost = std::get<2>(*std::min_element(std::begin(candidates), std::end(candidates),
                                         order_cost));

            auto it = std::copy_if(std::begin(candidates), std::end(candidates), std::begin(restrictedCandidates),
                         [&](const auto& candidate) {
                return std::get<2>(candidate) <= min_cost + threshold * (max_cost- min_cost);
            });


            // Asignamos uno escogido aleatoriamente
            restrictedCandidates.resize(std::distance(std::begin(restrictedCandidates),it));
            std::uniform_int_distribution<int> toChooseDist(0, restrictedCandidates.size()-1);
            auto selected = restrictedCandidates[toChooseDist(generator)];

            selectedStream = std::get<0>(selected);
            selectedDistance = std::get<1>(selected);

            solution.assign(selectedStream, selectedDistance);

            // Borramos de la lista del candidatos
            candidates.erase(std::remove_if(std::begin(candidates), std::end(candidates),
                                          [&](const auto& tuple) {
                return std::get<0>(tuple) == selectedStream || std::get<1>(tuple) == selectedDistance;

            }),std::end(candidates));
            solution.calculateCost(input);
        }
        solution.calculateCost(input);
    }


    }

    void apply() {
        initializeGRASP();
        for (auto& individual: poblation) {
            HillClimbing<> hc(individual,input);
            hc.apply();
            individual = hc.getSolution();
        }
    }

    std::string getSolverName() const {
        return "GRASP";
    }
    QAPRepresentation getSolution() const {
        return *std::min_element(std::begin(poblation), std::end(poblation));
    }
private:
    const InputData& input;
    std::default_random_engine generator;
    std::vector<QAPRepresentation> poblation;
    std::vector<InputData::Type> streamPotential;
    std::vector<InputData::Type> distancePotential;
};

#endif // GRASP_H
