#include "Entry.h"

Entry::Entry()
{
	county_state_name = "";
	county_state_code = 0;
	population = 0;
}
Entry::Entry(int code, int pop, string name)
{
	county_state_name = name;
	county_state_code = code;
	population = pop;
}
int Entry::getCode()
{
	return county_state_code;
}
int Entry::getPop()
{
	return population;
}
string Entry::getName()
{
	return county_state_name;
}
void Entry::setName(string name)
{
	county_state_name = name;
}
void Entry::setCode(int code)
{
	county_state_code = code;
}
void Entry::setPop(int pop)
{
	population = pop;
}

void Entry::printData()
{
	cout << county_state_code << " " << population << " " << county_state_name << " || ";
}
