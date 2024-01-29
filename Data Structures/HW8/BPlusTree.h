/* ASSUMPTIONS:
1. When a node must be split and has an odd number of keys, the extra key will go to the new right-hand node.
2. There will never be a duplicate key passed to insert.
*/

#include <vector>
#include <typeinfo>
#include <cmath>
using namespace std;

#ifndef DS_BPLUSTREE
#define DS_BPLUSTREE

///////////////////////////////////////////////////////////////////////////////
//DO NOT CHANGE THIS CODE
///////////////////////////////////////////////////////////////////////////////

//Do not implement the class here, this is a forward declaration. Implement at
//the bottom of the .h file
template <class T> class BPlusTree; 

template <class T>
class BPlusTreeNode{
public:
	BPlusTreeNode() : parent(NULL) {};
	bool is_leaf();
	bool contains(const T& key);

	//For grading only. This is bad practice to have, because
	//it exposes a private member variable.
	BPlusTreeNode* get_parent() { return parent; } 

	//We need this to let BPlusTree access private members
	friend class BPlusTree<T>; 
private:
	bool contains(const T& key,std::size_t low,std::size_t high);
	std::vector<T> keys;
	std::vector<BPlusTreeNode*> children;
	BPlusTreeNode* parent;
};

template <class T>
bool BPlusTreeNode<T>::is_leaf(){
	for(unsigned int i=0; i<children.size(); i++){
		if(children[i]){
			return false;
		}
	}
	return true;
}

template <class T>
bool BPlusTreeNode<T>::contains(const T& key){
	return contains(key,0,keys.size()-1);
}

//Private method takes advantage of the fact keys are sorted
template <class T>
bool BPlusTreeNode<T>::contains(const T& key,std::size_t low,std::size_t high){
	if(low>high){
		return false;
	}
	if(low==high){
		return key == keys[low];
	}
	std::size_t mid = (low+high)/2;
	if(key<=keys[mid]){
		return contains(key,0,mid);
	}
	else{
		return contains(key,mid+1,high);
	}
}

///////////////////////////////////////////////////////////////////////////////////////
//Your BPlusTree implementation goes below this point.
///////////////////////////////////////////////////////////////////////////////////////

