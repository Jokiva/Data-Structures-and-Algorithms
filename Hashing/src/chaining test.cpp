#include "HashTable.hpp"
#include <iostream>
#include <vector>
using namespace std;


int main() {
	HashTable<> table(10);
	
	// vector<int> data{ 34, 52, 4, 5, 45, 46 };
	for (int i = 0; i < 10; ++i) {
		table.insert(i * i);
	}

	cout << table.contains(1) << endl;
	cout << table.contains(4) << endl;

	system("pause");
	return 0;
}