#Compiler
CC=mpicc

#.c Files
File_0=mpi_mat_vect_time.c

File_1=mpi_mat_vect_time_approach.c

#Executable
EXEC_0=exe_0

EXEC_1=exe_1

all: $(EXEC_0) $(EXEC_1)

#Create executable
$(EXEC_0):$(File_0)
	$(CC) -o $(EXEC_0) $(File_0)

$(EXEC_1):$(File_1)
	$(CC) -o $(EXEC_1) $(File_1)

#Clear
clean:
	rm -f $(EXEC_0) $(EXEC_1)