#ifndef EX1_HACKERENROLLMENT_H
#define EX1_HACKERENROLLMENT_H
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "IsraeliQueue.h"

#define FRIEND_PAR 20
#define RIVAL_PAR 0
#define ONE 1   



typedef struct Course 
{
    int m_courseNum;
    int m_size;
    IsraeliQueue m_queue;
}Course;


typedef struct EnrollmentSystem 
{
  Student* m_students;
  int m_studentsSize;
  Course* m_courses;
  int m_coursesSize;
  bool m_ignoreCase;
    
}*EnrollmentSystem;


/*
*creates a new EnrollmetSystem 
@param students a file that holds the students and there information
@param courses a file that holds the courses and there information
@param hackers a file that holds the hackers and there information
* in any error return NULL
*/
EnrollmentSystem createEnrollment(FILE* students, FILE* courses, FILE* hackers);

EnrollmentSystem readEnrollment(EnrollmentSystem sys, FILE* queues);

void hackEnrollment(EnrollmentSystem sys, FILE* out);



#endif //EX1_HACKERENROLLMENT_H

/*

struct StudentNode {
    struct Student student;
    struct StudentNode* next;
};
*/

//gcc -std=c99 -o HackEnrollment -lm -I/home/mtm/public/2223b/ex1 -Itool -Wall -pedantic-errors -Werror -DNDEBUG main.c HackEnrollment.c IsraeliQueue.c
