#pragma once
#include <vector>
using namespace std;


// base class for all graphs
class Graph {
public:
	Graph(size_t vernum)
		: vertix_num{ vernum } {

	}

	~Graph() {

	}

	virtual bool init(size_t vernum, istream& input) = 0;
	virtual bool clear() = 0;

protected:
	const size_t vertix_num;
};
