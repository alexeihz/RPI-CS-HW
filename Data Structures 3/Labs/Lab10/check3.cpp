#include <iostream>
#include <iomanip>
 
class Node {
public:
    Node(int value) : value(value), left(NULL), right(NULL) {}
    int value;
    Node* left;
    Node* right;
};
 
bool shape_match(Node* a, Node* b)
{
    if (!a && !b) return true;
 
    if (a && b)
        return (shape_match(a->left, b->left) && shape_match(a->right, b->right));
 
    return false;
}
 
Node* find_subtree_match(Node* a, Node* v){
	if(!a){
		return NULL;
	}
	if(shape_match(a,v)){
		return a;
	}
	else{
		if(find_subtree_match(a-> right, v) != NULL){
			return find_subtree_match(a-> right, v);
			
		}
		else if(find_subtree_match(a->left,v) !=NULL){
			
			return find_subtree_match(a->left,v);
		}
		else{
			return NULL;
		}
	}
	
}
 
void print(Node* p, int indent)
{
    if(p)
    {
        if(p->right) print(p->right, indent+4);
        if (indent) std::cout << std::setw(indent) << ' ';
 
        if (p->right) std::cout <<" /\n" << std::setw(indent) << ' ';
        std::cout << p->value << "\n ";
 
        if(p->left)
        {
            std::cout << std::setw(indent) << ' ' <<" \\\n";
            print(p->left, indent+4);
        }
    }
}
 
int main()
{
    Node* test = new Node(1);
    test->left = new Node(2);
    test->right = new Node(3);
    test->left->left = new Node(4);
    test->left->right = new Node(5);
    test->right->left = new Node(6);
    test->right->right = new Node(7);
    printf("Tree 1\n");
    print(test, 0);
    printf("\n\n");
 
    Node* test2 = new Node(10);
    test2->left = new Node(20);
    test2->right = new Node(30);
    test2->left->left = new Node(40);
    test2->left->right = new Node(50);
    test2->right->left = new Node(60);
    test2->right->right = new Node(70);
    printf("Tree 2\n");
    print(test2, 0);
    printf("\n\n");
 
    Node* test3 = new Node(10);
    test3->left = new Node(20);
    test3->right = new Node(30);
    test3->left->right = new Node(50);
    test3->right->left = new Node(60);
    printf("Tree 3\n");
    print(test3, 0);
    printf("\n\n");
	
	
	Node* test4 = new Node(1);
    test4->left = new Node(2);
    test4->right = new Node(3);
    printf("Tree 4\n");
    print(test4, 0);
    printf("\n\n");
 
    printf("1 & 2 match: %d\n", shape_match(test, test2));
    printf("2 & 3 match: %d\n\n", shape_match(test2, test3));
 
    Node* v = find_subtree_match(test, test4);
	
    printf("Node w/ values: val1: %d, val2: %d", test4->value, v->value);
	printf("\n");
 
}