/*  Program: Project 4 - BST
 Author: Anthony Esmeralda, Kevin Ngo
 Class: CSCI 220
 Date:  Novemember 14, 2017
 Description: Binary Search Tree that uses an AVL tree search through records
 of county/state, population, and county/state name
 
 I certify that the code below is my own work.
 
 Exception(s): N/A
 */
#ifndef _ENTRY_H_
#define _ENTRY_H_
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

class Entry {
public:
	int county_state_code;
	string county_state_name;
	int population;
public:
	Entry();
	Entry(int code, int pop, string name);
	int getCode();
	int getPop();
	string getName();
	void setName(string name);
	void setCode(int code);
	void setPop(int pop);
	void printData();
};
#endif // !_ENTRY_H_
