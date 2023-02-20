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
	
#Clear
clean:
	rm -f $(EXEC)