CC = gcc
OBJS = IsraeliQueue.o HackEnrollment.o main.o
EXEC = HackEnrollment
DEBUG_FLAG = #when needed, assign -g for debug
COMP_FLAG = -std=c99 -Wall -Werror -pedantic
INCLUDE = -I/new_home/courses/mtm/public/2223b/ex1/ -I/tool
PATH = /new_home/courses/mtm/public/2223b/ex1/
TOOL = tool/
MATH = -lm

$(EXEC) : $(OBJS)
	$(CC) $(DEBUG_FLAG) $(INCLUDE) $(OBJS) -o $@ $(MATH)

IsraeliQueue.o :  $(PATH)IsraeliQueue.h IsraeliQueue.c
	$(CC) -c $(DEBUG_FLAG) $(INCLUDE) $(COMP_FLAG) $*.c

HackEnrollment.o : $(TOOL)HackEnrollment.h $(PATH)IsraeliQueue.h $(TOOL)HackEnrollment.c
	$(CC) -c $(DEBUG_FLAG) $(INCLUDE) $(COMP_FLAG) $(TOOL) $*.c

main.o : $(TOOL)main.c $(TOOL)HackEnrollment.h
	$(CC) -c $(DEBUG_FLAG) $(INCLUDE) $(COMP_FLAG) $(TOOL) $*.c

clean:
	rm -f $(OBJS) $(EXEC)