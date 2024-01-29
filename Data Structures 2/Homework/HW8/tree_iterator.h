#ifndef TREEITERATOR_H
#define TREEITERATOR_H

#include "tree_node.h"
#include "bidirectional_map.h"

template <class K, class V>
class tree_iterator {
	public:
		tree_iterator() : ptr_(NULL) {}
		tree_iterator(TreeNode<K,V>* p) : ptr_(p) {}
		tree_iterator(const tree_iterator<K,V>& old) : ptr_(old.ptr_) {}
		~tree_iterator() {}
		tree_iterator& operator=(const tree_iterator<K,V>& old) { ptr_ = old.ptr_;  return *this; }
		// operator* gives constant access to the value at the pointer
		const std::pair<K,V> operator*() const { return std::make_pair(ptr_->data, ptr_->link->data); }
		// comparions operators are straightforward
		bool operator== (const tree_iterator<K,V>& rgt) { return ptr_ == rgt.ptr_; }
		bool operator!= (const tree_iterator<K,V>& rgt) { return ptr_ != rgt.ptr_; }
			
		tree_iterator<K,V>& operator++();
		tree_iterator<K,V>& operator--();
		tree_iterator<K,V> operator++(int);
		tree_iterator<K,V> operator--(int);
		
		tree_iterator<V,K> follow_link(){ return tree_iterator<V,K>(ptr_->link);};
		
		TreeNode<K,V> *ptr(){ return ptr_;};
		
		template <class,class> friend class bidirectional_map;
	private:
		// representation
		TreeNode<K,V>* ptr_;
};

template <class K, class V>
tree_iterator<K,V>& tree_iterator<K,V>::operator++(){
	if (ptr_->right != NULL){
		ptr_ = ptr_->right;
		while (ptr_->left != NULL){
			ptr_ = ptr_->left; 
		}
    } else {
		while (ptr_->parent != NULL && ptr_->parent->left != ptr_){ 
			ptr_ = ptr_->parent; 
		}
		if(ptr_->parent == NULL){
			ptr_=NULL;
			return *this;
		}
		ptr_ = ptr_->parent;
	}
    return *this;
}

template <class K, class V>
tree_iterator<K,V>& tree_iterator<K,V>::operator--(){
	if (ptr_->left != NULL){ 
		ptr_ = ptr_->left;
		while (ptr_->right != NULL){
			ptr_ = ptr_->right; 
		}
    } 
	else {
		while (ptr_->parent != NULL && ptr_->parent->right != ptr_){ 
			ptr_ = ptr_->parent; 
		}
		if(ptr_->parent == NULL){
			ptr_=NULL;
			return *this;
		}
		ptr_ = ptr_->parent;
	}
    return *this;
}
	
template <class K, class V>
tree_iterator<K,V> tree_iterator<K,V>::operator--(int){
	tree_iterator<K,V> temp(*this);
	if (ptr_->left != NULL){ 
		ptr_ = ptr_->left;
		while (ptr_->right != NULL){
			ptr_ = ptr_->right; 
		}
    } 
	else {
		while (ptr_->parent != NULL && ptr_->parent->right != ptr_){ 
			ptr_ = ptr_->parent; 
		}
		if(ptr_->parent == NULL){
			ptr_ = NULL;
			return temp;
		}
		ptr_ = ptr_->parent;
	}
    return temp;
}

template <class K, class V>
tree_iterator<K,V> tree_iterator<K,V>::operator++(int){
	tree_iterator<K,V> temp(*this);
	if (ptr_->right != NULL){
		ptr_ = ptr_->right;
		while (ptr_->left != NULL){
			ptr_ = ptr_->left; 
		}
    } else {
		while (ptr_->parent != NULL && ptr_->parent->left != ptr_){ 
			ptr_ = ptr_->parent; 
		}
		if(ptr_->parent == NULL){
			ptr_ = NULL;
			return temp;
		}
		ptr_ = ptr_->parent;
	}
    return temp;
}
	
	


#endif