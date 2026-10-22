#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Bst.h"

/* ---------- creation ---------- */

BST bst_new()
{
    BST tree = {NULL, 0};
    return tree;
}

static TreeNode *_make_TreeNode(int32_t key)
{
    TreeNode *tnode = (TreeNode *)malloc(sizeof(TreeNode));
    assert(tnode != NULL);              /* added: catch malloc failure */
    tnode->key = key;
    tnode->left = tnode->right = NULL;
    return tnode;
}

/* ---------- add (iterative) ---------- */

BST *bst_add(BST *tree, int32_t key)
{
    TreeNode *root, *parent;
    root = parent = tree->root;

    /* walk down until we hit NULL or find the key (duplicates ignored) */
    while (root != NULL && root->key != key) {
        parent = root;
        if (key < root->key) {
            root = root->left;
        }
        else if (key > root->key) {
            root = root->right;
        }
    }

    if (root == NULL) {                 /* key not present -> insert */
        TreeNode *tnode = _make_TreeNode(key);
        if (parent == NULL) {
            tree->root = tnode;         /* empty tree */
        }
        else if (key < parent->key) {
            parent->left = tnode;
        }
        else {
            parent->right = tnode;
        }
        ++tree->max;
    }
    return tree;
}

/* ---------- find / max ---------- */

uint32_t bst_find(BST *tree, int32_t key)
{
    TreeNode *root = tree->root;
    while (root != NULL) {
        if (key < root->key) {
            root = root->left;
        }
        else if (key > root->key) {
            root = root->right;
        }
        else {
            break;
        }
    }
    return root != NULL;
}

uint32_t bst_max(BST *tree)
{
    return tree->max;
}

/* ---------- height ---------- */

static uint32_t _height(TreeNode *node)
{
    uint32_t height, lheight, rheight;
    if (node == NULL) {
        height = 0;
    }
    else {
        lheight = _height(node->left);
        rheight = _height(node->right);
        if (lheight > rheight) {
            height = lheight + 1;
        }
        else {
            height = rheight + 1;
        }
    }
    return height;
}

uint32_t bst_height(BST *tree)
{
    return _height(tree->root);
}

/* ---------- recursive traversals ---------- */

static void _inorder(TreeNode *root)            /* L R-oot R */
{
    if (root) {
        _inorder(root->left);
        printf("%d\t", root->key);
        _inorder(root->right);   /* FIX: notes had root->left here again */
    }
}

BST *bst_traversal_inorder_recursive(BST *tree)
{
    _inorder(tree->root);
    return tree;
}

static void _preorder(TreeNode *root)           /* Root Left Right */
{
    if (root) {
        printf("%d\t", root->key);
        _preorder(root->left);
        _preorder(root->right);
    }
}

BST *bst_traversal_preorder_recursive(BST *tree)
{
    _preorder(tree->root);
    return tree;
}

static void _post_order(TreeNode *root)         /* Left Right Root */
{
    if (root) {
        _post_order(root->left);
        _post_order(root->right);
        printf("%d\t", root->key);
    }
}

BST *bst_traversal_postorder_recursive(BST *tree)
{
    _post_order(tree->root);
    return tree;
}

/* ---------- delete ---------- */

static TreeNode *_find_min(TreeNode *root)      /* leftmost node */
{
    if (root->left == NULL) {
        return root;
    }
    else {
        return _find_min(root->left);
    }
}

static TreeNode *_bst_delete(BST *tree, TreeNode *root, int32_t key)
{
    TreeNode *temp;
    if (root == NULL) {
        return root;                            /* key not found */
    }
    else if (key < root->key) {
        root->left = _bst_delete(tree, root->left, key);
    }
    else if (key > root->key) {
        root->right = _bst_delete(tree, root->right, key);
    }
    else if (root->left && root->right) {
        /* two children: copy inorder successor, then delete it from right subtree */
        temp = _find_min(root->right);
        root->key = temp->key;
        root->right = _bst_delete(tree, root->right, root->key);
    }
    else {
        /* 0 or 1 child: splice the node out */
        temp = root;
        if (root->left == NULL)
            root = root->right;
        else
            root = root->left;
        free(temp);
        --tree->max;      /* answers your margin note: this is INSIDE the else,
                             so max drops once per node actually freed */
    }
    return root;
}

BST *bst_delete_recursive(BST *tree, int32_t key)
{
    TreeNode *root = _bst_delete(tree, tree->root, key);
    tree->root = root;
    return tree;
}

/* ---------- iterative traversals ----------
 * Your notes use separate stack/queue modules (stack_new, stack_push, queue_add...)
 * that weren't written down, so these use small private arrays instead.
 * Size = tree->max is always enough (each node is stored at most once).
 */

BST *bst_traversal_inorder_iterative(BST *tree)
{
    TreeNode **stk = (TreeNode **)malloc((tree->max + 1) * sizeof(TreeNode *));
    uint32_t top = 0;                           /* top == 0 means stack empty */
    TreeNode *root = tree->root;

    while (root != NULL || top > 0) {           /* FIX: notes had "&& stack empty" garbled */
        if (root) {
            stk[top++] = root;                  /* push, go left */
            root = root->left;
        }
        else {
            root = stk[--top];                  /* pop, visit, go right */
            printf("%d\t", root->key);
            root = root->right;
        }
    }
    free(stk);
    return tree;
}

BST *bst_traversal_level_order(BST *tree)
{
    TreeNode **q = (TreeNode **)malloc((tree->max + 1) * sizeof(TreeNode *));
    uint32_t head = 0, tail = 0;

    if (tree->root) {
        q[tail++] = tree->root;                 /* enqueue root */
    }
    while (head < tail) {                       /* replaces for(;;) + break */
        TreeNode *root = q[head++];             /* dequeue */
        printf("%d\t", root->key);
        if (root->left)  q[tail++] = root->left;
        if (root->right) q[tail++] = root->right;
    }
    free(q);
    return tree;
}