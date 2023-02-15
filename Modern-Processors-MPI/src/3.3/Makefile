#Compiler
CC=mpicc

#.c Files
Files=monte_carlo.c ../../modules/my_rand.c

#Executable
EXEC= exe

Threads = 1

#Create executable
$(EXEC):$(Files)
	$(CC) -fopenmp -o $(EXEC) $(Files)

run: $(EXEC)
	mpiexec -host linux01:$(Threads),linux03:$(Threads),linux04:$(Threads),linux05:$(Threads),linux06:$(Threads),linux07:$(Threads),linux08:$(Threads),linux09:$(Threads),linux10:$(Threads),linux11:$(Threads),linux12:$(Threads),linux13:$(Threads),linux14:$(Threads),linux15:$(Threads),linux16:$(Threads),linux17:$(Threads),linux18:$(Threads),linux19:$(Threads),linux20:$(Threads),linux21:$(Threads),linux24:$(Threads),linux25:$(Threads),linux26:$(Threads),linux27:$(Threads),linux28:$(Threads),linux29:$(Threads) -n 26 $(EXEC) 10000000000

#Clear
clean:
	rm -f $(EXEC) 	