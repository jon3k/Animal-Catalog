#include <iostream>
#include <fstream>
#include <conio.h>
#include <vector>
#include <string>
#include <windows.h>
#include <cmath>
#include "animals.h"
#include "manager.h"
using namespace std;

string Animal::g_species() { return species; }
string Animal::g_animal_kingdom() { return animal_kingdom; }
double Animal::g_age() { return age; }
double Animal::g_height() { return height; }
double Animal::g_weight() { return weight; }
void Animal::s_species(string new_species) { species = new_species; }
void Animal::s_animal_kingdom(string new_animal_kingdom) { animal_kingdom = new_animal_kingdom; }
void Animal::s_age(double new_age) { age = new_age; }
void Animal::s_height(double new_height) { height = new_height; }
void Animal::s_weight(float new_weight) { weight = new_weight; }

Manager::Manager()
{
}

Animal::Animal()
{
}

bool check_number(string str)
{
    int c = 0;
    for (int i = 0; i < str.length(); i++) {
        if (isdigit(str[i]) == false) {
            if (str[i] == '.' && c == 0) {
                c++;
            }
            else {
                return false;
            }
        }
        return true;
    }
}

double converter(string s)
{
    int dot = s.find('.');
    if (dot == -1) {
        dot = s.find(',');
        if (dot == -1) {
            dot = s.length();
        }
    }
    double result = 0.0;
    for (int i = 0; i < dot; i++) {
        result += (((double)s[i] - 48) * pow(10, dot - i - 1));
    }
    int c = -1;
    for (int k = dot + 1; k < s.length(); k++, c--) {
        result += (((double)s[k] - 48) * pow(10, c));
    }

    return result;
}

void Manager::add_animal()
{
    int d = 0;
    fstream data;
    data.open("save.txt", ios::out | ios::app);

    Animal animal;
    string input_helper = "";
    cout << "Enter the animal species: ";
    while (input_helper == "") {
        cin >> input_helper;
        if (input_helper == "") {
            cout << " "
                 << "Invalid value, try again" << endl;
        }
        else {
            animal.s_species(input_helper);
        }
    }
    data << animal.g_species() << endl;

    while (d != 1) {
        cout << "Enter the animal kingdom (reptile/insect/amphibian/bird/fish/mammal): ";
        cin >> input_helper;
        animal.s_animal_kingdom(input_helper);
        if (animal.g_animal_kingdom() != "reptile" && animal.g_animal_kingdom() != "insect" && animal.g_animal_kingdom() != "amphibian" && animal.g_animal_kingdom() != "bird" && animal.g_animal_kingdom() != "fish" && animal.g_animal_kingdom() != "mammal") {
            cout << " "
                 << "Invalid value, try again" << endl;
        }
        else
            d = 1;
    }
    data << animal.g_animal_kingdom() << endl;

    input_helper = "";
    cout << "Enter the age [in years]: ";
    while (input_helper == "") {
        cin >> input_helper;
        if (!check_number(input_helper) || converter(input_helper) <= 0.0) {
            cout << " "
                 << "Invalid value, try again" << endl;
            input_helper = "";
        }
        else {
            animal.s_age(converter(input_helper));
        }
    }
    data << animal.g_age() << endl;

    input_helper = "";
    cout << "Enter the height [in cm] : ";
    while (input_helper == "") {
        cin >> input_helper;
        if (!check_number(input_helper) || converter(input_helper) <= 0.0) {
            cout << " "
                 << "Invalid value, try again" << endl;
            input_helper = "";
        }
        else {
            animal.s_height(converter(input_helper));
        }
    }
    data << animal.g_height() << endl;

    input_helper = "";
    cout << "Enter the weight [in kg] : ";
    while (input_helper == "") {
        cin >> input_helper;
        if (!check_number(input_helper) || converter(input_helper) <= 0.0) {
            cout << " "
                 << "Invalid value, try again" << endl;
            input_helper = "";
        }
        else {
            animal.s_weight(converter(input_helper));
        }
    }
    data << animal.g_weight() << endl;

    cout << "Added successfully!" << endl;
    cout << endl;
    data.close();
    animal_number.push_back(animal);
}

void Manager::display_catalog()
{
    if (animal_number.size() > 0) {
        for (int i = 0; i < animal_number.size(); i++) {
            cout << "Position " << i << "." << endl;
            cout << "Species: " << animal_number[i].g_species() << endl;
            cout << "Animal kingdom: " << animal_number[i].g_animal_kingdom() << endl;
            cout << "Age: " << animal_number[i].g_age() << endl;
            cout << "Height: " << animal_number[i].g_height() << "cm" << endl;
            cout << "Weight: " << animal_number[i].g_weight() << "kg" << endl;
            cout << "--------------" << endl;
        }
    }
    else {
        cout << "Database is empty" << endl;
    }
}

