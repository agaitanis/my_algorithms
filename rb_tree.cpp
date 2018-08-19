#include <cstdio>
#include <iostream>
#include <vector>
#include <cassert>
#include <functional>
#include <unordered_set>
#include <queue>

#include "my_tools.hpp"
#include "rb_tree.hpp"

using namespace std;
using std::placeholders::_1;

enum RBColor {
	BLACK = 0,
	RED = 1
};


struct RBNode {
	RBNode(int key, RBNode *parent, RBNode *left, RBNode *right, RBColor color, size_t size) :
		key(key), parent(parent), left(left), right(right), color(color), size(size) {}

	int	key;
	RBNode	*parent;
	RBNode	*left;
	RBNode	*right;
	RBColor	color;
	size_t	size;
};

static RBNode *NullNode() 
{
	static RBNode *z = NULL;

	if (z == NULL) {
		z = new RBNode(0, NULL, NULL, NULL, BLACK, 0);
		z->parent = z;
		z->left = z;
		z->right = z;
	}

	return z;
}

class RBTree {
	public:
		RBTree();
		~RBTree();

		void insert(int key);
		void erase(int key);
		RBNode *find(int key);
		RBNode *find_recursive(int key);
		RBNode *get_min();
		RBNode *get_max();
		RBNode *get_next(RBNode *x);
		RBNode *get_prev(RBNode *x);
		size_t calc_size();
		size_t size();
		RBNode *nth_node(int i);
		size_t rank_of_node(RBNode *x);
		template <class Function> void in_order_traversal(Function fun);
		template <class Function> void pre_order_traversal(Function fun);
		template <class Function> void post_order_traversal(Function fun);
		template <class Function> void level_traversal(Function fun);

	private:
		void check_properties();
		void left_rotate(RBNode *x);
		void right_rotate(RBNode *y);
		void insert_fixup(RBNode *z);
		void erase_fixup(RBNode *x);
		void transplant(RBNode *u, RBNode *v);
		void increase_size_to_root(RBNode *y);
		void decrease_size_to_root(RBNode *y);

		RBNode	*m_root;
};

RBTree::RBTree() :
	m_root(NullNode())
{
}

RBTree::~RBTree()
{
	in_order_traversal(DeleteObject());
}

static size_t calc_size_recursive(RBNode *z)
{
	if (z == NullNode()) return 0;

	return 1 + calc_size_recursive(z->left) + calc_size_recursive(z->right);
}

size_t RBTree::calc_size()
{
	return calc_size_recursive(m_root);
}

size_t RBTree::size()
{
	return m_root->size;
}

static size_t calc_min_black_height(RBNode *z)
{
	if (z == NullNode()) return 0;

	int h = (z->color == BLACK) ? 1 : 0;

	return h + min(calc_min_black_height(z->left), calc_min_black_height(z->right));
}

static size_t calc_max_black_height(RBNode *z)
{
	if (z == NullNode()) return 0;

	int h = (z->color == BLACK) ? 1 : 0;

	return h + max(calc_max_black_height(z->left), calc_max_black_height(z->right));
}

template <class Function> static void pre_order_traversal_recursive(Function fun, RBNode *z)
{
	if (z == NullNode()) return;
	fun(z);
	pre_order_traversal_recursive(fun, z->left);
	pre_order_traversal_recursive(fun, z->right);
}

template <class Function> void RBTree::pre_order_traversal(Function fun)
{
	pre_order_traversal_recursive(fun, m_root);
}

template <class Function> static void post_order_traversal_recursive(Function fun, RBNode *z)
{
	if (z == NullNode()) return;
	post_order_traversal_recursive(fun, z->left);
	post_order_traversal_recursive(fun, z->right);
	fun(z);
}

template <class Function> void RBTree::post_order_traversal(Function fun)
{
	post_order_traversal_recursive(fun, m_root);
}

template <class Function> static void in_order_traversal_recursive(Function fun, RBNode *z)
{
	if (z == NullNode()) return;
	in_order_traversal_recursive(fun, z->left);
	fun(z);
	in_order_traversal_recursive(fun, z->right);
}

template <class Function> void RBTree::in_order_traversal(Function fun)
{
	in_order_traversal_recursive(fun, m_root);
}

template <class Function> void RBTree::level_traversal(Function fun)
/* Breadth First Search (BFS) */
{
	if (m_root == NullNode()) return;

	queue<RBNode *> q;

	q.push(m_root);

	while (!q.empty()) {
		RBNode *node = q.front();

		fun(node);

		q.pop();
		if (node->left != NullNode()) {
			q.push(node->left);
		}
		if (node->right != NullNode()) {
			q.push(node->right);
		}
	}
}

void RBTree::right_rotate(RBNode *y)
{
	RBNode *x = y->left;

	y->left = x->right;
	if (x->right != NullNode()) {
		x->right->parent = y;
	}

	x->parent = y->parent;
	if (y->parent == NullNode()) {
		m_root = x;
	} else if (y == y->parent->left) {
		y->parent->left = x;
	} else {
		y->parent->right = x;
	}

	x->right = y;
	y->parent = x;

	x->size = y->size;
	y->size = y->left->size + y->right->size + 1;
}

