// TREE NODE CLASS 

#ifndef TREENODE_H
#define TREENODE_H

template <class K, class V>
class TreeNode {
	public:
	  TreeNode<K,V>() : left(NULL), right(NULL), parent(NULL), link(NULL) {}
	  TreeNode<K,V>(const K& init) : data(init), left(NULL), right(NULL), parent(NULL), link(NULL) {}
	  K data;
	  TreeNode<K,V>	*left,*right,*parent;
	  TreeNode<V,K> *link;
};
#endif