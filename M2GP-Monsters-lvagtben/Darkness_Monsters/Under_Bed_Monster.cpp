#include "Under_Bed_Monster.h"
using namespace std;

Under_Bed_Monster::Under_Bed_Monster() : Darkness_Monster() {
}

Under_Bed_Monster::Under_Bed_Monster(int noe) : Darkness_Monster(noe) {
}

// implemented the scare method here
string Under_Bed_Monster::scare() {
    if(number_of_eyes < MAX_NUMBER_EYES/2) {
        return "You feel a cold breath wafting over your unexposed leg";
    }else {
        return "You feel a freezing wind slash through your room. Along with this comes a great urge to run";
    }
}