void RBTree::left_rotate(RBNode *x)
{
	RBNode *y = x->right;

	x->right = y->left;
	if (y->left != NullNode()) {
		y->left->parent = x;
	}

	y->parent = x->parent;
	if (x->parent == NullNode()) {
		m_root = y;
	} else if (x == x->parent->left) {
		x->parent->left = y;
	} else {
		x->parent->right = y;
	}

	y->left = x;
	x->parent = y;

	y->size = x->size;
	x->size = x->left->size + x->right->size + 1;
}

static RBNode *get_min_of_subtree(RBNode *z)
{
	while (z->left != NullNode()) {
		z = z->left;
	}

	return z;
}

RBNode *RBTree::get_min()
{
	return get_min_of_subtree(m_root);
}

static RBNode *get_max_of_subtree(RBNode *z)
{
	while (z->right != NullNode()) {
		z = z->right;
	}

	return z;
}

RBNode *RBTree::get_max()
{
	return get_max_of_subtree(m_root);
}

RBNode *RBTree::get_next(RBNode *x)
{
	if (x->right != NullNode()) {
		return get_min_of_subtree(x->right);
	} else {
		RBNode *y = x->parent;

		while (y != NullNode() && x == y->right) {
			x = y;
			y = y->parent;
		}

		return y;
	}
}

RBNode *RBTree::get_prev(RBNode *x)
{
	if (x->left != NullNode()) {
		return get_max_of_subtree(x->left);
	} else {
		RBNode *y = x->parent;

		while (y != NullNode() && x == y->left) {
			x = y;
			y = y->parent;
		}

		return y;
	}
}

void RBTree::increase_size_to_root(RBNode *y)
{
	while (y != NullNode()) {
		y->size++;
		y = y->parent;
	}
}

void RBTree::decrease_size_to_root(RBNode *y)
{
	while (y != NullNode()) {
		y->size--;
		y = y->parent;
	}
}

void RBTree::insert_fixup(RBNode *z)
{
	while (z->parent->color == RED) {
		if (z->parent == z->parent->parent->left) {
			if (z->parent->parent->right->color == RED) {
				z->parent->color = BLACK;
				z->parent->parent->right->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;
			} else {
				if (z == z->parent->right) {
					z = z->parent;
					left_rotate(z);
				}
				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				right_rotate(z->parent->parent);
			}
		} else {
			if (z->parent->parent->left->color == RED) {
				z->parent->color = BLACK;
				z->parent->parent->left->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;
			} else {
				if (z == z->parent->left) {
					z = z->parent;
					right_rotate(z);
				}
				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				left_rotate(z->parent->parent);
			}
		}
	}
	m_root->color = BLACK;
}

void RBTree::insert(int key)
{
	RBNode *z = new RBNode(key, NullNode(), NullNode(), NullNode(), RED, 1);
	RBNode *y = NullNode();
	RBNode *x = m_root;

	while (x != NullNode()) {
		y = x;
		if (z->key < x->key) {
			x = x->left;
		} else if (z->key > x->key) {
			x = x->right;
		} else {
			delete z;
			return;
		}
	}

	z->parent = y;
	if (y == NullNode()) {
		m_root = z;
	} else if (z->key < y->key) {
		y->left = z;
	} else {
		y->right = z;
	}

	increase_size_to_root(z->parent);
	insert_fixup(z);
	check_properties();
}

void RBTree::transplant(RBNode *u, RBNode *v)
{
	if (u->parent == NullNode()) {
		m_root = v;
	} else if (u == u->parent->left) {
		u->parent->left = v;
	} else {
		u->parent->right = v;
	}
	v->parent = u->parent;
}

void RBTree::erase_fixup(RBNode *x)
{
	while (x != m_root && x->color == BLACK) {
		if (x == x->parent->left) {
			RBNode *w = x->parent->right;

			if (w->color == RED) {
				w->color = BLACK;
				x->parent->color = RED;
				left_rotate(x->parent);
				w = x->parent->right;
			}
			if (w->left->color == BLACK && w->right->color == BLACK) {
				w->color = RED;
				x = x->parent;
			} else {
				if (w->right->color == BLACK) {
					w->left->color = BLACK;
					w->color = RED;
					right_rotate(w);
					w = x->parent->right;
				}
				w->color = x->parent->color;
				x->parent->color = BLACK;
				w->right->color = BLACK;
				left_rotate(x->parent);
				x = m_root;
			}
		} else {
			RBNode *w = x->parent->left;

			if (w->color == RED) {
				w->color = BLACK;
				x->parent->color = RED;
				right_rotate(x->parent);
				w = x->parent->left;
			}
			if (w->right->color == BLACK && w->left->color == BLACK) {
				w->color = RED;
				x = x->parent;
			} else {
				if (w->left->color == BLACK) {
					w->right->color = BLACK;
					w->color = RED;
					left_rotate(w);
					w = x->parent->left;
				}
				w->color = x->parent->color;
				x->parent->color = BLACK;
				w->left->color = BLACK;
				right_rotate(x->parent);
				x = m_root;
			}
		}
	}
	x->color = BLACK;
}

