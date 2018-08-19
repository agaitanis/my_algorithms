#include <cstdio>
#include <iostream>
#include <queue>
#include <climits>

#include "binary_tree.hpp"


using namespace std;

TreeNode::TreeNode(int _data) :
	data(_data),
	left(NULL),
	right(NULL)
{
}

BinaryTree::BinaryTree() :
	m_root(NULL)
{
} /* BinaryTree::BinaryTree */

static void delete_tree_node(TreeNode *p_node, int d, void *data)
{
	printf("data = %d, d = %d\n", p_node->data, d); // alex
	delete p_node;
}

BinaryTree::~BinaryTree()
{
	level_order_traversal(delete_tree_node, NULL);
}

void BinaryTree::fill_for_test()
/* test tree:
 *              20
 *             /  \
 *           10    30
 *          /  \    \
 *         5    15   33
 *        /    / \   / \
 *       3    11 17 31 40
 *                     / \
 *                    35 43
 */
{
	TreeNode *node3 = new TreeNode(3);
	TreeNode *node5 = new TreeNode(5);
	TreeNode *node10 = new TreeNode(10);
	TreeNode *node11 = new TreeNode(11);
	TreeNode *node15 = new TreeNode(15);
	TreeNode *node17 = new TreeNode(17);
	TreeNode *node20 = new TreeNode(20);
	TreeNode *node30 = new TreeNode(30);
	TreeNode *node31 = new TreeNode(31);
	TreeNode *node33 = new TreeNode(33);
	TreeNode *node35 = new TreeNode(35);
	TreeNode *node40 = new TreeNode(40);
	TreeNode *node43 = new TreeNode(43);

	m_root = node20;
		node20->left = node10;
			node10->left = node5;
				node5->left = node3;
			node10->right = node15;
				node15->left = node11;
				node15->right = node17;
		node20->right = node30;
			node30->right = node33;
				node33->left = node31;
				node33->right = node40;
					node40->left = node35;
					node40->right = node43;
}

void BinaryTree::level_order_traversal(FOR_EVERY_TREE_NODE_FUN2 fun, void *data)
{
	queue<TreeNode *> nodes;
	queue<int>depths;
	TreeNode *p_node = m_root;
	int	d = 1;

	if (p_node) {
		nodes.push(p_node);
		depths.push(d);
	}

	while (!nodes.empty()) {
		p_node = nodes.front();
		nodes.pop();

		d = depths.front();
		depths.pop();

		fun(p_node, d, data);

		if (p_node->left) {
			nodes.push(p_node->left);
			depths.push(d+1);
		}
		if (p_node->right) {
			nodes.push(p_node->right);
			depths.push(d+1);
		}
	}
}

static void travel_pre_order_core(TreeNode *p_node, FOR_EVERY_TREE_NODE_FUN fun, void *data)
{
	if (!p_node) return;
	fun(p_node, data);
	travel_pre_order_core(p_node->left, fun, data);
	travel_pre_order_core(p_node->right, fun, data);
}

void BinaryTree::pre_order_traversal(FOR_EVERY_TREE_NODE_FUN fun, void *data)
{
	travel_pre_order_core(m_root, fun, data);
}

void travel_in_order_core(TreeNode *p_node, FOR_EVERY_TREE_NODE_FUN fun, void *data)
{
	if (!p_node) return;
	travel_in_order_core(p_node->left, fun, data);
	fun(p_node, data);
	travel_in_order_core(p_node->right, fun, data);
}

void BinaryTree::in_order_traversal(FOR_EVERY_TREE_NODE_FUN fun, void *data)
{
	travel_in_order_core(m_root, fun, data);
}

static void travel_post_order_core(TreeNode *p_node, FOR_EVERY_TREE_NODE_FUN fun, void *data)
{
	if (!p_node) return;
	travel_post_order_core(p_node->left, fun, data);
	travel_post_order_core(p_node->right, fun, data);
	fun(p_node, data);
}

void BinaryTree::post_order_traversal(FOR_EVERY_TREE_NODE_FUN fun, void *data)
{
	travel_post_order_core(m_root, fun, data);
}

