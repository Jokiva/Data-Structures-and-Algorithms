#include "AVLTree.hpp"
#include <vector>

int main() {
	vector<int> vec{ 23, 3, 57, 7, 43, 25, 42, 32, 4, 27, 24, 42 };
	// vector<int> vec{ 23, 3, 57, 7, 43, 25, 42, 32 };
	AVLTree<int> AVLT;

	// insertion test
	for (auto x : vec) {
		AVLT.insert(x);
	}

	AVLT.print();

	// looking-up functions
	cout << AVLT.contains(27) << endl;
	cout << AVLT.contains(2) << endl;

	cout << AVLT.find_max() << endl;
	cout << AVLT.find_min() << endl;

	// remove test
	cout << endl;
	AVLT.remove(4);
	AVLT.remove(0);
	AVLT.print();

	// AVLT.remove(0);
	// AVLT.print();

	system("pause");
	return 0;
}