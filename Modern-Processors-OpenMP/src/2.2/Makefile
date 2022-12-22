#Compiler
CC=gcc

#.o Files
OBJS_O=omp_mat_vect_rand_split_original.o

OBJS_1=omp_mat_vect_rand_split_first_approach.o

OBJS_2=omp_mat_vect_rand_split_second_approach.o

#Executable
EXEC_O=exe_o

EXEC_1=exe_1

EXEC_2=exe_2

#Parameters for run
ARGS= 1 2 2


all: $(EXEC_O) $(EXEC_1) $(EXEC_2)

#Create executable
$(EXEC_O):$(OBJS_O)
	$(CC) -g -Wall $(OBJS_O) -o $(EXEC_O) -fopenmp

$(EXEC_1):$(OBJS_1)
	$(CC) -g -Wall $(OBJS_1) -o $(EXEC_1) -fopenmp

$(EXEC_2):$(OBJS_2)
	$(CC) -g -Wall $(OBJS_2) -o $(EXEC_2) -fopenmp


original: $(EXEC_0)
	./$(EXEC_0) $(ARGS)

# first: $(EXEC_1)
# 	./$(EXEC_1) $(ARGS)

# second: $(EXEC_2)
# 	./$(EXEC_2) $(ARGS)
#Clear
clean:
	rm -f $(OBJS_O) $(OBJS_1) $(OBJS_2) $(EXEC_O) $(EXEC_1) $(EXEC_2) 	