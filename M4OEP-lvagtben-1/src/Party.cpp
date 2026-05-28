//
// Created by bobjo on 9/12/2024.
//

#include "Party.h"
Party::Party() {
    maxPartySize = defaultMaxPartySize;
}
Party::Party(int maxPartySize) {
    this->maxPartySize = maxPartySize;
}
void Party::setMaxPartySize(int maxPartySize) {
    this->maxPartySize = maxPartySize;
}

vector<character>& Party::getParty() {
    return party;

}
character Party::getCharacterAt(int index) {
    return party[index];
}

vector<string> Party::getMembers() {
    vector<string> members;
    for(character thing : party) {
        members.push_back(thing.getName());
    }
    return members;
}

void Party::addMember(character &c) {
    if(party.size() < maxPartySize) {
        party.push_back(character(c));
    }
}
bool Party::everyoneIsLiving() const {
    for(character p : party) {
        if(p.getLiving()) {
            return true;
        }
    }
    return false;
}
int Party::findIndexFromName(string name) {
    int result = -1;
    for(int i = 0; i < party.size(); i++) {
        if(party[i].getName() == name)
            result = i;
    }
    return result;
}
int Party::findIndexOfFirstLivingPerson() {
    for(int i = 0; i < party.size(); i++) {
        if(party[i].getLiving())
            return i;
    }
    return -1;
}

void Party::unBlock() {
    for(character p : party) {
        if(p.getStatusString() == "BLOCKING")
            p.setStatus("CHILLING");
    }
}
void Party::unStun() {
    for(character p : party) {
        if(p.getStatusString() == "STUNNED")
            p.setStatus("CHILLING");
    }
}
void Party::levelUpParty() {
     for(character p : party) {
         p.levelUp();
     }
}
ostream& operator <<(ostream& outs, const Party& subjects) {
    int i = 1;
    //https://www.geeksforgeeks.org/different-ways-to-print-elements-of-vector/#
    for(character p : subjects.party) {
        outs << "Mmember " << i <<": " << p << ' ';
        ++i;
    }
    return outs;
}

