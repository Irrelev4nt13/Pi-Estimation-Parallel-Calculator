#Compiler
CC=mpicc

#.c Files
File_0=mpi_mat_vect_time.c

File_1=mpi_mat_vect_time_approach.c

File_2=kk.c

#Executable
EXEC_0=exe_0

EXEC_1=exe_1

EXEC_2=exe_2

#Arguments
ARGS= 40000 1

all: $(EXEC_0) $(EXEC_1) $(EXEC_2)

#Processes
proc=4

#Create executable
$(EXEC_0):$(File_0)
	$(CC) -o $(EXEC_0) $(File_0)

$(EXEC_1):$(File_1)
	$(CC) -o $(EXEC_1) $(File_1)

$(EXEC_2):$(File_2)
	$(CC) -o $(EXEC_2) $(File_2)

#Run
orig: $(EXEC_0)
	mpiexec -n $(proc) $(EXEC_0) $(ARGS) < 1.txt

appr: $(EXEC_1)
	mpiexec -n $(proc) $(EXEC_1) $(ARGS) < 1.txt

test: $(EXEC_2)
	mpiexec -n $(proc) $(EXEC_2) $(ARGS) < 1.txt

#Clear
clean:
	rm -f $(EXEC_0) $(EXEC_1) $(EXEC_2)