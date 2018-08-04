#pragma once
template <typename T>
struct AVLNode {
	T element;
	AVLNode<T>* left;
	AVLNode<T>* right;
	int height;

	// constructors
	AVLNode(const T& e, AVLNode<T>* l, AVLNode<T>* r, int h = 0)
		: element{ e }, left{ l }, right{ r }, height{ h } {

	}

	AVLNode(T&& e, AVLNode<T>* l, AVLNode<T>* r, int h = 0)
		: element{ std::move(e) }, left{ l }, right{ r }, height{ h } {

	}
};

template<typename T>
int height(AVLNode<T>* t) {
	if (t == nullptr) {
		return -1;
	}

	else {
		return t->height;
	}
}