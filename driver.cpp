#include <iostream>
#include <string>
#include "SearchTree.h"
using namespace std;

int main()
{
    /* Hey anthony i'm adding this code through updates and what not... via terminal. */
	typedef Entry E;
	SearchTree t;
	E asdf;
	E newData(50, 200, "CA");
	t.insert(newData);
	E newestData(21, 300, "LA");
	t.insert(newestData);
	E elements;
	BinaryTree::Position test;
	E newestData_two(55, 700, "SD");
	E newestData_three(71, 451, "OH");
	t.insert(newestData_two);
	t.insert(newestData_three);
	SearchTree::Iterator it(t.begin());
	for (it; it != t.end(); ++it)
	{
		asdf = *it;
		asdf.printData();
	}
	return 0;
}