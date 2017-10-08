/*
 * Contact.h
 *
 *  Created on: Oct 3, 2017
 *      Author: Shaila Hirji
 *      Supervisor:Dr Fatma Serce
 */

#ifndef CONTACT_H_
#define CONTACT_H_
#include<string>

using namespace std;

class Contact {

private:
	string _Fname;
	string _Lname;
	string _phone;

public:
	Contact() {
	} //default
	Contact(string Fname, string Lname, string phone); //3 pm
	void setContactFName(string Fname);
	void setContactLName(string Lname);
	void setContactPhone(string phone);
	string getContactFName();
	string getContactLName();
	string getContactPhone();
	bool operator==(const Contact& person1);
	friend void print(Contact);
	virtual ~Contact();

};

#endif /* CONTACT_H_ */
