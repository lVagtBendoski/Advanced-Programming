#include "Sea_Monster.h"
using namespace std;

Sea_Monster::Sea_Monster() : Water_Monster() {
}

Sea_Monster::Sea_Monster(int npe) : Water_Monster(npe) {
}

string Sea_Monster::scare() {
    if (rand() % 2) {
        if (number_people_eaten == 1) {
            return "\"1 person eaten and counting\"";
        }
        return "\"" + to_string(number_people_eaten) + " people eaten and counting\"";
    }
    return "\"You're gonna need a bigger boat\"";
}