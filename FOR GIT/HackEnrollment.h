#ifndef EX1_HACKERENROLLMENT_H
#define EX1_HACKERENROLLMENT_H
#include <stdio.h>
#include<stdbool.h>

#define FRIEND_PAR 20
#define RIVAL_PAR -20
#define NEUTRAL_PAR 0
#define ONE 1   


 typedef struct Student
{
    int m_studentId;
    int m_totalCredits;
    int m_gpa;
    char* m_name;
    char* m_surname;
    char* m_city;
    char* m_department;
    int* m_courses;
    int m_numOfCourses;
    int* m_friends;
    int m_numOfFriends;
    int* m_rivals;
    int m_numOfRivals;
}Student;

typedef struct Course 
{
    int m_courseNum;
    int m_size;
    Student* m_queue;
}Course;


typedef struct EnrollmentSystem 
{
  Student* m_students;
  Course* m_courses;
    
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

