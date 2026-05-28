#ifndef CLOUD_MONSTER_H
#define CLOUD_MONSTER_H

#include "Sky_Monster.h"

class Cloud_Monster : public Sky_Monster {
public:
    /**
     * Requires: nothing
     * Modifies: number_of_wings and raining
     * Effects: calls parent default constructor and sets raining to true
     */
    Cloud_Monster();

    /**
     * Requires: nothing
     * Modifies: number_of_wings and raining
     * Effects: calls parent non-default constructor and sets raining to true
     */
    explicit Cloud_Monster(int now);

    /**
     * Requires: nothing
     * Modifies: raining
     * Effects: if raining, set raining to false and return true; otherwise return false
     */
    bool stop_the_rain();

    /**
     * Requires: nothing
     * Modifies: nothing
     * Effects: returns raining
     */
    bool is_raining() const;

    /**
     * Requires: nothing
     * Modifies: raining
     * Effects: if raining, returns "torrential downpour"
     *          otherwise, sets raining to true and returns "into the storm"
     */
    std::string scare() override;

private:
    bool raining;
};

#endif
