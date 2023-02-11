#Compiler
CC=gcc

#.o Files
OBJ1= pth_ll_rwl.c ../../modules/my_rand.c
OBJ2= pth_ll_rwl_impl.c ../../modules/my_rand.c

#Executable
EXEC1=exe1
EXEC2=exe2

#Create executable
$(EXEC1):$(OBJ1)
	$(CC) -g -Wall -o $(EXEC1) $(OBJ1) -lpthread 

$(EXEC2):$(OBJ2)
	$(CC) -g -Wall -o $(EXEC2) $(OBJ2) -lpthread 
#-DOUTPUT -DDEBUG 
orig: $(EXEC1)
	./$(EXEC1) 4 r < em.txt

impl: $(EXEC2)
	./$(EXEC2) 4 r <em.txt

#Clear
clean:
	rm -f $(EXEC1) $(EXEC2) 	