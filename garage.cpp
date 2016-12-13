#include <iostream>
#include <time.h>
#include <string>
#include <unistd.h> //for usleep
#include <fstream> //for logging
#include "GPIOClass.h"
#include "email.h"

using namespace std;

int main(void)
{
	time_t timeOld = time(NULL);
	time_t timeNow;
	string timeNowStr;
	string statusOld = "0"; 
	string gpio21_val; // state of input pin
	string logline;
	email* gOpen = new email("root","kkjayne@gmail.com","WARNING! Garage is open","At the time of this email the garage has been open for half an hour.");

	ofstream doorLog;
	doorLog.open("doorLog.txt", ios::app);
	if(doorLog.is_open()){
		cout << "logging" << endl;
	}else{
		cout << "unable to log" << endl;
	}

	GPIOClass* gpio21 = new GPIOClass("21");

	gpio21->export_gpio();
	gpio21->setdir_gpio("in");

	while(1){
		usleep(50000);
		gpio21->getval_gpio(gpio21_val);

		if (statusOld != gpio21_val){
			timeNow = time(NULL); 
			timeNowStr = ctime(&timeNow); //stringify time
			timeNowStr.erase(timeNowStr.end()-1, timeNowStr.end()); //remove newline at end

			if(gpio21_val == "0"){
				cout << "circuit open" << endl;
				cout << "the garage is closed all is well" << endl;
				
				logline.append (timeNowStr);
				logline.append (" - closed");
				doorLog << logline << endl;
			}

			if(gpio21_val =="1"){
				cout << "circuit closed" << endl;
				cout << "the garage is open, need to close it" << endl;
				
				logline.append (timeNowStr);
				logline.append (" - opened");
				doorLog << logline << endl;

			}
			statusOld = gpio21_val;

			cout << "seconds since last change: " << difftime(time(NULL),timeOld) << endl;

			timeOld = time(NULL);
			logline = "";
		}else{
			if(gpio21_val == "1" && difftime(time(NULL),timeOld) > 30) {
				timeNow = time(NULL); 
				timeNowStr = ctime(&timeNow); //stringify time
				timeNowStr.erase(timeNowStr.end()-1, timeNowStr.end()); //remove newline at end
			
				cout << "The garage has been open for too long" << endl;
				gOpen->sendEmail();
				logline.append (timeNowStr);
				logline.append (" - email sent");
				doorLog << logline << endl;

				timeOld = time(NULL);
				logline = "";
			}
		}
	}

	//closing shop
	doorLog.close();
	gpio21->unexport_gpio();

	return 0;
}
