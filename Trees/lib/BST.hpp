#include <iostream>
using namespace std;

template <typename T>
class BST {
public:
	// constructor
	BST() {

	}
	// copy constructor
	BST(const BST& rhs) {
		root = clone(rhs.root);
	}
	// right value reference copy constructor
	BST(BST&& rhs) {
		root = clone(rhs.root);
	}
	// destructor
	~BST() {
		clear();
	}

	// find the max value in a BST
	const T find_max() const {
		return find_max(root)->element;
	}
	
	// find the min value in a BST
	const T find_min() const {
		return find_min(root)->element;
	}

	// check if a value is contained in a BST
	bool contains(const T& x) const {
		return contains(x, root);
	}

	// check is the BST is empty
	bool is_empty() const {
		if ((root->left == nullptr) && (left->right == nullptr)) {
			return true;
		}

		else {
			return false;
		}
	}
	
	// print the BST to an ostream, default is cout
	void print(ostream& out = cout) const {
		print_help(root, out);
	}
	
	// clear all elements in the BST
	void clear() {
		clear(root);
	}
	
	// insert an element
	void insert(const T& x) {
		insert(x, root);
	}
	
	// insert an element right value reference
	void insert(T&& x) {
		insert(x, root);
	}
	
	// remove a element
	void remove(const T& x) {
		remove(x, root);
	}

	// overloaded assignment operator
	BST& operator=(const BST& rhs) {
		return BST(rhs);
	}
	
	// overloaded assignment operator
	BST& operator=(BST&& rhs) {
		return BST(move(rhs));
	}

private:
	// node type for BST
	struct Node {
		T element;
		Node* left;
		Node* right;

		// constructor
		Node(const T& e, Node* l, Node* r)
			: element{ e }, left{ l }, right{ r } {

		}

		Node(T&& e, Node* l, Node* r)
			: element{ move(e) }, left{ l }, right{ r } {

		}
	};


	Node* root;


	void insert(const T& x, Node*& t) {
		if (t == nullptr) {
			t = new Node{ x, nullptr, nullptr };
			return;
		}

		if (x < t->element) {
			insert(x, t->left);
		}

		else {
			insert(x, t->right);
		}
	}
	
	void insert(T&& x, Node*& t) {
		if (t == nullptr) {
			t = new Node{ move(x), nullptr, nullptr };
		}

		if (x < t->element) {
			insert(move(x), t->left);
		}

		else if (x >= t->element) {
			insert(move(x), t->right);
		}
	}

	void remove(const T& x, Node*& t) {
		if (t == nullptr) {
			return;
		}

		// locate the node to remove
		if (x < t->element) {
			remove(x, t->left);
		}

		else if (x > t->element) {
			remove(x, t->right);
		}

		else {
			if ((t->left != nullptr) && (t->right != nullptr)) {
				t->element = find_min(t->right)->element;
				remove(t->element, t->right);
			}

			else {
				Node* old = t;
				t = (t->left != nullptr) ? t->left : t->right;
				delete old;
			}
		}
	}
	
	Node* find_max(Node* t) const {
		if (t != nullptr) {
			while (t->right != nullptr) {
				t = t->right;
			}
		}

		return t;
	}
	
	Node* find_min(Node* t) const {
		if (t == nullptr) {
			return nullptr;
		}

		if (t->left == nullptr) {
			return t;
		}

		return find_min(t->left);
	}
	
	bool contains(const T& x, Node* t) const {
		if (t == nullptr) {
			return false;
		}

		else if (x == t->element) {
			return true;
		}

		else if (x < t->element) {
			return contains(x, t->left);
		}

		else {
			return contains(x, t->right);
		}
	}
	
	void clear(Node*& t) {
		if (t != nullptr) {
			clear(t->left);
			clear(t->right);
			delete t;
		}

		t = nullptr;
	}
	
	void print_help(Node* t, ostream& out) const {
		if (t == nullptr) {
			return;
		}

		else {
			print_help(t->left, out);
			out << t->element << endl;
			print_help(t->right, out);
		}
	}
	
	Node* clone(Node* t) const {
		if (t == nullptr) {
			return nullptr;
		}

		else {
			return new Node{ t->element, clone(t->left), clone(t->right) };
		}
	}
};