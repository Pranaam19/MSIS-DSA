#include <stdio.h>      /* added: printf is used in display */
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "student.h"

/* ---------- private helper: build one node ---------- */

static StudentNode *_student_list_new_node_(uint32_t roll_no, const char *name, float marks){
    StudentNode *student_node = (StudentNode *) malloc(sizeof(StudentNode));

    if(student_node == NULL) return NULL;

    student_node -> data.roll_no = roll_no;
    strncpy(student_node -> data.name, name, MAX_NAME_LENGTH - 1);
    student_node -> data.name[MAX_NAME_LENGTH - 1] = '\0';   /* strncpy may not terminate */
    student_node -> data.marks = marks;

    student_node -> next = NULL;        /* a new node is always the last one */

    return student_node;
}

/* ---------- create / free / size ---------- */

StudentList *student_list_new(void){
    StudentList *student_list = (StudentList *) malloc(sizeof(StudentList));

    if(student_list == NULL) return NULL;

    student_list -> head = NULL;
    student_list -> tail = NULL;
    student_list -> size = 0;

    return student_list;
}

StudentList *student_list_free(StudentList *student_list){
    if(student_list == NULL) return NULL;

    StudentNode *p;
    while(student_list -> head != NULL){
        p = student_list -> head;
        student_list -> head = student_list -> head -> next;   /* move on BEFORE freeing */
        free(p);
    }
    /* removed: tail = NULL / size = 0 (pointless, the struct is freed next) */

    free(student_list);
    return NULL;                        /* caller: list = student_list_free(list); */
}

size_t student_list_size(StudentList *student_list){
    if(student_list == NULL) return 0;

    return student_list -> size;
}

/* ---------- lookups (traverse pattern) ---------- */

StudentNode *student_list_lookup_roll_no(StudentList *student_list, uint32_t roll_no){
    if(student_list == NULL) return NULL;           /* added: NULL check */

    StudentNode *student_node;
    for(student_node = student_list -> head; student_node != NULL; student_node = student_node -> next){
        if(student_node -> data.roll_no == roll_no) return student_node;
    }
    return NULL;
}

StudentNode *student_list_lookup_name(StudentList *student_list, const char *name){
    if(student_list == NULL) return NULL;           /* added: NULL check */

    StudentNode *student_node;
    for(student_node = student_list -> head; student_node != NULL; student_node = student_node -> next){
        if(strcmp(student_node -> data.name, name) == 0) return student_node;
    }
    return NULL;
}

/* ---------- add at tail ---------- */

StudentList *student_list_add_student(StudentList *student_list, uint32_t roll_no, const char *name, float marks){
    if(student_list == NULL) return NULL;

    /* duplicate roll number: ignore silently, list unchanged */
    if(student_list_lookup_roll_no(student_list, roll_no)) return student_list;

    StudentNode *new_student_node = _student_list_new_node_(roll_no, name, marks);
    if(new_student_node == NULL) return NULL;

    if(student_list -> head == NULL){
        student_list -> head = student_list -> tail = new_student_node;   /* empty list */
    } else {
        student_list -> tail -> next = new_student_node;
        student_list -> tail = new_student_node;
    }
    ++student_list -> size;
    return student_list;
}

/* ---------- remove (previous / current pattern) ---------- */

StudentList *student_list_remove_student(StudentList *student_list, uint32_t roll_no){
    if(student_list == NULL || student_list -> head == NULL) return student_list;

    StudentNode *previous = NULL;
    StudentNode *current = student_list -> head;

    while(current != NULL){
        if(current -> data.roll_no == roll_no){
            if(previous == NULL){
                student_list -> head = current -> next;     /* removing the head */
            } else {
                previous -> next = current -> next;         /* bypass current */
            }

            if(current == student_list -> tail){
                student_list -> tail = previous;            /* removing the tail */
            }

            free(current);
            --student_list -> size;

            return student_list;
        }

        previous = current;
        current = current -> next;
    }
    return student_list;                                     /* not found */
}

/* ---------- contains / display ---------- */

bool student_list_contains(StudentList *student_list, uint32_t roll_no){
    return student_list_lookup_roll_no(student_list, roll_no) != NULL;   /* simplified */
}

void student_list_display(StudentList *student_list){
    if(student_list == NULL){
        printf("--- NULL ---\n");                            /* added newline */
    } else {
        printf("\nSTUDENT_LIST{\n\t");
        for(StudentNode *student_node = student_list -> head; student_node != NULL; student_node = student_node -> next){
            printf("| %5u | %-10s | %12f | -> \n\t", student_node -> data.roll_no, student_node -> data.name, student_node -> data.marks);
        }
        printf("NULL\n}\n");
    }
}