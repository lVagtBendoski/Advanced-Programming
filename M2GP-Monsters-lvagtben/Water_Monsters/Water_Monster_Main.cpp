#include "Lake_Monster.h"
#include "Sea_Monster.h"
#include <ctime>
#include <iostream>
#include <memory>
#include <vector>
using namespace std;

int get_int_input(string prompt, string invalid, int low, int high);
void player_mode();

int main() {
    cout << "Get ready to face a water monster!" << endl;
    player_mode();
    return 0;
}

int get_int_input(string prompt, string invalid, int low, int high) {
    cout << prompt;
    int choice = 0;
    string junk;
    while (!(cin >> choice) || choice < low || choice > high) {
        cout << invalid;
        cin.clear();
        getline(cin, junk);
    }
    return choice;
}

void player_mode() {
    vector<unique_ptr<Water_Monster>> monsters;
    srand(time(NULL));

    const int NUM_MONSTERS = 10;

    for (int i = 0; i < NUM_MONSTERS; ++i) {
        if (rand() % 2) {
            monsters.push_back(make_unique<Lake_Monster>());
        } else {
            monsters.push_back(make_unique<Sea_Monster>());
        }
    }

    bool user_dead = false;
    int index, choice;
    while (!user_dead && monsters.size() > 0) {
        index = get_int_input("Enter a number from 0 to " + to_string(monsters.size() - 1) + ": ",
                                  "Invalid input. Try again: ",
                                  0,
                                  monsters.size() - 1);
        cout << "The monster approaches: " << monsters[index]->scare() << endl;
        choice = get_int_input("Choose a number between 1 and 3: ",
                                   "Invalid input. Pick a number from 1 to 3: ",
                                   1,
                                   3);
        if (rand() % 3 + 1 == choice) {
            cout << "You were lucky and beat the monster!" << endl;
            monsters.erase(monsters.begin() + index);
        } else {
            cout << "The monster ate you!" << endl;
            monsters[index]->eat_person();
            user_dead = true;
        }
    }
    if (user_dead) {
        cout << "You beat " << NUM_MONSTERS - monsters.size() << " monster(s)!" << endl;
        cout << "Better luck next time" << endl;
    } else {
        cout << "Wow, you beat all " << NUM_MONSTERS << " monsters! You really beat the odds!" << endl;
    }
}