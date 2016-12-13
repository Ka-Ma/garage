#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <stdlib.h>
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

void email::sendEmail(){
	string msg =  "echo -e 'FROM: " + sender + "\nTO: " + receiver + "\nSubject: " + subject + "\n\n" + body + "' | sendmail -t";
	
	system(msg.c_str());	
}
