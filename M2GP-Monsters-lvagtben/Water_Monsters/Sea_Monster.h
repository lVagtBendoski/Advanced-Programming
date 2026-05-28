#ifndef SEA_MONSTER_H
#define SEA_MONSTER_H

#include "Water_Monster.h"

class Sea_Monster : public Water_Monster {
public:
    /**
     * Requires: nothing
     * Modifies: number_people_eaten
     * Effects: calls parent default constructor
     */
    Sea_Monster();

    /**
     * Requires: nothing
     * Modifies: number_people_eaten
     * Effects: calls parent non-default constructor
     */
    explicit Sea_Monster(int npe);

    /**
     * Requires: nothing
     * Modifies: nothing
     * Effects: returns either "[number_people_eaten] people eaten and counting"
     *          or "you’re gonna need a bigger boat"
     */
    virtual std::string scare() override;
};

#endif
