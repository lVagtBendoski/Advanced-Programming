#include "Lake_Monster.h"
using namespace std;

Lake_Monster::Lake_Monster() : Water_Monster(), frozen(false) {
}

Lake_Monster::Lake_Monster(int npe) : Water_Monster(npe), frozen(false) {
}

bool Lake_Monster::freeze_lake() {
    if (frozen) {
        return false;
    } else {
        frozen = true;
        return true;
    }
}

string Lake_Monster::scare() {
    if (frozen) {
        frozen = false;
        return "*Breaks through and melts the ice*";
    } else {
        return "*Swims towards you*";
    }
}

