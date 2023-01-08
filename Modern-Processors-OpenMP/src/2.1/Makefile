#Compiler
CC=gcc

#.o Files
FILES=monte_carlo_main.c ../../modules/monte_carlo.c ../../modules/my_rand.c
# FILES=book.c ../../modules1/my_rand.c
#Executable
EXEC=exe

#Parameters for run
ARGS=100000000 4 

#Create executable
$(EXEC):$(FILES)
	$(CC) -g -fopenmp -o $(EXEC) $(FILES) -lpthread 

#Run
run: $(EXEC)
	./$(EXEC) $(ARGS)

#Clear
clean:
	rm -f $(EXEC) 	