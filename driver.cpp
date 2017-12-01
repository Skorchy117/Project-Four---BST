#include <iostream>
#include <string>
#include "AVLTree.h"
using namespace std;

int main()
{
	typedef Entry E;
	/*SearchTree t;
	E asdf;
	E newData(50, 200, "CA");
	t.insert(newData);
	E newestData(21, 300, "LA");
	t.insert(newestData);
	E elements;
	BinaryTree::Position test;
	E newestData_two(55, 700, "SD");
	E newestData_three(55, 451, "OH");
	t.insert(newestData_two);
	t.insert(newestData_three);
	SearchTree::Iterator it(t.begin());
	for (it; it != t.end(); ++it)
	{
		asdf = *it;
		asdf.printData();
	}*/
	AVLTree newTree;
	E newestDataz(5, 10, "asdf");
	newTree.insert(newestDataz);
	E newData(3, 300, "fadsf");
	newTree.insert(newData);
	E newestData_three(2, 451, "OH");
	E uno(4, 322, "asdf");
	E dos(1, 123, "asdf");
	newTree.insert(newestData_three);
	newTree.insert(uno);
	newTree.insert(dos);
	SearchTree::Iterator it(newTree.begin());
	E output;
	for (it; it != newTree.end(); ++it)
	{
		output = *it;
		output.printData();
	}
	return 0;


}