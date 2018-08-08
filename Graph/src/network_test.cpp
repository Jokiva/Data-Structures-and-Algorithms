#include "../lib/Network.hpp"
#include <fstream>
#include <vector>
using namespace std;

int main() {
	ifstream input("../test/network_test.txt");

	try {
		Network* n = new Network_Vertix{ 7 , input};
		cout << endl;

		// indegree test
		vector<size_t> indegrees = n->get_indegree();
		for (auto x : indegrees) {
			cout << x << endl;
		}
		cout << endl << n->get_indegree(3) << endl << endl;

		// outdegree test
		vector<size_t> outdegrees = n->get_outdegree();
		for (auto x : outdegrees) {
			cout << x << endl;
		}
		cout << endl << n->get_outdegree(3) << endl << endl;
	}

	catch (const std::exception& exp) {
		cout << exp.what() << endl;
	}

	system("pause");
	return 0;
}