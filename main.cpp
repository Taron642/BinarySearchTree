#include <iostream>
#include "BinaryTree.h"

int main()
{
	BinaryTree<int> tree;

	tree.insertR(20);
	tree.insertI(10);
	tree.insertR(30);
	tree.insertR(9);
	tree.insertI(15);
	tree.insertR(16);
	tree.insertR(7);
	tree.insertI(25);
	tree.insertI(7);
	tree.insertR(15);

	std::cout << "tree findR 55: " << std::boolalpha << tree.findR(55) << std::endl;
	std::cout << "tree findI 55: " << std::boolalpha << tree.findI(55) << std::endl;
	std::cout << "tree findR 15: " << std::boolalpha << tree.findR(15) << std::endl;
	std::cout << "tree findI 15: " << std::boolalpha << tree.findI(15) << std::endl;
	std::cout << "tree findR -5: " << std::boolalpha << tree.findR(-5) << std::endl;
	std::cout << "tree findI -5: " << std::boolalpha << tree.findI(-5) << std::endl;

	std::cout <<"\npreorder recoursive: ";
	tree.preorderR();

	std::cout << "\npreorder iterative:  ";
	tree.preorderI();

	std::cout << "\ninorder recoursive: ";
	tree.inorderR();

	std::cout << "\ninorder iterative:  ";
	tree.inorderI();

	std::cout << "\npostorder recoursive: ";
	tree.postorderR();

	std::cout << "\npostorder iterative:  ";
	tree.postorderI();

	std::cout << "\nlevelorder iterative:  ";
	tree.levelorder();

	std::cout << "\nCount of Nodes: " << tree.countOfNodesR();
	std::cout << "\nCount of Leaves: " << tree.countOfLeavesR();

	std::cout << "\nHeightR of Tree: " << tree.heightR();
	std::cout << "\nHeightI of Tree: " << tree.heightI();

	std::cout << "\nWidthI of Tree: " << tree.widthI();
	std::cout << "\nWidthR of Tree: " << tree.widthR();

	std::cout << "\nMax of Tree: " << tree.findMaxI();
	std::cout << "\nMin of Tree: " << tree.findMinR();

	std::cout << "\ndeleting 7 15 20" << std::endl;
    

	tree.eraseI(7);
	tree.eraseR(15);
	tree.eraseR(20);
	tree.eraseI(15);


	std::cout << "\ninorder recoursive after deleting nodes: ";
	tree.inorderR();

	std::cout << "\nlevelorder iterative:  ";
	tree.levelorder();

	tree.clearR();

	std::cout << "\npostorder after clearing: ";
	tree.postorderR();



	return 0;

}
