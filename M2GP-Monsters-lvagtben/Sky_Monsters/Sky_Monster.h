//
// Created by bobjo on 9/24/2024.
//

#ifndef SKY_MONSTER_H
#define SKY_MONSTER_H
#include <string>


class Sky_Monster {
public:
    Sky_Monster();

    Sky_Monster(int now);

    virtual ~Sky_Monster() = default;

    int get_number_of_wings();

    void set_number_of_wings(int number_of_wings);

    void growth_spurt();

    virtual std::string scare() = 0;

    static const int MAX_NUMBER_WINGS = 100;
protected:
    int number_of_wings;
};



#endif //SKY_MONSTER_H
