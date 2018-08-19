#ifndef BINARY_TREE_HPP
#define BINARY_TREE_HPP

struct TreeNode {
	TreeNode(int _data);

	int	data;
	TreeNode *left;
	TreeNode *right;
};

typedef void (* FOR_EVERY_TREE_NODE_FUN)(struct TreeNode *p_node, void *data);
typedef void (* FOR_EVERY_TREE_NODE_FUN2)(struct TreeNode *p_node, int d, void *data);

class BinaryTree {
	public:
		BinaryTree();
		~BinaryTree();

		void fill_for_test();
		void level_order_traversal(FOR_EVERY_TREE_NODE_FUN2 fun, void *data);
		void pre_order_traversal(FOR_EVERY_TREE_NODE_FUN fun, void *data);
		void in_order_traversal(FOR_EVERY_TREE_NODE_FUN fun, void *data);
		void post_order_traversal(FOR_EVERY_TREE_NODE_FUN fun, void *data);
		void travel_top_view(FOR_EVERY_TREE_NODE_FUN fun, void *data);
		int calc_height();
		void insert_node(int data);
		TreeNode *lowest_common_ancestor(int data1, int data2);
		void fill_for_swap_nodes();
		void swap_nodes();

	private:
		bool is_binary_search_tree();

		TreeNode	*m_root;
};

extern void BinaryTreeTest();


#endif // BINARY_TREE_HPP