void Manager::load()
{
    {
        fstream data;
        data.open("save.txt");

        if (data.is_open()) {
            data.close();
        }
        else {
            data.open("save.txt", std::ios::out);
            data.close();
        }
    }

    string input_helper = "0";
    ifstream data;
    data.open("save.txt");
    while (!data.eof()) {
        Animal x;
        data >> input_helper;
        x.s_species(input_helper);
        data >> input_helper;
        x.s_animal_kingdom(input_helper);
        data >> input_helper;
        x.s_age(converter(input_helper));
        data >> input_helper;
        x.s_height(converter(input_helper));
        data >> input_helper;
        x.s_weight(converter(input_helper));
        animal_number.push_back(x);
    }
    data.close();
}

void Manager::delete_animal()
{

    if (animal_number.size() > 0) {

        display_catalog();
        int w = 0;
        cout << "Which position do you want to delete?: ";
        cin >> w;
        animal_number.erase(animal_number.begin() + w);
        cout << "Deleted successfully!" << endl;
    }
    else {
        cout << "Database is empty" << endl;
    }
}

void Manager::save()
{

    ofstream data;
    data.open("save.txt", ios::out);
    for (int i = 0; i < animal_number.size(); i++) {
        data << animal_number[i].g_species() << endl;
        data << animal_number[i].g_animal_kingdom() << endl;
        data << animal_number[i].g_age() << endl;
        data << animal_number[i].g_height() << endl;
        data << animal_number[i].g_weight() << endl;
    }
    data.close();
}

void Manager::edit_animal()
{
    if (animal_number.size() > 0) {

        string input_helper;
        display_catalog();
        int w, k = 0;
        cout << "Which position do you want to edit?: ";
        cin >> w;
        cout << "Enter the new species: ";
        cin >> input_helper;
        animal_number[w].s_species(input_helper);

        while (k != 1) {
            cout << "Enter the new animal kingdom (reptile/insect/amphibian/bird/fish/mammal): ";
            cin >> input_helper;
            animal_number[w].s_animal_kingdom(input_helper);
            if (animal_number[w].g_animal_kingdom() != "reptile" && animal_number[w].g_animal_kingdom() != "insect" && animal_number[w].g_animal_kingdom() != "amphibian" && animal_number[w].g_animal_kingdom() != "bird" && animal_number[w].g_animal_kingdom() != "fish" && animal_number[w].g_animal_kingdom() != "mammal") {
                cout << " "
                     << "Invalid value, try again" << endl;
            }
            else
                k = 1;
        }

        input_helper = "";
        cout << "Enter the new age [in years]: ";
        while (input_helper == "") {
            cin >> input_helper;
            if (!check_number(input_helper) || converter(input_helper) <= 0.0) {
                cout << " "
                     << "Invalid value, try again" << endl;
                input_helper = "";
            }
            else {
                animal_number[w].s_age(converter(input_helper));
            }
        }

        input_helper = "";
        cout << "Enter the new height [in cm]: ";
        while (input_helper == "") {
            cin >> input_helper;
            if (!check_number(input_helper) || converter(input_helper) <= 0.0) {
                cout << " "
                     << "Invalid value, try again" << endl;
                input_helper = "";
            }
            else {
                animal_number[w].s_height(converter(input_helper));
            }
        }

        input_helper = "";
        cout << "Enter the new weight [in kg]: ";
        while (input_helper == "") {
            cin >> input_helper;
            if (!check_number(input_helper) || converter(input_helper) <= 0.0) {
                cout << " "
                     << "Invalid value, try again" << endl;
                input_helper = "";
            }
            else {
                animal_number[w].s_weight(converter(input_helper));
            }
        }
    }
    else {
        cout << "Database is empty" << endl;
    }
}

void Manager::run()
{
    load();
    animal_number.pop_back();
    char choice = 0;
    while (choice != '5') {
        system("cls");
        cout << "A N I M A L   C A T A L O G" << endl;
        cout << "Option 1: Add an animal to your database" << endl;
        cout << "Option 2: Display catalog" << endl;
        cout << "Option 3: Delete the animal from the catalog" << endl;
        cout << "Option 4: Edit the animal in the catalog" << endl;
        cout << "Option 5: Save & exit" << endl;
        cin >> choice;
        switch (choice) {

        case '1':
            system("cls");
            add_animal();
            _getch();
            break;
        case '2':
            system("cls");
            display_catalog();
            _getch();
            break;
        case '3':
            system("cls");
            delete_animal();
            _getch();
            break;
        case '4':
            system("cls");
            edit_animal();
            _getch();
            break;
        }
    }
    save();
}
