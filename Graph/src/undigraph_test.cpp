#include "..\lib\Undigraph.hpp"
#include <vector>


int main() {
	try {
		typedef Undigraph_List Undigraph;
		Undigraph g{ 4 };

		vector<size_t> degree = g.get_degree();
		for (auto x : degree)
			cout << x << " ";
		cout << endl;
	}
	
	catch (exception& exp) {
		cout << exp.what() << endl;
	}

	system("pause");
	return 0;
}
