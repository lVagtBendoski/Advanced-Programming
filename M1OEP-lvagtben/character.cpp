//
// Created by bobjo on 9/11/2024.
//
#include <string>
#include <vector>
#include "inventory.h"
#include "character.h"
#include "equipment.h"

using namespace std;



character::character() {
    health = startingHealth;
    unarmedDamage = startingUnarmedDamage;
    level = startingLevel;
    name = defaultName;
    isLiving = true;
    inv;
    rightHand;
    leftHand;
    armor;
    maxInventorySize = defaultMaxInventorySize;
    status = CHILLING;
}
character::character(string name, double health, double unarmedDamage, int level, int maxInventorySize, inventory inv, equipment rightHand, equipment leftHand, equipment armor) {
    this->name = name;
    this->health = health;
    this->unarmedDamage = unarmedDamage;
    this->level = level;
    this->maxInventorySize = maxInventorySize;
    isLiving = true;
    this->inv = new inventory(inv);
    this->rightHand = new equipment(rightHand);
    this->leftHand = new equipment(leftHand);
    this->armor = new equipment(armor);
    status = CHILLING;
}
double character::getHealth() const{
    return health;
}
double character::getUnarmedDamage() const {
    return unarmedDamage;
}
int character::getLevel() const {
    return level;
}
string character::getName() const {
    return name;
}
bool character::getLiving() const {
    return isLiving;
}
inventory character::getCharacterInventory() const {
    return *inv;
}
equipment character::getEquippedArmour() const {
    return *armor;
}
equipment character::getEquippedRightHand() const {
    return *rightHand;
}
equipment character::getEquippeLeftHand() const {
    return *leftHand;
}
string equipment::getTypeOfEquipment() const {
    if(typeOfEquipment == WEAPON) {
        return "WEAPON";
    }else if(typeOfEquipment == SHIELD) {
        return "SHIELD";
    }else if(typeOfEquipment == ARMOUR) {
        return "ARMOUR";
    }else {
        return "MISC";
    }

}

void character::setHealth(double health) {
    this->health = health;
}
void character::setUnarmedDamage(double unarmedDamage) {
    this->unarmedDamage = unarmedDamage;
}
void character::setLevel(int level) {
    this->level = level;
}
void character::setLiving(bool living) {
    this->isLiving = living;
}
void character::setName(string name) {
    this->name = name;
}
void character::setStatus(string status) {
    if(status == "BLOCKING") {
        this->status = BLOCKING;
    }else if(status == "STUNNED") {
        this->status = STUNNED;
    }else if(status == "CHILLING") {
        this->status = CHILLING;
    }
}

bool character::equipArmor(equipment e) {
    if(e.getTypeOfEquipment() == "ARMOUR") {
        armor->swapWith(e);
        return true;
    }else {
        return false;
    }
}
bool character::equipRightHand(equipment e) {
    if(e.getTypeOfEquipment() == "WEAPON") {
        armor->swapWith(e);
        return true;
    }else {
        return false;
    }
}
bool character::equipLeftHand(equipment e) {
    if(e.getTypeOfEquipment() == "WEAPON" || e.getTypeOfEquipment() == "SHIELD") {
        armor->swapWith(e);
        return true;
    }else {
        return false;
    }
}
void character::levelUp() {
    level++;
    health = startingHealth * level;
    unarmedDamage += 2;
}
double character::calculateDamage() {
    double damage = unarmedDamage;
    if(rightHand->getTypeOfEquipment() == "WEAPON") {
        damage += rightHand->getDamage();
        if(leftHand->getTypeOfEquipment() == "WEAPON") {
            damage += leftHand->getDamage();
        }
    }
    return damage;
}

bool character::dealDamageTo(character &enemy) {
    if(!enemy.getLiving()) {
        return false;
    }
    double damage = calculateDamage();
    damage -= enemy.armor->getDefense();
    if(enemy.status == BLOCKING) {
        damage -= enemy.leftHand->getDefense();
    }
    if (damage > 0) {
        enemy.health = enemy.health - damage;
    }else {
        damage = 0;
    }
    cout << "Damage dealt: " << damage << ' ' << enemy.name << " current health:" << enemy.health << endl;
    if(enemy.health <= 0) {
        enemy.setLiving(false);
        cout <<"!!!!!!" << enemy.name << " is dead!!!!" << endl;
    }
    return true;
}
void character::displayDetailedStats() {
    cout << "Name: " << name << endl;
    cout << "Health: " << health << endl;
    cout << "Level: " << level << endl;
    cout << "Damage: " << calculateDamage() << endl;
    cout << "Equipped in right hand: " << "name, " << rightHand->getName() << "damage, " << rightHand->getDamage()
    << "defense, " << rightHand->getDefense() << "type, " <<rightHand->getTypeOfEquipment() << endl;
    cout << "Equipped in left hand: " << leftHand->getName() << "damage, " << leftHand->getDamage()
    << "defense, " << leftHand->getDefense() << "type, " <<leftHand->getTypeOfEquipment() << endl;
    cout << "Equipped armor: " << armor->getName() << "defense, " << armor->getDefense() << endl;
}

ostream& operator <<(ostream& outs, const character& subject) {
    outs << "Name: " << subject.name;
    if(subject.isLiving) {
        outs << ", Is alive";
    }else
        outs << ", Is dead";
    outs <<", Level: " << subject.level;
    outs << ", Health: " << subject.health;
    return outs;
}
bool operator==(const character &lhs, const character &rhs) {
    return lhs.getName() == rhs.getName();
}







