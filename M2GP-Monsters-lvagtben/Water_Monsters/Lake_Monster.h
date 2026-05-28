#ifndef LAKE_MONSTER_H
#define LAKE_MONSTER_H

#include "Water_Monster.h"

class Lake_Monster : public Water_Monster {
public:
    /**
     * Requires: nothing
     * Modifies: number_people_eaten and frozen
     * Effects: calls parent default constructor and sets frozen to false
     */
    Lake_Monster();

    /**
     * Requires: nothing
     * Modifies: number_people_eaten and frozen
     * Effects: calls parent non-default constructor and sets frozen to false
     */
    explicit Lake_Monster(int npe);

    /**
     * Requires: nothing
     * Modifies: frozen
     * Effects: if frozen is false, sets frozen to true and returns true.
     *          if frozen is true, returns false.
     */
    bool freeze_lake();

    /**
     * Requires: Nothing
     * Modifies: frozen
     * Effects: if the lake is frozen, unfreeze the lake and return "breaks through and melts the ice"
     *          if the lake is not frozen, return "swims towards you"
     */
    std::string scare() override;

protected:
    bool frozen;
};

#endif
