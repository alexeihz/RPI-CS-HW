/*
Write your Rope implementation in this file. 
You do not have to keep any of the code that is already in this file.
Functions that are required that you have not implemented have an assert 0
meaning they will always crash. This should help you make sure you implement
everything.
*/

#include <cassert>
#include "Rope.h"
//finds all the leafs from a starting node in a list and adds their weights
//finds the leaves
int Rope::findLeaves(Node* p){
	if(!p){
		return 0;
	}
	
	if(is_leaf(p)){
		return p -> weight;
	}
	return findLeaves(p->left) + findLeaves(p->right);
}
//finds the index
Node* Rope::find_index(int &num){
	Node* temp = this->root;
	Node* temp2 = temp;
	while(is_leaf(temp)==false && temp!=NULL){
		if(num < temp->weight){
			temp = temp->left;
			temp -> parent = temp2;
			temp2 = temp;
		}
		else if(num >= temp->weight){
			num = num - temp->weight;
			temp = temp->right;
			temp -> parent = temp2;
			temp2 = temp;
		}		
		
	}
	return temp;
}
//gets the size by counting the weights of the right nodes 
int Rope::getSize(Node* root){
	int num=0;
	while(root != NULL){
		num = num + root->weight;
		root = root->right;
	}
	return num;
}

//Should advance to the next Node using in-order traversal
//It can point at any Node, not just leaves
rope_iterator& rope_iterator::operator++(){
	//assert(0 && "rope_iterator operator++ not implemented!");
	//operator++ from lecture
	
	 if (ptr_->right != NULL) { // find the leftmost child of the right node
      ptr_ = ptr_->right;
      while (ptr_->left != NULL) { ptr_ = ptr_->left; }
    } else { // go upwards along right branches...  stop after the first left
      while (ptr_->parent != NULL && ptr_->parent->right == ptr_) { ptr_ = ptr_->parent; }
      ptr_ = ptr_->parent;
    }
	
	return *this;
}

//Point to the first Node for in-order traversal
rope_iterator Rope::begin() const{
	//assert(0 && "rope_iterator begin() not implemented!");
	if (!root){
		return rope_iterator(NULL);
	}
	Node* p = root;
	while (p->left != NULL){
		p = p->left;
	}
    return rope_iterator(p);
}

Rope::Rope(){
	//assert(0 && "Rope default constructor not implemented!");
	root = NULL;
	size_ = 0;
}

//Should make the root = p and adjust any member variables
//This should not make a copy of the rope with root at p,
//it should just "steal" the Node*
Rope::Rope(Node* p){
	//assert(0 && "Rope constructor from Node not implemented!")
	root = p;
	root -> parent = NULL;
	size_ = getSize(root);
	
}

Rope::~Rope(){
	//assert(0 && "Rope destructor not implemented!");
	this->destroy_tree(root);
	root = NULL;
}

Rope::Rope(const Rope& r){
	//assert(0 && "Rope copy constructor not implemented!");
	root = this->copy_tree(r.root,r.root->parent);
	size_ = r.size_;
}

Rope& Rope::operator= (const Rope& r){
	// assert(0 && "Rope assignment not implemented!");
	if (&r != this) {
      this->destroy_tree(root);
      root = this->copy_tree(r.root,r.root->parent);
      size_ = r.size_;
    }
    return *this;
}

//MUST BE ITERATIVE
//Get a single character at index i
bool Rope::index(int i, char& c) const{
	//assert(0 && "Rope index() not implemented!");
	Node* temp = this->root;
	while(is_leaf(temp)==false && temp!=NULL){
		if(i < temp->weight){
			temp = temp->left;
		}
		if(i >= temp->weight){
			i = i - temp->weight;
			temp = temp->right;
		}		
	}
	if(temp == NULL){
		return false;
	}
	else{
		c = temp->value[i];
		return true;
	}
}

//Add the other rope (r)'s string to the end of my string
void Rope::concat(const Rope& r){
	//assert(0 && "Rope concat() not implemented!");
	Node* new_root = new Node;
	new_root -> parent = NULL;
	Node* right_copy = copy_tree(r.root,NULL);
	new_root -> left = this->root;
	new_root -> weight = findLeaves(new_root->left);
	new_root -> right = right_copy;
	right_copy-> parent  = new_root;
	this->root->parent = new_root;
	right_copy = new_root;
	this->root = new_root;
	size_ = getSize(new_root);
	
}

//Get a substring from index i to index j.
//Includes both the characters at index i and at index j.
//String can be one character if i and j match
//Returns true if a string was returned, and false otherwise
//Function should be written with efficient running time.
bool Rope::report(int i, int j, std::string& s) const{
	//assert(0 && "Rope report() not implemented!");
	std::string str = "";
	char c;
	if(i > j){
		return false;
	}
	//if(i <= j)
	else{
		int num = i;
		while(num <= j){
			if(index(num,c)){
				str = str + c;
			}
			else{
				return false;
			}
			num++;
		}
		s = str;
		return true;
	}
}

