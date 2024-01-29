//Node.h

#ifndef NODE_H
#define NODE_H

//class for Node
template <class T>
class Node {
	public:
		Node() : up(NULL), down(NULL), left(NULL), right(NULL) {}
	
		Node<T> *up, *down, *left, *right;
		T value;
};

#endif