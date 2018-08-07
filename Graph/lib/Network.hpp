#pragma once
#include "Graph.h"
#include <list>
#include <iostream>
using namespace std;

class Network : public Graph {
public:
	Network(size_t vernum)
		: Graph(vernum) {
		
	}

	~Network() {

	}
};


struct Vertix {
	size_t index;
	list<Path*> adj_list;

};


struct Path {
	size_t next;
	int weight;
};


class Network_Vertix : public Network {
public:
	Network_Vertix(size_t vernum, istream& input)
		: Network(vernum) {
		init(input);
	}

	~Network_Vertix() {

	}

	bool init(istream& input) {
		vertices.resize(vertix_num);
		return true;
	}

	bool clear() {
		return true;
	}

private:
	vector<Vertix> vertices;
};