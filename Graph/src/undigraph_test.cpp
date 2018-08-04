#include "..\lib\Undigraph.hpp"
#include <vector>


int main() {
	try {
		typedef Undigraph_List Undigraph;
		Undigraph g{ 4 };

		vector<size_t> indegree = g.get_indegree();
		for (auto x : indegree)
			cout << x << " ";
		cout << endl;
	}
	
	catch (exception& exp) {
		cout << exp.what() << endl;
	}

	system("pause");
	return 0;
}
