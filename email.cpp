#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "email.h"

using namespace std;

email::email(){
	email("root","root","test","this is a test");
}

email::email(string sndr, string rcvr, string sbj, string bdy){
	setSender(sndr);
	setReceiver(rcvr);
	setSubject(sbj);
	setBody(bdy);
	makeMessage();
}

void email::setSender(string sndr){
	this->sender = sndr;
}

void email::setReceiver(string rcvr){
	this->receiver = rcvr;
}

void email::setSubject(string sbj){
	this->subject = sbj;
}

void email::setBody(string bdy){
	this->body = bdy;
}

void email::makeMessage() {
	time_t timeNow = time(NULL);
	string timeNowStr = ctime(&timeNow);
	timeNowStr.erase(timeNowStr.end()-1, timeNowStr.end());
	ofstream messageDoc;
	
	messageDoc.open("message.mail", ios::trunc);
	
	if(messageDoc.is_open()){
		cout << "creating message.mail" << endl;
	}else{
		cout << "unable to create message.mail" << endl;
	}
	
	messageDoc << "Subject: " << this->subject << endl;
	messageDoc << this->body << endl;
	messageDoc << "\nThis session of monitoring has been running since " << timeNowStr << endl;
	
	messageDoc.close();
}

void email::sendEmail(){
	FILE *in;
	char buff[512];
	string msg =  "sendmail " + this->receiver + " < message.mail"; 
	
	if(!(in = popen(msg.c_str(),"w"))){
		cout << "can't send email"<<endl;
	}
		
	while(fgets(buff, sizeof(buff), in) != NULL){
		cout << buff;
	}
	
	pclose(in);
}
