//
// Created by bobjo on 9/11/2024.
//
#include <string>
#include <vector>
#include "inventory.h"
#include "character.h"
#include "equipment.h"

using namespace std;


//https://www.geeksforgeeks.org/default-constructors-in-cpp/#
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
bool character::getTurn() const {
    return turn;
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
string character::getStatusString() const {
    if(status == CHILLING) {
        return "CHILLING";
    } else if(status == BLOCKING) {
        return "BLOCKING";
    }else if(status == STUNNED) {
        return "STUNNED";
    }else {
        return "UNDEFINED";
    }
}
void character::setHealth(double newHealth) {
    health = newHealth;
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
void character::setTurn(bool turn) {
    this->turn = turn;
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
    if(e.getTypeOfEquipment() == "ARMOR") {
        armor->swapWith(e);
        return true;
    }else {
        return false;
    }
}
bool character::equipRightHand(equipment e) {
    if(e.getTypeOfEquipment() == "WEAPON") {
        rightHand->swapWith(e);
        return true;
    }else {
        return false;
    }
}
bool character::equipLeftHand(equipment e) {
    if(e.getTypeOfEquipment() == "WEAPON" || e.getTypeOfEquipment() == "SHIELD") {
        leftHand->swapWith(e);
        return true;
    }else {
        return false;
    }
}
void character::levelUp() {
    level++;
    health = startingHealth * level;
    unarmedDamage += 2;
    cout << name << " leveled up!" << endl;
}
double character::calculateDamage() {
    double damage = unarmedDamage;
    if(rightHand->getTypeOfEquipment() == "WEAPON") {
        if(rightHand->getAttributestring() == "FLAMING") {
            damage += unarmedDamage;
        }
        damage += rightHand->getDamage();
        if(leftHand->getTypeOfEquipment() == "WEAPON") {
            if(leftHand->getAttributestring() == "FLAMING") {
                damage += unarmedDamage;
            }
            damage += leftHand->getDamage();
        }
    }
    return damage;
}

double character::dealDamageTo(character& enemy) {
    if(!enemy.getLiving()) {
        return false;
    }
    double damage = calculateDamage();
    damage -= enemy.getEquippedArmour().getDefense();
    if(enemy.status == BLOCKING) {
        damage -= enemy.getEquippeLeftHand().getDefense();
    }
    if (damage > 0) {
        enemy.health = enemy.health - damage;
    }else {
        damage = 0;
    }
    cout << name << " attacked " << enemy.name << ' ' << "Damage dealt: " << damage << ' ' << enemy.name << " current health:"
    << enemy.health << endl;
    if(enemy.health <= 0) {
        enemy.setLiving(false);
        cout <<"!!!!!!" << enemy.name << " is dead!!!!" << endl;
    }else if(rightHand->getAttributestring() == "STUNNING" || leftHand->getAttributestring() == "STUNNING") {
        enemy.stun();
    }
    return enemy.health;
}
//TODO: delete this function. it is dumb, but I keep for now
double character::takeDamageFrom(character &enemy){
    double damage = enemy.calculateDamage();
    damage -= armor->getDamage();
    if(status == BLOCKING) {
        damage -= leftHand->getDefense();
    }
    if(damage > 0) {
        this->health -= damage;
    }else {
        damage = 0;
    }
    cout << "damage dealt: " << damage << name << "'s current health" << health << endl;
    if(health <= 0) {
        isLiving = false;
        cout <<"!!!!!!" << name << " is dead!!!!" << endl;
    }
    return health;

}
void character::stun() {
    status = STUNNED;
}

void character::displayDetailedStats() {
    cout << "Name: " << name << endl;
    cout << "Health: " << health << endl;
    cout << "Level: " << level << endl;
    cout << "unarmedDamage: " << unarmedDamage << endl;
    cout << "Damage: " << calculateDamage() << endl;
}
//https://www.geeksforgeeks.org/operator-overloading-cpp/
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







