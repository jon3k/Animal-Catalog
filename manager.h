#include <iostream>
#include <vector>
using namespace std;
#ifndef MANAGER_H
#define MANAGER_H

class Manager : public Animal {
    vector<Animal> animal_number;

public:
    Manager();
    void add_animal();
    void load();
    void display_catalog();
    void delete_animal();
    void save();
    void edit_animal();
    void run();
};

#endif
