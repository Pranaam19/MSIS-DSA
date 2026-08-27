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





#endif // SLIST_H_INCLUDED
