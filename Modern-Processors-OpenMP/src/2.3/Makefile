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
	./$(EXEC) 1 1500 1 2 1

#Clear
clean:
	rm -f $(EXEC)