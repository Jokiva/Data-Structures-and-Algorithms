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


class Vertix {
private:
	size_t index;
	list<Path*> adj_list;

public:
	Vertix(size_t i, const vector<size_t>& nodes, const vector<int>& w)
		: index{ i } {
		for (size_t i = 0; i < nodes.size(); ++i) {
			adj_list.push_back(new Path(nodes[i], w[i]));
		}
	}
};


class Path {
private:
	size_t next;
	int weight;

public:
	Path(size_t n, int w)
		: next{ n }, weight{ w } {

	}
};


class Network_Vertix : public Network {
public:
	Network_Vertix(size_t vernum, istream& input=cin)
		: Network(vernum) {
		init(input);
	}

	~Network_Vertix() {
		clear();
	}

	bool init(istream& input) {
		vertices.resize(vertix_num);
		
		for (size_t i = 0; i < vertix_num; ++i) {
			// Vertix& curr_vertix = vertices[i];
			size_t outdegree;
			input >> outdegree;
			
			vector<size_t> nodes;
			nodes.resize(outdegree);
			vector<int> w;
			w.resize(outdegree);

			for (size_t j = 0; j < outdegree; ++j) {
				input >> nodes[j];
				input.ignore();
				input >> w[j];
			}

			vertices[i] = new Vertix(i, nodes, w);
		}
		return true;
	}

	bool clear() {
		for (auto& x : vertices) {
			delete x;
		}

		return true;
	}

private:
	vector<Vertix*> vertices;
};