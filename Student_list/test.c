#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "student.h"

int main(void) {

   /* ---- new list ---- */
   StudentList *studentList = student_list_new();

   assert(studentList -> head == NULL);
   assert(studentList -> tail == NULL);
   assert(studentList -> size == 0);
   student_list_display(studentList);

   assert(student_list_size(studentList) == 0);

   /* ---- add (third call is a duplicate roll no, must be ignored) ---- */
   student_list_add_student(studentList, 67, "Varun", 100);
   student_list_add_student(studentList, 74, "Arun", 90);
   student_list_add_student(studentList, 67, "Ajay", 80);

   assert(studentList -> head -> data.roll_no == 67);
   assert(strcmp(studentList -> head -> data.name, "Varun") == 0);
   assert(studentList -> tail -> data.roll_no == 74);
   assert(student_list_size(studentList) == 2);              /* added: size check */
   student_list_display(studentList);

   student_list_add_student(studentList, 45, "Nitr0x", 99);
   student_list_add_student(studentList, 39, "Goku", 85);
   student_list_add_student(studentList, 88, "Dev", 75);
   assert(student_list_size(studentList) == 5);              /* added */

   student_list_display(studentList);

   /* ---- lookups ---- */
   StudentNode *node = student_list_lookup_roll_no(studentList, 67);
   assert(node != NULL);
   assert(node -> data.roll_no == 67);

   node = student_list_lookup_name(studentList, "Nitr0x");
   assert(node != NULL);
   assert(node -> data.roll_no == 45);

   assert(student_list_lookup_name(studentList, "Nobody") == NULL);   /* added */

   student_list_display(studentList);

   /* ---- contains ---- */
   assert(student_list_contains(studentList, 67));
   assert(!student_list_contains(studentList, 1));
   assert(student_list_contains(studentList, 88));
   assert(!student_list_contains(studentList, 44));

   /* ---- remove: middle (list is 67,74,45,39,88) ---- */
   assert(student_list_lookup_roll_no(studentList, 74));
   student_list_remove_student(studentList, 74);
   assert(!student_list_lookup_roll_no(studentList, 74));
   assert(student_list_size(studentList) == 4);               /* added */
   student_list_display(studentList);

   /* ---- remove: head (added) ---- */
   student_list_remove_student(studentList, 67);
   assert(studentList -> head -> data.roll_no == 45);
   assert(student_list_size(studentList) == 3);

   /* ---- remove: tail, tail pointer must move back (added) ---- */
   student_list_remove_student(studentList, 88);
   assert(studentList -> tail -> data.roll_no == 39);
   assert(studentList -> tail -> next == NULL);
   assert(student_list_size(studentList) == 2);

   /* ---- remove: not found, list unchanged (added) ---- */
   student_list_remove_student(studentList, 999);
   assert(student_list_size(studentList) == 2);
   student_list_display(studentList);

   /* ---- remove everything, then add again (added) ---- */
   student_list_remove_student(studentList, 45);
   student_list_remove_student(studentList, 39);
   assert(studentList -> head == NULL);
   assert(studentList -> tail == NULL);
   assert(student_list_size(studentList) == 0);

   student_list_add_student(studentList, 1, "Test", 50);
   assert(studentList -> head == studentList -> tail);        /* both point to the one node */
   assert(student_list_size(studentList) == 1);

   /* ---- free ---- */
   studentList = student_list_free(studentList);
   assert(studentList == NULL);
   assert(student_list_size(studentList) == 0);

   printf("\nAll tests passed.\n");
   return 0;
}