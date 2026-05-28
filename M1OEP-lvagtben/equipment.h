//
// Created by bobjo on 9/11/2024.
//

#ifndef EQUIPMENT_H
#define EQUIPMENT_H
#include <string>
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
    enum equipType {WEAPON, ARMOUR, SHIELD, MISC};
    equipType typeOfEquipment;
public:
    equipment();
    
    equipment(double dam, double def, string des, string n, string typeOfEquipment);

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

    void swapWith(equipment &e);

    void reset();

    friend bool operator == (const equipment& lhs, const equipment& rhs);

    friend bool operator < (const equipment& lhs, const equipment& rhs);

    friend bool operator > (const equipment& lhs, const equipment& rhs);


};
#endif //EQUIPMENT_H
