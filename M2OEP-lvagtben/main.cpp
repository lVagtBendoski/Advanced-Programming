#include <iostream>
#include <vector>
#include  <string>
#include "Party.h"
#include "equipment.h"
#include "inventory.h"
#include "character.h"
//
// Created by bobjo on 9/10/2024.
//

using namespace std;
string getInputFromUser(vector<string> acceptableInputs);
void printStringVector(vector<string> vec);
char getCharFromUser();
void removeStringFromVec(vector<string> &vec, string str);
void combat(Party &playerParty, Party &enemies);
void playerCombatTurn(Party &playerParty, Party &enemies);
void enemyCombatTurn(Party &playerParty, Party &enemies);
char combatInputGrabber(character &ally);
string getSentenceFromUser();
void displayEmptySymbol();
void visitTavern(Party &playerParty);
void begBlacksmith(Party &playerParty);
void checkDonations(Party &playerParty);
void investigateMarket(Party &playerParty);
void choosePathAtTownSquare(Party &playerParty, vector<string> &availablePaths);
int main() {
    Party party;
    inventory emptyInventory;
    equipment noEquipment;
    character Glimbo("Glimbo", 7, 3, 1, 10, emptyInventory,
        noEquipment, noEquipment, noEquipment);
    party.addMember(Glimbo);
    vector<string> acceptableInputs;
    cout << "Welcome to a day in the life of Glimbo. Glimbo is a goblin, you are Glimbo. "
            "One day after coimning home you find you gold missing. Whoever took your precious gold"
            "obviously left in a rush after finding the gold as all the silver goblets and plates"
            "are still stored safely in the cupboard. Would you like to go into town to investigate? (y/n)" << endl;
    acceptableInputs.push_back("y");
    acceptableInputs.push_back("n");
    if (getInputFromUser(acceptableInputs) == "y") {
        cout << "As you wander into the town you see a dumb looking guard. Would you like to talk to it?"
                "(y/n)" << endl;
        if (getInputFromUser(acceptableInputs) == "y") {
            cout << "You ask him about your missing gold. He say's duuurh I don't know about gold duuuum." << endl;
        }else {
            cout << "Good choice." << endl;
        }
        cout << "With that settled, you look around the town square you find yourself in. Assessing your option you realize"
                "that you can (t) go into the tavern to perhaps find more information, (i) investigate the market for more information,"
                "(d) check the town donation bin for something that may be helpful, or (b) beg the blacksmith for equipment"
                "to help on your quest" << endl;
        acceptableInputs.clear();
        acceptableInputs.push_back("t");
        acceptableInputs.push_back("d");
        acceptableInputs.push_back("b");
        acceptableInputs.push_back("i");
        choosePathAtTownSquare(party, acceptableInputs);
    }else {
        cout << "Glimbo never found his gold, leaving him to die impoverished and sad";
    }
    return 0;
}
string getInputFromUser(vector<string> acceptableInputs) {
    string result;
    result = getSentenceFromUser();
    while(count(acceptableInputs.begin(), acceptableInputs.end(), result) < 1 ) {
        cout << "enter one of these list items: ";
        printStringVector(acceptableInputs);
       result = getSentenceFromUser();
    }
    return result;
}
void printStringVector(vector<string> vec) {
    cout <<'[';
    for(string s : vec) {
        cout << " "<< s << " ";
    }
    cout <<']';
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
void displayEmptySymbol() {
    cout << "________________" << endl;
    cout << "|              |" << endl;
    cout << "|              |" << endl;
    cout << "|              |" << endl;
    cout << "|              |" << endl;
    cout << "|______________|" << endl;
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
    for(character &ally : playerParty.getParty()) {
        if(ally.getStatusString() != "STUNNED" && ally.getLiving()) {
            playerParty.setPartyMembersStatus(ally.getName(), "CHILLING");
            char choice =combatInputGrabber(ally);
            while (choice == 'a') {
                ally.displayDetailedStats();
                choice = combatInputGrabber(ally);
            }if (choice == 'b') {
                vector<string> enemyNames = enemies.getMembers();
                cout << "this is a list of your enemies: " << enemies << endl;
                cout << "Who would you like " << ally.getName() << " to attack?" << endl;
                string target = getSentenceFromUser();
                //https://www.geeksforgeeks.org/check-if-vector-contains-given-element-in-cpp/#
                int cnt = count(enemyNames.begin(), enemyNames.end(), target);
                while(cnt < 1) {
                    cout << "Please choose your target from this list:" << enemies << endl;
                    target = getSentenceFromUser();
                    cnt = count(enemyNames.begin(), enemyNames.end(), target);
                }
                int index = enemies.findIndexFromName(target);
                enemies.setPartyMembersHealth(target, ally.dealDamageTo(enemies.getParty()[index]));
                if(enemies.getParty()[index].getHealth() <= 0) {
                    enemies.setPartyMembersLivingStatus(target, false);
                }else if((ally.getEquippedRightHand().getAttributestring() == "STUNNING" ||
                    ally.getEquippeLeftHand().getAttributestring() == "STUNNING") &&
                    enemies.getParty()[index].getHealth() > 0) {
                    enemies.setPartyMembersStatus(target, "STUNNED");
                    }
            }else if (choice == 'c') {
                ally.setStatus("BLOCKING");
            }else if (choice == 'd') {
                cout << "after being stabbed in the back by who Glimbo once considered an ally he crumples. "
                        "Not only the pain kept him from getting up but mainly the miserable realization "
                        "that he did not have " << ally.getName() << " as a friend. if this person could "
                        "act so disengenously as Glimbo's friend then he would not ever know a true friend "
                        "as he would never again be able to trust. Glimbo did not wish to live in a world where"
                        "such a terrible thing could be true, so instead he just bled out slowly and coldly." << endl;
                //https://www.gavilan.edu/csis/languages/stop-end.html#:~:text=C%2B%2B%20uses%20the%20exit()%20function%20to%20terminate%20the%20program%20execution.
                exit(1);
            }
        }
        else {
            cout << ally.getName() << " was stunned and couldn't attack this turn!" << endl;
            playerParty.setPartyMembersStatus(ally.getName(), "CHILLING");
        }
    }

}
char combatInputGrabber(character &ally) {
    cout << "Options for " << ally.getName() << ':' << endl;
    cout << "view "<< ally.getName() <<"'s stats in detail (a)" << endl;
    cout << "attack (b)" << endl;
    cout << "block (c)" << endl;
    cout << "attack Glimbo (d)" << endl;
    char choice = getCharFromUser();
    while(!(choice == 'a' || choice == 'b' || choice == 'c' || choice == 'd')) {
        cout << "Enter a or b or c or d" << endl;
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
void removeStringFromVec(vector<string> &vec, string str) {
    for(auto it = vec.begin(); it != vec.end(); it++) {
        if(*it == str) {
            vec.erase(it);
        }
    }
}
void enemyCombatTurn(Party &playerParty, Party &enemies) {
    for( character &foe : enemies.getParty()) {
        if(foe.getStatusString() != "STUNNED" && foe.getLiving()) {
            enemies.setPartyMembersStatus(foe.getName(), "CHILLING");
            int target = playerParty.findIndexOfFirstLivingPerson();
            if(!(target == -1)) {
                playerParty.setPartyMembersHealth(target,foe.dealDamageTo(playerParty.getParty()[target]));
            }else if(foe.getEquippedRightHand().getAttributestring() == "STUNNING" ||
                foe.getEquippeLeftHand().getAttributestring() == "STUNNING") {
                playerParty.setPartyMembersStatus(target, "STUNNED");
            }
        }
        else {
            cout << foe.getName() << " was stunned and couldn't attack this turn!" << endl;
            enemies.setPartyMembersStatus(foe.getName(), "CHILLING");
        }
    }
}
void choosePathAtTownSquare(Party &playerParty, vector<string> &availablePaths) {
    string path = getInputFromUser(availablePaths);
    cout << endl;
    while(availablePaths.size() > 0) {
        if(path == "t") {
            visitTavern(playerParty);
            removeStringFromVec(availablePaths, path);
            printStringVector(availablePaths);
        }if(path == "d") {
            checkDonations(playerParty);
            removeStringFromVec(availablePaths, path);
            printStringVector(availablePaths);
        }if(path == "b") {
            begBlacksmith(playerParty);
            removeStringFromVec(availablePaths, path);
            printStringVector(availablePaths);
        }
        if(path == "i") {
            investigateMarket(playerParty);
        }
        path = getInputFromUser(availablePaths);

    }
}

void visitTavern(Party &playerParty) {
    cout << "As you walk up to Pimley's Pub and the stench of stale ale and gross, unwashed patrons wash over you, \n"
            "find a dysfunctional staff shouting over each other about how to take care of the rats crowding the escape\n"
            "tunnel. The staff decides that each person will vote for who they like the least. Whoever gets the most votes\n"
            "has to clear out the rats. After a decisive vote Charlie walks away from the group looking absolutely dejected.\n"
            "In that moment Charlie curses his former friends (coworkers) and looks out to the wide world for new people.\n"
            "It is at this point that he lays eye's upon you. He asks you if you'd like to join him in the basement. \n"
            "do you agree? (y/n)";
    vector<string> coolInputs;
    coolInputs.push_back("coworkers");
    coolInputs.push_back("y");
    coolInputs.push_back("n");
    string choice = getInputFromUser(coolInputs);
    if(choice == "coworkers") {
        cout << "WOW! you really think you're clever huh? EAT MY FARTS LOSER. HAAAAAAAA" << endl;
    }else if(choice == "y") {
        inventory emptyInv;
        equipment noEquipment;
        equipment charliesRatBashinStick(4, 0, "Bashes rats.", "charliesRatBashinStick", "WEAPON", "STUNNING");
        character Charlie("Charlie", 10, 1, 1, 10, emptyInv, charliesRatBashinStick, noEquipment, noEquipment);
        playerParty.addMember(Charlie);
        cout << "Woah look!!! some rats!!! At the sight of these pests Charlie brandishes his trusty rat bashin stick\n"
                "and gets ready to get to work" << endl;
        character rat1("Leonardo", 2, 1, 1, 0, emptyInv, noEquipment, noEquipment, noEquipment);
        character rat2(rat1);
        rat2.setName("Raphael");
        character rat3(rat1);
        rat3.setName("Donatello");
        character rat4(rat1);
        rat4.setName("Mikey");
        Party rats;
        rats.addMember(rat1);
        rats.addMember(rat2);
        rats.addMember(rat3);
        rats.addMember(rat4);
        combat(playerParty, rats);
        cout << "HORAY! the rat's are dead! Great celebreations all around!" << endl;
        cout << "As the exhilaration of successful battle rushes through the both of you your eye's lock and Glimbo must \n"
                "ask himself what to do now. Will he (l)leave without a word, or stop and (k) kiss Charlie?" << endl;
        coolInputs.clear();
        coolInputs.push_back("l");
        coolInputs.push_back("k");
        choice = getInputFromUser(coolInputs);
        if(choice == "l") {
            cout << "Charlie makes it clear that he much enjoys the company of Glimbo and will stay with him through \n"
                    "the rest of Glimbo's journey." << endl;
        }else if(choice == "k") {
            cout << "To thank you for such a wonderful time Charlie not only will follow you till the ends of the earth,\n"
                    "but has also commited to fashion Glimbo his very own rat bashin stick." << endl;
            equipment GlimbosVeryOwnRatBashinStick(charliesRatBashinStick);
            playerParty.setPartyMembersEquipped(0, "RIGHTHAND", GlimbosVeryOwnRatBashinStick);
        }
    }else if(choice == "n") {
        cout<<"Seeing nothing left here for you, you leave" << endl;
    }
    playerParty.levelUpParty();
}
void begBlacksmith(Party &playerParty) {
    cout<<"You approach the kind blacksmith and ask her for solid metal sword to aid you on your journey. The blacksmith"
          "explains that while she would love to help you, she runs a business and not a charity, and that to grant the"
          "wishes of everyone that walked in would leave her destined for destitution. However, she can spare a suit of"
          "leather armor, although it may be ineffective it will be far better than the paper that goblins call skin, "
          "or any shirt a goblin could reasonably procure. Glimbo equips it and discards his old crap" << endl;
    equipment leatherArmor(0, 2, "Is leather armor.", "leather armor", "ARMOR", "NONE");
    playerParty.setPartyMembersEquipped(0, "ARMOR", leatherArmor);
    cout << "After visiting the blacksmith, where would you like to go next?" << endl;
}
void checkDonations(Party &playerParty) {
    cout << "The donation box shows slim pickings. All that's in there is a cloth tunic. Upon seeing what Glimbo perceives"
            "to be fine threads and masterful weaving he discards the relative garbage that was on his chest and throws"
            "on this cloth tunic wil all haste" << endl;
    equipment clothTunic(0, 1, "it's a mideavil time shirt", "clothTunic", "ARMOR", "NONE");
    playerParty.setPartyMembersEquipped(0, "ARMOR", clothTunic);
    cout << "With your brand new, quite crummy, shirt where would you like to go next?" << endl;
}
void investigateMarket(Party &playerParty) {
    cout << "There in the market you find the most evil and dastardly criminal. Martin Shkreli. His lore proceeds him"
            "as although it is common knowledge that this is not a good man before you the exact nature and procedure"
            "of his crimes remains veiled under a thick fog of garbage corporate language for Glimbo and all goblins"
            "of his time." << endl;
    equipment MartinSpecialDagger(10, 0, "Stabbed the american people in the back", "Martins Special Dagger", "WEAPON", "NONE");
    equipment noEquip;
    inventory noInv;
    equipment expensiveLawyers(0, 3, "They only protect the rich", "expensiveLawyers", "ARMOR", "NONE");
    character martinShkreli("Martin Shkreli", 14, 5, 5, 999, noInv,MartinSpecialDagger, noEquip, expensiveLawyers);
    character martinMinion1("Insurance fraud", 7, 3, 2, 0, noInv, noEquip, noEquip, expensiveLawyers);
    character martinMinion2(martinMinion1);
    martinMinion2.setName("securities fraud");
    Party boss;
    boss.addMember(martinShkreli);
    boss.addMember(martinMinion1);
    boss.addMember(martinMinion2);
    combat(playerParty, boss);
    cout << "The End" << endl;
    exit(0);
}



