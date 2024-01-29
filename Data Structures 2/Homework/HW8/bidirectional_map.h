//bidirectional_map.h
#ifndef BIDIRECTIONALMAP_H
#define BIDIRECTIONALMAP_H

#include <iostream>
#include <cmath>
#include <list>
#include <iomanip>
#include "tree_iterator.h"
#include "tree_node.h"

template <class K, class V>
class bidirectional_map{
	public:
		typedef bidirectional_map<K,V> bdMap;
		typedef tree_iterator<K,V> key_iterator;
		typedef tree_iterator<V,K> value_iterator;
		
		bidirectional_map() : current_size(0), key_root_(NULL), val_root_(NULL) {}
		bidirectional_map(const bdMap &old);
		bdMap &operator=(const bdMap &old);
		~bidirectional_map();
		
		int size() const { return current_size; }
		bool operator==(const bdMap& old) const { return (old.key_root_ == this->key_root_ && old.val_root_ == this->val_root_); }
		
		key_iterator find(const K& key_value) { return findKey(key_value, key_root_); }
		value_iterator find(const V& val_value) { return findValue(val_value, val_root_); }
		int erase(const K &key_value);
		std::pair< tree_iterator<K,V>, bool > insert(const std::pair<K,V>& pair_value);
		K operator[](const V &val_value);
		V operator[](const K &key_value);
		
		key_iterator key_begin() const;
		key_iterator key_end() const;
		value_iterator value_begin() const;
		value_iterator value_end() const;
		
		void print(std::ostream &out) const;
		

		template <class,class> friend class tree_iterator;
	private:
		void copy_tree(const bdMap &old);
		void copy_tree_helper(TreeNode<K, V> *old_key, TreeNode<K, V> *&key_root, TreeNode<V, K> *&val_root);
		
		key_iterator findKey(const K &key, TreeNode<K, V> *p);
		value_iterator findValue(const V &value, TreeNode<V, K> *p);
		
		void destroy_tree(TreeNode<K, V> *key_root, TreeNode<V, K> *val_root);
		void destroy_key(TreeNode<K, V> *p);
		void destroy_value(TreeNode<V, K> *p);
		
		std::pair<tree_iterator<K, V>, bool> insertNode(const std::pair<K, V> &pair_value, TreeNode<K, V> *&key_root, TreeNode<V, K> *&value_root);
		std::pair<TreeNode<K, V> *, bool> insertKey(const K &key, TreeNode<K, V> *&p);
		std::pair<TreeNode<V, K> *, bool> insertValue(const V &value, TreeNode<V, K> *&p);
		
		void print_key_tree(std::ostream &ostr, const TreeNode<K, V> *p, int depth) const;
		void print_value_tree(std::ostream &ostr, const TreeNode<V, K> *p, int depth) const;
    
		int current_size;
		TreeNode<K,V> *key_root_;
		TreeNode<V,K> *val_root_;
};

template<class K, class V>
bidirectional_map<K,V>::bidirectional_map(const bdMap& old){
	current_size = old.current_size;
	this -> copy_tree(old);
}

template<class K, class V>
typename bidirectional_map<K, V>::bdMap& bidirectional_map<K, V>::operator=(const bdMap &old) {
    if (&old != this) {
        this->destroy_tree(key_root_, val_root_);
        this->copy_tree(old);
        current_size = old.current_size;
    }
    return *this;
}

template<class K, class V>
bidirectional_map<K, V>::~bidirectional_map() {
    this->destroy_tree(key_root_, val_root_);
    key_root_ = NULL;  val_root_ = NULL;
    current_size = 0;
}


template<class K, class V>
V bidirectional_map<K, V>::operator[](const K &target_key) {
    key_iterator pos = this->find(target_key);
    if (pos != this->key_end()){
        return (*pos).second;
    }else {
        return (*this->insert(std::make_pair(target_key, V())).first).second;
    }
}

template<class K, class V>
K bidirectional_map<K, V>::operator[](const V &target_value) {
    value_iterator pos = this->find(target_value);
    if (pos != this->value_end()) {
        return (*pos).second;
    }else {
        return (*this->insert(std::make_pair(K(), target_value)).first).first;
    }
}

template<class K, class V>
std::pair<tree_iterator<K, V>, bool> bidirectional_map<K, V>::insert(const std::pair<K, V> &pair_value) {
    if (current_size == 0){
        key_root_ = new TreeNode<K, V>(pair_value.first);
        val_root_ = new TreeNode<V, K>(pair_value.second);
        key_root_->link = val_root_; 
		val_root_->link = key_root_;
        ++current_size;
        return std::make_pair(tree_iterator<K, V>(key_root_), true);
    }else {
        return insertNode(pair_value, key_root_, val_root_);
    }
}

