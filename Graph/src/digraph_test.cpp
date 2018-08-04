#include "Digraph.hpp"
#include <iostream>
#include <vector>
using namespace std;


int main() {
	Digraph* g = new Digraph_List{ 4 };
	try {
		
		vector<size_t> degree;

		degree = g->get_indegree();
		for (auto x : degree)
			cout << x << endl;
		cout << endl;

		degree = g->get_outdegree();
		for (auto x : degree)
			cout << x << endl;
		cout << endl;

		vector<size_t> sort_result = g->top_sort();
		for (auto x : sort_result)
			cout << x << endl;
		cout << endl;

		vector<size_t> length = g->shortest_path(0);
		for (auto x : length)
			cout << x << endl;
		cout << endl;

		// Network_List* n = new Network_List{ 4 };
	}

	catch (exception& exp) {
		cout << exp.what() << endl;
	}

	delete g;
	system("pause");
	return 0;
}
