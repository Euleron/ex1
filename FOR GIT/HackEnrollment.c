#include "HackEnrollment.h"

// Misc. funcs

void strCpyVal(char* source, char* dest){
    if(!*source)
        return NULL;
    
    int size = 0;
    char* cursor = source;
    while(*cursor){
        size++;
        cursor++;
    }
    cursor = source;
    char* new = malloc(sizeof(char)*(size + 1));
    char* temp = new;
    int i = 0;
    while(i < size){
        *temp = *cursor;
        i++;
        temp++;
        cursor++;
    }
    *temp = '\0';
    return new;
}

int nameDistance(char* s1, char* s2){
    int s1Size = 0;
    int s2Size = 0;
    char* temp = s1;
    while(*temp){
        s1Size++;
        temp++;
    }
    temp = s2;
}

int getNumLines(FILE* doc){
    FILE* fp = fopen(doc, "r");
    if (!fp) {
        return NULL; 
    }
    int size = 0;
    char* line;
    char* temp;
    while (fgets(line, 1, fp) != NULL) { 
        if (*line == '\n') {
            size++; 
        }
        temp = line;
    }
    if(*temp != '\n')
        size++;
    fclose(fp);
    return size;
}
/*
int getMaxLine(FILE* doc)
{
    FILE* fp = fopen("doc", "r");
    char *line = NULL;
    int length = 0;
    int maxLine = 0;
    int size;
    if (!fp)
        return NULL;
    while ((size = getline(&line, &length, fp)) != -1) {
        if (size > maxLine){
            maxLine = size;
        }
    }
    fclose(fp);
    return maxLine;
}
*/

// Rivals funcs

void destroyAll(Rivals* rivals){
    if(rivals -> m_next == NULL){
        free(rivals);
        return;
    }
    destroyAll(rivals -> m_next);
    free(rivals);
}

Rivals* createRival(int studentId){
    Rivals* new = malloc(sizeof(new));
    new -> m_studentId = studentId;
    new -> m_next = NULL;
    return new;
}

Rivals* duplicateSingle(Rivals* rival){ // m_next set to NULL
    Rivals* new = malloc(sizeof(new));
    new -> m_studentId = rival -> m_studentId;
    new -> m_next = NULL;
    return new;
}

Rivals* duplicateAll(Rivals* rivals){
    if(!rivals)
        return NULL;
    Rivals* new = duplicateSingle(rivals);
    Rivals* temp = new -> m_next;
    rivals = rivals -> m_next;
    while(rivals){
        temp = duplicateSingle(rivals);
        temp = temp -> m_next;
        rivals = rivals -> m_next;
    }
    return new;
}

void rivalEnqueue(Rivals* rivals, Rivals* new){
    while(rivals)
        rivals = rivals -> m_next;
    rivals = new;
}

// Friends funcs

void destroyAll(Friends* friends){
    if(friends -> m_next == NULL){
        free(friends);
        return;
    }
    destroyAll(friends -> m_next);
    free(friends);
}

Friends* createFriend(int studentId){
    Friends* new = malloc(sizeof(new));
    new -> m_studentId = studentId;
    new -> m_next = NULL;
    return new;
}

Friends* duplicateSingle(Friends* friend){ // m_next set to NULL
    Friends* new = malloc(sizeof(new));
    new -> m_studentId = friend -> m_studentId;
    new -> m_next = NULL;
    return new;
}

Friends* duplicateAll(Friends* friends){
    if(!friends)
        return NULL;
    Courses* new = duplicateSingle(friends);
    Courses* temp = new -> m_next;
    friends = friends -> m_next;
    while(friends){
        temp = duplicateSingle(friends);
        temp = temp -> m_next;
        friends = friends -> m_next;
    }
    return new;
}

void friendEnqueue(Friends* friends, Friends* new){
    while(friends)
        friends = friends -> m_next;
    friends = new;
}

// Courses funcs

void destroyAll(Courses* courses){
    if(courses -> m_next == NULL){
        free(courses);
        return;
    }
    destroyAll(courses -> m_next);
    free(courses);
}

Courses* createCourse(int courseNum,int size)
{
    Courses* new = malloc(sizeof(new));
    new -> m_courseNum = courseNum;
    new -> m_size = size;
    new -> m_next = NULL;
    return new;
}

Courses* duplicateSingle(Courses* course){ // m_next set to NULL
    Courses* new = malloc(sizeof(new));
    new -> m_courseNum = course -> m_courseNum;
    new -> m_size = course -> m_size;
    new -> m_next = NULL;
    return new;
}

Courses* duplicateAll(Courses* courses){
    if(!courses)
        return NULL;
    Courses* new = duplicateSingle(courses);
    Courses* temp = new -> m_next;
    courses = courses -> m_next;
    while(courses){
        temp = duplicateSingle(courses);
        temp = temp -> m_next;
        courses = courses -> m_next;
    }
    return new;  
}

void courseEnqueue(Courses* courses, Courses* new){
    while(courses)
        courses = courses -> m_next;
    courses = new;
}

