#include <iostream>

#include "engine/src/board.cpp"
#include "engine/src/figure.cpp"
#include "engine/dependencies/olmallet81/GALGO-2.0/Galgo.hpp"

using namespace std;

template <typename T>
class MyObjective
{
public:
    static std::vector<T> Objective(const std::vector<T>& x)
    {
        T obj = -(pow(1-x[0],2)+100*pow(x[1]-x[0]*x[0],2));
        return {obj};
    }

};


int main() {
    galgo::Parameter<double> par1({0.0,1.0});
    galgo::Parameter<double> par2({0.0,13.0});

    galgo::GeneticAlgorithm<double> ga(MyObjective<double>::Objective,100,10000,true,par1,par2);
    ga.run();
}
