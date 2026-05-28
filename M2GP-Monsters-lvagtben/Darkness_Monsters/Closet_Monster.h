#ifndef CLOSET_MONSTER_H
#define CLOSET_MONSTER_H

#include "Darkness_Monster.h"

class Closet_Monster : public Darkness_Monster {
public:
    /**
     * Requires: nothing
     * Modifies: number_of_eyes and door_is_open
     * Effects: calls parent default constructor and sets door_is_open to false
     */
    Closet_Monster();

    /**
     * Requires: nothing
     * Modifies: number_of_eyes and door_is_open
     * Effects: calls parent non-default constructor and sets door_is_open to false
     */
    explicit Closet_Monster(int noe);

    /**
     * Requires: nothing
     * Modifies: door_is_open
     * Effects: if door is closed, set it to open and return true; otherwise return false
     */
    bool open_door();

    /**
     * Requires: nothing
     * Modifies: nothing
     * Effects: returns door_is_open
     */
    bool is_open() const;

    /**
     * Requires: nothing
     * Modifies: door_is_open
     * Effects: if the door is closed, return "*Knocks on door*"
     *          if the door is open, set the door to be closed and return "*Slams door*"
     */
    // TODO: Implement this method in Closet_Monster.cpp
    std::string scare() override;

private:
    bool door_is_open;
};


#endif
