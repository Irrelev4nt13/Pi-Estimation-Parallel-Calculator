#Compiler
CC=gcc

#.o Files
Files1 = pth_ll_rwl.c ../../modules/my_rand.c
Files2 = pth_ll_rwl_impl.c ../../modules/my_rand.c

#Executable
EXEC_1 = exe_1
EXEC_2 = exe_2

all: $(EXEC_1) $(EXEC_2)

#Create executable
$(EXEC_1):$(Files1)
	$(CC) -g -Wall -o $(EXEC_1) $(Files1) -lpthread 

$(EXEC_2):$(Files2)
	$(CC) -g -Wall -o $(EXEC_2) $(Files2) -lpthread 

#Clear
clean:
	rm -f $(EXEC_1) $(EXEC_2) 	