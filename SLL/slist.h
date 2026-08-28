#ifndef SLIST_H_INCLUDED
#define SLIST_H_INCLUDED

#include <stdint.h>
#include <stddef.h>

typedef struct __node__ Node;
typedef struct __slist__ List;
struct __slist__{
    Node *head;
    Node *tail;
    int32_t length;
    int32_t minn;  // Added to track min
    int32_t maxx;
    };
struct __node__{
    int32_t data;
    Node *next;
};

List * slist_new();
List * slist_free(List*);
uint32_t slist_length(const List * list);
uint32_t slist_lookup(const List * list,int32_t key);
List * slist_add_head(List * list,int32_t data);
List * slist_add_tail(List * list,int32_t data);
List * slist_delete_head(List * list);
List * slist_delete_tail(List * list);
List * slist_min_max(List *list);
List * slist_reverse(List * list);
List * display(List * list);
List * slist_add_on_data(List * list,int32_t key, int32_t data);
List * slist_delete_on_data(List * list, int32_t data);

/* Standard SLL Extensions */
List * slist_remove_duplicates(List * list);
int32_t slist_has_cycle(const List * list);
int32_t slist_get_nth_head(const List * list, uint32_t n, int32_t * status);
int32_t slist_get_nth_tail(const List * list, uint32_t n, int32_t * status);
List * slist_delete_nth(List * list, uint32_t n);

/* Set Operations */
List * slist_union(const List * list1, const List * list2);
List * slist_intersection(const List * list1, const List * list2);
List * slist_difference(const List * list1, const List * list2);

/* Stack Wrapper Interface */
typedef List Stack;

Stack * stack_new(void);
Stack * stack_push(Stack * stack, int32_t data);
int32_t stack_pop(Stack * stack, int32_t * status);
int32_t stack_peek(const Stack * stack, int32_t * status);
uint32_t stack_is_empty(const Stack * stack);
void stack_free(Stack * stack);


#endif // SLIST_H_INCLUDED


