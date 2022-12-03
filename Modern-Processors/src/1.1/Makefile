#Compiler
CC=gcc

#.cpp files
Files=monte_carlo_main.c ../../modules/monte_carlo.c ../../modules/my_rand.c 
#.o Files
OBJS=monte_carlo_main.o ../../modules/monte_carlo.o ../../modules/my_rand.o

#Executable
EXEC=exe

#Parameters for run
ARGS= 10000000 12

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
valgrind: $(EXEC)
	valgrind --leak-check=full -s \
	--leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --verbose \
		  ./$(EXEC) $(ARGS) $(INPUT)
#https://stackoverflow.com/questions/5134891/how-do-i-use-valgrind-to-find-memory-leaks 

#Clear
clean:
	rm -f $(OBJS) $(EXEC) 	