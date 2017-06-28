#ifndef BMB_H
#define BMB_H
#include "qaprepresentation.h"
#include "hillclimbing.h"

class BMB
{
public:

    BMB(const InputData& input) : input(input) {}


    void apply() {
        poblation = QAPRepresentation::randomPoblation(25, input);
        for (auto& individual: poblation) {
            HillClimbing<> hc(individual,input);
            hc.apply();
            individual = hc.getSolution();
        }
    }

    QAPRepresentation getSolution() {
        return *std::min_element(std::begin(poblation), std::end(poblation));
    }

    std::string getSolverName() {
        return "Búsqueda Multiarranque básica";
    }
private:
    std::vector<QAPRepresentation> poblation;
    const InputData& input;
};

#endif // BMB_H
