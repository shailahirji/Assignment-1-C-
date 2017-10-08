/*
 * App.cpp
 * This class is contains the main method for PhoneBook Application
 *
 *  Created on: Oct 3, 2017
 *      Author: Shaila Hirji
 *      Supervisor:Dr Fatma Serce
 */
#include<iostream>
#include<fstream>
#include<string>
#include <sstream>
#include "Helper.h"
#include "Contact.h"
using namespace std;

//accesible to all methods in this class
Contact* pointer;
int numberContacts;
int main() {

	cout << "***My Phonebook Application***" << endl;
	cout << "Please choose operation:\n";
	string line;
	ifstream myFile("phonebook.txt");
	if (myFile.is_open()) {
		while (getline(myFile, line)) {
			numberContacts++;	//increment
		}
		myFile.close();
	} else
		cout << "unable to open file" << endl;

	pointer = new Contact[numberContacts];//points to the array with contacts, user noC only first time you create array
	loadArray();
	//----------------- to do always------------------------------
	bool run = true;
	char userRequest;
	while (run) // to exit, user enters q.
	{
		userRequest = operationPrompt(); 
		switch (userRequest) {
		case 'A':
		case 'a': {
			numberContacts++; //contact added, count increase by 1
			string _name, _phone;
			cout << "Enter name:";
			getline(cin, _name);
			cout << "Enter phone:";
			getline(cin, _phone);
			pointer = addContact(_name, _phone);
			cout << endl;
		}
			break;
		case 'S':
		case 's': {
			string request;
			cout << "Enter Name:";
			getline(cin, request);
			string number = searchContact(request);
			cout << number << '\n';
			cout << endl;
		}
			break;
		case 'D':
		case 'd': {
			string request;
			cout << "Enter Name:";
			getline(cin, request);
			pointer = deleteContact(request);
			numberContacts--; //after delete successful, decrement
			cout << endl;
		}
			break;
		case 'L':
		case 'l': {
			listContacts();
			cout << endl;
		}
			break;
		case 'Q':
		case 'q': {
			run = false; //flag
			return 0;
		}
			break;
		default:
			cout << "\nPlease, try again.\n";
		}
	}

	return 0;
}
//-------------------------------HELPER METHODS---------------------------------
/*
 * Prints operation prompt
 */
char operationPrompt() {
	char userWants;
	cout << " A (Add) | S (Search) | D (Delete) | L (List) | Q(Quit): ";
	cin >> userWants;
	cin.ignore();
	return userWants;

}

/*
 * Helper method, loads array from assigned text file
 */
void loadArray() {

	string contactInfo;
	ifstream myFile("phonebook.txt");
	if (myFile.is_open()) {

		int index = 0;
		while (!myFile.eof()) { //

			string Fname = "";
			string Lname = "";
			string phone = "";

			myFile >> Fname; //get first name
			myFile >> Lname; //get last name
			myFile >> phone; //get phone

			//if file has no empty lines, add them to index, if empty line, go to next line

			if (Fname != "" && Lname != "" && phone != "") {
				pointer[index] = Contact(Fname, Lname, phone); //update array with new contact
				index++;
			}
		}

		myFile.close();
	} else
		cout << "Unable to open file" << endl;

}
/*
 * lists contacts in phone book on user's request, prints to console via friend print function from Contact.cpp
 * Reads the contacts off text file
 */
void listContacts() {

	string contactInfo;
	ifstream myFile("phonebook.txt");
	if (myFile.is_open()) {

		while (!myFile.eof()) { //

			string Fname = "";
			string Lname = "";
			string phone = "";

			myFile >> Fname; //get first name
			myFile >> Lname; //get last name
			myFile >> phone; //get phone

			Contact person(Fname, Lname, phone); //creating a contact
			print(person); //using friend function
		}
		myFile.close();
	} else
		cout << "unable to list contacts" << endl;
}
/*
 * Method called on user's request to add contact, returns updates pointer*
 * creates new array, updates text file on creation of new contact
 */
Contact* addContact(string name, string phone) {

	delete[] pointer;
	pointer = new Contact[numberContacts]; //create new array
	loadArray(); //loads a new array of +1 length;
	string fname, lname;
	istringstream iss(name);
	iss >> fname;
	iss >> lname;

	Contact person(fname, lname, phone);
	pointer[numberContacts - 1] = person; //add new contact to last index of array
	ofstream outfile("phonebook.txt"); //write in new contacts
	for (int i = 0; i < numberContacts; i++) {
		person = pointer[i];
		outfile << person.getContactFName() << " " << person.getContactLName()
				<< " " << person.getContactPhone() << endl;
	}
	outfile.close();
	return pointer;
}

/*
 * Method called on user's request, method searches for contact's phone number
 * returns a string of phone number
 */
string searchContact(string name) {
//user passes in name, break name into Fname and LName
	string fname, lname;
	istringstream iss(name);
	iss >> fname;
	iss >> lname;

	for (int i = 0; i < numberContacts;) { //traverse each index of array

		if (pointer[i].getContactFName() == fname
				&& pointer[i].getContactLName() == lname) {
			return pointer[i].getContactPhone(); //if contact found
		} else {
			i++;
		}
	}
	return "Contact Not Found";
}

/*
 * Method called on user's request to delete contact
 * returns a new pointer after re assignment, reassigment of old pointer(w/contact) to new pointer (w/o contact)
 * updates text file, removes desired contact
 */
Contact* deleteContact(string name) {

	string fname, lname;
	istringstream iss(name);
	iss >> fname;
	iss >> lname;

	Contact* newPointer = new Contact[numberContacts - 1]; //build 1 index smaller array
	for (int i = 0; i < numberContacts - 1;) { //traverse only numberContacts-1 times

		if (pointer->getContactFName() == fname
				&& pointer->getContactLName() == lname) {
			pointer++; //increment old pointer, but keep position of newpointer, newpointer lags
		} else { //if not a match
			newPointer[i] = Contact(pointer->getContactFName(),
					pointer->getContactLName(), pointer->getContactPhone());
			i++;
			pointer++;
		}

	}

	//write back the array to the file
	ofstream outfile("phonebook.txt");

	for (int i = 0; i < numberContacts - 1; i++) { //re write to file, traversing 1 less than original number
		Contact person = newPointer[i];
		outfile << person.getContactFName() << " " << person.getContactLName()
				<< " " << person.getContactPhone() << endl;
	}

	//re assign pointer
	pointer = newPointer;
	return pointer;
}
