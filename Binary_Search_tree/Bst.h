#ifndef _INCLUDED_BST_
#define _INCLUDED_BST_

#include <stdint.h>   /* int32_t / uint32_t */

typedef struct _tree_node TreeNode;
typedef struct _bst BST;

struct _tree_node {
    int32_t key;
    TreeNode *left;
    TreeNode *right;
};

struct _bst {
    TreeNode *root;
    uint32_t max;      /* number of nodes currently in the tree */
};

BST      bst_new();                                   /* returns BST by value */
BST     *bst_add(BST *tree, int32_t key);
uint32_t bst_find(BST *tree, int32_t key);            /* 1 if found, else 0   */
uint32_t bst_max(BST *tree);                          /* node count           */
uint32_t bst_height(BST *tree);
BST     *bst_delete_recursive(BST *tree, int32_t key);

BST     *bst_traversal_inorder_recursive(BST *tree);
BST     *bst_traversal_preorder_recursive(BST *tree);
BST     *bst_traversal_postorder_recursive(BST *tree);
BST     *bst_traversal_inorder_iterative(BST *tree);
BST     *bst_traversal_level_order(BST *tree);

#endif