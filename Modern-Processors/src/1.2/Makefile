#Compiler
CC=gcc

#.cpp files
Files=pth_mat_vect_rand_split_1.c
#.o Files
OBJS=pth_mat_vect_rand_split_1.o

#Executable
EXEC=exe2

#Parameters for run
ARGS= 8 8 8000000 

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