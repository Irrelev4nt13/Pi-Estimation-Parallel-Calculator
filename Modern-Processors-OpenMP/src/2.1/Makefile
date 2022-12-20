#Compiler
CC=gcc

#.o Files
OBJS=monte_carlo_main.o ../../modules/monte_carlo.o ../../modules/my_rand.o

#Executable
EXEC=exe

#Parameters for run
ARGS= 1000000 4

#Create executable
$(EXEC):$(OBJS)
	$(CC) -g -Wall $(OBJS) -o $(EXEC) -fopenmp

#Run
run: $(EXEC)
	./$(EXEC) $(ARGS)

#Clear
clean:
	rm -f $(OBJS) $(EXEC) 	