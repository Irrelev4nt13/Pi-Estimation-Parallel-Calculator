#Compiler
CC=gcc

#.o Files
OBJS_O=pth_mat_vect_rand_split_original.o

OBJS_1=pth_mat_vect_rand_split_first_approach.o

OBJS_2=pth_mat_vect_rand_split_second_approach.o

#Executable
EXEC_O=exe_o

EXEC_1=exe_1

EXEC_2=exe_2

all: $(EXEC_O) $(EXEC_1) $(EXEC_2)

#Create executable
$(EXEC_O):$(OBJS_O)
	$(CC) -g -Wall $(OBJS_O) -o $(EXEC_O) -lpthread

$(EXEC_1):$(OBJS_1)
	$(CC) -g -Wall $(OBJS_1) -o $(EXEC_1) -lpthread

$(EXEC_2):$(OBJS_2)
	$(CC) -g -Wall $(OBJS_2) -o $(EXEC_2) -lpthread

#Clear
clean:
	rm -f $(OBJS_O) $(OBJS_1) $(OBJS_2) $(EXEC_O) $(EXEC_1) $(EXEC_2) 	