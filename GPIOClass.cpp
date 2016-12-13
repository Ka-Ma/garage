#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include "GPIOClass.h"

using namespace std;

GPIOClass::GPIOClass(){
	this->gpionum = "21";
}

GPIOClass::GPIOClass(string x){
	this->gpionum = x;
}

int GPIOClass::export_gpio(){
	string export_str = "/sys/class/gpio/export";
	ofstream exportgpio(export_str.c_str()); // linus pathname needs c string

	if(exportgpio < 0){
		cout << "Can't export GPIO" << this->gpionum << endl;
		return -1;
	}

	exportgpio << this->gpionum;
	exportgpio.close();

	return 0;
}

int GPIOClass::unexport_gpio(){
	string unexport_str = "/sys/class/gpio/unexport";
	ofstream unexportgpio(unexport_str.c_str()); // linus pathname needs c string

	if(unexportgpio < 0){
		cout << "Can't unexport GPIO" << this->gpionum << endl;
		return -1;
	}

	unexportgpio << this->gpionum;
	unexportgpio.close();

	return 0;
}

int GPIOClass::setdir_gpio(string dir){
	string setdir_str = "/sys/class/gpio/gpio"+ this->gpionum + "/direction";
	ofstream setdirgpio(setdir_str.c_str()); // linus pathname needs c string

	if(setdirgpio < 0){
		cout << "Can't set direction GPIO" << this->gpionum << endl;
		return -1;
	}

	setdirgpio << dir;
	setdirgpio.close();

	return 0;

}

int GPIOClass::setval_gpio(string val){
	string setval_str = "/sys/class/gpio/gpio" + this->gpionum + "/value";
	ofstream setvalgpio(setval_str.c_str()); // linus pathname needs c string

	if(setvalgpio < 0){
		cout << "Can't set value GPIO" << this->gpionum << endl;
		return -1;
	}

	setvalgpio << val;
	setvalgpio.close();

	return 0;
}

int GPIOClass::getval_gpio(string& val){
	string getval_str = "/sys/class/gpio/gpio" + this->gpionum + "/value";
	ifstream getvalgpio(getval_str.c_str());

	if(getvalgpio < 0){
		cout << "Can't get value GPIO" << this->gpionum << endl;
		return -1;
	}

	getvalgpio >> val;

	if(val != "0")
		val = "1";
	else
		val = "0";

	getvalgpio.close();

	return 0;
}

string GPIOClass::get_gpionum(){
	return this->gpionum;
}
