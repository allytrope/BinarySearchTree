#include <iostream>
using namespace std;

class Node {
public:
	Node* left;
	Node* right;
	int val;
};

//cur_node starts at root
void insertNode(Node* cur_node, int value) {
	if (cur_node == NULL) {
		Node* new_node;
		new_node = new Node();//adds new node to heap
		new_node->left = NULL;
		new_node->right = NULL;
		new_node->val = value;
		return;
	}
	if (value < cur_node->val) {
		//creates new left node
		if (cur_node->left == NULL) {
			Node* new_node;
			new_node = new Node();
			new_node->val = value;
			cur_node->left = new_node;
		}
		//recursively calls left node
		else {
			insertNode(cur_node->left, value);
		}
	}
	else {
		//creates new right node
		if (cur_node->right == NULL) {
			Node* new_node;
			new_node = new Node();
			new_node->val = value;
			cur_node->right = new_node;
		}
		//recursively calls right node
		else {
			insertNode(cur_node->right, value);
		}
	}
}

//returns rightmost node
//used in findBeforePred()
Node* secondrightmost(Node* nd) {
	if (nd->right->right == NULL) {
		return nd;
	}
	else {
		Node* pred = secondrightmost(nd->right);
		return pred;
	}
}

//returns parent of predecessor of node
//used in deleteNode()
Node* findBeforePred(Node* node) {
	//checks if predecessor exists
	if (node->left == NULL) {
		cout << "No predecessor" << endl;
		return NULL;
	}
	//checks if root is parent of predecessor
	else if (node->left->right == NULL) {
		return node;
	}
	else {
		return secondrightmost(node->left);
	}
}

Node* findParent(Node * root, int value) {
	if (root->left != NULL) {
		if (root->left->val == value) {
			return root;
		}
	}
	if (root->right != NULL) {
		if (root->right->val == value) {
			return root;
		}
	}
	if (root->val < value) {
		findParent(root->right, value);
	}
	else {
		findParent(root->left, value);
	}
}

void deleteNode(Node* root, Node* node) {
	//for if predecessor doesn't exist
	if (node->left == NULL) {
		//this is for when the node is a leaf
		if (node->right == NULL) {
			//finds a node whose child is the deleted node and changes its link
			Node* parent = findParent(root, node->val);
			if (parent->right == node) {
				parent->right = NULL;
			}
			else {
				parent->left = NULL;
			}
			node->val = NULL;
			node = NULL;
			delete node;
		}
		else {
			cout << "Predecessor required for this assignment." << endl;
		}
	}
	//for if the left child is the predecessor
	else if (node->left->right == NULL) {
		node->val = node->left->val;
		Node* tmp = node->left;
		node->left = node->left->left;
		delete tmp;
	}
	else {
		Node* beforePred = findBeforePred(node);
		Node* pred = beforePred->right;
		node->val = pred->val; //copy predecessor's value to the node whose value is being deleted
		beforePred->right = pred->left; //link around the predecessor
		delete pred; //delete the predecessor
	}
}

//finds node to be passed to deleteNode function
Node* findNode(Node* root, int value) {
	if (root->val == value) {
		return root;
	}
	if (root->val < value) {
		findNode(root->right, value);
	}
	else {
		findNode(root->left, value);
	}
}

//starts at root
void inOrderTrav(Node *node) {
	if (node == NULL) {
		return;
	}
	inOrderTrav(node->left);
	cout << node->val << endl;
	inOrderTrav(node->right);
	}

int main() {
	//values to be inserted into tree
	int array[15] = { 50, 40, 80, 20, 45, 60, 100, 70, 65, 42, 44, 30, 25, 35, 33 };

	//constructs tree
	Node root;
	Node* ptr = &root;
	ptr->val = array[0];
	ptr->left = NULL;
	ptr->right = NULL;
	for (int x = 1; x < 15; x++) {
		insertNode(ptr, array[x]);
	}

	cout << "In-order traversal of tree: " << endl;
	inOrderTrav(ptr);

	//deletes the root, which is 50
	deleteNode(ptr, ptr);
	cout << "\nIn-order traversal after deleting root: " << endl;
	inOrderTrav(ptr);

	//deletes node 40
	Node* nextDeleted = findNode(ptr, 40);
	deleteNode(ptr, nextDeleted);
	cout << "\nIn-order traversal after deleting 40: " << endl;
	inOrderTrav(ptr);

	//deletes node 65
	nextDeleted = findNode(ptr, 65);
	deleteNode(ptr, nextDeleted);
	cout << "\nIn-order traversal after deleting 65: " << endl;
	inOrderTrav(ptr);

	//deletes node 35
	nextDeleted = findNode(ptr, 35);
	deleteNode(ptr, nextDeleted);
	cout << "\nIn-order traversal after deleting 35: " << endl;
	inOrderTrav(ptr);

	return 0;
}