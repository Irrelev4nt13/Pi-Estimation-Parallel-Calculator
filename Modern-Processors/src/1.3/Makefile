#Compiler
CC=gcc

#.o Files
OBJ1= pth_ll_rwl.c ../../modules/my_rand.c
OBJ2= pth_ll_rwl_impl.c ../../modules/my_rand.c

#Executable
EXEC_1 = exe_1
EXEC_2 = exe_2

all: $(EXEC_1) $(EXEC_2)

#Create executable
$(EXEC_1):$(OBJ1)
	$(CC) -g -Wall -o $(EXEC_1) $(OBJ1) -lpthread 

$(EXEC_2):$(OBJ2)
	$(CC) -g -Wall -o $(EXEC_2) $(OBJ2) -lpthread 
#-DOUTPUT -DDEBUG 
# orig: $(EXEC_1)
# 	./$(EXEC_1) 4 r < em.txt

# impl: $(EXEC_2)
# 	./$(EXEC_2) 4 r <em.txt

#Clear
clean:
	rm -f $(EXEC_1) $(EXEC_2) 	