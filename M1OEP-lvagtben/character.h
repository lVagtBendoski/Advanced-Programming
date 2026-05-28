//
// Created by bobjo on 9/11/2024.
//

#ifndef CHARACTER_H
#define CHARACTER_H
#include <string>
#include <iostream>
#include "inventory.h"
#include "equipment.h"
using namespace std;



class character {
private:
    double health;
    double unarmedDamage;
    int level;
    int maxInventorySize;
    string name;
    bool isLiving;
    inventory *inv;
    equipment *rightHand;
    equipment *leftHand;
    equipment *armor;
    const int startingHealth=5;
    const int startingLevel=1;
    const int startingUnarmedDamage = 1;
    const int defaultMaxInventorySize=10;
    const string defaultName="Default";
    enum charStatus {BLOCKING, STUNNED, CHILLING,};
    charStatus status;

public:
    character();
    character(string name, double health, double unarmedDamage, int level, int maxInventorySize, inventory inv, equipment rightHand, equipment leftHand, equipment armor);
    character(string name, int level);
    double getHealth() const;
    double getUnarmedDamage() const;
    int getLevel() const;
    bool getLiving() const;
    inventory getCharacterInventory() const;
    equipment getEquippedRightHand() const;
    equipment getEquippeLeftHand() const;
    equipment getEquippedArmour() const;
    charStatus getStatus() const;
    string getName() const;
    void setHealth(double health);
    string getStatusString() const;
    void setUnarmedDamage(double unarmedDamage);
    void setLevel(int level);
    void setLiving(bool living);
    void setStatus(string status);
    bool equipRightHand(equipment e);
    bool equipLeftHand(equipment e);
    bool equipArmor(equipment e);
    void setName(string name);
    bool dealDamageTo(character &enemy);
    void levelUp();
    void displayDetailedStats();
    double calculateDamage();
    friend ostream& operator <<(ostream& outs, const character& subject);

};



#endif //CHARACTER_H
