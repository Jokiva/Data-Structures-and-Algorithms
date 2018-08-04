#include "BST.hpp"
#include <vector>


int main() {
	BST<int> T;

	vector<int> v{ 6,2, 23, 23, 12, 6, 7, 12, 14, 34, 235, 34, 1 };

	for (auto x : v) {
		T.insert(x);
	}

	T.print();
	cout << endl << T.find_max() << endl;
	cout << endl << T.find_min() << endl;
	
	BST<int> T2 = T;
	T2.print();
	T2.remove(12);
	cout << endl << endl;
	T2.print();
	T.print();
	cout << T2.contains(999) << endl;
	
	
	system("pause");


	return 0;
}