template <class T> class BPlusTree{
	public:
		BPlusTree() : root_(NULL), length_(0) {}
		BPlusTree(const BPlusTree<T>& old) :length_(old.length_), size_(old.size_){ 
			root_ = this->copy_tree(old.root_,NULL); 
		}
		void print_BFS(std::ofstream& outfile) const{
			print_BFS(outfile,root_);
			
		}
		~BPlusTree(){ 
			this->destroy_tree(root_);  
			root_ = NULL; 
		}
		BPlusTree& operator=(const BPlusTree<T>& old){
			if (&old != this){
				this->destroy_tree(root_);
				root_ = this->copy_tree(old.root_, old.root_->parent);
				length_ = old.length_;
				size_ = old.size_;
			}
			return *this;
		}
		BPlusTree(int b){
			this->create_tree(b-1);
		}
		void print_sideways(std::ofstream& outfile) const{
			print_sideways(outfile,root_,0);
		}
		
		BPlusTreeNode<T>* find(const T& key) const{
			return find(key, root_);
		}
		
		bool insert(const T& key){
			return insert(key, root_);
		}
		
		
		
	private:
		BPlusTreeNode<T>* root_;
		int size_;
		int length_;
		typename std::vector<BPlusTreeNode<T>* >::iterator itr;
		void print_BFS(std::ostream& ostr, BPlusTreeNode<T>* p){
			
		}
		
		BPlusTreeNode<T>* find(const T& key, BPlusTreeNode<T>* node){
			if(node){
				if((*node).keys().size() ==0){
					return NULL;
				}
				else{
					if((*node).isleaf()){ 
						if((*node).contains(key)){
							return node;
						}
					}
					if(!((*node).is_leaf())){
						bool up,down = false;
						unsigned num1,num2,i;
						
						while(i<(*node).keys().size()){
							if(key > (*node).keys[i] || key == (*node).keys[i] ){
								down = true;
								num2 = i;
								continue;
							}
							else{
								num1 = i;
								up=true;
								break;
							}
							i++
						}
						
						if(up == true){
							if(down == true){
								float num3 = float(num1 + num2)/2;
								if(num3 != ceil(float(num1 + num2)/2){
									num3 = ceil(num3);
								}
								return find(key, (*node).children[num3]);
							}
						}
						if(up == true){
							if(down != true){
								return find(key, (*node).children[0]);
							}
						}
						if(up != true){
							if(down == true){
								j=1;
								return find(key, (*node).children[(*node).children.size() - j]);
							}
						}
						if(up != true){
							if(down != true){
								return node;
							}
						}
					}
					else{
						return node;
					}
				}
			}
			else{
				return NULL;
			}
			
		}
		
		void print_sideways(std::ostream& ostr, const BPlusTreeNode<T>* p, int depth) const {
			if(depth ==0){
				if(!(p) || p-> keys.size() == 0){
					ostr << "Tree is empty.\n";
					return;
				}
			}
			if (p) {
				unsigned num =  floor(p->children.size()/2);
				int i = 0;
				while(i<num){
					print_sideways(ostr, p->children[i],depth+1);
					i++;
				}
				i = 0;
				while(i<depth){
					ostr<<"     "
					i++;
				}
				i =0;
				while(i<p->keys.size()){
					if(i==p->keys.size()-1){
						ostr << p->keys[i];
					}
					else{
						ostr << p->keys[i]<<",";
					}
				}
				ostr << "\n";
			}
			while(i < p-> children.size()){
				print_sideways(ostr, p->children[i],depth+1);
				i++;
			}
		}
		
		void destroy_tree(BPlusTreeNode<T>* node) {
			if (not(node)) return;
			int i =0;
			while(i<node->children){
				destroy_tree(node -> children[i]);
				i++;
			}
			delete node;
		}
		
		BPlusTreeNode<T>*  copy_tree(BPlusTreeNode<T>* old_root, BPlusTreeNode<T>* the_parent) {
		if (old_root == NULL){
		  return NULL;
		}
			BPlusTreeNode<T> *answer = new BPlusTreeNode<T>();
			answer->keys = old_root->keys;
			answer->children = old_root->children;
			answer->parent = old_root->the_parent;
			if(answer->is_leaf()){
				return answer;
			}
			else{
				for(unsigned int i = 0; i < answer->children.size(); i++){
					copy_tree(answer->children[i], answer);
				}
				return answer;
			}
			
		}
		/*
		void eraseParent(BPlusTreeNode<T>* save, BPlusTreeNode<T>* left, BPlusTreeNode<T>* right){
			typename vector<BPlusTreeNode<T>* >::iterator itr;
			itr = find(save->children.begin(), save->children.end(), node);
			itr = save->children.erase(itr);
			print_sideways(cout, root_, 0);
			
			itr = save->children.insert(itr, left);
			++itr;
			save->children.insert(itr, right);	
		}
		*/
		bool insert (const T& key, BPlusTreeNode<T>* & node){
			if(node->keys.size() < 1){
				node->keys.push_back(key);
				return true;
			}
			
			if(node-> is_leaf() && node->keys.size() != size_){
				bool bigger1,smaller1 = false;
				unsigned big,small;
				unsigned i =0;
				while(i<node->keys.size()){
					if(key < node->keys[i]){
						if(!smaller1){
							big = i;
							bigger1 = true;
							break;
						}
					}
					if(key > node->keys[i]){
						small = i;
						smaller1 = true;
						continue;
					}
					i++;
				}
				if(smaller1==true){
					if(bigger1==true){
						node -> keys.insert(node -> keys.begin() + big, key);
					}
				}
				if(smaller1==true){
					if(bigger1!=true){
						node -> keys.insert(node -> keys.end(), key);
					}
				}
				if(smaller1!=true){
					if(bigger1==true){
						node -> keys.insert(node -> keys.begin(), key);
					}
				}
				
				if(bigger1==true){
					return true;
				}
				else if(smaller1==true){
					return true;
				}
				else{
					return false;
				}
			}
			else if(node -> is_leaf() && node -> keys.size() == size_){
				vector<BPlusTreeNode<T>* temp_vec = node -> children;
				BPlusTreeNode<T>* keyTemp = node;
				//bool temp,temp2 = false;
				bool bigger, smaller = false;
				unsigned big1, small1;
				unsigned j = 0;
				while(j<keyTemp->keys.size()){
					if(key < keyTemp->keys[j]){
						if(!smaller){
							big1 = j;
							bigger = true;
							break;
						}
					}
					if(key > keyTemp->keys[j]){
						small1 = j;
						smaller = true;
						continue;
					}
					j++;
				}
				if(smaller==true){
					if(bigger==true){
						keyTemp -> keys.insert(keyTemp -> keys.begin() + big, key);
					}
				}
				else if(smaller==true){
					keyTemp -> keys.insert(keyTemp->keys.end(),key);
				}
				else{
					keyTemp -> keys.insert(keyTemp->keys.begin(),key);
				}
				
				vector<T> keyTemp2 = keyTemp -> keys;
				if(keyTemp2.size() > size_){
					
				}
				else if(keyTemp2.size() < size_ || keyTemp2.size() == size_){
					node->keys = keyTemp2;
					while(node->parent){
						node = node -> parent;
					}
					return node;
				}
				
				if(node -> is_leaf()){
					float num = keyTemp2.size()/2;
					if(floor(keyTemp2.size()/2) != num){
						num = floor(num);
					}
					BPlusTreeNode<T>* subRightTree = new BPlusTreeNode<T>;
					BPlusTreeNode<T>* subLeftTree = new BPlusTreeNode<T>;
					unsigned k = 0;
					while(k<keyTemp2.size()){
						if(k > num || k == num){
							(*subRightTree).keys().push_back(keyTemp2[k]);
						}
						if(k < num){
							(*subLeftTree).keys().push_back(keyTemp2[k]);
						}
						
					}
					if((*node).parent()){
						BPlusTreeNode<T> save = (*node).parent;
						subRightTree -> parent = save;
						subLeftTree -> parent = save;
						
						itr = find(save -> children.begin, save-> children.end(),node){
						itr = save -> children.erase(itr);
						itr = save -> children.insert(itr,subLeftTree);
						itr++;
						save -> children.insert(itr, subRightTree);
						}
					}
					
				}
				
				
				return true;
			}
		}
		
		void create_tree(int num){
			length_ = 1;
			root_ = new BPlusTreeNode<T>;
			size_ = num;
		}
};

#endif