template<class K, class V>
int bidirectional_map<K, V>::erase(const K &target_key){
    key_iterator pos = find(target_key);
    if (pos == key_end()){ // do not have this key
        return 0;
    }else {
        TreeNode<K, V> *curr = pos.ptr(), *rmost;
        TreeNode<V, K> *curr2 = pos.ptr()->link, *rmosV;
        // delete the node in the key tree
        if (curr->left == NULL){ // curr does not have a left node, directly move its right node to curr
            if (curr->parent == NULL){ // curr is the root
                key_root_ = curr->right;
                if (key_root_) key_root_->parent = NULL;
                delete (curr);  curr = NULL;
            }else if (curr->parent->left == curr) { // curr is left node of its parent
                curr->parent->left = curr->right;
                if (curr->right != NULL) curr->right->parent = curr->parent;
                delete (curr);  curr = NULL;
            }else if (curr->parent->right == curr) { // curr is right node of its parent
                curr->parent->right = curr->right;
                if (curr->right != NULL) curr->right->parent = curr->parent;
                delete (curr);  curr = NULL;
            }
        }else { // curr does have a left node
            // find the right most node in curr's left tree
            rmost = curr->left;
            while (rmost->right != NULL)  rmost = rmost->right;
            // copy the data of the right most node to curr
            curr->data = rmost->data;
            curr->link = rmost->link;  curr->link->link = curr;
            // delete the right most node
            if (rmost != curr->left){
                rmost->parent->right = rmost->left;
                if (rmost->left != NULL) rmost->left->parent = rmost->parent;
                delete (rmost);  rmost = NULL;
            }else {
                rmost->parent->left = rmost->left;
                if (rmost->left != NULL) rmost->left->parent = rmost->parent;
                delete (rmost);  rmost = NULL;
            }
        }

        // delete the node in the value tree
        if (curr2->left == NULL){ // curr2 does not have a left node, directly move its right node to curr
            if (curr2->parent == NULL){ // curr2 is the root
                val_root_ = curr2->right;
                if (val_root_) val_root_->parent = NULL;
                delete (curr2);  curr2 = NULL;
            }else if (curr2->parent->left == curr2) { // curr2 is left node of its parent
                curr2->parent->left = curr2->right;
                if (curr2->right != NULL) curr2->right->parent = curr2->parent;
                delete (curr2);  curr2 = NULL;
            }else if (curr2->parent->right == curr2) { // curr2 is right node of its parent
                curr2->parent->right = curr2->right;
                if (curr2->right != NULL) curr2->right->parent = curr2->parent;
                delete (curr2);  curr2 = NULL;
            }
        }else { // curr2 does have a left node
            // find the right most node in curr2's left tree
            rmosV = curr2->left;
            while (rmosV->right != NULL)  rmosV = rmosV->right;
            // copy the data of the right most node to curr2
            curr2->data = rmosV->data;
            curr2->link = rmosV->link;  curr2->link->link = curr2;
            // delete the right most node
            if (rmosV != curr2->left) {
                rmosV->parent->right = rmosV->left;
                if (rmosV->left != NULL) rmosV->left->parent = rmosV->parent;
                delete (rmosV);  rmosV = NULL;
            }else {
                rmosV->parent->left = rmosV->left;
                if (rmosV->left != NULL) rmosV->left->parent = rmosV->parent;
                delete (rmosV);  rmosV = NULL;
            }
        }
        --current_size; return 1;
    }
}

template<class K, class V>
void bidirectional_map<K, V>::print(std::ostream &ostr) const {
    ostr << "=================================================\n";
    ostr << "KEYS:\n";
    print_key_tree(ostr, key_root_, 0);
    ostr << "-------------------------------------------------\n";
    ostr << "VALUES:\n";
    print_value_tree(ostr, val_root_, 0);
    ostr << "=================================================\n";
}

template<class K, class V>
typename bidirectional_map<K, V>::key_iterator bidirectional_map<K, V>::key_begin() const {
    if (!key_root_) return key_iterator(NULL);
    TreeNode<K, V> *p = key_root_;
    while (p->left) p = p->left;
    return key_iterator (p);
}

template<class K, class V>
typename bidirectional_map<K, V>::value_iterator bidirectional_map<K, V>::value_begin() const {
    if (!val_root_) return value_iterator (NULL);
    TreeNode<V, K> *p = val_root_;
    while (p->left) p = p->left;
    return value_iterator (p);
}

template<class K, class V>
typename bidirectional_map<K, V>::key_iterator bidirectional_map<K, V>::key_end() const {
    return key_iterator (NULL);
}

template<class K, class V>
typename bidirectional_map<K, V>::value_iterator bidirectional_map<K, V>::value_end() const {
    return value_iterator (NULL);
}

template<class K, class V>
void bidirectional_map<K, V>::copy_tree(const bdMap &old){
    if (old.size() != 0){
        copy_tree_helper(old.key_root_, key_root_, val_root_);
    }
}

template<class K, class V>
void bidirectional_map<K, V>::copy_tree_helper(TreeNode<K, V> *old_key, TreeNode<K, V> *&key_root, TreeNode<V, K> *&val_root){
    if (old_key != NULL) {
        insertNode(std::make_pair(old_key->data, old_key->link->data), key_root, val_root);
        copy_tree_helper(old_key->left,  key_root, val_root);
        copy_tree_helper(old_key->right, key_root, val_root);
    }
}

