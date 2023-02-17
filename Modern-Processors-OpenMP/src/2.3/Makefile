#Compiler
CC=gcc

#.o Files
Files=implementation.c

#Executable
EXEC=exe

all: $(EXEC)

#Create executable
$(EXEC):$(Files)
	$(CC) -g -Wall -fopenmp -o $(EXEC) $(Files) 

run: $(EXEC)
	./$(EXEC) 3 3 1 2 0

#Clear
clean:
	rm -f $(EXEC)