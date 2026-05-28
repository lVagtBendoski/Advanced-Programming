//
// Created by bobjo on 9/11/2024.
//

#ifndef EQUIPMENT_H
#define EQUIPMENT_H
#include <string>
#include <iostream>
using namespace std;

class equipment {
private:
    double damage;
    double defense;
    double level;
    string description;
    string name;
    const double defaultDamageAndDefense = 0;
    const string defaultDescriptionAndName;
    //https://stackoverflow.com/questions/9630744/should-you-declare-enums-inside-or-outside-a-class#:~:text=I%20declare%20enums%20(or%20whatever,to%20use%20it%20in%20lambda.
    enum equipType {WEAPON, ARMOR, SHIELD, MISC};
    enum specialAttributes {STUNNING, FLAMING, DUMB, NONE};
    equipType typeOfEquipment;
    specialAttributes specialAttributesOfEquipment;
public:
    equipment();
    equipment(double dam, double def, string des, string n, string typeOfEquipment, string attribute);
    equipment(const equipment& e1);
    void setDamage(double d);
    void setDefense(double d);
    void setDescription(string s);
    void setName(string s);
    double getDamage() const;
    double getDefense() const;
    string getDescription() const;
    string getName() const;
    string getTypeOfEquipment() const;
    string getAttributestring() const;
    void swapWith(equipment &e);
    void reset();
    friend bool operator == (const equipment& lhs, const equipment& rhs);

    friend bool operator < (const equipment& lhs, const equipment& rhs);

    friend bool operator > (const equipment& lhs, const equipment& rhs);

    friend ostream& operator <<(ostream& outs, const equipment& subject);


};
#endif //EQUIPMENT_H
