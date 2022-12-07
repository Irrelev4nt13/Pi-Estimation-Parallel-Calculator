#Compiler
CC=gcc

#.o Files
OBJS=monte_carlo_main.o ../../modules/monte_carlo.o ../../modules/my_rand.o

#Executable
EXEC=exe

#Create executable
$(EXEC):$(OBJS)
	$(CC) -g -Wall $(OBJS) -o $(EXEC) -lpthread 

#Clear
clean:
	rm -f $(OBJS) $(EXEC) 	