void inputCoursesFromFileToArray(Courses* coursesArray[],FILE* courses,int size)
 {
    Students* head;
    int i=0;
    while(!(feof(students))){
        int n = fscanf(students,"%d,%d,%d,%s,%s,%s,%s\n",head->m_studentId,head->m_totalCredits,head->m_gpa,head->m_name,head->m_surname,head->m_city,head->m_department);
        if(n != 7)
            break;
        studentsArray[i] = duplicateStudent(head);
        i++;
    }
 }

// Students funcs

void destroy(Students* student){
    free(student -> m_name);
    free(student -> m_surname);
    free(student -> m_city);
    free(student -> m_department);
    destroyAll(student -> m_courseNode);
    destroyAll(student -> m_friendsNode);
    destroyAll(student -> m_rivalsNode);
    free(student);
}

void destroyAll(Students* students){
    if(students -> m_next == NULL){
        destroy(students);
        return;
    }
    destroyAll(students -> m_next);
    destroy(students);
}

Students* studentCreate(int studentId, int totalCredits, int gpa, char* name, char* surname, char* city, char* department, Courses* courses, Friends* friends, Rivals* rivals){
    Students* student = malloc(sizeof(student));
    student -> m_studentId = studentId;
    student -> m_totalCredits = totalCredits;
    student -> m_gpa = gpa;
    strCpyVal(name, student -> m_name);
    strCpyVal(surname, student -> m_surname);
    strCpyVal(city, student -> m_city);
    strCpyVal(department, student -> m_department);
    student -> m_courseNode = duplicateAll(courses);
    student -> m_friendsNode = duplicateAll(friends);
    student -> m_rivalsNode = duplicateAll(rivals);
    student -> m_next = NULL;
    return student;
}

Students* duplicateStudent(Students* student){
    Students* new = malloc(sizeof(new));
    // field to field duplicate
    return new;
}

void inputStudentsFromFileToArray(Students* studentsArray[],FILE* students,int size)
 {
    Students* head;
    int i=0;
    while(!(feof(students))){
        int n = fscanf(students,"%d,%d,%d,%s,%s,%s,%s\n",head->m_studentId,head->m_totalCredits,head->m_gpa,head->m_name,head->m_surname,head->m_city,head->m_department);
        if(n != 7)
            break;
        studentsArray[i] = duplicateStudent(head);
        i++;
    }
 }


EnrollmentSystem createEnrollment(FILE* students, FILE* courses, FILE* hackers){
    EnrollmentSystem enrollmentSystem;
    int studentsSize = getNumLines(students);
    int coursesSize = getNumLines(courses);
    Students* studentArray = malloc(sizeof(studentArray)*studentsSize);
    Courses* courseArray = malloc(sizeof(courseArray)*coursesSize);
    inputStudentsFromFileToArray(studentArray, students, studentsSize);
}

  






    /* 
     Students* head = NULL;
    while (!feof(students)) {
         Students* node = (Students*)malloc(sizeof(Students));
        int n = fscanf(students, "%d %d %lf %s %s %s %s\n",node->m_studentId , node->m_totalCredits, node->m_gpa, node->m_name, node->m_surname, node->m_city, node->m_department);
        if (n != 7) {
            free(node); // Error reading data, free memory
            break;
        }
        node->m_next = head;
        head = node;
    }
        Students* nodeH =(Students*)malloc(sizeof(Students));
    while(!feof(hackers)){
        nodeH->m_courseNode = NULL;
        nodeH->m_friendsNode = NULL;
        nodeH->m_rivalsNode = NULL; 
        Students* headH=nodeH;
        //this reads the id 
        int n= fscanf(hackers,"%d\n",nodeH->m_studentId);
        if(n!= ONE)
        {
            free(nodeH);
            break;
        }
        
        //Read courses numbers
        //need to check if the fscanf works 
         nodeH->m_courseNode = createCourse(0,-1); 
        while(fscanf(hackers,"%d\n",nodeH->m_courseNode->m_courseNum)){
            nodeH->m_courseNode->m_next = createCourse(0,-1);
            nodeH->m_courseNode = nodeH->m_courseNode->m_next;
            nodeH->m_courseNode->m_next = NULL;
        }
         // Read friends
       while (fscanf(hackers, "%d\n", nodeH->m_friendsNode->m_studentId)) {
            nodeH->m_friendsNode->m_next = createFriend(nodeH->m_friendsNode->m_studentId);
            nodeH->m_friendsNode = nodeH->m_friendsNode->m_next;
            nodeH->m_friendsNode->m_next = NULL;
         }
         // Read rivals
        while (fscanf(hackers, "%d\n", nodeH->m_rivalsNode->m_studentId)) {
            nodeH->m_rivalsNode->m_next = createRival(nodeH->m_rivalsNode->m_studentId);
            nodeH->m_rivalsNode = nodeH->m_rivalsNode->m_next;
            nodeH->m_rivalsNode->m_next = NULL;
        }

    }

    // Add students to enrollment system
    /*
     Students* curr = head;
    while (curr) {
        addStudentToEnrollmentSystem(&enrollmentSystem, curr->student);
         Students* temp = curr;
        curr = curr->m_next;
        free(temp);
    }
    // ...
    return enrollmentSystem;
    */
}



