//
// Created by bobjo on 10/2/2024.
//
#include "saver.h"
/*
 *This ended up being too hard, and not worth the points. Not deleted in case it's useful later.
saver::saver(string sfn, int checkpointNum, Party& partyToSave) {
    saveFileName = sfn;
    checkpointNumber = checkpointNum;
    for(int i = 0; i < partyToSave.getParty().size(); i++) {
        partyToSave.getParty();
        character tempChar(partyToSave.getParty()[i]);
        playerParty.addMember(tempChar);
    }
}
saver::~saver() {
    fileIn.close();
    fileOut.close();
}
void saver::setSaveFileName(std::string name) {
    saveFileName = name;
}
void saver::setCheckpointNumber(int num) {
    checkpointNumber = num;
}
string saver::getSaveFileName() {
    return saveFileName;
}
int saver::getCheckpointNumber() {
    return checkpointNumber;
}
bool saver::loadSave(std::string &sfn) {
return true;

}
bool saver::saveProgress() {
    fileIn.open(fileName);
    if(fileIn.good()) {
        string currLine;
        //https://www.geeksforgeeks.org/getline-string-c/#
        getline(fileIn, currLine);
        while(currLine != "") {
             getline(fileIn, currLine);
        }
        fileOut << saveFileName << ',';
        fileOut << checkpointNumber << ',';
        fileOut << playerParty.getParty().size() << ',';
        for(character c :playerParty.getParty()) {
            c.printCharacterDataToFile(fileOut);
        }
        fileOut << '\n';
    }else {
        cout << "fileIn not good" << endl;
        return false;
    }
    return true;
    fileIn.close();
}
    */








