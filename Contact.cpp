/*
 * Contact.cpp
 *
 *  Created on: Oct 3, 2017
 *      Author: Shaila Hirji
 *      Supervisor:Dr Fatma Serce
 */

#include "Contact.h"
#include <iostream>
using namespace std;

Contact::Contact(string Fname, string Lname, string phone) {
	//assign passed values
	_Fname = Fname;
	_Lname = Lname;
	_phone = phone;

}
Contact::~Contact() {

}

void Contact::setContactFName(string Fname) {
	_Fname = Fname;
}

void Contact::setContactLName(string Lname) {
	_Lname = Lname;
}

void Contact::setContactPhone(string phone) {
	_phone = phone;
}

string Contact::getContactFName() {
	return _Fname;

}

string Contact::getContactLName() {
	return _Lname;

}

string Contact::getContactPhone() {
	return _phone;
}

void print(Contact person) { //friend function
	cout << person.getContactFName() << " " << person.getContactLName() << " "
			<< person.getContactPhone() << endl;
}

bool Contact::operator==(const Contact& p1) {

	return (p1._Fname == this->_Fname && p1._Lname == this->_Lname);

}

