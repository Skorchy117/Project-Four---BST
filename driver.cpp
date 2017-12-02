#include <iostream>
#include <string>
#include "AVLTree.h"
using namespace std;

int main()
{
	typedef Entry E;
	AVLTree newTree;
	E uno(20, 1, "asdf");
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
	for (it; it != newTree.end(); ++it)
	{
		output = *it;
		output.printData();
	}
	return 0;


}