#Compiler
CC=mpicc

#.c Files
Files=monte_carlo.c ../../modules/my_rand.c

#Executable
EXEC= exe

#Create executable
$(EXEC):$(Files)
	$(CC) -o $(EXEC) $(Files)

#Clear
clean:
	rm -f $(EXEC) 	