void RBTree::erase(int key)
{
	RBNode *z = find(key);

	if (z == NullNode()) return;

	RBNode *y = z;
	RBNode *x;
	RBColor init_color_y = y->color;

	if (z->left == NullNode()) {
		decrease_size_to_root(z->parent);
		x = z->right;
		transplant(z, z->right);
	} else if (z->right == NullNode()) {
		decrease_size_to_root(z->parent);
		x = z->left;
		transplant(z, z->left);
	} else {
		y = get_min_of_subtree(z->right);
		init_color_y = y->color;
		x = y->right;
		if (y->parent == z) {
			decrease_size_to_root(z->parent);
			x->parent = y;
		} else {
			decrease_size_to_root(y->parent);
			transplant(y, y->right);
			y->right = z->right;
			y->right->parent = y;
		}
		transplant(z, y);
		y->left = z->left;
		y->left->parent = y;
		y->color = z->color;
		y->size = y->left->size + y->right->size + 1;
	}

	if (init_color_y == BLACK) {
		erase_fixup(x);
	}
	delete z;
	check_properties();
}

RBNode *find_recursive_in_subtree(RBNode *z, int key)
{
	if (z == NullNode()) return NullNode();

	if (key < z->key) {
		return find_recursive_in_subtree(z->left, key);
	} else if (key > z->key) {
		return find_recursive_in_subtree(z->right, key);
	} else {
		return z;
	}
}

RBNode *RBTree::find_recursive(int key)
{
	return find_recursive_in_subtree(m_root, key);
}

RBNode *RBTree::find(int key)
{
	RBNode *z = m_root;

	while (z != NullNode()) {
		if (key < z->key) {
			z = z->left;
		} else if (key > z->key) {
			z = z->right;
		} else {
			return z;
		}
	}

	return NullNode();
}

static void check_rb_node(RBNode *z)
{
	assert(z->color == RED || z->color == BLACK);
	if (z->color == RED) {
		assert(z->left->color == BLACK);
		assert(z->right->color == BLACK);
	}
	assert(calc_min_black_height(z) == calc_max_black_height(z));
	assert(z->size == z->left->size + z->right->size + 1);
}

void RBTree::check_properties()
{
	assert(m_root->color == BLACK);
	in_order_traversal(check_rb_node);
}

static RBNode *nth_node_of_subtree(RBNode *x, size_t i)
{
	if (x == NullNode()) return NullNode();

	size_t r = x->left->size;

	if (i == r) return x;

	if (i < r) {
		return nth_node_of_subtree(x->left, i);
	} else {
		return nth_node_of_subtree(x->right, i - r - 1);
	}
}

RBNode *RBTree::nth_node(int i)
{
	return nth_node_of_subtree(m_root, i);
}

size_t RBTree::rank_of_node(RBNode *x)
{
	size_t	r = x->left->size;
	RBNode	*y = x;

	while (y != m_root) {
		if (y == y->parent->right) {
			r += y->parent->left->size + 1;
		}
		y = y->parent;
	}

	return r;
}

static void fill_keys(RBNode *x, vector<int> *keys)
{
	keys->push_back(x->key);
}

void test_rb_tree()
{
	for (int i = 0; i < 100; i++) {
		RBTree tree;
		vector<int> ordered_keys;
		int len = rand_int(0, 1000);
		unordered_set<int> unique_keys;

		for (int j = 0; j < len; j++) {
			int	key = rand_int(1, 1000);
			int	do_erase = rand_int(0, 1);

			tree.insert(key);
			unique_keys.insert(key);

			if (do_erase) {
				tree.erase(key);
				unique_keys.erase(key);
			}
		}

		assert(tree.size() == tree.calc_size());
		assert(unique_keys.size() == tree.calc_size());

		tree.in_order_traversal(bind(fill_keys, _1, &ordered_keys));
		for (size_t j = 1; j < ordered_keys.size(); j++) {
			assert(ordered_keys[j-1] < ordered_keys[j]);
		}
		for (size_t j = 0; j < ordered_keys.size(); j++) {
			RBNode *x = tree.nth_node(j);

			assert(x != NullNode());
			assert(x->key == ordered_keys[j]);
			assert(tree.rank_of_node(x) == j);
		}

		int cnt = 0;
		for (RBNode *x = tree.get_min(); x != NullNode(); x = tree.get_next(x)) {
			assert(x->key == ordered_keys[cnt]);
			cnt++;
		}

		cnt = (int)ordered_keys.size()-1;
		for (RBNode *x = tree.get_max(); x != NullNode(); x = tree.get_prev(x)) {
			assert(x->key == ordered_keys[cnt]);
			cnt--;
		}

		for (int j = 0; j < len; j++) {
			int	key = rand_int(1, 1000);

			if (unique_keys.find(key) != unique_keys.end()) {
				assert(tree.find(key) != NullNode());
				assert(tree.find_recursive(key) != NullNode());
			} else {
				assert(tree.find(key) == NullNode());
				assert(tree.find_recursive(key) == NullNode());
			}
		}
	}
}
