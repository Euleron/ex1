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

int numOfHackerField(FILE* doc){
    FILE* fp = fopen(doc, "r");
    if (!fp){
        fclose(fp);
        return NULL; 
    }
    char* curr;
    /*
    int firstLine;
    switch(flag){
        case COURSES:
            firstLine = 2;
            break;
        case FRIENDS:
            firstLine = 3;
            break;
        case RIVALS:
            firstLine = 4;
            break;
    }
    
    while(firstLine > 1){
        fgets(curr, 1, fp);
        if(*curr == '\n')
            firstLine--;
    }
    */
    int numOfField = 0;
    bool onField = false;
    while(*curr != '\n'){
        fgets(curr, 1, fp);
        if(*curr >='0' && *curr<='9'){
            if(onField){
                continue;
            }
            else{
                numOfField++;
                onField = true;
            }
        }
        else{
            if(onField)
                onField = false;
        }
    }
    fclose(fp);
    return numOfField;
}

void parseArray(int arr [], int size, FILE* file){
    FILE* fp = fopen(file, "r");
    int i = 0;
    bool onNum = false;
    int tempValue = 0;
    char* curr;
    while(*curr != '\n'){
        fgets(curr, 1, fp);
        if(*curr >= '0' && *curr <= '9'){
            onNum = true;
            tempValue *= 10;
            tempValue += (*curr - '0');
        }
        else{
            if(!onNum)
                continue;
            else{
                arr[i] = tempValue;
                onNum = false;
                i++;
                tempValue = 0;
            }
        }
    }
    fclose(fp);
}

int inputHackersFromFileToArray(Student* arr [], int arrSize, FILE* hackers){
    FILE* fp = fopen(hackers, "r");
    int tempStudentId;
    char* curr;
    while(fscanf(fp,"%d",tempStudentId) != EOF){
        for(int i=0;i<arrSize;i++){
            if(arr[i]->m_studentId==tempStudentId){

                // Deal with course array
                arr[i] -> m_numOfCourses = numOfHackerField(fp);
                arr[i] -> m_courses = malloc(sizeof(int)*(arr[i] ->m_numOfCourses));
                parseArray(arr[i] -> m_courses, arr[i] -> m_numOfCourses, fp);
                while(*curr != '\n')
                    fgets(curr, 1, fp);

                // Deal with friend array
                arr[i] -> m_numOfFriends = numOfHackerField(fp);
                arr[i] -> m_friends = malloc(sizeof(int)*(arr[i] -> m_numOfFriends));
                parseArray(arr[i] -> m_friends, arr[i] -> m_numOfFriends, fp);
                while(*curr != '\n')
                    fgets(curr, 1, fp);

                // Deal with rival array
                arr[i] -> m_numOfRivals = numOfHackerField(fp);
                arr[i] -> m_rivals = malloc(sizeof(int)*(arr[i] ->m_numOfRivals));
                parseArray(arr[i] -> m_rivals, arr[i] -> m_numOfRivals, fp);
                while(*curr != '\n')
                    fgets(curr, 1, fp);
            }
        }
    }
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

// Courses funcs

void destroyAll(Course* courses){
    if(courses -> m_next == NULL){
        free(courses);
        return;
    }
    destroyAll(courses -> m_next);
    free(courses);
}

Course* createCourse(int courseNum,int size)
{
    Course* new = malloc(sizeof(new));
    new -> m_courseNum = courseNum;
    new -> m_size = size;
    new -> m_next = NULL;
    return new;
}

Course* duplicateSingle(Course* course){ // m_next set to NULL
    Course* new = malloc(sizeof(new));
    new -> m_courseNum = course -> m_courseNum;
    new -> m_size = course -> m_size;
    new -> m_next = NULL;
    return new;
}

Course* duplicateAll(Course* courses){
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

void courseEnqueue(Course* courses, Course* new){
    while(courses)
        courses = courses -> m_next;
    courses = new;
}

void inputCoursesFromFileToArray(Course* coursesArray[],FILE* courses)
 {
    Course* head;
    int i=0;
    while(!(feof(courses))){
        int n = fscanf(courses,"%d,%d,\n",head -> m_courseNum, head -> m_size);
        if(n != 2)
            break;
        coursesArray[i] = duplicateSingle(head);
        i++;
    }
 }

// Students funcs

void destroy(Student* student){
    free(student -> m_name);
    free(student -> m_surname);
    free(student -> m_city);
    free(student -> m_department);
    destroyAll(student -> m_courseNode);
    destroyAll(student -> m_friendsNode);
    destroyAll(student -> m_rivalsNode);
    free(student);
}

void destroyAll(Student* students){
    if(students -> m_next == NULL){
        destroy(students);
        return;
    }
    destroyAll(students -> m_next);
    destroy(students);
}

Student* studentCreate(int studentId, int totalCredits, int gpa, char* name, char* surname, char* city, char* department, Courses* courses, Friends* friends, Rivals* rivals){
    Student* student = malloc(sizeof(student));
    student -> m_studentId = studentId;
    student -> m_totalCredits = totalCredits;
    student -> m_gpa = gpa;
    strCpyVal(name, student -> m_name);
    strCpyVal(surname, student -> m_surname);
    strCpyVal(city, student -> m_city);
    strCpyVal(department, student -> m_department);
    return student;
}

Student* duplicateStudent(Student* student){
    Student* new = malloc(sizeof(new));
    // field to field duplicate
    return new;
}

void inputStudentsFromFileToArray(Student* studentsArray[],FILE* students,int size)
 {
    Student* head;
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
    EnrollmentSystem* enrollmentSystem = malloc(sizeof(enrollmentSystem));
    int studentsSize = getNumLines(students);
    int coursesSize = getNumLines(courses);
    Student* studentArray = malloc(sizeof(studentArray)*studentsSize);
    Course* courseArray = malloc(sizeof(courseArray)*coursesSize);
    inputStudentsFromFileToArray(studentArray, students, studentsSize);
    inputCoursesFromFileToArray(courseArray, courses);
    inputHackersFromFileToArray(studentArray, studentsSize, hackers);
    enrollmentSystem -> m_students = studentArray;
    enrollmentSystem -> m_courses = courseArray;
    return *enrollmentSystem;
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



