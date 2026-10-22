#include <stdio.h>
#include "bst.h"

int main()
{
    BST tree = bst_new();
    int32_t keys[] = {50, 30, 70, 20, 40, 60, 80};
    int n = sizeof(keys) / sizeof(keys[0]);

    for (int i = 0; i < n; i++)
        bst_add(&tree, keys[i]);

    printf("count  : %u\n", bst_max(&tree));
    printf("height : %u\n", bst_height(&tree));
    printf("find 40: %u, find 99: %u\n", bst_find(&tree, 40), bst_find(&tree, 99));

    printf("inorder   (rec): "); bst_traversal_inorder_recursive(&tree);   printf("\n");
    printf("preorder  (rec): "); bst_traversal_preorder_recursive(&tree);  printf("\n");
    printf("postorder (rec): "); bst_traversal_postorder_recursive(&tree); printf("\n");
    printf("inorder   (itr): "); bst_traversal_inorder_iterative(&tree);   printf("\n");
    printf("level order    : "); bst_traversal_level_order(&tree);         printf("\n");

    /* delete: leaf (20), one child (30), two children (50) */
    bst_delete_recursive(&tree, 20);
    bst_delete_recursive(&tree, 30);
    bst_delete_recursive(&tree, 50);

    printf("\nafter deleting 20, 30, 50\n");
    printf("count  : %u\n", bst_max(&tree));
    printf("inorder: "); bst_traversal_inorder_recursive(&tree); printf("\n");
    printf("level  : "); bst_traversal_level_order(&tree);       printf("\n");

    return 0;
}