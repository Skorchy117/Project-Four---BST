#ifndef _ENTRY_H_
#define _ENTRY_H_

#include <iostream>
#include <string>
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
