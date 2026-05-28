#include "Closet_Monster.h"

#include <ostream>
using namespace std;

Closet_Monster::Closet_Monster() : Darkness_Monster(), door_is_open(false) {
}

Closet_Monster::Closet_Monster(int noe) : Darkness_Monster(noe), door_is_open(false) {
}

bool Closet_Monster::open_door() {
    if (door_is_open) {
        return false;
    }
    door_is_open = true;
    return true;
}

bool Closet_Monster::is_open() const {
    return door_is_open;
}

// Implement the scare method here
string Closet_Monster::  scare() {
    if(door_is_open) {
        return "You feel a number of eye's staring at you with great intesity";
    }else {
        return "You might just start drifting to sleep soon";
    }
}
