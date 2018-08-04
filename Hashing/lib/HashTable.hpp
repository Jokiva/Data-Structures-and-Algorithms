#include <vector>
#include <list>
#include <algorithm>
#include <functional>
using namespace std;


template <typename T=int>
class HashTable {
public:
	explicit HashTable(int size = 101)
		: curr_size{ 0 } {
		the_lists.resize(size);
	}

	~HashTable() {
		clear();
	}
	
	bool contains(const T& x) const {
		auto& which_list = the_lists[my_hash(x)];
		return find(which_list.begin(), which_list.end(), x) != which_list.end();
	}


	void clear() {
		for (auto& this_list : the_lists) {
			this_list.clear();
		}
	}

	bool insert(const T& x) {
		auto& which_list = the_lists[my_hash(x)];
		if (find(which_list.begin(), which_list.end(), x) != which_list.end()) {
			return false;
		}

		which_list.push_back(x);
		++curr_size;
		return true;
	}

	bool insert(T&& x) {
		auto& which_list = the_lists[my_hash(x)];
		auto iter = find(which_list.begin(), which_list.end(), std::move(x));

		if (iter != which_list.end()) {
			return false;
		}

		which_list.push_back(std::move(x));
		++curr_size;
		return true;
	}

	bool remove(const T& x) {
		auto& which_list = the_lists[my_hash(x)];
		auto iter = find(which_list.begin(), which_list.end(), x);

		if (iter == which_list.end()) {
			return false;
		}

		else {
			which_list.erase(iter);
			--curr_size;
			return true;
		}
	}

private:
	vector<list<T>> the_lists;
	int curr_size;

	void rehash();

	size_t my_hash(const T& x) const {
		static hash<T> hf;
		return hf(x) % the_lists.size();
	}
};


template <typename T>
class hash {
public:
	size_t operator()(const T& x) const;
};


size_t hash( int key )
{
    return key;
}