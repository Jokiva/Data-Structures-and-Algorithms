#pragma once
#include "Graph.h"
#include <vector>
#include <list>
#include <queue>
#include <set>
#include <stdexcept>
#include <iostream>
#include <algorithm>
using namespace std;


class Digraph : public Graph {
public:
	Digraph(size_t vernum)
		: Graph{ vernum } {

	}

	~Digraph() {

	}

	// get the indegree of each vertix
	virtual vector<size_t> get_indegree() const = 0;

	// get the indegree of a specific vertix

	// get the outdegree of each vertix
	virtual vector<size_t> get_outdegree() const = 0;

	// get the outdegree of a specific vertix

	// get a topological sorting result
	virtual vector<size_t> top_sort() const = 0;

	// find the shortest path from a vertix to each vertix
	virtual vector<int> shortest_path_length(size_t start) const = 0;

	// find the shortest path from a vertix to a specific one
	// virtual vector<size_t> shortest_path(size_t start, size_t end) const = 0;
};


class Digraph_List : public Digraph {
public:
	Digraph_List(size_t vernum, istream& input = cin)
		: Digraph{ vernum } {
		init(input);
	}

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

	vector<size_t> get_indegree() const {
		// first create the container
		vector<size_t> indegree(vertix_num);

		// traverse the adjacent list 
		// to get the indegree
		for (const auto& curr_list : the_graph)
			for (auto index : curr_list)
				++indegree[index];

		return indegree;
	}

	vector<size_t> get_outdegree() const {
		// first create the container
		vector<size_t> outdegree(vertix_num);

		// traverse the adjacent list 
		// to get the outdegree
		for (size_t i = 0; i < the_graph.size(); ++i) 
			outdegree[i] = the_graph[i].size();

		return outdegree;
	}

	vector<size_t> top_sort() const {
		// containetr of the sort result
		vector<size_t> sort_result(vertix_num);
		vector<size_t>::iterator iter = sort_result.begin();
		// queue to store current zero degree vertices
		queue<size_t> zero_indegree;
		// the indegrees of vertices
		vector<size_t> indegree = get_indegree();

		
		for (size_t i = 0; i < vertix_num; i++) {
			if (indegree[i] == 0) {
				zero_indegree.push(i);
			}
		}
				

		size_t i = 0;
		while (!zero_indegree.empty()) {
			size_t curr_front = zero_indegree.front();
			zero_indegree.pop();
			*iter = curr_front;
			++iter;
			++i;

			for (auto x : the_graph[curr_front])
				if (--indegree[x] == 0)
					zero_indegree.push(x);
		}

		if (i != vertix_num) {
			throw logic_error("at least loop is contained the the graph");
		}
		return sort_result;
	}

	vector<int> shortest_path_length(size_t start) const {
		// container for path from start to each vertix
		// list<size_t> path;

		// container for length of path from start to each vertix
		vector<int> length(vertix_num);
		// initialization step. length from start to start is set to zero
		// others are set to -1 to denote that there are no path
		for (size_t i = 0; i < vertix_num; ++i) {
			if (i == start) {
				length[i] = 0;
			}

			else {
				length[i] = -1;
			}
		}
		// a set will remember if a vertix is visited
		set<size_t> visited;
		
		// bredth first search, length of path or depth of layer
		// the worst case is that the graph degrades to a link
		// when the depth is the number of vertices
		for (size_t i = 0; i < vertix_num; ++i) {
			// traverse the graph, j is the vertic index for each run
			for (size_t j = 0; j < vertix_num; ++j) {
				// if vertix is not visited and in current layer
				if (visited.count(j) == 0 && length[j] == i) {
					// mark as visited
					visited.insert(j);
					// travers the adjacent list of current unvisited vertix
					auto& adj = the_graph[j];
					for (auto x : adj) {
						// if a vertix in the adjacent list is not visited
						// set the length of path and mark as visited
						if (visited.count(x) == 0) {
							length[x] = i + 1;
							visited.insert(x);
						}
					}
				}
			}
		}

		return length;
	}

private:
	typedef vector<list<size_t>> adj_list_graph;

	adj_list_graph the_graph;
	

	vector<size_t>::iterator find_zero(vector<size_t>& indegree) {
		return find(indegree.begin(), indegree.end(), 0);
	}
};


class Network_List : public Digraph_List {
public:
	Network_List(size_t vernum, istream& input)
		: Digraph_List(vernum, input) {
		;
	}

private:
	struct Adj_Vertix {
		size_t index;
		int weight;
	};

	vector<Adj_Vertix> the_network;
};
