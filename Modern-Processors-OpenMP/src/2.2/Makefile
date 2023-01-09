#Compiler
CC=gcc

#.o Files
OBJS_0=omp_mat_vect_rand_split_original.o

OBJS_1=omp_mat_vect_rand_split_first_approach.o

OBJS_2=omp_mat_vect_rand_split_second_approach.o

OBJS_3=book.o

#Executable
EXEC_0=exe_0

EXEC_1=exe_1

EXEC_2=exe_2

EXEC_3=exe_3

#Parameters for run
ARGS= 4 8000000 8


all: $(EXEC_0) $(EXEC_1) $(EXEC_2) $(EXEC_3)

#Create executable
$(EXEC_0):$(OBJS_0)
	$(CC) -g -Wall $(OBJS_0) -o $(EXEC_0) -fopenmp

$(EXEC_1):$(OBJS_1)
	$(CC) -g -Wall $(OBJS_1) -o $(EXEC_1) -fopenmp

$(EXEC_2):$(OBJS_2)
	$(CC) -g -Wall $(OBJS_2) -o $(EXEC_2) -fopenmp

$(EXEC_3):$(OBJS_3)
	$(CC) -g -Wall $(OBJS_3) -o $(EXEC_3) -fopenmp


original: $(EXEC_0)
	./$(EXEC_0) $(ARGS)

first: $(EXEC_1)
	./$(EXEC_1) $(ARGS)

second: $(EXEC_2)
	./$(EXEC_2) $(ARGS)

third: $(EXEC_3)
	./$(EXEC_3) $(ARGS)
#Clear
clean:
	rm -f $(OBJS_0) $(OBJS_1) $(OBJS_2) $(OBJS_3) $(EXEC_0) $(EXEC_1) $(EXEC_2) $(EXEC_3)