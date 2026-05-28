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
    vector<character> getParty();
    void addMember(character c);
    vector<string> getMembers();
    bool everyoneIsLiving() const;
    void unBlock();
    void unStun();
    int findIndexOfFirstLivingPerson();
    int findIndexFromName(string name);
    void removeMember(character c);
    void clearParty();
    friend ostream& operator <<(ostream& outs, const Party& subjects);

};



#endif //PARTY_H
