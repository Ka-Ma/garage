#ifndef GPIO_CLASS_H
#define GPIO_CLASS_H

#include <string>

using namespace std;

class GPIOClass {
public: 
	GPIOClass(); // defaults to GPIO4
	GPIOClass(string x); //specifies the pin
	int export_gpio(); 
	int unexport_gpio();
	int setdir_gpio(string dir); // sets direction of GPIO
	int setval_gpio(string val); //sets whether the pin is high or low
	int getval_gpio(string& val); //gets the pin value
	string get_gpionum(); // gets the gpio number associated with the instance
private:
	string gpionum; //gpio number associated with the instance
};

#endif
