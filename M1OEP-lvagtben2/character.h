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
    //https://www.learncpp.com/cpp-tutorial/lvalue-references/
    inventory *inv;
    equipment *rightHand;
    equipment *leftHand;
    equipment *armor;
    const int startingHealth=5;
    const int startingLevel=1;
    const int startingUnarmedDamage = 1;
    const int defaultMaxInventorySize=10;
    const string defaultName="Default";
    //https://stackoverflow.com/questions/9630744/should-you-declare-enums-inside-or-outside-a-class#:~:text=I%20declare%20enums%20(or%20whatever,to%20use%20it%20in%20lambda.
    enum charStatus {BLOCKING, STUNNED, CHILLING,};
    charStatus status;

public:
    character();
    character(string name, double health, double unarmedDamage, int level, int maxInventorySize, inventory inv, equipment rightHand, equipment leftHand, equipment armor);
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
    void setHealth(double newHealth);
    string getStatusString() const;
    void setUnarmedDamage(double unarmedDamage);
    void setLevel(int level);
    void setLiving(bool living);
    void setStatus(string status);
    bool equipRightHand(equipment e);
    bool equipLeftHand(equipment e);
    bool equipArmor(equipment e);
    void setName(string name);
    double dealDamageTo(character& enemy);
    double takeDamageFrom(character& enemy);
    void stun();
    void levelUp();
    void displayDetailedStats();
    double calculateDamage();
    friend ostream& operator <<(ostream& outs, const character& subject);
    friend bool operator == (const character& subject1, const character& subject2);

};



#endif //CHARACTER_H
