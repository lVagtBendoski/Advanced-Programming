#include "Closet_Monster.h"
#include "Under_Bed_Monster.h"
#include "Darkness_Monster.h"
#include <ctime>
#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
using namespace std;
void fillMonsterVector(vector<unique_ptr<Darkness_Monster>> &monsters, int numMonsters);
string getInputFromUser(vector<string> acceptableInputs);
string getSentenceFromUser();
void printStringVector(vector<string> vec);
int main() {
    /*
     * Create a vector of Darkness Monster unique pointers and push a variety of ten Closet Monsters and Under Bed Monsters to it.
     * Tell the user that there are monster eyes staring at them from the darkness!
     * 2.2 answer for books is no
     * TODO: Repeatedly give the user the option to poke the eyes or run away.
     *     - If they choose to poke the eyes, loop through the vector and call the poke_eye and scare method on each monster. Output the scare method return values to the console.
     *         - Note: the calls to poke_eye are NOT polymorphism.
     *         - Note: the calls to scare are polymorphism.
     *     - If they choose to run away, the program ends.
    */
    vector<unique_ptr<Darkness_Monster>> monsters;
    const int NUM_MONSTERS = 10;
    vector<string> acceptableInputs;
    acceptableInputs.push_back("poke");
    acceptableInputs.push_back("run");
    fillMonsterVector(monsters, NUM_MONSTERS);
    string choice;
    cout << "there are monster eyes staring at them from the darkness!" << endl;
    for(int i = 0; i < monsters.size(); ++i) {
        cout << "will you poke the eye's or run away?" << endl;
        cout << "to poke the eye's enter: poke, to run enter: run" << endl;
        choice = getInputFromUser(acceptableInputs);
        monsters[i]->scare();
        if(choice == "poke") {
            for(int j = 0; j < monsters.size(); ++j) {
                cout <<monsters[j]->scare() << endl;
                if(monsters[j]->poke_eye() == true){
                     cout << "You successfully poked all the eye's away!" << endl;
                }else {
                    cout << "Too many eye's! you are dead now. womp womp." << endl;
                    exit(0);
                }
            }
        }else if(choice == "run") {
            cout << "you have run away like a little coward baby. Wah Wah little baby." << endl;
            exit(0);
        }
    }
    return 0;
}
void fillMonsterVector(vector<unique_ptr<Darkness_Monster>> &monsters, int numMonsters) {

    for (int i = 0; i < numMonsters; ++i) {
        if (rand() % 2) {
            monsters.push_back(make_unique<Under_Bed_Monster>());
        } else {
            monsters.push_back(make_unique<Closet_Monster>());
        }
    }

}
string getInputFromUser(vector<string> acceptableInputs) {
    string result;
    result = getSentenceFromUser();
    while(count(acceptableInputs.begin(), acceptableInputs.end(), result) < 1 ) {
        cout << "enter one of these list items: ";
        printStringVector(acceptableInputs);
        cout << endl;
        result = getSentenceFromUser();
    }
    return result;
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

void printStringVector(vector<string> vec) {
    cout <<'[';
    for(string s : vec) {
        cout << " "<< s << " ";
    }
    cout <<']';
}