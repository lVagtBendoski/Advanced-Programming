//
// Created by bobjo on 9/2/2024.
//

#ifndef TEMP_H
#define TEMP_H
class temp {
// just some cute fields and constant numbers
private:
    double fahrenheit;
    double celsius;
    const double conversionRatio = 5/9;
    const int conversionOffset = 32;
    const int fahrenheitFreezingPoint = 32;
    const int celsiusFreezingPoint = 0;
public:
    //default constructor
    temp() {
        celsius = celsiusFreezingPoint;
        fahrenheit = fahrenheitFreezingPoint;
    }
    //Constructor with specifics for the fahrenheit and celsius settings
    temp(double f, double c) {
        celsius = c;
        fahrenheit = f;
    }
    //getters
    double getFahrenheit() const{
        return fahrenheit;
    }
    double getCelsius() const{
        return celsius;
    }
    //setters
    void setCelsius(double num){
        celsius = num;
    }
    void setFahrenheit(double num){
        fahrenheit = num;
    }
    //conversions using the values already stored
    double fahrenheitToCelsius() const{
        return (fahrenheit-conversionOffset) * conversionRatio;
    }
    double celsiusToFahrenheit() const{
        return celsius * conversionRatio + conversionOffset;
    }
    //conversions using any value
    double fahrenheitToCelsius(double tempInF) const{
        return (tempInF - conversionOffset) * conversionRatio;
    }
    double celsiusToFahrenheit(double tempInC) const{
        return tempInC * conversionRatio + conversionOffset;
    }
};
#endif //TEMP_H
