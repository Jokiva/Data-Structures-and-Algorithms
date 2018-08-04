#pragma once
#include "AVLNode.hpp"
#include <stdexcept>
#include <iostream>
#include <algorithm>
using namespace std;


template <typename T>
class AVLTree {
public:
	AVLTree()
		:root{ nullptr } {

	}

	AVLTree(const AVLTree& rhs)
		: root{ nullptr } {
		root = clone(rhs.root);
	}

	AVLTree(AVLTree && rhs) : root{ rhs.root } {
		rhs.root = nullptr;
	}

	~AVLTree() {
		clear();
	}

	AVLTree& operator=(AVLTree& rhs) {
		AVLTree copy = rhs;
		std::swap(*this, copy);
		return *this;
	}

	AVLTree& operator=(AVLTree&& rhs) {
		std::swap(root, rhs.root);
		return *this;
	}

	const T& find_max() const {
		if (is_empty()) {
			throw underflow_error("the tree is empty\n");
		}

		return find_max(root)->element;
	}

	const T& find_min() const {
		if (is_empty()) {
			throw overflow_error("the tree is empty\n");
		}

		return find_min(root)->element;
	}

	bool contains(const T& x) const {
		return contains(x, root);
	}

	bool is_empty() const {
		if (root == nullptr) {
			return true;
		}

		else {
			return false;
		}
	}

	void print() const {
		if (is_empty()) {
			cout << "empty tree" << endl;
		}

		else {
			print(root);
		}
	}

	void clear() {
		clear(root);
	}

	void insert(const T& x) {
		insert(x, root);
	}

	void insert(const T&& x) {
		insert(move(x), root);
	}

	void remove(const T& x) {
		remove(x, root);
	}

private:
	static const int ALLOWED_IMBALANCE = 1;
	AVLNode<T>* root;
	int max(int lhs, int rhs) {
		return lhs > rhs ? lhs: rhs;
	}

	void insert(const T& x, AVLNode<T>*& t) {
		if (t == nullptr) {
			t = new AVLNode<T>{ x, nullptr, nullptr };
		}

		else if (x < t->element) {
			insert(x, t->left);
		}

		else {
			insert(x, t->right);
		}

		balance(t);
	}

	void insert(T&& x, AVLNode<T>*& t) {
		if (t == nullptr) {
			t = new AVLNode<T>*{ move(x), nullptr, nullptr };
		}

		else if (x < t->element) {
			insert(move(x), t->left);
		}

		else {
			insert(move(x), t->right);
		}
	}

	void remove(const T& x, AVLNode<T>*& t) {
		// empty tree or not found
		if (t == nullptr) {
			return;
		}

		// searching for the node
		if (x < t->element) {
			remove(x, t->left);
		}

		else if (x > t->element) {
			remove(x, t->right);
		}

		// node found
		else {
			// two children
			if ((t->left != nullptr) && t->right != nullptr) {
				t->element = find_min(t->right)->element;
				remove(t->element, t->right);
			}

			else {
				AVLNode<T>* old = t;
				t = (t->left != nullptr) ? t->left : t->right;
				delete old;
			}
		}

		balance(t);
	}

	// balance a specific node
	void balance(AVLNode<T>*& t) {
		if (t == nullptr) {
			return;
		}

		// left tree unbalanced
		if ((height(t->left) - height(t->right)) > ALLOWED_IMBALANCE) {
			// case one, single rotation
			if (height(t->left->left) >= height(t->left->right)) {
				single_rotate_left_child(t);
			}

			else {
				double_rotate_left_child(t);
			}
		}

		else if ((height(t->right) - height(t->left)) > ALLOWED_IMBALANCE) {
			if (height(t->right->right) >= height(t->right->left)) {
				single_rotate_right_child(t);
			}

			else {
				double_rotate_right_child(t);
			}
		}

		t->height = max(height(t->left), height(t->right)) + 1;
	}

	AVLNode<T>* find_max(AVLNode<T>* t) const {
		if (t == nullptr) {
			return nullptr;
		}

		else {
			if (t->right == nullptr) {
				return t;
			}

			else {
				return find_max(t->right);
			}
		}
	}

	AVLNode<T>* find_min(AVLNode<T>* t) const {
		if (t == nullptr) {
			return nullptr;
		}

		else {
			if (t->left == nullptr) {
				return t;
			}

			else {
				return find_min(t->left);
			}
		}
	}

	bool contains(const T& x, AVLNode<T>* t) const {
		if (t == nullptr) {
			return false;
		}

		else {
			if (x < t->element) {
				return contains(x, t->left);
			}

			else if (x > t->element) {
				return contains(x, t->right);
			}

			else {
				return true;
			}
		}
	}

	void clear(AVLNode<T>* t) {
		if (t != nullptr) {
			clear(t->left);
			clear(t->right);
			delete t;
		}

		t = nullptr;
	}

	void print(AVLNode<T>* t) const {
		if (t != nullptr) {
 			print(t->left);
			cout << t->element << endl;
			print(t->right);
		}
	}

	void single_rotate_left_child(AVLNode<T>*& k2) {
		// modify bindings
		AVLNode<T>* k1 = k2->left;
		k2->left = k1->right;
		k1->right = k2;

		// modify heights
		k2->height = max(height(k2->left), height(k2->right)) + 1;
		k1->height = max(height(k1->left), k2->height) + 1;

		k2 = k1;
	}

	void single_rotate_right_child(AVLNode<T>*& k1) {
		// modify bingings
		AVLNode<T>* k2 = k1->right;
		k1->right = k2->left;
		k2->left = k1;

		// modify heights
		k1->height = max(height(k1->left), height(k1->right)) + 1;
		k2->height = max(height(k2->right), k1->height) + 1;

		k1 = k2;
	}

	void double_rotate_left_child(AVLNode<T>*& k3) {
		single_rotate_right_child(k3->left);
		single_rotate_left_child(k3);
	}

	void double_rotate_right_child(AVLNode<T>*& k1) {
		single_rotate_left_child(k1->right);
		single_rotate_right_child(k1);
	}
};