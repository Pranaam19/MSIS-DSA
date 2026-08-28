#ifndef SLIST_C_INCLUDED
#define SLIST_C_INCLUDED

#include<stdio.h>
#include <limits.h>
#include<stdlib.h>
#include<stddef.h>
#include<assert.h>
#include "slist.h"

List * slist_new()
{
    List * list;
    list = (List *)malloc(sizeof(List));
    list->head=NULL;
    list->tail=NULL;
    list->length=0;
    list->minn = 1000;
    list->maxx = 0;
    return list;
}

List * slist_free(List * list){
    Node * cur, *p;
    if(slist_length(list)>0){
        assert(list->head && list->tail);
        cur = list->head;
        list->head = NULL;
        list->tail = NULL;
    while(cur!=NULL){
        p=cur;
        cur=cur->next;
        free(p);
        --list->length;
    }
    }
    return list;

}

static Node * _list_node_new(int32_t data){
    Node * node = (Node*)malloc(sizeof(Node));
    node->data =data;
    node->next = NULL;
    return node;
}

List * slist_add_head(List * list,int32_t data)
{

    Node *node = _list_node_new(data);
    node->next = list->head;
    list->head = node;
    if(list->tail == NULL){
        list->tail =node;
    }
    ++list->length;
    assert((list->length==1 && list->head==list->tail)|| (list->length>0 && list->head!=list->tail));
    return list;
}

uint32_t slist_length(const List*list)
{
    return list->length;
}
uint32_t slist_lookup(const List*list, int32_t key){
    Node * node = list->head;
    for(node =list->head; node!=NULL;node=node->next)
    {
        if(node->data == key)break;
    }
    return (node!=NULL);
}

List * slist_add_tail(List * list,int32_t data)
{
    Node*node = _list_node_new(data);
    if(list->tail !=NULL)
    {
        list->tail->next = node;
        list->tail=node;
    }
    else{
        list->head = list->tail = node;
    }
    ++list->length;
    return list;
}
List * slist_delete_head(List * list)
{
    Node * node;
    if(list->head!=NULL){
        assert(list->length>0);
        node=list->head;
        list->head=list->head->next;
        --list->length;
        if(list->head==NULL){
            list->tail=NULL;
            assert(list->length==0);
        }
        free(node);
    }
    return list;
}


List * slist_delete_tail(List * list)
{
    assert(list!=NULL);
    Node * node;
    Node * tail = list->tail;
    if(list->tail!=NULL){
        assert(list->length>0);
        if(list->tail ==list->head)
        {
            list->head=list->tail=NULL;
        }
        else
        {
            for(node = list->head; node->next!=list->tail;node=node->next);
            list->tail=node;
            list->tail->next=NULL;
            free(tail);
        }
    --list->length;
    }
    return list;
}

List * slist_add_on_data(List * list,int32_t key, int32_t data)
{
    if(list->head!=NULL){
        Node * cur = list->head;
        Node * node = _list_node_new(data);
        for(; cur!=NULL && cur->data!=key; cur=cur->next);
        if(cur!=NULL){
            node->next = cur->next;
            cur->next = node;
            if(node->next ==NULL){
                    list->tail = node;
            }
            ++list->length;
        }
    }
    return list;
}

List * slist_delete_on_data(List * list, int32_t data)
{
    if (list != NULL && list->head != NULL)
    {
        Node *p = NULL, *cur;
        cur = list->head;

        if (cur->data == data) {
            list->head = cur->next;
            /* MISTAKE FIXED: If head was the only node, clear list->tail as well */
            if (list->head == NULL) {
                list->tail = NULL;
            }
            free(cur); /* MISTAKE FIXED: Free the deleted head node */
            --list->length; /* MISTAKE FIXED: Decrement length only when deletion occurs */
        }
        else {
            p = cur;
            cur = cur->next;
            while (cur != NULL) {
                if (cur->data == data) {
                    p->next = cur->next;

                    /* MISTAKE FIXED: Update list->tail if deleting the last node */
                    if (cur == list->tail) {
                        list->tail = p;
                    }

                    free(cur); /* MISTAKE FIXED: Free node inside match condition */
                    --list->length; /* MISTAKE FIXED: Decrement length here */
                    break; /* MISTAKE FIXED: Must break after deletion to stop loop and prevent infinite execution */
                }
                else {
                    p = cur;
                    cur = cur->next;
                }
            }
            /* MISTAKE FIXED: Removed free(cur) and tail checks from after the loop.
               If item wasn't found, cur would be NULL, leading to a no-op or erroneous updates. */
        }
    }
    return list; /* MISTAKE FIXED: Added missing return statement */
}

List * slist_min_max(List *list)
{
    if(list->head==NULL){
            return list;
    }
    Node *cur = list->head;

    int32_t minn = cur->data;
    int32_t maxx = cur->data;
    cur=cur->next;

    while(cur!=NULL){
        if(cur->data>maxx){
            maxx = cur->data;
        }
        if(cur->data<minn){
            minn = cur->data;
        }
        cur=cur->next;
        list->minn = minn;
        list->maxx = maxx;
    }
    return list;
}

