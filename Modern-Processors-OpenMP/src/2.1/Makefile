#Compiler
CC=gcc

#.o Files
FILES=monte_carlo_main.c ../../modules/monte_carlo.c ../../modules/my_rand.c

#Executable
EXEC=exe

#Create executable
$(EXEC):$(FILES)
	$(CC) -g -fopenmp -o $(EXEC) $(FILES) -lpthread 

#Clear
clean:
	rm -f $(EXEC) 	