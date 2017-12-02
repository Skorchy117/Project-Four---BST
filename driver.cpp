#include <iostream>
#include <fstream>
#include <string>
#include "AVLTree.h"
using namespace std;

void fillTree(AVLTree& t, string fileName);
void stringToEntry(string s, Entry& e);

int main()
{
	typedef Entry E;
	AVLTree newTree;
	fillTree(newTree, "p4small.txt");
	/*E uno(20, 1, "asdf");
	E dos(55, 21, "asdf");
	E tres(13, 123, "123");
	E quatro(10, 1234, "1234");
	E cinco(100, 1234, "asdfasdf");
	E seis(121, 123, "asdfasdf");
	newTree.insert(uno);
	newTree.insert(dos);
	newTree.insert(tres);
	newTree.insert(quatro);
	newTree.insert(cinco);
	newTree.insert(seis);
	SearchTree::Iterator it(newTree.begin());
	E output;
	*/
	SearchTree::Iterator it(newTree.begin());
	E output;
	for (it; it != newTree.end(); ++it)
	{
		output = *it;
		output.printData();
	}
	string s;
	cin >> s;
	return 0;
}

void fillTree(AVLTree& t, string fileName)
{
	Entry E;
	string record;
	fstream infile;
	infile.open(fileName);
	if (infile.is_open())
	{
		while (!infile.eof())
		{
			getline(infile, record);
			stringToEntry(record, E);
			t.insert(E);
		}
	}
	else
		cout << "Incorrect file name passed or does not exist.\n";
}

void stringToEntry(string s, Entry& e)
{
	int sSize = s.length(), lowerBound = 0, upperBound, dummyV;
	bool commaOne = false, commaTwo = false;
	string subString;
	for (int i = 0; i < sSize; i++)
	{
		if ((s[i] == ',') && (commaOne != true))
		{
			commaOne = true;
			upperBound = i;
			subString = s.substr(lowerBound, upperBound - lowerBound);
			lowerBound = ++upperBound;
			dummyV = atoi(subString.c_str());
			e.county_state_code = dummyV;
		}
		else if ((s[i] == ',') && (commaTwo != true) && (commaOne == true))
		{
			commaTwo = true;
			upperBound = i;
			subString = s.substr(lowerBound, upperBound - lowerBound);
			lowerBound = upperBound + 2;
			dummyV = atoi(subString.c_str());
			e.population = dummyV;
		}
		if ((s[i] == '\"') && (commaOne && commaTwo))
		{
			upperBound = i;
			subString = s.substr(lowerBound, upperBound - lowerBound);
			e.county_state_name = subString;
		}
	}
}