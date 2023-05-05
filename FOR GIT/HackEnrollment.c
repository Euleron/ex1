#include "HackEnrollment.h"

#define FRIENDS 20
#define RIVALS -20
#define NEUTRAL 0


// Misc. funcs
bool charIsNum(char* c){
    return (*c >= '0' && *c <= '9');
}

bool charIsNewLine(char *c){
    return (*c == '\n');
}

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

int numOfHackerField(FILE* doc){
    FILE* fp = fopen(doc, "r");
    if (!fp){
        fclose(fp);
        return NULL; 
    }
    char* curr;
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
                arr[i]->m_hacker=true;
                arr[i] -> m_missedCourses = 0;
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

// Friendship funcs

FriendshipFunction areFriends(Student* hacker, Student* student){
    
    //If hacker has friends, look for student.
    if(hacker -> m_numOfFriends > 0)
        for(int i = 0; i < hacker -> m_numOfFriends; i++)
            if(hacker -> m_friends[i] == student -> m_studentId);
                return FRIENDS;
    
    //If hacker has rivals, look for student.
    if(hacker -> m_numOfRivals > 0)
        for(int i = 0; i < hacker -> m_numOfRivals; i++)
            if(hacker -> m_rivals[i] == student -> m_studentId);
                return RIVALS;

    // If student is neither a friend nor rival, return neutral.
    return NEUTRAL;
}

FriendshipFunction nameDelta(Student* hacker, Student* student){
    int sumAsciiHacker=0;
    int sumAsciiHStudent=0;
    int lenHacker=strlen(hacker->m_name);
    int lenStudent=strlen(student->m_name); 
    int lenStudentSurname=strlen(student->m_surname);
    int lenHackerSurname=strlen(hacker->m_surname);
//checks if UPPER 
    if((hacker->m_name>='A'&& hacker->m_name<='Z')&&(student->m_name>='A'&& student->m_name<='Z'))
    {
         for(int i=0;i<lenStudent;i++)
        {
            sumAsciiHStudent+=student->m_name[i];
        }
        for(int i=0;i<lenStudentSurname;i++)
        {
            sumAsciiHStudent+=student->m_surname[i];
        }

        for(int i=0;i<lenHacker;i++)
        {
            sumAsciiHacker+=hacker->m_name[i];
        }
        
        for(int i=0;i<lenHackerSurname;i++)
        {
            sumAsciiHacker+=hacker->m_surname[i];
        }

        return abs(sumAsciiHacker-sumAsciiHStudent);
        
    }
    //if the names are LOWER
    else{
        for(int i=0;i<lenStudent;i++)
        {
            sumAsciiHStudent+=student->m_name[i];
        }
        for(int i=0;i<lenStudentSurname;i++)
        {
            sumAsciiHStudent+=student->m_surname[i];
        }

        for(int i=0;i<lenHacker;i++)
        {
            sumAsciiHacker+=hacker->m_name[i];
        }
        
        for(int i=0;i<lenHackerSurname;i++)
        {
            sumAsciiHacker+=hacker->m_surname[i];
        }

        return abs(sumAsciiHacker-sumAsciiHStudent);

        
        
        
    }
}

FriendshipFunction idDelta(Student* hacker, Student* student){
    int delta = hacker ->m_studentId - student -> m_studentId;
    if (delta < 0)
        return ((-1) * delta);
    return delta;
}

FriendshipFunction* hackerFuntions(){
    FriendshipFunction* f = malloc(sizeof(f)*3);
    f[0] = &areFriends;
    f[1] = &nameDelta;
    f[2] = &idDelta;
    return f;
}
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
    new -> m_queue = NULL;
    return new;
}

Course* duplicateSingle(Course* course){ // m_next set to NULL
    Course* new = malloc(sizeof(new));
    new -> m_courseNum = course -> m_courseNum;
    new -> m_size = course -> m_size;
    new -> m_queue = NULL;
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
    if(student==NULL) {
        return;
    }
    free(student -> m_name);
    free(student -> m_surname);
    free(student -> m_city);
    free(student -> m_department);
    free(student->m_friends);
    free(student->m_courses);
    free(student->m_rivals);
    free(student);
}

