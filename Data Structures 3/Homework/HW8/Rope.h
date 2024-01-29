/*
You may add things to this .h file as needed. 
However keep in mind that Rope_provided.cpp will always be compiled in Submitty tests.
So you should not delete or change any methods that are implemented in Rope_provided.cpp
All your implementation should go in Rope_student.cpp
*/

#ifndef _ROPE_H
#define _ROPE_H

#include <string>
#include <vector>
#include <iostream>

class Node{
public:
	Node() : left{NULL}, right{NULL}, parent{NULL}, weight{0} {}
	Node* left;
	Node* right;
	Node* parent;
	int weight;
	std::string value;
};

class Rope;

class rope_iterator{
public:
	rope_iterator();
	rope_iterator(Node* p);
	rope_iterator& operator++();
	rope_iterator operator++(int);
	int weight() const;
	const std::string& value() const;
	friend class Rope;
	bool operator!=(const rope_iterator& it2) const;
private:
	Node* ptr_;
};

class Rope{
public:
	Rope();
	~Rope();
	Rope(Node* p);
	Rope(const Rope& r);
	Rope& operator= (const Rope& r);

	bool index(int i, char& c) const; //Get a single character
	void concat(const Rope& r); //Add the other string to me
	bool report(int i, int j, std::string& s) const; //Substring
	Rope& split(int i, Rope& rhs); //Split the string at index i into this (LHS) and a new Rope rhs
	
	int getSize(Node* root);
	int findLeaves(Node* p);
	Node* find_index(int &i);
	
	rope_iterator begin() const;
	rope_iterator end() const;

	int size() const;
	void print(std::ostream& out) const;
	void print_strings(std::ostream& out) const;
	Node* expose_root() const;

private:
	void print(std::ostream& out, Node* head, int depth) const;
private:
	int size_;
	Node* root;
	
	//Helper functions
	//destroy_tree from lecture notes
	void destroy_tree(Node* & p){
		if (!p) {
			p = NULL;
			size_ = 0;
			return;
		}

		destroy_tree(p->left);
		Node* tmp = p->right;
		delete p;
		p = NULL;
		destroy_tree(tmp);
	}
	//copy_tree from lecture notes
	Node* copy_tree(Node* old_root, Node* the_parent){
		if(old_root == NULL){
		  return NULL;
		}
		Node* temp_root = new Node;
		temp_root->value = old_root->value;
		temp_root->weight = old_root->weight;
		temp_root -> left = copy_tree(old_root->left,temp_root);
		temp_root -> right = copy_tree(old_root->right,temp_root);
		temp_root -> parent = the_parent;
		
		return temp_root;
	}
};

bool is_leaf(Node* p);

#endif