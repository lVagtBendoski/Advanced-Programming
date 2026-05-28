#include "Water_Monster.h"

Water_Monster::Water_Monster() {
    number_people_eaten = rand() % (MAX_PEOPLE_EATEN + 1);
}

Water_Monster::Water_Monster(int npe) {
    set_number_people_eaten(npe);
}

int Water_Monster::get_number_people_eaten() const {
    return number_people_eaten;
}

void Water_Monster::set_number_people_eaten(int npe) {
    if (npe < 0 || npe > MAX_PEOPLE_EATEN) {
        npe = MAX_PEOPLE_EATEN;
    }
    number_people_eaten = npe;
}

void Water_Monster::eat_person() {
    if (number_people_eaten < MAX_PEOPLE_EATEN) {
        ++number_people_eaten;
    }
}