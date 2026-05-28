#ifndef UNDER_BED_MONSTER_H
#define UNDER_BED_MONSTER_H

#include "Darkness_Monster.h"

class Under_Bed_Monster : public Darkness_Monster {
public:
    /**
     * Requires: nothing
     * Modifies: number_of_eyes
     * Effects: calls parent default constructor
     */
    Under_Bed_Monster();

    /**
     * Requires: nothing
     * Modifies: number_of_eyes
     * Effects: calls parent non-default constructor
     */
    explicit Under_Bed_Monster(int noe);

    /**
     * Requires: nothing
     * Modifies: nothing
     * Effects: randomly returns either "*Grabs you*" or "*[number_of_eyes] eyes watching you*".
     */
    // implemented this method in Under_Bed_Monster.cpp
    std::string scare() override;
};

#endif
