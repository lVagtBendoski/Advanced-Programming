//
// Created by bobjo on 9/12/2024.
//

#ifndef PARTY_H
#define PARTY_H
#include <vector>
#include <bits/stdc++.h>
#include "character.h"



class Party {
private:
    vector<character> party;
    int maxPartySize;
    const int defaultMaxPartySize = 5;
public:
    Party();
    Party(int maxPartySize);
    void setMaxPartySize(int maxPartySize);
    void setPartyMembersHealth(string name, double health);
    void setPartyMembersHealth(int index, double health);
    void setPartyMembersLivingStatus(string name, bool living);
    void setPartyMembersEquipped(int index, string equipmentType, equipment equip);
    void setPartyMembersStatus(string target,string statusEffect);
    void setPartyMembersStatus(int target,string statusEffect);
    vector<character>& getParty();
    character getCharacterAt(int index);
    void addMember(character &c);
    vector<string> getMembers();
    int findIndexOfFirstLivingPerson();
    bool everyoneIsLiving() const;
    void unBlock();
    void unStun();
    int findIndexFromName(string name);
    void removeMember(character c);
    void levelUpParty();
    friend ostream& operator <<(ostream& outs, const Party& subjects);

};



#endif //PARTY_H