List * slist_reverse(List * list)
{
    Node * prev = NULL;
    Node * current = list->head;
    Node * next;
    list->tail = list->head;
    while(current!=NULL){
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    list->head = prev;
}

List * display(List * list){
    Node * cur = list->head;

    if(list->head == NULL){
        printf("The list is empty\n");
        return list;
    }
    while(cur!=NULL){
        printf("%d\n",cur->data);
        cur=cur->next;
    }
    printf("NULL\n");

    return list;
}

/* 1. Remove all duplicate elements from the list */
List * slist_remove_duplicates(List * list) {
    if (list == NULL || list->head == NULL) return list;

    Node *cur = list->head;
    while (cur != NULL) {
        Node *runner = cur;
        while (runner->next != NULL) {
            if (runner->next->data == cur->data) {
                Node *dup = runner->next;
                runner->next = dup->next;
                if (dup == list->tail) {
                    list->tail = runner;
                }
                free(dup);
                --list->length;
            } else {
                runner = runner->next;
            }
        }
        cur = cur->next;
    }
    return list;
}

/* 2. Detect cycle using Floyd's Tortoise and Hare algorithm */
int32_t slist_has_cycle(const List * list) {
    if (list == NULL || list->head == NULL) return 0;

    Node *slow = list->head;
    Node *fast = list->head;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            return 1; /* Cycle detected */
        }
    }
    return 0; /* No cycle */
}

/* 3. Return 1-based nth element from head */
int32_t slist_get_nth_head(const List * list, uint32_t n, int32_t * status) {
    if (list == NULL || n == 0 || n > list->length) {
        if (status) *status = 0;
        return -1;
    }

    Node *cur = list->head;
    for (uint32_t i = 1; i < n; i++) {
        cur = cur->next;
    }

    if (status) *status = 1;
    return cur->data;
}

/* 4. Return 1-based nth element from tail using two-pointer technique */
int32_t slist_get_nth_tail(const List * list, uint32_t n, int32_t * status) {
    if (list == NULL || n == 0 || n > list->length) {
        if (status) *status = 0;
        return -1;
    }

    Node *fast = list->head;
    Node *slow = list->head;

    for (uint32_t i = 0; i < n; i++) {
        fast = fast->next;
    }

    while (fast != NULL) {
        fast = fast->next;
        slow = slow->next;
    }

    if (status) *status = 1;
    return slow->data;
}

/* 5. Delete element at 1-based position n */
List * slist_delete_nth(List * list, uint32_t n) {
    if (list == NULL || n == 0 || n > list->length) return list;

    if (n == 1) {
        return slist_delete_head(list);
    }
    if (n == list->length) {
        return slist_delete_tail(list);
    }

    Node *prev = list->head;
    for (uint32_t i = 1; i < n - 1; i++) {
        prev = prev->next;
    }

    Node *to_delete = prev->next;
    prev->next = to_delete->next;
    free(to_delete);
    --list->length;

    return list;
}

/* 6a. Find Union of two lists (Unique elements only) */
List * slist_union(const List * list1, const List * list2) {
    List * result = slist_new();

    if (list1 != NULL) {
        for (Node *cur = list1->head; cur != NULL; cur = cur->next) {
            if (!slist_lookup(result, cur->data)) {
                slist_add_tail(result, cur->data);
            }
        }
    }

    if (list2 != NULL) {
        for (Node *cur = list2->head; cur != NULL; cur = cur->next) {
            if (!slist_lookup(result, cur->data)) {
                slist_add_tail(result, cur->data);
            }
        }
    }

    return result;
}

/* 6b. Find Intersection of two lists (Unique elements only) */
List * slist_intersection(const List * list1, const List * list2) {
    List * result = slist_new();
    if (list1 == NULL || list2 == NULL) return result;

    for (Node *cur = list1->head; cur != NULL; cur = cur->next) {
        if (slist_lookup(list2, cur->data) && !slist_lookup(result, cur->data)) {
            slist_add_tail(result, cur->data);
        }
    }

    return result;
}

/* 7. Find relative difference: elements in list1 but NOT in list2 (Unique) */
List * slist_difference(const List * list1, const List * list2) {
    List * result = slist_new();
    if (list1 == NULL) return result;

    for (Node *cur = list1->head; cur != NULL; cur = cur->next) {
        int32_t exists_in_l2 = (list2 != NULL) ? slist_lookup(list2, cur->data) : 0;
        if (!exists_in_l2 && !slist_lookup(result, cur->data)) {
            slist_add_tail(result, cur->data);
        }
    }

    return result;
}

/* 8. Stack Implementation via SLL Wrapper */
Stack * stack_new(void) {
    return slist_new();
}

Stack * stack_push(Stack * stack, int32_t data) {
    return slist_add_head(stack, data);
}

int32_t stack_pop(Stack * stack, int32_t * status) {
    if (stack == NULL || stack->head == NULL) {
        if (status) *status = 0;
        return -1;
    }
    int32_t val = stack->head->data;
    slist_delete_head(stack);
    if (status) *status = 1;
    return val;
}

int32_t stack_peek(const Stack * stack, int32_t * status) {
    if (stack == NULL || stack->head == NULL) {
        if (status) *status = 0;
        return -1;
    }
    if (status) *status = 1;
    return stack->head->data;
}

uint32_t stack_is_empty(const Stack * stack) {
    return (stack == NULL || stack->length == 0);
}

void stack_free(Stack * stack) {
    if (stack) {
        slist_free(stack);
        free(stack);
    }
}



#endif // SLIST_C_INCLUDED
