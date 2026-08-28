#include <stdio.h>
#include <stdlib.h>
#include<stdint.h>
#include<assert.h>
#include "slist.h"
void test_slist_generic()
{
/*    List * list = slist_new();
    assert(slist_length(list)==0);

    slist_add_head(list,10);

    slist_add_head(list,20);
    assert(slist_length(list) == 2);
    assert(slist_lookup(list, 20));
    slist_add_tail(list,30);
    slist_add_tail(list,40);
    slist_add_head(list,5);
    display(list);
    list = slist_min_max(list);
    slist_reverse(list);
    display(list);
    printf("Minimum: %d\n", list->minn);
    printf("Maximum: %d\n", list->maxx);
    assert(slist_length(list)==5);
    slist_delete_head(list);
    assert(slist_length(list)==4);
    slist_delete_tail(list);
    assert(slist_length(list)==3);

    slist_free(list);
    assert(slist_length(list)==0);
    slist_delete_head(list);
    slist_delete_tail(list);
*/
    List * l1 = slist_new();
    slist_add_tail(l1, 10);
    slist_add_tail(l1, 20);
    slist_add_tail(l1, 10);
    slist_add_tail(l1, 30);
    slist_add_tail(l1, 20);
    slist_remove_duplicates(l1);
    assert(slist_length(l1) == 3); /* 10, 20, 30 */

    /* 2. Nth from head / tail & deletion */
    int32_t status = 0;
    int32_t val_head = slist_get_nth_head(l1, 2, &status);
    assert(status == 1 && val_head == 20);

    int32_t val_tail = slist_get_nth_tail(l1, 1, &status);
    assert(status == 1 && val_tail == 30);

    slist_delete_nth(l1, 2); /* Deletes '20' */
    assert(slist_length(l1) == 2);

    /* 3. Union & Intersection */
    List * l2 = slist_new();
    slist_add_tail(l2, 30);
    slist_add_tail(l2, 40);
    slist_add_tail(l2, 50);

    List * u_list = slist_union(l1, l2);         /* 10, 30, 40, 50 */
    List * i_list = slist_intersection(l1, l2);  /* 30 */
    List * d_list = slist_difference(l1, l2);    /* 10 */

    assert(slist_length(u_list) == 4);
    assert(slist_length(i_list) == 1);
    assert(slist_length(d_list) == 1);

    /* Cleanup lists */
    slist_free(l1); free(l1);
    slist_free(l2); free(l2);
    slist_free(u_list); free(u_list);
    slist_free(i_list); free(i_list);
    slist_free(d_list); free(d_list);

    /* 4. Stack operations */
    Stack * st = stack_new();
    stack_push(st, 100);
    stack_push(st, 200);
    assert(stack_peek(st, &status) == 200);
    assert(stack_pop(st, &status) == 200);
    assert(stack_pop(st, &status) == 100);
    assert(stack_is_empty(st) == 1);
    stack_free(st);

    printf("All test assertions passed successfully!\n");


}
int main()
{
    test_slist_generic();
    return 0;
}
