#include "sorting-algorithms/bubbleSort.h"
#include "sorting-algorithms/heapSort.h"
#include "sorting-algorithms/insertionSort.h"
#include "sorting-algorithms/selectionSort.h"
#include "stability-test/contactsList.h"
#include "SuicideRateDataHandler.h"
#include <chrono>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;
using namespace std::chrono;

void stabilityTest();
void collectAndSendDataToCSV();

#ifdef _WIN32
const string systemType = "windows";
#else
const string systemType = "mac";
#endif

// Different OSs use different CLI commands to run Python
#ifdef _WIN32
// TODO: If your Windows machine runs Python in CLI with "python" instead of "py", update this line.
const string python = "python";
#else
// TODO: If your Mac/Linux machine runs Python in CLI with "python3" instead of "python", update this line.
const string python = "python";
#endif


int main() {
    collectAndSendDataToCSV();
    stabilityTest();
    //calling python file
    string filename = "../customData.py";
    string sortingDataFilePath = "../data/sortingData.csv";
    string imageFolderFilePath = "../images/";
    string command = python + ' ' + filename + " " + sortingDataFilePath + " " + imageFolderFilePath;
    system(command.c_str());
    return 0;
}

void writeToCSV(ofstream &file, int &reads, int &writes, vector<SuicideRateDataHandler> &vec, time_point<system_clock> &startWin,
                time_point<system_clock> &stopWin, duration<double> elapsedMicroSeconds,
                time_point<steady_clock> &startMac, time_point<steady_clock> &stopMac) {
#ifdef _WIN32
    stopWin = high_resolution_clock::now();
    elapsedMicroSeconds = duration_cast<microseconds>(stopWin - startWin);
#else
    stopMac = high_resolution_clock::now();
    elapsedMicroSeconds = duration_cast<microseconds>(stopMac - startMac);
#endif

    file << reads << ',' << writes << ',' << elapsedMicroSeconds.count() <<',';
#ifdef _WIN32
    startWin = high_resolution_clock::now();
#else
    startMac = high_resolution_clock::now();
#endif
}
void collectAndSendDataToCSV(){
    ofstream outFile;
    int i, reads, writes;
    vector<SuicideRateDataHandler> vectorToBeSorted;
    time_point<system_clock> startWin, stopWin;
    time_point<steady_clock> startMac, stopMac;
    duration<double> elapsedMicroSeconds;
    if(systemType == "windows") {
        elapsedMicroSeconds = duration_cast<microseconds>(stopWin - startWin);
    }else {
        elapsedMicroSeconds = duration_cast<microseconds>(stopMac - startMac);
    }
    SuicideRateDataHandler dataHandler;
    if (dataHandler.getDataFromFile(vectorToBeSorted)) {
        vectorToBeSorted.resize(6300);
        outFile.open("../data/sortingData.csv");
        outFile << "Vector size,Bubble sort reads,Bubble sort writes,Bubble sort execution time (s),Heap sort reads,Heap sort writes,";
        outFile << "Heap sort execution time (s),Insertion sort Reads,Insertion sort writes,Insertion sort execution time (s),";
        outFile << "Selection sort reads,Selection sort writes,Selection sort execution time (s)" << endl;
        for (i = 0; i < 63; ++i) {
            outFile << vectorToBeSorted.size() << ',';
            #ifdef _WIN32
            startWin = high_resolution_clock::now();
            #else
            startMac = high_resolution_clock::now();
            #endif
            bubbleSort(vectorToBeSorted, reads, writes);
            writeToCSV(outFile, reads, writes, vectorToBeSorted, startWin, stopWin,
                        elapsedMicroSeconds, startMac, stopMac);
            heapSort(vectorToBeSorted, reads, writes);
            writeToCSV(outFile, reads, writes, vectorToBeSorted, startWin, stopWin,
                        elapsedMicroSeconds, startMac, stopMac);
            insertionSort(vectorToBeSorted, reads, writes);
            writeToCSV(outFile, reads, writes, vectorToBeSorted, startWin, stopWin,
                        elapsedMicroSeconds, startMac, stopMac);
            selectionSort(vectorToBeSorted, reads, writes);
            writeToCSV(outFile, reads, writes, vectorToBeSorted, startWin, stopWin,
                        elapsedMicroSeconds, startMac, stopMac);
            #ifdef _WIN32
            stopWin = high_resolution_clock::now();
            elapsedMicroSeconds = duration_cast<microseconds>(stopWin - startWin);
            #else
            stopMac =high_resolution_clock::now();
            elapsedMicroSeconds = duration_cast<microseconds>(stopMac - startMac);
            #endif
            outFile << endl;
            vectorToBeSorted.resize(vectorToBeSorted.size() - 100);
        }

        outFile.close();
    }

}

void stabilityTest() {
    ContactsList people;
    people.readContactsFromFile("../stability-test/names.csv");
    cout << "People (Default ordering)" << endl;
    people.printList();

    cout << endl << "Bubble Sort" << endl;
    people.sortAndPrint(bubbleSort<contact>);

    cout << endl << "Insertion Sort" << endl;
    people.sortAndPrint(insertionSort<contact>);

    cout << endl << "Heap Sort" << endl;
    people.sortAndPrint(heapSort<contact>);

    cout << endl << "selectionSort" << endl;
    people.sortAndPrint(selectionSort<contact>);
}