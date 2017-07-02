#include <iostream>
#include <time.h>
#include <string>
#include <unistd.h> //for usleep
#include <fstream> //for logging
#include <wiringPi.h> //for gpio, replaces GPIOClass.h
#include <lcd.h> //for lcd
#include "email.h"

using namespace std;

//defining wiringPi pin identifiers for connnectors
#define GDS 29 //garage door switch
#define LCD_RS 6
#define LCD_E 5
#define LCD_D4 4
#define LCD_D5 0
#define LCD_D6 2
#define LCD_D7 3

//functions
string getStringTimeNow();
string calcUpTime(time_t tStart);

int main(void)
{
	time_t timeOld = time(NULL);
	string timeNowStr;
	int statusOld = 0; // starts closed
	int gpio21_val; // state of input pin garage door switch
	string logline;
	time_t timeStart = time(NULL);
	string upTime;
	email* gOpen = new email("root","kama,flex","WARNING! Garage is open","At the time of this email the garage has been open for half an hour.");
	int lcd;
	wiringPiSetup();
	
	//initialise lcd
	if(lcd = lcdInit(2, 16, 4, LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7, 0, 0, 0, 0)){
		printf("lcd init failed");
		return -1;
	}
	
	//opening file to log door activity
	ofstream doorLog;
	doorLog.open("doorLog.txt", ios::app);
	if(doorLog.is_open()){
		cout << "logging door activity" << endl;
		logline.append(getStringTimeNow());
		logline.append(" - Pi booted up");
		doorLog << logline << endl;
		logline = "";
	}else{
		cout << "unable to log" << endl;
	}
	
	//enabling GPIO for magnetic switch attached to door
	pinMode(GDS, INPUT);
	
	//infinite loop for monitoring door
	while(1){
		usleep(1000000); //wait 1 second
		
		//get current status
		gpio21_val = digitalRead(GDS);
		
		//update LCD
		lcdPosition(lcd,0,0);
		lcdPuts(lcd, "Up time: ");
		upTime = calcUpTime(timeStart); //days, hours, mins, secs eg: 34d 23h 59m 59s
		lcdPosition(lcd,0,1);
		lcdPuts(lcd, upTime.c_str());
				
		//checking if status changed
		if (statusOld != gpio21_val){
			timeNowStr = getStringTimeNow();

			if(gpio21_val == 0){
				cout << "circuit open" << endl;
				cout << "the garage is closed, all is well" << endl;
				
				logline.append (timeNowStr);
				logline.append (" - closed");
				doorLog << logline << endl;
			}

			if(gpio21_val == 1){
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
			// if garage is open and has been for 30 minutes
			if(gpio21_val == 1 && difftime(time(NULL),timeOld) > 1800) {
				timeNowStr = getStringTimeNow();
			
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
	
	return 0;
}

string getStringTimeNow() {
	time_t timeNow = time(NULL); 
	string timeNowStr = ctime(&timeNow); //stringify time
	timeNowStr.erase(timeNowStr.end()-1, timeNowStr.end()); //remove newline at end
	
	return timeNowStr;
}

string calcUpTime(time_t tStart) {
	time_t timeNow = time(NULL);
	int seconds = difftime(timeNow, tStart);
	int secs = seconds%60;
	int minutes = seconds/60;
	int mins = minutes%60;
	int hours = minutes/60;
	int hrs = hours%60;
	int days = hours/24;
	int dy = dy%24;
	
	string duration = to_string(dy) + "d ";
	if(hrs < 10){
		duration = duration.append("0");
	}
	duration = duration.append(to_string(hrs)+"h ");
	
	if(mins<10){
		duration = duration.append("0");
	}
	duration = duration.append(to_string(mins)+"m ");
	
	if(secs<10){
		duration = duration.append("0");
	}
	duration = duration.append(to_string(secs)+"s");
		
	return duration;
}