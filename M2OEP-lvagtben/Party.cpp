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

void Party::setPartyMembersHealth(string name, double health) {
    int index = findIndexFromName(name);
    party[index].setHealth(health);
}
void Party::setPartyMembersHealth(int index, double health) {
    party[index].setHealth(health);
}
void Party::setPartyMembersEquipped(int index, string equipmentType, equipment equip) {
    if(equipmentType == "RIGHTHAND") {
        party[index].equipRightHand(equip);
    }else if(equipmentType == "LEFTHAND") {
        party[index].equipLeftHand(equip);
    }else if(equipmentType == "ARMOR") {
        party[index].equipArmor(equip);
    }
}
void Party::setPartyMembersStatus(string target, string statusEffect) {
    int index = findIndexFromName(target);
    if(statusEffect == "STUNNED") {
        party[index].setStatus("STUNNED");
    }else if(statusEffect == "BLOCKING") {
        party[index].setStatus("BLOCKING");
    }else if(statusEffect == "CHILLING") {
        party[index].setStatus("CHILLING");
    }

}
void Party::setPartyMembersStatus(int target, string statusEffect) {
    if(statusEffect == "STUNNED") {
        party[target].setStatus("STUNNED");
    }else if(statusEffect == "BLOCKING") {
        party[target].setStatus("BLOCKING");
    }else if(statusEffect == "CHILLING") {
        party[target].setStatus("CHILLING");
    }

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
void Party::setPartyMembersLivingStatus(string name, bool living){
    int index = findIndexFromName(name);
    party[index].setLiving(living);
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
void Party::removeMember(character c){
    //TODO:fix this so it doesn't throw a million compiler errors, but is also better than the solution in inventory.cpp.

    // I technically used this as source code, but it didn't work so idk: https://www.geeksforgeeks.org/how-to-remove-an-element-from-vector-in-cpp/#
    // auto index = find(party.begin(), party.end(), c);
    //  if(index != party.end()) {
    //      party.erase(index);
    //      cout << c.getName() << "has left the party." << endl;
    //  }
    //!!!THIS ALSO DOESN'T WORK!!!
    // for (auto it = party.begin(); it != party.end();++it) {
    //     if(*it == c) {
    //         party.erase(it);
    //     }
    // }
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

