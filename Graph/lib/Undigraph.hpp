#pragma once
#include "Graph.h"
#include <vector>
#include <list>
#include <stdexcept>
#include <iostream>
#include <cctype>
using namespace std;


class Undigraph : public Graph {
public:
	Undigraph(size_t vernum) 
		: Graph{ vernum } {
	}

	~Undigraph() {

	}

	// virtual bool init(size_t vernum, istream& input) = 0;
	// virtual bool clear() = 0;
};


// adjacent list representation of an undigraph 
// in a graph object itself
class Undigraph_List: public Undigraph{
public:
	// default constructor
	Undigraph_List(size_t vernum, istream& input=cin)
		: Undigraph{ vernum } {
		init(input);
	}

	~Undigraph_List() {
		
	}

	// read a adjacent list from an input
	bool init(istream& input) {
		the_graph.resize(vertix_num);

		// loop the read the adjacent list of each vertix
		for (size_t i = 0; i < vertix_num; ++i) {
			// get current
			auto& curr_list = the_graph[i];

			size_t cnt = 0;
			char buffer;


			while (true) {
				if (cnt >= vertix_num)
					throw logic_error("exceeds the limit of edges of a single vertix");

				cin >> buffer;
				if (isdigit(buffer)) {
					if ((size_t)buffer - 48 >= vertix_num)
						throw out_of_range("vertix index out of range");

					curr_list.push_back((size_t)buffer - 48);
					++cnt;
				}

				else
					break;
			}
		}

		// clear input buffer;
		input.clear();
		return true;
	}

	bool clear() {
		the_graph.clear();
		return true;
	}

	vector<size_t> get_degree() const {
		vector<size_t> degree(vertix_num);

		// traverse the adjacent list based graph 
		// and compute the indegrees
		for (const auto& curr_list : the_graph)
			for (const auto& index : curr_list)
				++degree[index];

		return degree;
	}

private:
	typedef vector<list<int>> adj_list_graph;

	adj_list_graph the_graph;
	// replaced in Graph base class
	// const size_t vertix_num;
};


// adjacent list representation of an undigraph 
// the sdjacent list is stored in a vertix
class Undigraph_Vertix : public Undigraph {
public:
	Undigraph_Vertix(size_t vernum, istream& input=cin)
		: Undigraph{ vernum } {
		init(input);
	}

	~Undigraph_Vertix() {
		
	}

	bool init(istream& input) {
		// change the size of vector storing the vertix info
		vertices.resize(vertix_num);

		for (size_t i = 0; i < vertix_num; ++i) {
			auto& curr_vertix = vertices[i];
			
			char buffer;
			size_t cnt = 0;
			list<size_t> the_adj_list;

			while (true) {
				if (cnt >= vertix_num)
					throw logic_error("exceeds the limit of edges of a single vertix");
				

				cin >> buffer;
				if (isdigit(buffer)) {
					the_adj_list.push_back((size_t)buffer - 48);
					++cnt;
				}

				else
					break;
			}

			curr_vertix = new Vertix(i, the_adj_list);
		}
		return true;
	}

	bool clear() {
		for (auto x : vertices) {
			delete x;
		}

		return true;
	}

	vector<size_t> get_degree() const {
		// create the container to hold degres
		vector<size_t> degrees(vertix_num);

		for (size_t i = 0; i < vertix_num; ++i) {
			degrees[i] = vertices[i]->adj_list.size();
		}

		return degrees;
	}

private:
	struct Vertix {
		size_t index;
		list<size_t> adj_list;

		Vertix(size_t the_index, list<size_t>& the_adj_list) {
			index = the_index;
			adj_list = the_adj_list;
		}
	};

	// stores the vertix info
	vector<Vertix*> vertices;
};