//This file is just used for the main. It makes our main much easier to read, because we just use this class to 
//carry out all functions of our project.

#include "BeginProgram.h"

BeginProgram::BeginProgram()
{
	fillTree(mahogany, oak, "p4Large.txt");
}

void BeginProgram::start()
{
	Entry ent;
	cout << "success!\n\n";
	int option;
	char optionTwo;
	do
	{
		cout << "Select A to work with Search Tree and B to work with AVL Tree (AVLTree will be selected if did not choose A or B): ";
		cin >> optionTwo;
		if (toupper(optionTwo) == 'A')
		{
			cout << "You are in the BST Tree\n";
			option = menu();
			if ((option != 5) && (option != 0)) // If option is 0, will just rerun the loop, only 5 will terminate this
			{
				performAction(mahogany, option);
			}
		}
		else
		{
			cout << "You are in the AVL Tree\n";
			option = menu();
			if ((option != 5) && (option != 0)) // If option is 0, will just rerun the loop, only 5 will terminate this
			{
				performAction(oak, option);
			}
		}
	} while (option != 5);
}
void BeginProgram::fillTree(SearchTree st, AVLTree at, string fileName)
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
			st.insert(E);
			at.insert(E);
		}
	}
	else
		cout << "Incorrect file name passed or does not exist.\n";
	infile.close();
}
void BeginProgram::stringToEntry(string s, Entry &e)
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

int BeginProgram::menu()
{
	string input;
	char inputAsChar;
	cout << "1. Search for a record\n2. Insert a record\n3. Delete a record\n4. List all records\n5. Exit\n";
	cout << "input: ";
	cin >> input;
	inputAsChar = input[0];
	switch (inputAsChar)
	{
	case '1':
		return 1;
		break;
	case '2':
		return 2;
		break;
	case '3':
		return 3;
		break;
	case '4':
		return 4;
	case '5':
		return 5;
	default:
		return 0;
	}
}
void BeginProgram::performAction(AVLTree& tree, int _case)
{
	int countySC, population;
	string name;
	if (_case == 1)
	{
		cout << "You chose to search for a record, enter a county-state-code: ";
		cin >> countySC;
		SearchTree::Iterator found = tree.find(countySC);
		Entry element = *found;
		cout << endl;
		if (element.county_state_code != 0)
		{
			cout << left << setw(20) << "county state code" << setw(20) << "population" << setw(20) << left << "county state name";
			cout << endl;
			cout << "----------------------------------------------------------------------------\n";
			element.printData();
			cout << endl << endl;

			int runTime = tree.findDepth(countySC);
			cout << "RunTime: " << runTime << " milli-seconds" << endl;
		}
		else cout << "No data found" << endl;
		cout << endl;
	}
	if (_case == 2)
	{
		cout << "You chose to insert a record\n";
		cout << "Enter county-state-code: ";
		cin >> countySC;
		cout << "Enter population: ";
		cin >> population;
		cout << "Enter the state/county name: ";
		cin.ignore();
		getline(cin, name);
		Entry element(countySC, population, name);
		tree.insert(element);
		int runTime = tree.findDepth(countySC);
		cout << "RunTime: " << runTime << " milli-seconds" << endl;
		cout << "Succesfully entered your record\n";
	}
	if (_case == 3)
	{
		cout << "You chose to delete a record\n";
		cout << "Enter which record you would like to delete by county-state-code: ";
		cin >> countySC;
		int runTime = tree.findDepth(countySC);
		cout << endl;
		cout << "\nRunTime: " << runTime << " milli - seconds\n" << endl << endl;
		tree.erase(countySC);
	}
	if (_case == 4)
	{
		SearchTree::Iterator it(tree.begin());
		Entry output;
		setfill(" ");
		myFile.open("AVLoutput.txt");
		cout << left << setw(20) << "county state code" << setw(20) << "population" << setw(20) << left << "county state name" << endl;
		cout << "----------------------------------------------------------------------------\n";
		myFile << left << setw(20) << "county state code" << setw(20) << "population" << setw(20) << left << "county state name" << endl;
		myFile << "----------------------------------------------------------------------------\n";
		for (it; it != tree.end(); ++it)
		{
			output = *it;
			countySC = output.getCode();
			population = output.getPop();
			name = output.getName();
			cout << left << setw(20) << countySC << setw(20) << population << setw(15) << left << name << right << endl;
			myFile << left << setw(20) << countySC << setw(20) << population << setw(15) << left << name << right << endl;
		}
		myFile.close();
		cout << endl;
	}
}
void BeginProgram::performAction(SearchTree& tree, int _case)
{
	int countySC, population;
	string name;
	if (_case == 1)
	{
		cout << "You chose to search for a record, enter a county-state-code: ";
		cin >> countySC;
		SearchTree::Iterator found = tree.find(countySC);
		Entry element = *found;
		cout << endl;
		if (element.county_state_code != 0)
		{
			cout << left << setw(20) << "county state code" << setw(20) << "population" << setw(20) << left << "county state name";
			cout << endl;
			cout << "----------------------------------------------------------------------------\n";
			element.printData();
			cout << endl << endl;

			int runTime = tree.findDepth(countySC);
			cout << "RunTime: " << runTime << " milli - seconds" << endl;
		}
		else cout << "No data found" << endl;
		cout << endl;
	}
	if (_case == 2)
	{
		cout << "You chose to insert a record\n";
		cout << "Enter county-state-code: ";
		cin >> countySC;
		cout << "Enter population: ";
		cin >> population;
		cout << "Enter the state/county name: ";
		cin.ignore();
		getline(cin, name);
		Entry element(countySC, population, name);
		tree.insert(element);
		int runTime = tree.findDepth(countySC);
		cout << "\nRunTime: " << runTime << " milli - seconds\n" << endl;
		cout << "Succesfully entered your record\n";
	}
	if (_case == 3)
	{
		cout << "You chose to delete a record\n";
		cout << "Enter which record you would like to delete by county-state-code: ";
		cin >> countySC;
		int runTime = tree.findDepth(countySC);
		cout << endl;
		cout << "RunTime: " << runTime << " milli - seconds" << endl << endl;
		tree.erase(countySC);
	}
	if (_case == 4)
	{
		SearchTree::Iterator it(tree.begin());
		Entry output;
		setfill(" ");
		cout << endl;
		myFile.open("BSToutput.txt");
		cout << left << setw(20) << "county state code" << setw(20) << "population" << setw(20) << left << "county state name" << endl;
		cout << "----------------------------------------------------------------------------\n";
		myFile << left << setw(20) << "county state code" << setw(20) << "population" << setw(20) << left << "county state name" << endl;
		myFile << "----------------------------------------------------------------------------\n";
		for (it; it != tree.end(); ++it)
		{
			output = *it;
			countySC = output.getCode();
			population = output.getPop();
			name = output.getName();
			cout << left << setw(20) << countySC << setw(20) << population << setw(15) << left << name << right << endl;
			myFile << left << setw(20) << countySC << setw(20) << population << setw(15) << left << name << right << endl;
		}
		myFile.close();
		cout << endl;
	}
}
