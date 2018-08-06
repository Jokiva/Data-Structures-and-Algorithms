#include "..\lib\Undigraph.hpp"
#include <vector>


int main() {
	try {
		// test implementation one
		// store the adjacent list in the graph itself
		typedef Undigraph_List Undigraph;
		Undigraph g{ 4 };

		vector<size_t> degree = g.get_degree();
		for (auto x : degree)
			cout << x << " ";
		cout << endl;

		// test implementation one
		// store the adjacent list in each vertix
		Undigraph_Vertix g2{ 4 };
		vector<size_t> degree2 = g.get_degree();
		for (auto x : degree2)
			cout << x << " ";
		cout << endl;
	}
	
	catch (exception& exp) {
		cout << exp.what() << endl;
	}

	system("pause");
	return 0;
}