//The first i characters should stay in the current rope, while a new
//Rope (rhs) should contain the remaining size_-i characters.
//A valid split should always result in two ropes of non-zero length.
//If the split would not be valid, this rope should not be changed,
//and the rhs rope should be an empty rope.
//The return value should be this rope (the "left") part of the string
//This function should move the nodes to the rhs instead of making new copies.

Rope& Rope::split(int i, Rope& rhs){	
	// assert(0 && "Rope split() not implemented!");
	int num = i;
	int num2 = i;
	Node* temp2 = this->find_index(num2);
	Node* temp = this->find_index(num);
	if(temp == NULL){
		return *this;
	}
	else{
		//right = false
		//left = true
		bool direction;
		if(num==0){			
			//determines initial direction from leaf node
			if(temp -> parent -> left == temp){
				direction = true;
			}
			else if(temp -> parent -> right == temp){
				direction = false;
			}			
			std::vector <Node*> oof;
			oof.push_back(temp2);
			while(temp -> parent !=NULL){
				if((temp  ->parent ->right != NULL) && (temp  -> parent ->right == temp) && (direction == true)){
					//fills rhs
					if(temp -> parent -> left != NULL){
						oof.push_back(temp-> left->parent);
						Rope split2(temp -> parent -> left);
						Rope split1(temp2);
						split2.concat(split1);
						if(rhs.root == NULL && rhs.size_ == 0){
							rhs = split2;
						}
						else{
							rhs.concat(split2);
						}
					}
				}
				else if(temp -> parent -> left != NULL && temp -> parent -> left == temp && direction == false){
					//fills rhs
					if(temp -> parent -> right != NULL){
						oof.push_back(temp -> parent -> right);
						Rope split1(temp2);
						Rope split2(temp -> parent -> right );
						split1.concat(split2);
						rhs = split1;
					}
				}
				temp = temp -> parent;
			}
			//unlinks proper nodes from *this rope
			for(unsigned j = 0; j< oof.size(); j++){
				for(rope_iterator it = begin(); it!= end(); it++){
					if(it.ptr_ -> right != NULL && it.ptr_ -> right == oof[j]){						
						it.ptr_-> right = NULL;
						it.ptr_ -> weight = findLeaves(it.ptr_);
						break;
					}
					else if(it.ptr_ -> left != NULL && it.ptr_ -> left == oof[j]){
						it.ptr_-> left = NULL;
						it.ptr_ -> weight = findLeaves(it.ptr_);
						break;
					}
				}
			}
			this -> size_ = size_ - rhs.size();
			return *this;
		}
		
		else{
			//splits leaf node in *this rope
			Node* left_node = new Node;
			int num3 = i;
			Node* temp3 = this->find_index(num3);
			rope_iterator itr = begin();
			for(; itr!= end(); itr++){
				if(itr.ptr_ == temp3){
					break;
				}
			}
			left_node -> value = temp3 -> value.substr(0,num3);
			left_node -> weight = num3;
			Node* right_node = new Node;
			right_node -> value = temp3 -> value.substr(num3,std::string::npos);
			right_node -> weight = temp3 -> weight - num3;
			temp3 -> weight = num3;
			temp3 -> value = "";
			temp3 -> left = left_node;
			temp3 -> right = right_node;
			right_node -> parent = temp3;
			left_node -> parent = temp3;
			itr.ptr_ = temp3;
			
			int num = i;
			int num2 = i;
			temp2 = this->find_index(num2);
			temp = this->find_index(num);
			//determines initial direction from leaf node
			if(temp -> parent -> left == temp){
				direction = true;
			}
			else if(temp -> parent -> right == temp){
				direction = false;
			}			
			std::vector <Node*> oof;
			oof.push_back(temp2);
			while(temp -> parent !=NULL){
				if((temp  ->parent ->right != NULL) && (temp  -> parent ->right == temp) && (direction == true)){
					//fills rhs
					if(temp -> parent -> left != NULL){
						oof.push_back(temp-> left->parent);
						Rope split2(temp -> parent -> left);
						Rope split1(temp2);
						split2.concat(split1);
						if(rhs.root == NULL && rhs.size_ == 0){
							rhs = split2;
						}
						else{
							rhs.concat(split2);
						}
					}
				}
				else if(temp -> parent -> left != NULL && temp -> parent -> left == temp && direction == false){
					//fills rhs
					if(temp -> parent -> right != NULL){
						oof.push_back(temp -> parent -> right);
						
						Rope split1(temp2);
						Rope split2(temp -> parent -> right );
						split1.concat(split2);
						rhs = split1;
					}
				}
				temp = temp -> parent;
			}
			//unlinks proper nodes from *this rope
			for(unsigned j = 0; j< oof.size(); j++){
				for(rope_iterator it = begin(); it!= end(); it++){
					if(it.ptr_ -> right != NULL && it.ptr_ -> right == oof[j]){
						it.ptr_-> right = NULL;
						it.ptr_ -> weight = findLeaves(it.ptr_);
						break;
					}
					else if(it.ptr_ -> left != NULL && it.ptr_ -> left == oof[j]){
						it.ptr_-> left = NULL;
						it.ptr_ -> weight = findLeaves(it.ptr_);
						break;
					}
				}
			}
			this -> size_ = size_ - rhs.size();
			return *this;
		}
		
	}
	
}

