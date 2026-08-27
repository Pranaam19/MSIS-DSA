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

List * display_nth_end(List * list, int32_t n)
{
    
}



#endif // SLIST_C_INCLUDED
