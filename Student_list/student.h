#ifndef _INCLUDED_STUDENT_SLIST_
#define _INCLUDED_STUDENT_SLIST_

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#define MAX_NAME_LENGTH 32

typedef struct _student_data {
    uint32_t roll_no;
    char name[MAX_NAME_LENGTH];
    float marks;
} StudentData;

typedef struct _student_node StudentNode;
struct _student_node {
    StudentData data;
    StudentNode *next;
};

typedef struct _student_list {
    StudentNode *head;
    StudentNode *tail;      /* tail pointer makes adding at the end O(1) */
    size_t size;
} StudentList;

StudentList *student_list_new(void);
StudentList *student_list_free(StudentList *student_list);   /* returns NULL */
size_t       student_list_size(StudentList *student_list);

StudentNode *student_list_lookup_roll_no(StudentList *student_list, uint32_t roll_no);
StudentNode *student_list_lookup_name(StudentList *student_list, const char *name);

StudentList *student_list_add_student(StudentList *student_list, uint32_t roll_no,
                                      const char *name, float marks);
StudentList *student_list_remove_student(StudentList *student_list, uint32_t roll_no);

bool         student_list_contains(StudentList *student_list, uint32_t roll_no);
void         student_list_display(StudentList *student_list);

#endif