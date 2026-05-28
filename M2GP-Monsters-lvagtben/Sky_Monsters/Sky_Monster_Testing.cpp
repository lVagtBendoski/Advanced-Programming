#include "Cloud_Monster.h"
#include "Comet_Monster.h"
#include <ctime>
#include <iostream>
using namespace std;

bool test_Sky_Monster();
bool test_Cloud_Monster();
bool test_Comet_Monster();

int main() {
    srand(time(NULL));
    if (test_Sky_Monster()) {
        cout << "Passed all Sky Monster test cases" << endl;
    }
    if (test_Cloud_Monster()) {
        cout << "Passed all Cloud Monster test cases" << endl;
    }
    if (test_Comet_Monster()) {
        cout << "Passed all Comet Monster test cases" << endl;
    }
    return 0;
}

bool test_Sky_Monster() {
    bool passed = true;
    // Sky Monster is abstract so we can only access it through the child classes
    Cloud_Monster cm;
    if (cm.get_number_of_wings() < 2 || cm.get_number_of_wings() > Sky_Monster::MAX_NUMBER_WINGS || cm.get_number_of_wings() % 2 != 0) {
        passed = false;
        cout << "FAILED default constructor test case" << endl;
    }
    Cloud_Monster cm2(1);
    if (cm2.get_number_of_wings() != Sky_Monster::MAX_NUMBER_WINGS) {
        passed = false;
        cout << "FAILED 1 test case" << endl;
    }
    cm2.set_number_of_wings(50);
    if (cm2.get_number_of_wings() != 50) {
        passed = false;
        cout << "FAILED 50 test case" << endl;
    }
    cm2.set_number_of_wings(101);
    if (cm2.get_number_of_wings() != Sky_Monster::MAX_NUMBER_WINGS) {
        passed = false;
        cout << "FAILED 101 test case" << endl;
    }
    cm2.set_number_of_wings(50);
    cm2.set_number_of_wings(-7);
    if (cm2.get_number_of_wings() != Sky_Monster::MAX_NUMBER_WINGS) {
        passed = false;
        cout << "FAILED negative test case" << endl;
    }
    cm2.set_number_of_wings(13);
    if (cm2.get_number_of_wings() != Sky_Monster::MAX_NUMBER_WINGS) {
        passed = false;
        cout << "FAILED odd number  within range test case" << endl;
    }
    cm2.set_number_of_wings(48);
    cm2.growth_spurt();
    if (cm2.get_number_of_wings() != 50) {
        passed = false;
        cout << "FAILED growth spurt test case" << endl;
    }
    cm2.set_number_of_wings(Sky_Monster::MAX_NUMBER_WINGS);
    cm2.growth_spurt();
    if (cm2.get_number_of_wings() != Sky_Monster::MAX_NUMBER_WINGS) {
        passed = false;
        cout << "FAILED max growth spurt test case" << endl;
    }
    return passed;
}

bool test_Cloud_Monster() {
    bool passed = true;
    Cloud_Monster cm(4);
    if (!cm.is_raining()) {
        passed = false;
        cout << "FAILED non-default constructor test case" << endl;
    }
    if (cm.scare() != "*Torrential downpour*") {
        passed = false;
        cout << "FAILED torrential downpour test case" << endl;
    }
    cm.stop_the_rain();
    if (cm.is_raining()) {
        passed = false;
        cout << "FAILED stop the rain test case" << endl;
    }
    if (cm.scare() != "\"Into the storm!\"") {
        passed = false;
        cout << "FAILED into the storm test case" << endl;
    }
    Cloud_Monster cm2;
    if (!cm2.is_raining()) {
        passed = false;
        cout << "FAILED default constructor test case" << endl;
    }
    return passed;
}

bool test_Comet_Monster() {
    bool passed = true;
    Comet_Monster cm(78);
    if (cm.get_number_of_wings() != 78) {
        passed = false;
        cout << "FAILED non-default constructor case" << endl;
    }
    Comet_Monster cm2;
    if (cm2.get_number_of_wings() < 2 || cm2.get_number_of_wings() > Sky_Monster::MAX_NUMBER_WINGS) {
        passed = false;
        cout << "FAILED default constructor case" << endl;
    }
    Comet_Monster cm3(2);
    int scareCountWings = 2;
    string message;
    for (int i = 0; i < Sky_Monster::MAX_NUMBER_WINGS / 2; ++i) {
        message = cm3.scare();
        if (message == "*Barreling down at you*") {
            ++++scareCountWings;
            cm3.growth_spurt();
        } else {
            // message is *[number_of_wings] wings encompassing you*. Check that the number_of_wings is correct
            if (stoi(message.substr(1, message.find_first_of(' '))) != scareCountWings) {
                passed = false;
                // Note: no cout statement because this is in a loop and we don't want to crowd the console output
            }
        }
    }
    return passed;
}