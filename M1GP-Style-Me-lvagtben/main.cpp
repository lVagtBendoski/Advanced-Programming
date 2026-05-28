#include <iostream>
#include "temp.h"
#include <sstream>

using namespace std;

double getTodaysTempFromUser(const string& unitPref);
double getFloatFromUser();


int main() {
    //declarations
    double temperatureToday;
    int freezingPoint = 0;
    int uncomfortablyHotPoint = 30;
    string dayType;
    string unitChoice;
    temp myTemp = temp();
    //This lets the user choose if they want to give the temperature in Celsius or Fahrenheit.
    cout << "Enter the units you prefer. your choices are Celsius, or Fahrenheit:" << endl;
    getline(cin, unitChoice);
    //this will trap the user until they choose to use Celsius or Fahrenheit
    while (!(unitChoice == "Celsius" || unitChoice == "Fahrenheit")) {
        cout << "you can only celsius or fahrenheit:" << endl;
        getline(cin, unitChoice);
    }
    /*
     *Here there are two different paths depending on if the user wanted to use Celsius or Fahrenheit.
     *In the Celsius path the user is prompted to enter the temp in Celsius and units are compared to
     *freezing/too hot point in Celsius. In the Fahrenheit path the user is prompted to enter the temp
     *in Fahrenheit. after this the temp is converted to Celsius so they can both be compared against
     *the same numbers.
     */

    if (unitChoice == "Celsius"){
        //This is the Celsius path
        temperatureToday = getTodaysTempFromUser(unitChoice);
        myTemp.setCelsius(temperatureToday);
    }else{
        //This is the Fahrenheit path
        temperatureToday = getTodaysTempFromUser(unitChoice);
        myTemp.setCelsius(myTemp.fahrenheitToCelsius(temperatureToday));
    }
    //sets dayType to the type of day that it actually is
    if (myTemp.getCelsius() < freezingPoint) {
        dayType="cold";
    }else if (myTemp.getCelsius() > uncomfortablyHotPoint){
        dayType="hot";
    }else
        dayType="beautiful";
    //greets the type of world this program currently exists in
    cout << "Hello, " << dayType << " World!" << endl;

    return 0;
}
//gets today's temp from the user in the unit that the user prefers
double getTodaysTempFromUser(const string& unitPref){
    double result;
    cout << "Enter the temperature today in " + unitPref + ":" << endl;
    result = getFloatFromUser();
    return result;
}
//gets a float from the user
double getFloatFromUser() {
    //declarations
    double num;
    string input;
    stringstream ss;
    bool inputNotValid = true;
    //traps the user until they input a valid float
    while (inputNotValid) {
        inputNotValid = false;
        getline(cin, input);
        ss << input;
        if(input.empty()) {
            inputNotValid = true;
            cout << "No input. Enter a float:";
        }else if(!(ss >> num)){
            inputNotValid = true;
            cout << "Invalid input. Enter a float:";
        }
        ss.clear();
        ss.str("");
    }
    ss >> num;
    //returns that float
    return num;
}
