#ifndef EX1_HACKERENROLLMENT_H
#define EX1_HACKERENROLLMENT_H
#include <stdio.h>

#define FRIEND_PAR 20
#define RIVAL_PAR -20
#define NEUTRAL_PAR 0
#define ONE 1   

typedef struct Rivals
{
    int m_studentId;
    Rivals* m_next;
    
} Rivals;

typedef struct Friends 
{
    int m_studentId;
    Friends * m_next;
    
}Friends;

typedef struct CourseList
{
    int m_courseNum;
    CourseList* m_next;
    
} CourseList;

 typedef struct Students
{
    int m_studentId;
    int m_totalCredits;
    int m_gpa;
    char* m_name;
    char* m_surname;
    char* m_city;
    char* m_department;
    CourseList* m_courseList;
    Friends* m_friendsNode;
    Rivals* m_rivalsNode;
    Students* m_next;
}Students;

typedef struct Courses 
{
    int m_courseNum;
    int m_size;
    Students* m_studentNode;
    Courses* m_next;
    
}Courses;

//typedef enum {EnrollmentSystem_NULL,EnrollmentSystem_SUCSS} enrollmentSystemEror;

typedef struct EnrollmentSystem 
{
  Students* m_students;
  Courses* m_courses;
    
}EnrollmentSystem;



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

