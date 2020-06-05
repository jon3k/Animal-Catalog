#include <iostream>
#include <vector>
using namespace std;
#ifndef ANIMALS_H
#define ANIMALS_H

class Animal {

protected:
    string species;
    string animal_kingdom;
    double age;
    double height;
    float weight;

public:
    Animal();
    string g_species();
    string g_animal_kingdom();
    double g_age();
    double g_height();
    double g_weight();
    void s_species(string);
    void s_animal_kingdom(string);
    void s_age(double);
    void s_height(double);
    void s_weight(float);
};

#endif
