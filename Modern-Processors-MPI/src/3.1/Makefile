#Compiler
CC=mpicc

#.c Files
Files=monte_carlo.c ../../modules/my_rand.c

#Executable
EXEC= exe

#Arguments
ARGS= 1000000000

#Processes
proc=8

#Create executable
$(EXEC):$(Files)
	$(CC) -o $(EXEC) $(Files)

#Run
run: $(EXEC)
	mpiexec -n $(proc) $(EXEC) $(ARGS)

#Clear
clean:
	rm -f $(EXEC) 	