//
// Created by bobjo on 10/3/2024.
//
#include "ShuffleHandler.h"
#include <iostream>
#include <sstream>
#include <chrono>
#include <thread>
#include <unistd.h>

using namespace std;

bool checkNoElementsLost(vector<int>& v, string s);
bool checkAllElementsChangedPosition(vector<int>& v, string s);
bool checkAllElementsHaveDifferentNeighbors(vector<int>& v, string s);
bool hasMadeUpItems(vector<int>& v, string s);
bool checkReversed(vector<int>& v, string s);

int main() {
    int i;
    vector<int> v;
    for(i = 0; i < 100; i++) {
        v.push_back(i);
    }
    int numFailures = 0;
    int numChecks = 1000;
    for (i = 0; i < numChecks; i++) {
        if(!checkNoElementsLost(v, "luke")) {
            numFailures++;
        }else if(!checkAllElementsChangedPosition(v, "luke")) {
            numFailures++;
        }else if(!checkAllElementsHaveDifferentNeighbors(v, "luke")) {
            numFailures++;
        }else if(!hasMadeUpItems(v, "luke")) {
            numFailures++;
        }else if(!checkReversed(v, "luke")) {
            numFailures++;
        }
    }
    cout <<"Number of failed randomization's :"<< numFailures << endl;
    if(numFailures <= numChecks/10) {
        cout << "Luke's shuffle function is valid and random :)" << endl;
    }
    numFailures = 0;
    for (i = 0; i < numChecks; i++) {
        if(!checkNoElementsLost(v, "olivia")) {
            numFailures++;
        }else if(!checkAllElementsChangedPosition(v, "olivia")) {
            numFailures++;
        }else if(!checkAllElementsHaveDifferentNeighbors(v, "olivia")) {
            numFailures++;
        }else if(!hasMadeUpItems(v, "olivia")) {
            numFailures++;
        }else if(!checkReversed(v, "olivia")) {
            numFailures++;
        }
    }
    cout << endl;
    cout << endl;
    cout << endl;
    cout <<"Number of failed randomization's :"<< numFailures << endl;
    if(numFailures <= numChecks/10) {
        cout << "Olivia's shuffle function is valid and random :)" << endl;
    }
    return 0;
}


bool checkNoElementsLost(vector<int>& v, string s) {
    bool result = true;
    ShuffleHandler<int> shuffler(v);
    vector<int> shuffled;
    if(s == "luke") {
        shuffled = shuffler.shuffleLVAGTBEN();
    }else if(s == "olivia") {
        shuffled = shuffler.shuffleOGALEXAN();
    }else {
        cout << s << " is not a valid input." << endl;
        return false;
    }
    for(int num: v) {
        if(count(shuffled.begin(), shuffled.end(), num) < 1) {
            result = false;
        }
    }
    return result;
}
bool checkAllElementsChangedPosition(vector<int>& v, string s) {
    bool result = true;
    int numUnchanged = 0;
    ShuffleHandler<int> shuffler(v);
    vector<int> shuffled;
    if(s == "luke") {
        shuffled = shuffler.shuffleLVAGTBEN();
    }else if(s == "olivia") {
        shuffled = shuffler.shuffleOGALEXAN();
    }else {
        cout << s << " is not a valid input." << endl;
        return false;
    }
    for(int i = 0; i < v.size(); i++) {
        if(shuffled[i] == v[i]) {
            numUnchanged++;
        }
    }
    if(numUnchanged >= v.size()/5) {
        result = false;
    }

    return result;
}

bool checkAllElementsHaveDifferentNeighbors(vector<int>& v, string s) {
    bool result = true;
    int numProblems = 0;
    if(v.size() == 1) {
        cout << "input a better, larger vector" << endl;
        return false;
    }
    ShuffleHandler<int> shuffler(v);
    vector<int> shuffled;
    if(s == "luke") {
        shuffled = shuffler.shuffleLVAGTBEN();
    }else if(s == "olivia") {
        shuffled = shuffler.shuffleOGALEXAN();
    }else {
        cout << s << " is not a valid input." << endl;
        return false;
    }
    vector<vector<int>> neighbors;
    for(int i = 0; i < v.size(); i++) {
        vector<int> nextVec;
        nextVec.push_back(v[i]);
        if(i == 0) {
            nextVec.push_back(v[v.size()-1]);
            nextVec.push_back(v[i+1]);
        }else if(i == v.size()-1) {
            nextVec.push_back(v[i-1]);
            nextVec.push_back(v[0]);
        }else {
            nextVec.push_back(v[i-1]);
            nextVec.push_back(v[i+1]);
        }
        neighbors.push_back(nextVec);
    }
    int indexOfElement;
    for(int i = 0; i < shuffled.size(); i++) {
        //https://www.geeksforgeeks.org/how-to-find-index-of-a-given-element-in-a-vector-in-cpp/#
        auto it = find(shuffled.begin(), shuffled.end(), neighbors[i][0]);
        indexOfElement = it - shuffled.begin();
        if(indexOfElement == 0) {
            if(shuffled[indexOfElement+1] == neighbors[i][1] && shuffled[shuffled.size()-1] == neighbors[i][2]) {
                ++numProblems;
            }
        }else if(indexOfElement == shuffled.size()-1) {
            if(shuffled[indexOfElement-1] == neighbors[i][1] && shuffled[0] == neighbors[i][2]) {
                ++numProblems;
            }
        }else {
            if(shuffled[indexOfElement-1] == neighbors[i][1] && shuffled[indexOfElement-1] == neighbors[i][2]) {
                ++numProblems;
            }
        }
    }
    if(numProblems >= v.size()/5) {
        result = false;
    }
    return result;
}
bool hasMadeUpItems(vector<int>& v, string s) {
    bool result = true;
    ShuffleHandler<int> shuffler(v);
    vector<int> shuffled;
    if(s == "luke") {
        shuffled = shuffler.shuffleLVAGTBEN();
    }else if(s == "olivia") {
        shuffled = shuffler.shuffleOGALEXAN();
    }else {
        cout << s << " is not a valid input." << endl;
        return false;
    }
    for(int num: shuffled) {
        if(count(v.begin(), v.end(), num) < 1) {
            result = false;
        }
        if(count(v.begin(), v.end(), num) > 100) {
            result = false;
        }
    }
    return result;
}
bool checkReversed(vector<int>& v, string s) {
    bool result = true;
    int numUnchanged = 0;
    ShuffleHandler<int> shuffler(v);
    vector<int> shuffled;
    vector<int> reversed;
    if(s == "luke") {
        shuffled = shuffler.shuffleLVAGTBEN();
    }else if(s == "olivia") {
        shuffled = shuffler.shuffleOGALEXAN();
    }else {
        cout << s << " is not a valid input." << endl;
        return false;
    }
    reverse(v.begin(), v.end());
    for(int i = 0; i < v.size(); i++) {
        if(shuffled[i] == v[i]) {
            numUnchanged++;
        }
    }
    if(numUnchanged >= v.size()/5) {
        result = false;
    }

    return result;
}
