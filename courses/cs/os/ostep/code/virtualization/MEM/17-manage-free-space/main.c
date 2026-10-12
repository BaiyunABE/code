#include <stdio.h>
#include "mm_malloc.h"

struct tree_node {
	unsigned long long data;
	struct tree_node* left;
	struct tree_node* right;
};

void insert(struct tree_node** root, unsigned long long data)
{
	if (*root == NULL) {
		*root = mm_malloc(sizeof(struct tree_node));
		(*root)->data = data;
		(*root)->left = NULL;
		(*root)->right = NULL;
	}
	else if (data < (*root)->data)
		insert(&(*root)->left, data);
	else
		insert(&(*root)->right, data);
}

void print_tree(struct tree_node* root)
{
	if (root == NULL)
		return;
	
	print_tree(root->left);
	printf("%llu\n", root->data);
	print_tree(root->right);
}

void destroy(struct tree_node** root)	
{
	if (*root == NULL)
		return;
	
	destroy(&(*root)->left);
	destroy(&(*root)->right);
	mm_free(*root);
	*root = NULL;
}

int main(void)
{
	init();
	print();
	
	struct tree_node* tree = NULL;
	
	insert(&tree, 30);
	printf("insert(&tree, 30)\n");
	print_tree(tree);
	print();
	
	insert(&tree, 10);
	printf("insert(&tree, 10)\n");
	print_tree(tree);
	print();
	
	insert(&tree, 40);
	printf("insert(&tree, 40)\n");
	print_tree(tree);
	print();
	
	insert(&tree, 20);
	printf("insert(&tree, 20)\n");
	print_tree(tree);
	print();
	
	insert(&tree, 50);
	printf("insert(&tree, 50)\n");
	print_tree(tree);
	print();
	
	destroy(&tree);
	printf("destroy(&tree)\n");
	print_tree(tree);
	print();
	
	return 0;
}

