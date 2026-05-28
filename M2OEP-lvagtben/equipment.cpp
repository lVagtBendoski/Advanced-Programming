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
    specialAttributesOfEquipment = NONE;
}
equipment::equipment(double dam, double def, string des, string n, string equipmentType, string atribute) {
    damage = dam;
    defense = def;
    level = defense + damage;
    description = des;
    name = n;
    if(equipmentType == "WEAPON") {
        typeOfEquipment = WEAPON;
    }else if(equipmentType == "ARMOR") {
        typeOfEquipment = ARMOR;
    }else if(equipmentType == "SHIELD") {
        typeOfEquipment = SHIELD;
    }else{
        typeOfEquipment = MISC;
    }
    if(atribute == "FLAMING") {
        specialAttributesOfEquipment = FLAMING;
    }else if(atribute == "STUNNING") {
        specialAttributesOfEquipment = STUNNING;
    }else if(atribute == "DUMB") {
        specialAttributesOfEquipment = DUMB;
    }else {
        specialAttributesOfEquipment = NONE;
    }
}
//https://www.geeksforgeeks.org/copy-constructor-in-cpp/#
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
    if(typeOfEquipment == WEAPON) {
        return "WEAPON";
    }else if(typeOfEquipment == SHIELD) {
        return "SHIELD";
    }else if(typeOfEquipment == ARMOR) {
        return "ARMOR";
    }else {
        return "MISC";
    }
}
string equipment::getAttributestring() const {
    switch(specialAttributesOfEquipment) {
        case NONE:
            return "NONE";
        case STUNNING:
            return "STUNNING";
        case DUMB:
            return "DUMB";
        case FLAMING:
            return "FLAMING";
    }
    return "NONE";
}

void equipment::swapWith(equipment &e) {
    equipment temp = e;
    e.damage = damage;
    e.defense = defense;
    e.level = level;
    e.description = description;
    e.name = name;
    e.typeOfEquipment = typeOfEquipment;
    e.specialAttributesOfEquipment = specialAttributesOfEquipment;
    damage = temp.damage;
    defense = temp.defense;
    level = temp.level;
    description = temp.description;
    name = temp.name;
    typeOfEquipment = temp.typeOfEquipment;
    specialAttributesOfEquipment = temp.specialAttributesOfEquipment;


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
    return lhs.name == rhs.name;
}

bool operator<(const equipment& lhs, const equipment& rhs){
    return lhs.level < rhs.level;
}

bool operator>(const equipment& lhs, const equipment& rhs){
    return lhs.level > rhs.level;
}

ostream& operator <<(ostream& outs, const equipment& subject) {
    outs << "Name: " << subject.name;
    outs << "Damage: " << subject.damage;
    outs << "Defense: " << subject.defense;
    outs << "Level: " << subject.level;
    outs << "Description: " << subject.description;
    outs << "TypeOfEquipment: " << subject.getTypeOfEquipment();
    outs << "Special Attributes: " << subject.getAttributestring();
}


