#include "Lake_Monster.h"
#include "Sea_Monster.h"
#include "Water_Monster.h"
#include <ctime>
#include <iostream>
using namespace std;

bool test_Water_Monster();
bool test_Lake_Monster();
bool test_Sea_Monster();

int main() {
    srand(time(NULL));
    if (test_Water_Monster()) {
        cout << "Passed all Water Monster test cases" << endl;
    }
    if (test_Lake_Monster()) {
        cout << "Passed all Lake Monster test cases" << endl;
    }
    if (test_Sea_Monster()) {
        cout << "Passed all Sea Monster test cases" << endl;
    }
    return 0;
}

bool test_Water_Monster() {
    bool passed = true;
    Lake_Monster lm(0);
    if (lm.get_number_people_eaten() != 0) {
        passed = false;
        cout << "FAILED 0 test case" << endl;
    }
    lm.set_number_people_eaten(50);
    if (lm.get_number_people_eaten() != 50) {
        passed = false;
        cout << "FAILED 50 test case" << endl;
    }
    lm.eat_person();
    if (lm.get_number_people_eaten() != 51) {
        passed = false;
        cout << "FAILED eat person test case" << endl;
    }
    lm.set_number_people_eaten(Water_Monster::MAX_PEOPLE_EATEN);
    if (lm.get_number_people_eaten() != Water_Monster::MAX_PEOPLE_EATEN) {
        passed = false;
        cout << "FAILED Water_Monster::MAX_PEOPLE_EATEN test case" << endl;
    }
    lm.eat_person();
    if (lm.get_number_people_eaten() != Water_Monster::MAX_PEOPLE_EATEN) {
        passed = false;
        cout << "FAILED cannot eat person test case" << endl;
    }
    Lake_Monster lm2;
    if (lm2.get_number_people_eaten() < 0 || lm2.get_number_people_eaten() > Water_Monster::MAX_PEOPLE_EATEN) {
        passed = false;
        cout << "FAILED default constructor test case" << endl;
    }
    lm2.set_number_people_eaten(-4);
    if (lm2.get_number_people_eaten() != Water_Monster::MAX_PEOPLE_EATEN) {
        passed = false;
        cout << "FAILED negative test case" << endl;
    }
    lm.set_number_people_eaten(222);
    if (lm2.get_number_people_eaten() != Water_Monster::MAX_PEOPLE_EATEN) {
        passed = false;
        cout << "FAILED > Water_Monster::MAX_PEOPLE_EATEN test case" << endl;
    }
    return passed;
}

bool test_Lake_Monster() {
    bool passed = true;
    Lake_Monster lm;
    if (lm.scare() != "*Swims towards you*") {
        passed = false;
        cout << "FAILED default constructor scare test case" << endl;
    }
    if (!lm.freeze_lake()) {
        passed = false;
        cout << "FAILED freeze lake test case" << endl;
    }
    if (lm.freeze_lake()) {
        passed = false;
        cout << "FAILED frozen lake test case" << endl;
    }
    if (lm.scare() != "*Breaks through and melts the ice*") {
        passed = false;
        cout << "FAILED frozen scare test case" << endl;
    }
    if (!lm.freeze_lake()) {
        passed = false;
        cout << "FAILED freeze lake after scare test case" << endl;
    }
    return passed;
}

bool test_Sea_Monster() {
    bool passed = true;
    int count = 0;
    Sea_Monster sm(0);
    if (sm.get_number_people_eaten() != 0) {
        passed = false;
        cout << "FAILED constructor test case" << endl;
    }
    int scareCountBoat = 0;
    string message;
    for (int i = 0; i < Water_Monster::MAX_PEOPLE_EATEN; ++i) {
        message = sm.scare();
        if (message == "\"You're gonna need a bigger boat\"") {
            ++scareCountBoat;
            sm.eat_person();
        } else {
            // message is [number_people_eaten] people eaten and counting. Check that the number_people_eaten is correct
            if (stoi(message.substr(1, message.find_first_of(' '))) != scareCountBoat) {
                passed = false;
                // Note: no cout statement because this is in a loop and we don't want to crowd the console output
            }
        }
    }
    return passed;
}