void destroyAll(Student* students[],int size){
    for(int i=0;i<size;i++) {
        destroy(students[i]);
    }

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
    new->m_studentId=student->m_studentId;
    new->m_totalCredits=student->m_totalCredits;
    new->m_gpa=student->m_gpa;
    new->m_name=student->m_name;
    new->m_surname=student->m_surname;
    new->m_city=student->m_city;
    new->m_department=student->m_department;
    new->m_courses=NULL;
    new->m_friends=NULL;
    new->m_rivals=NULL;
    new->m_numOfCourses=0;
    new->m_numOfFriends=0;
    new->m_numOfRivals=0;
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
        studentsArray[i]->m_hacker=false;
        i++;
    }
 }


// Enrollment funcs

EnrollmentSystem createEnrollment(FILE* students, FILE* courses, FILE* hackers){
    EnrollmentSystem* enrollmentSystem = malloc(sizeof(enrollmentSystem));
    if(!enrollmentSystem){
        free(enrollmentSystem);
        return ;
    }
    int studentsSize = getNumLines(students);
    int coursesSize = getNumLines(courses);
    Student* studentArray = malloc(sizeof(studentArray)*studentsSize);
    Course* courseArray = malloc(sizeof(courseArray)*coursesSize);
    inputStudentsFromFileToArray(studentArray, students, studentsSize);
    inputCoursesFromFileToArray(courseArray, courses);
    inputHackersFromFileToArray(studentArray, studentsSize, hackers);
    enrollmentSystem -> m_students = studentArray;
    enrollmentSystem -> m_courses = courseArray;
    enrollmentSystem -> m_studentsSize = studentsSize;
    enrollmentSystem -> m_coursesSize = coursesSize;
    return *enrollmentSystem;
}

EnrollmentSystem readEnrollment(EnrollmentSystem sys, FILE* queues){
    if(!queues)
        return NULL;
    FriendshipFunction* f = hackerFuntions();
    FILE* fp = fopen(queues, "r");
    int i = 0;
    int j = 0;
    int courseNum = 0;
    char* curr;
    int studentId = 0;
    while(fscanf(fp,"%d",courseNum) != EOF){

        // Find index of course with courseNum.
        for(; i < sys.m_coursesSize; i++){
            if(sys.m_courses[i].m_courseNum == courseNum)
                break;
        }
        
        // Check that a course was actually found.
        if(i == sys.m_coursesSize)
            return NULL;

        // Read IDs until new line
        while(!charIsNewLine(curr)){
            fgets(curr, 1, fp);
            //go in when character is not a number 
            if(!(charIsNum(curr)))
                continue;
            
            //Get student ID
            while(charIsNum(curr)){
                studentId *= 10;
                studentId += *curr - '0';
                fgets(curr, 1, fp);
            }
            //Find student in array USE J 
            for(;j<sys.m_studentsSize;j++)
                if(sys.m_students[j].m_studentId == studentId)
                    break;
                    
            // Place student j, at the end of the queue for course i
            IsraeliQueue tempQueue = IsraeliQueueCreate(f,NULL,FRIEND_PAR,RIVAL_PAR);
            tempQueue -> m_student = &sys.m_students[j];
            IsraeliQueueEndOfLine(sys.m_courses[i].m_queue, tempQueue);
            
            //Variable reset
            studentId = 0;
            j = 0;
        }
        i=0;
    }
    fclose(fp);
    return sys;
}

void hackEnrollment(EnrollmentSystem sys, FILE* out){
    FriendshipFunction* f = hackerFuntions();
    Student* hacker;
    int k = 0;
    for(int i = 0; i < sys.m_studentsSize; i++){
    //check if student is hacker 
        if(sys.m_students[i].m_hacker){
            hacker = &(sys.m_students[i]);
            //here we put hacker inside the israeli quqe of every course 
            for(int j = 0; j < hacker -> m_numOfCourses; j++){
                IsraeliQueue tempQueue = IsraeliQueueCreate(f,NULL,FRIEND_PAR,RIVAL_PAR);
                tempQueue -> m_student = hacker;
                //here we find the correct course in the array courses 
                for(; k < sys.m_coursesSize; k++)
                    if(sys.m_courses[k].m_courseNum == hacker -> m_courses[j])
                        break;
                IsraeliQueueEnqueue(sys.m_courses[k].m_queue,tempQueue);
                IsraeliQueue curr = sys.m_courses[k].m_queue;
                int count = 0;
                while(curr){
                    if(curr -> m_student -> m_hacker && count >= sys.m_courses[k].m_size){
                        // Print to out that hacker's demands cannot be satisfied.
                        return;
                    }
                    count++;
                    curr = curr -> m_next;
                }
            }
            k = 0;
        }
    }

}

// For next session: 
  

































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



