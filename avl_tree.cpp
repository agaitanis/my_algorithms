#include <iostream>
#include <functional>
#include <utility>
#include <vector>

#include "avl_tree.hpp"

using namespace std;
using std::placeholders::_1;

struct Node;

struct Node {
	Node(int key, int data) :
		key(key), data(data), left(NULL), right(NULL), ht(0), sz(1) {}

	int key;
	int data;
	struct Node* left;
	struct Node* right;
	int ht;
	int sz;
};

typedef pair<Node *, Node *> NodePair;

template <class Function> static void in_order_traversal(Node *x, Function fun)
{
	if (x == NULL) return;
	in_order_traversal(x->left, fun);
	fun(x);
	in_order_traversal(x->right, fun);
}

static void print_node(Node *x)
{
	printf("%d -> (%d, %d) [sz = %d]\n", x->key, x->left ? x->left->key : -1, x->right ? x->right->key : -1, x->sz);
}

static void print_tree(Node *x)
{
	in_order_traversal(x, print_node);
	printf("\n");
}

static int node_height(Node *x)
{
	if (x == NULL) return -1;
	return x->ht;
}

static int node_size(Node *x)
{
	if (x == NULL) return 0;
	return x->sz;
}

static void update_node_ht_sz(Node *x)
{
	x->ht = 1 + max(node_height(x->left), node_height(x->right));
	x->sz = 1 + node_size(x->left) + node_size(x->right);
}

static int node_balance(Node *x)
{
	if (x == NULL) return 0;
	return node_height(x->right) - node_height(x->left);
}

static Node *left_rotate(Node *x)
{
	Node *y = x->right;
	x->right = y->left;
	y->left = x;
	update_node_ht_sz(x);
	update_node_ht_sz(y);
	return y;
}

static Node *right_rotate(Node *x)
{
	Node *y = x->left;
	x->left = y->right;
	y->right = x;
	update_node_ht_sz(x);
	update_node_ht_sz(y);
	return y;
}

static Node *rebalance(Node *x)
{
	if (node_balance(x) < -1) {
		if (node_balance(x->left) > 0) {
			x->left = left_rotate(x->left);
		}
		return right_rotate(x);
	} else if (node_balance(x) > 1) {
		if (node_balance(x->right) < 0) {
			x->right = right_rotate(x->right);
		}
		return left_rotate(x);
	} else {
		return x;
	}
}

static Node *insert_node(Node *x, int key, int data = 0)
{
	if (x == NULL) return new Node(key, data);

	if (key < x->key) {
		x->left = insert_node(x->left, key, data);
	} else if (key > x->key) {
		x->right = insert_node(x->right, key, data);
	} else {
		return x;
	}

	update_node_ht_sz(x);
	x = rebalance(x);

	return x;
}

static Node *get_min_node(Node *x)
{
	while (x->left) {
		x = x->left;
	}
	return x;
}

static Node *get_max_node(Node *x)
{
	while (x->right) {
		x = x->right;
	}
	return x;
}

static Node *delete_node(Node *x, int key)
{
	if (x == NULL) return NULL;

	if (key < x->key) {
		x->left = delete_node(x->left, key);
	} else if (key > x->key) {
		x->right = delete_node(x->right, key);
	} else {
		if (x->left == NULL) {
			delete x;
			x = x->right;
		} else if (x->right == NULL) {
			delete x;
			x = x->left;
		} else {
			Node *temp = get_min_node(x->right);

			x->key = temp->key;
			x->data = temp->data;
			x->right = delete_node(x->right, temp->key);
		}
	}

	if (x == NULL) return NULL;

	update_node_ht_sz(x);
	x = rebalance(x);

	return x;
}

static Node *merge_with_root(Node *x, Node *y, Node *root)
{
	if (abs(node_height(x) - node_height(y)) <= 1) {
		root->left = x;
		root->right = y;
		update_node_ht_sz(root);
		return root;
	} else if (node_height(x) > node_height(y)) {
		x->right = merge_with_root(x->right, y, root);
		update_node_ht_sz(x);
		x = rebalance(x);
		return x;
	} else {
		y->left = merge_with_root(x, y->left, root);
		update_node_ht_sz(y);
		y = rebalance(y);
		return y;
	}
}

static Node *merge(Node *x, Node *y)
{
	if (x == NULL) return y;
	if (y == NULL) return x;

	Node *z = get_max_node(x);
	Node *root = new Node(z->key, z->data);

	x = delete_node(x, z->key);
	root = merge_with_root(x, y, root);

	return root;
}

static NodePair split(Node *root, int key)
{
	if (root == NULL) {
		return make_pair((Node *)NULL, (Node *)NULL);
	}

	NodePair p;
	Node *z;

	if (key <= root->key) {
		p = split(root->left, key);
		z = merge_with_root(p.second, root->right, root);
		return make_pair(p.first, z);
	} else {
		p = split(root->right, key);
		z = merge_with_root(root->left, p.first, root);
		return make_pair(z, p.second);
	}
}

static Node *nth_node(Node *x, int i)
{
	if (x == NULL) return NULL;

	int r = node_size(x->left);

	if (i == r) return x;

	if (i < r) {
		return nth_node(x->left, i);
	} else {
		return nth_node(x->right, i - r - 1);
	}
}

void test_avl_tree()
{
	Node *root = NULL;

	for (int i = 0; i < 8; i++) {
		root = insert_node(root, i);
	}
	
	print_tree(root);
}


