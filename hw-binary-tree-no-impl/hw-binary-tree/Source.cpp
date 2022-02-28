#include "BinarySearchTree.h"

int main() 
{
	//testing tree construction, insert and report
	cout << "testing tree construction, insert and report" << endl;
	BinarySearchTree* tree = new BinarySearchTree();

	Employee tempEmployee = Employee(10, 19, "Zach");
	tree->insert(tempEmployee);

	tempEmployee = Employee(5, 18, "Zachariah Wilson");
	tree->insert(tempEmployee);

	tempEmployee = Employee(7, 20, "Zach W");
	tree->insert(tempEmployee);

	tempEmployee = Employee(1, 21, "Zach Wilson");
	tree->insert(tempEmployee);

	tempEmployee = Employee(13, 21, "Zach Wilson");
	tree->insert(tempEmployee);

	tempEmployee = Employee(11, 21, "Zach Wilson");
	tree->insert(tempEmployee);

	tree->report();

	std::cout << std::endl << std::endl;

	for (int i = 1; i <= 2; i++)
	{
		cout << "test number " << i << " of the tree." << endl;
		//testing remove method
		cout << "testing remove method" << endl;


		tree->find(11);
		tree->remove(11);
		tree->find(11);


		tree->report();

		std::cout << std::endl << std::endl;

		//testing the insert method
		cout << "testing the insert method" << endl;

		tree->find(11);
		tree->insert(tempEmployee);
		tree->find(11);


		tree->report();

		std::cout << std::endl << std::endl;

		//testing find min method
		cout << "testing find min method" << endl;

		Employee tempEmployee2 = tree->findMin();
		cout << "Employee Name: " << tempEmployee2.name << ", ID Number: " << tempEmployee2.id << ", Employee Age: " << tempEmployee2.age << endl;


		tree->report();

		std::cout << std::endl << std::endl;

		//testing find max method
		cout << "testing find max method" << endl;

		tempEmployee2 = tree->findMax();
		cout << "Employee Name: " << tempEmployee2.name << ", ID Number: " << tempEmployee2.id << ", Employee Age: " << tempEmployee2.age << endl;


		tree->report();

		std::cout << std::endl << std::endl;

		//testing the make empty method
		cout << "testing the make empty method" << endl;

		tree->makeEmpty();

		tree->report();

		std::cout << std::endl << std::endl;

		//testing the is empty method
		cout << "testing the is empty method" << endl << endl;

		if (tree->isEmpty())
			cout << "true";
		else
			cout << "false";

		std::cout << std::endl << std::endl;
	}
}