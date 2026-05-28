//
// Created by bobjo on 9/24/2024.
//

#include "Sky_Monster.h"

Sky_Monster::Sky_Monster() {
    number_of_wings = rand() % (MAX_NUMBER_WINGS - 1) + 2;
    if (number_of_wings % 2 !=0) {
        number_of_wings++;
    }
}

Sky_Monster::Sky_Monster(int now) {
    if(now > MAX_NUMBER_WINGS || now < 2) {
        number_of_wings = MAX_NUMBER_WINGS;
    }else if (now % 2 != 0) {
        number_of_wings = now + 1;
    }else {
        number_of_wings = now;
    }

}

int Sky_Monster::get_number_of_wings(){
    return number_of_wings;
}

void Sky_Monster::set_number_of_wings(int now) {
    if(now < 2 || now > MAX_NUMBER_WINGS || now & 2 != 0) {
        number_of_wings = MAX_NUMBER_WINGS;
    } else {
        number_of_wings = now;
    }
}

void Sky_Monster::growth_spurt() {
    if (number_of_wings + 2 > MAX_NUMBER_WINGS) {
        number_of_wings = MAX_NUMBER_WINGS;
    } else {
        number_of_wings += 2;
    }
}
