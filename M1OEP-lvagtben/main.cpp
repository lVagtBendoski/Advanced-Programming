#include <iostream>
#include <vector>
#include "Party.h"
#include "equipment.h"
#include "inventory.h"
#include "character.h"
//
// Created by bobjo on 9/10/2024.
//

using namespace std;
char getInputFromUser();
char getCharFromUser();
void combat(Party &playerParty, Party &enemies);
void playerCombatTurn(Party &playerParty, Party &enemies);
char combatInputGrabber(character &ally);
string getSentenceFromUser();
void enemyCombatTurn(Party &playerParty, Party &enemies);
int main() {
    Party party;
    Party enemies;
    inventory emptyInventory;
    equipment noEquipment;
    character Glimbo("Glimbo", 4, 2, 1, 10, emptyInventory, noEquipment, noEquipment, noEquipment);
    character evilGlimbo("evilGlimbo", 5, 1, 1, 7, emptyInventory, noEquipment, noEquipment, noEquipment);
    party.addMember(Glimbo);
    enemies.addMember(evilGlimbo);
    combat(party, enemies);

    cout << "Welcome to a day in the life of Glimbo. Glimbo is a goblin, you are Glimbo. "
            "One day after coimning home you find you gold missing. As a goblin yourself"
            "you know this to be unnaceptable. Would you like to go into town to investigate?"
            "(y/n)" << endl;
    if (getCharFromUser() == 'y') {
        cout << "As you wander into the town you see a dumb looking guard. Would you like to talk to it?"
                "(y/n)" << endl;
        if (getCharFromUser() == 'y') {
            cout << "You ask him about your missing gold. He say's duuurh I don't know about gold duuuum" << endl;
        }else {
            cout << "Good choice" << endl;
        }

    }else {
        cout << "Glimbo never found his gold, leaving him to die impoverished and sad";
    }
    return 0;
}
char getInputFromUser() {
    char result;
    result = getCharFromUser();
    while(result != 'y' && result != 'n') {
        cout << "enter y or n" << endl;
       result = getCharFromUser();
    }
    return result;
}
char getCharFromUser() {
    // NOTE: a char is not restricted to an alphabet letter
    string candidate;
    bool inputNotValid = true;
    while (inputNotValid) {
        inputNotValid = false;
        getline(cin, candidate);
        if (candidate.length() > 1) {
            inputNotValid = true;
            cout << "Invalid input. Enter a single character:";
        }else if (candidate.empty()) {
            inputNotValid = true;
            cout << "No input. Enter a single character:";
        }
    }
    char c = candidate[0];
    return c;
}
void combat(Party &playerParty, Party &enemies) {
    while(playerParty.everyoneIsLiving() && enemies.everyoneIsLiving()) {
        cout << "Your party consist of ***" <<  playerParty << "***" <<endl;
        cout << "Enemy party consist of ***" <<  enemies << "***" <<endl;
        playerCombatTurn(playerParty, enemies);
        enemyCombatTurn(playerParty, enemies);

    }
}
void playerCombatTurn(Party &playerParty, Party &enemies) {
    playerParty.unBlock();
    for(character &ally : playerParty.getParty()) {
        if(ally.getStatusString() != "STUNNED") {
            char choice =combatInputGrabber(ally);
            while (choice == 'a') {
                ally.displayDetailedStats();
                choice = combatInputGrabber(ally);
            }if (choice == 'b') {
                vector<string> enemyNames = enemies.getMembers();
                cout << "this is a list of your enemies: " << enemies << endl;
                cout << "Who would you like " << ally.getName() << " to attack?" << endl;
                string target = getSentenceFromUser();
                int cnt = count(enemyNames.begin(), enemyNames.end(), target);
                while(cnt < 1) {
                    cout << "Please choose your target from this list:" << endl << enemies << endl;
                }
                int index = enemies.findIndexFromName(target);
                ally.dealDamageTo(enemies.getParty()[index]);
            }else if (choice == 'c') {
                ally.setStatus("BLOCKING");
            }else if (choice == 'd') {
                cout << "after being stabbed in the back by who Glimbo once considered an ally he crumples. "
                        "Not only the pain kept him from getting up but mainly the miserable realization "
                        "that he did not have " << ally.getName() << " as a friend. if this person could "
                        "act so disengenously as Glimbo's friend then he would not ever know a true friend "
                        "as he would never again be able to trust. Glimbo did not wish to live in a world where"
                        "such a terrible thing could be true, so instead he just bled out slowly and coldly." << endl;
                exit(1);
            }
        }
    }
    playerParty.unStun();
}
char combatInputGrabber(character &ally) {
    cout << "Options for " << ally.getName() << ':' << endl;
    cout << "view "<< ally.getName() <<"'s stats in detail (a)" << endl;
    cout << "attack (b)" << endl;
    cout << "block (c)" << endl;
    cout << "attack Glimbo (d)" << endl;
    char choice = getCharFromUser();
    while(!(choice == 'a' || choice == 'b' || choice == 'c' || choice == 'd')) {
        cout << "Enter a or b or c or d or e" << endl;
        choice = getCharFromUser();
    }
    return choice;
}
string getSentenceFromUser() {
    // NOTE: a sentence does NOT need punctuation or syntax validation
    string candidate = " ";
    bool inputNotValid = true;
    while (inputNotValid) {
        inputNotValid = false;
        getline(cin, candidate);
        if(candidate.empty()) {
            cout << "No input. Enter a sentence:";
            inputNotValid = true;
        }
    }
    return candidate;
}
void enemyCombatTurn(Party &playerParty, Party &enemies) {
    enemies.unBlock();
    for( character &foe : enemies.getParty()) {
        if(foe.getStatusString() != "STUNNED") {
            int target = playerParty.findIndexOfFirstLivingPerson();
            if(!(target == -1)) {
                foe.dealDamageTo(playerParty.getParty()[target]);
            }
        }
    }

}


