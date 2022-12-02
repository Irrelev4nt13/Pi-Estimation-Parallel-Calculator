#Compiler
CC=gcc

#.cpp files
Files=main.c ../modules/monte_carlo.c
#.o Files
OBJS=main.o ../modules/monte_carlo.o

#Executable
EXEC=exe

#Parameters for run
ARGS= 100000000 3

#input file
INPUT= 

#Create executable
$(EXEC):$(OBJS)
	$(CC) -g -Wall $(OBJS) -o $(EXEC) -lpthread 

#Run
run: $(EXEC)
	./$(EXEC) $(ARGS) $(INPUT)

#debug
debug: 
	$(CC) -g3 $(Files) -o $(EXEC) 
	gdb -q $(EXEC)

#memory-loss
memory:
	make
	valgrind --leak-check=full -s ./$(EXEC) $(ARGS) $(INPUT)
#--leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --verbose \
         --log-file=valgrind-out.txt \
		 ./executable exampleParam1 \
https://stackoverflow.com/questions/5134891/how-do-i-use-valgrind-to-find-memory-leaks 

#Clear
clean:
	rm -f $(OBJS) $(EXEC) 	