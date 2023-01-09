#Compiler
CC=gcc

#.o Files
File_0=omp_mat_vect_rand_split_original.c

File_1=omp_mat_vect_rand_split_first_approach.c

File_2=omp_mat_vect_rand_split_second_approach.c


#Executable
EXEC_0=exe_0

EXEC_1=exe_1

EXEC_2=exe_2

EXEC_3=exe_3

#Parameters for run
ARGS= 2 8000 8000 1 100

all: $(EXEC_0) $(EXEC_1) $(EXEC_2)

#Create executable
$(EXEC_0):$(File_0)
	$(CC) -g -Wall -fopenmp -o $(EXEC_0) $(File_0) 

$(EXEC_1):$(File_1)
	$(CC) -g -Wall -fopenmp -o $(EXEC_1) $(File_1) 

$(EXEC_2):$(File_2)
	$(CC) -g -Wall -fopenmp -o $(EXEC_2) $(File_2) 

# original: $(EXEC_0)
# 	./$(EXEC_0) $(ARGS)

# first: $(EXEC_1)
# 	./$(EXEC_1) $(ARGS)

second: $(EXEC_2)
	./$(EXEC_2) $(ARGS)

#Clear
clean:
	rm -f $(EXEC_0) $(EXEC_1) $(EXEC_2)