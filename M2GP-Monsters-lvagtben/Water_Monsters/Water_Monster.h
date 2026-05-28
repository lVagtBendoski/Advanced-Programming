#ifndef WATER_MONSTER_H
#define WATER_MONSTER_H

#include <string>

class Water_Monster {
public:
    /**
     * Requires: nothing
     * Modifies: number_people_eaten
     * Effects: sets number_people_eaten to random int in range 0-100
     */
    Water_Monster();

    /**
     * Requires: nothing
     * Modifies: nothing
     * Effects: does nothing
     */
    virtual ~Water_Monster() = default;

    /**
     * Requires: nothing
     * Modifies: number_people_eaten
     * Effects: calls set_number_people_eaten with npe
     */
    explicit Water_Monster(int npe);

    /**
     * Requires: nothing
     * Modifies: nothing
     * Effects: returns number_people_eaten
     */
    virtual int get_number_people_eaten() const;

    /**
     * Requires: nothing
     * Modifies: number_people_eaten
     * Effects: sets number_people_eaten to npe if npe is in range
     *          0-100. Otherwise sets number_people_eaten to 100.
     */
    void set_number_people_eaten(int npe);

    /**
     * Requires: nothing
     * Modifies: number_people_eaten
     * Effects: increments number_people_eaten by one if not already at 100
     */
    virtual void eat_person();

    // pure virtual method to return a scary string
    virtual std::string scare() = 0;

    static const int MAX_PEOPLE_EATEN = 100;
protected:
    int number_people_eaten;
};

#endif