template<class K, class V>
typename bidirectional_map<K, V>::key_iterator bidirectional_map<K, V>::findKey(const K &key, TreeNode<K, V> *p) {
    if (!p) return key_iterator(NULL);
    if (p->data > key)
        return findKey(key, p->left);
    else if (p->data < key)
        return findKey(key, p->right);
    else
        return key_iterator(p);
}

template<class K, class V>
typename bidirectional_map<K, V>::value_iterator bidirectional_map<K, V>::findValue(const V &value, TreeNode<V, K> *p) {
    if (!p) return value_iterator(NULL);
    if (p->data > value)
        return findValue(value, p->left);
    else if (p->data < value)
        return findValue(value, p->right);
    else
        return value_iterator(p);
}

template<class K, class V>
void bidirectional_map<K, V>::destroy_tree(TreeNode<K, V> *key_root, TreeNode<V, K> *val_root){
    destroy_key(key_root);
    destroy_value(val_root);
    key_root_ = NULL;  val_root_ = NULL;  current_size = 0;
}

template<class K, class V>
void bidirectional_map<K, V>::destroy_value(TreeNode<V, K> *p) {
    if (p != NULL){
        destroy_value(p->left);
        destroy_value(p->right);
        delete p;  p = NULL;
    }
}

template<class K, class V>
void bidirectional_map<K, V>::destroy_key(TreeNode<K, V> *p) {
    if (p != NULL){
        destroy_key(p->left);
        destroy_key(p->right);
        delete p;  p = NULL;
    }
}


template<class K, class V>
std::pair<tree_iterator<K, V>, bool> bidirectional_map<K, V>::insertNode(const std::pair<K, V> &pair_value, TreeNode<K, V> *&key_root, TreeNode<V, K> *&value_root){
    key_iterator keyPos = findKey(pair_value.first, key_root);
    value_iterator valuePos = findValue(pair_value.second, value_root);
    if (keyPos == key_end() && valuePos == value_end()) { // there are no duplicates in keyTree and valueTree
        TreeNode<K, V> *p1 = insertKey(pair_value.first, key_root).first;
        TreeNode<V, K> *p2 = insertValue(pair_value.second, value_root).first;
        p1->link = p2;  p2->link = p1;
        return std::pair<key_iterator, bool>(tree_iterator<K, V>(p1), true);
    }else { // already have the same key or the same value
        return std::pair<key_iterator, bool>(keyPos, false);
    }
}

template<class K, class V>
std::pair<TreeNode<K, V> *, bool> bidirectional_map<K, V>::insertKey(const K &key, TreeNode<K, V> *&p) {
    if (!p) {
        p = new TreeNode<K, V>(key);
        this->current_size++;
        return std::make_pair(p, true);
    } else if (key < p->data){ // go to the left node
        if (p->left == NULL){
            p->left = new TreeNode<K, V>(key);
            p->left->parent = p;
            this->current_size++;
            return std::make_pair(p->left, true);
        }else {
            return insertKey(key, p->left);
        }
    } else if (key > p->data) { // go to the right node
        if (p->right == NULL){
            p->right = new TreeNode<K, V>(key);
            p->right->parent = p;
            this->current_size++;
            return std::make_pair(p->right, true);
        }else {
            return insertKey(key, p->right);
        }
    } else {// have the same value with the current node
        return std::make_pair(p, false);
    }
}

template<class K, class V>
std::pair<TreeNode<V, K> *, bool> bidirectional_map<K, V>::insertValue(const V &value, TreeNode<V, K> *&p) {
    if (!p) {
        p = new TreeNode<V, K>(value);
        return std::make_pair(p, true);
    } else if (value < p->data){ // go to the left node
        if (p->left == NULL){
            p->left = new TreeNode<V, K>(value);
            p->left->parent = p;
            return std::make_pair(p->left, true);
        }else {
            return insertValue(value, p->left);
        }
    } else if (value > p->data){ // go to the right node
        if (p->right == NULL){
            p->right = new TreeNode<V, K>(value);
            p->right->parent = p;
            return std::make_pair(p->right, true);
        }else {
            return insertValue(value, p->right);
        }
    } else { // have the same value with the current node
        return std::make_pair(p, false);
    }
}

template<class K, class V>
void bidirectional_map<K, V>::print_key_tree(std::ostream &ostr, const TreeNode<K, V> *p, int depth) const {
    if (p) {
        print_key_tree(ostr, p->right, depth + 1);
        for (int i = 0; i < depth; ++i) ostr << "    ";
        ostr << p->data << " [" << p->link->data << "]\n";
        print_key_tree(ostr, p->left, depth + 1);
    }
}

template<class K, class V>
void bidirectional_map<K, V>::print_value_tree(std::ostream &ostr, const TreeNode<V, K> *p, int depth) const {
    if (p) {
        print_value_tree(ostr, p->right, depth + 1);
        for (int i = 0; i < depth; ++i) ostr << "    ";
        ostr << p->data << " [" << p->link->data << "]\n";
        print_value_tree(ostr, p->left, depth + 1);
    }
}

#endif