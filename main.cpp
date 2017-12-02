/*  Program: Project 4 - BST
 Author: Anthony Esmeralda, Kevin Ngo
 Class: CSCI 220
 Date:  Novemember 14, 2017
 Description: Binary Search Tree that uses an AVL tree search through records
 of county/state, population, and county/state name
 
 I certify that the code below is my own work.
 
 Exception(s): N/A
 */
#include <iostream>
#include <fstream>
#include <string>
#include "AVLTree.h"
using namespace std;

void fillAVLTree(AVLTree t, string fileName);
void stringToEntry(string s,Entry & e);
int menu();
void performAction(AVLTree& tree, int _case);

int main()
{
    cout << "Authors: Kevin Ngo & Anthony Esmeralda\n";
    cout << "Planting the AVL/BS tree(s).....";
    AVLTree oak;
    Entry ent;
    fillAVLTree(oak,"p4large.txt");
    cout << "success!\n";
    int option;
    do
    {
        option = menu();
        if ((option != 5) && (option != 0)) // If option is 0, will just rerun the loop, only 5 will terminate this
        {
            performAction(oak,option);
        }
    } while(option != 5);
    return 0;
}

void fillAVLTree(AVLTree t, string fileName)
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
    infile.close();
}

void stringToEntry(string s, Entry &e)
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

int menu()
{
    string input;
    char inputAsChar;
    cout << "1. Search for a record\n2. Insert a record\n3. Delete a record\n4. List all records\n5. Exit\n";
    cin >> input;
    inputAsChar = input[0];
    switch(inputAsChar)
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

void performAction(AVLTree& tree, int _case)
{
    int countySC, population;
    string name;
    if (_case == 1)
    {
        cout << "You chose to search for a record, enter a 
    }
}
