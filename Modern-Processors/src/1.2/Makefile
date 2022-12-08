#Compiler
CC=gcc

#.o Files
OBJS_O=pth_mat_vect_rand_split_original.o

OBJS_1=pth_mat_vect_rand_split_first_approach.o

OBJS_2=pth_mat_vect_rand_split_second_approach.o

#Executable
EXEC_O=exe_o

EXEC_1=exe_1

EXEC_2=exe_2

#Parameters for run
ARGS= 4 8000000 8

#input file
INPUT= 

all: $(EXEC_O) $(EXEC_1) $(EXEC_2)

#Create executable
$(EXEC_O):$(OBJS_O)
	$(CC) -g -Wall $(OBJS_O) -o $(EXEC_O) -lpthread

$(EXEC_1):$(OBJS_1)
	$(CC) -g -Wall $(OBJS_1) -o $(EXEC_1) -lpthread

$(EXEC_2):$(OBJS_2)
	$(CC) -g -Wall $(OBJS_2) -o $(EXEC_2) -lpthread

#Run
# run: $(EXEC)
# 	./$(EXEC) $(ARGS) $(INPUT)

#debug
# debug: 
# 	$(CC) -g3 $(Files) -o $(EXEC) -lpthread 
# 	gdb -q $(EXEC)

#memory-loss
# valgrind: $(EXEC)
# 	valgrind --leak-check=full -s \
# 	--leak-check=full \
#          --show-leak-kinds=all \
#          --track-origins=yes \
#          --verbose \
# 		  ./$(EXEC) $(ARGS) $(INPUT)
#https://stackoverflow.com/questions/5134891/how-do-i-use-valgrind-to-find-memory-leaks 

#Clear
clean:
	rm -f $(OBJS_O) $(OBJS_1) $(OBJS_2) $(EXEC_O) $(EXEC_1) $(EXEC_2) 	