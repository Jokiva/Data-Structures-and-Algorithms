#include "../lib/Network.hpp"


int main() {
	try {
		Graph* n = new Network_Vertix{ 7 };
	}

	catch (const std::exception& exp) {
		cout << exp.what() << endl;
	}
	system("pause");
	return 0;
}