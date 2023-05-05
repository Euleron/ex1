#include <stdio.h>
#include "HackEnrollment.h"
#include <string.h>

int main(int argc,char** argv) {
    if(argc < 5 || argc > 6){
        printf("Incorrect usage\n");
        return 1;
    }
    int modifier = 0;
    bool ignoreCase = false;
    if(argc == 5)
        modifier = -1;
    else if(strcmp(argv[1],"-i"))
            ignoreCase = true;
    FILE* students = fopen(argv[2+modifier], "r");
    FILE* courses = fopen(argv[3+modifier], "r");
    FILE* hackers = fopen(argv[4+modifier], "r");
    FILE* queues = fopen(argv[5+modifier], "r");
    FILE* target = fopen(argv[6+modifier], "w");
    EnrollmentSystem sys = createEnrollment(students, courses, hackers);
    sys = readEnrollment(sys, queues);
    hackEnrollment(sys, target);
    return 0;
}


