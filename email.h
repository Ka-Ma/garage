#ifndef EMAIL_H
#define EMAIL_H

#include <string>

using namespace std;

class email {
public: 
	email();  
	email(string sndr, string rcvr, string sbj, string bdy);
	void setSender(string sndr);
	void setReceiver(string rcvr);
	void setSubject(string sbj);
	void setBody(string bdy);
	void sendEmail();
private:
	string sender;
	string receiver;
	string subject;
	string body;
};

#endif