static void travel_left_top_view(TreeNode *p_node, FOR_EVERY_TREE_NODE_FUN fun, void *data)
{
	if (!p_node) return;

	travel_left_top_view(p_node->left, fun, data);
	fun(p_node, data);
}

static void travel_right_top_view(TreeNode *p_node, FOR_EVERY_TREE_NODE_FUN fun, void *data)
{
	if (!p_node) return;

	fun(p_node, data);
	travel_right_top_view(p_node->right, fun, data);
}

void BinaryTree::travel_top_view(FOR_EVERY_TREE_NODE_FUN fun, void *data)
{
	if (!m_root) return;

	travel_left_top_view(m_root->left, fun, data);
	fun(m_root, data);
	travel_right_top_view(m_root->right, fun, data);
}

void calc_height_core(TreeNode *p_node, int *h, int *max_h)
{
	if (!p_node) return;

	(*h)++;
	if (*h > *max_h) *max_h = *h;

	calc_height_core(p_node->left, h, max_h);
	calc_height_core(p_node->right, h, max_h);

	(*h)--;
}

int BinaryTree::calc_height()
{
	int	h = 0;
	int	max_h = 0;

	calc_height_core(m_root, &h, &max_h);

	return max_h;
}

static void insert_node_core(TreeNode *p_node, int data)
{
	if (data == p_node->data) return;

	if (data < p_node->data) {
		if (p_node->left) {
			insert_node_core(p_node->left, data);
		} else {
			p_node->left = new TreeNode(data);
		}
	} else {
		if (p_node->right) {
			insert_node_core(p_node->right, data);
		} else {
			p_node->right = new TreeNode(data);
		}
	}
}

void BinaryTree::insert_node(int data)
{
	if (!m_root) {
		m_root = new TreeNode(data);
		return;
	}

	insert_node_core(m_root, data);
}

TreeNode *BinaryTree::lowest_common_ancestor(int data1, int data2)
{
	TreeNode *p_node = m_root;

	while (p_node) {
		if (data1 < p_node->data && data2 < p_node->data) {
			p_node = p_node->left;
		} else if (data1 > p_node->data && data2 > p_node->data) {
			p_node = p_node->right;
		} else {
			return p_node;
		}
	};

	return p_node;
}

void BinaryTree::fill_for_swap_nodes()
{
	queue<TreeNode *> nodes;
	int     n;

	m_root = new TreeNode(1);
	nodes.push(m_root);

	cin >> n;
	for (int i = 0; i < n; i++) {
		int     data1, data2;
		TreeNode *parent = nodes.front();

		nodes.pop();

		cin >> data1 >> data2;

		if (data1 != -1) {
			TreeNode *node = new TreeNode(data1);

			parent->left = node;
			nodes.push(node);
		}

		if (data2 != -1) {
			TreeNode *node = new TreeNode(data2);

			parent->right = node;
			nodes.push(node);
		}
	}
}

static void print_node(TreeNode *p_node, void *data)
{
	printf("%d ", p_node->data);
}

static void swap_node(TreeNode *p_node, int d, void *data)
{
	int	k = *(int *)data;

	if (d%k) return;

	swap(p_node->left, p_node->right);
}

void BinaryTree::swap_nodes()
{
	std::vector<int> ks;
	int     t;

	cin >> t;

	for (int i = 0; i < t; i++) {
		int     k;

		cin >> k;
		ks.push_back(k);
	}

	for (int i = 0; i < (int)ks.size(); i++) {
		int	k = ks[i];

		level_order_traversal(swap_node, &k);
		in_order_traversal(print_node, 0);
		printf("\n");
	}
}

static bool is_binary_search_subtree(TreeNode *x, int min_data, int max_data)
{
	if (x == NULL) return true;

	if (x->data <= min_data) return false;
	if (x->data >= max_data) return false;

	if (!is_binary_search_subtree(x->left, min_data, x->data)) return false;
	if (!is_binary_search_subtree(x->right, x->data, max_data)) return false;

	return true;
}

bool BinaryTree::is_binary_search_tree()
{
	return is_binary_search_subtree(m_root, -INT_MAX, INT_MAX);
}

void BinaryTreeTest()
{
	BinaryTree tree;

	tree.fill_for_test();
}

