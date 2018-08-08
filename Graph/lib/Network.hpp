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

	virtual vector<size_t> get_indegree() const = 0;

	virtual size_t get_indegree(size_t end) const = 0;

	virtual vector<size_t> get_outdegree() const = 0;

	virtual size_t get_outdegree(size_t out) const = 0;

};


class Path {
	friend class Vertix;
	friend class Network_Vertix;

private:
	size_t next;
	int weight;

public:
	Path(size_t n, int w)
		: next{ n }, weight{ w } {

	}
};


class Vertix {
	friend class Network_Vertix;

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

	vector<size_t> get_indegree() const {
		vector<size_t> indegrees(vertix_num);

		for (const Vertix* curr_vertix : vertices) {
			for (const Path* curr_path : curr_vertix->adj_list) {
				++indegrees[curr_path->next];
			}
		}

		return indegrees;
	}

	size_t get_indegree(size_t end) const {
		return get_indegree()[end];
	}

	vector<size_t> get_outdegree() const {
		vector<size_t> outdegrees(vertix_num);

		for (size_t i = 0; i < vertix_num; ++i) {
			outdegrees[i] = vertices[i]->adj_list.size();
		}

		return outdegrees;
	}

	size_t get_outdegree(size_t start) const {
		return vertices[start]->adj_list.size();
	}

private:
	vector<Vertix*> vertices;
};