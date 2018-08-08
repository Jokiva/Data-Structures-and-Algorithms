#include "../lib/Network.hpp"
#include <fstream>
using namespace std;

int main() {
	ifstream input("../test/network_test.txt");

	try {
		Graph* n = new Network_Vertix{ 7 , input};
		cout << endl;
	}

	catch (const std::exception& exp) {
		cout << exp.what() << endl;
	}

	system("pause");
	return 0;
}