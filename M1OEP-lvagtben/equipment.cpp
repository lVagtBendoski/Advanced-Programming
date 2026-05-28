//
// Created by bobjo on 9/11/2024.
//
//
// Created by bobjo on 9/11/2024.
//

#include <string>
#include <vector>
#include "equipment.h"
using namespace std;

equipment::equipment() {
    damage = defaultDamageAndDefense;
    defense = defaultDamageAndDefense;
    level = defense + damage;
    description = defaultDescriptionAndName;
    name = defaultDescriptionAndName;
    typeOfEquipment = MISC;
}
equipment::equipment(double dam, double def, string des, string n, string equipmentType) {
    damage = dam;
    defense = def;
    level = defense + damage;
    description = des;
    name = n;
    if(equipmentType == "WEAPON") {
        typeOfEquipment = WEAPON;
    }else if(equipmentType == "ARMOUR") {
        typeOfEquipment = ARMOUR;
    }else if(equipmentType == "SHIELD") {
        typeOfEquipment = SHIELD;
    }else{
        typeOfEquipment = MISC;
    }
}
equipment::equipment(const equipment &e1)  {
    damage = e1.damage;
    defense = e1.defense;
    level = e1.level;
    description = e1.description;
    name = e1.name;
    typeOfEquipment = e1.typeOfEquipment;
}

void equipment::setDamage(double d) {
    damage = d;
    level = defense + damage;
}
void equipment::setDefense(double d) {
    defense = d;
    level = defense + damage;
}
void equipment::setDescription(string s) {
    description = s;
}
void equipment::setName(string s) {
    name = s;
}
double equipment::getDamage() const {
    return damage;
}
double equipment::getDefense() const {
    return defense;
}
string equipment::getDescription() const {
    return description;
}
string equipment::getName() const {
    return name;
}
string equipment::getTypeOfEquipment() const {
    if(typeOfEquipment == MISC) {
        return "MISC";
    }
    if(typeOfEquipment == WEAPON) {
        return "WEAPON";
    }
    if(typeOfEquipment == SHIELD) {
        return "SHIELD";
    }
    if(typeOfEquipment == ARMOUR) {
        return "ARMOUR";
    }
    return "MISC";
}
void equipment::swapWith(equipment &e) {
    equipment temp = e;
    e.damage = damage;
    e.defense = defense;
    e.level = level;
    e.description = description;
    e.name = name;
    e.typeOfEquipment = typeOfEquipment;
    damage = temp.damage;
    defense = temp.defense;
    level = temp.level;
    description = temp.description;
    name = temp.name;
    typeOfEquipment = temp.typeOfEquipment;

}
void equipment::reset() {
    damage = defaultDamageAndDefense;
    defense = defaultDamageAndDefense;
    level = defense + damage;
    description = defaultDescriptionAndName;
    name = defaultDescriptionAndName;
    typeOfEquipment = MISC;
}

 bool operator==(const equipment& lhs, const equipment& rhs){
    return lhs.level == rhs.level;
}

bool operator<(const equipment& lhs, const equipment& rhs){
    return lhs.level < rhs.level;
}

bool operator>(const equipment& lhs, const equipment& rhs){
    return lhs.level > rhs.level;
}


