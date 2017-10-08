/*
 * Helper.h
 *
 *  Created on: Oct 3, 2017
 *      Author: Shaila Hirji
 *      Supervisor:Dr Fatma Serce
 * This class contains prototypes for methods used in App.cpp
 */

#ifndef HELPER_H_
#define HELPER_H_
#include "Contact.h"

string searchContact(string name);
Contact* deleteContact(string name);
string searchContact(string name);
Contact* addContact(string name, string phone);
void listContacts();
void loadArray();
char operationPrompt();

#endif /* HELPER_H_ */
