#! /bin/bash
#
if [ $# != 1 ]
then
    exit 
fi
make -s clean && make all -s
step=1024
echo "Running..."
FILE="output.txt"
rm -f ${FILE}
touch ${FILE}
for k in {1..6} 
do  
    thread_num=$1
    for i in {1..5}
    do
        echo "$step * $step"
        declare -a values=([0]=0)
        for i in {1..4}
        do 
            values[0]=$(echo ${values[0]} + $(mpiexec -n $thread_num exe_0 $step 1) | bc -l | sed 's/^\./0./')
        done
        
        values[0]=$(echo " ${values[0]} / 4" | bc -l | sed 's/^\./0./' )
        
        echo "$thread_num ${values[0]}" >> ${FILE}

        echo "#" >> ${FILE}

        declare -a values=([0]=0)
        for i in {1..4}
        do 
            values[0]=$(echo ${values[0]} + $(mpiexec -n $thread_num exe_2 $step 1) | bc -l | sed 's/^\./0./')
        done
        
        values[0]=$(echo " ${values[0]} / 4" | bc -l | sed 's/^\./0./' )
        
        echo "$step * $step"

        echo "$thread_num ${values[0]}" >> ${FILE}

        echo "$" >> ${FILE}
        thread_num=$(( $thread_num * 2 ))
    done
    step=$(( $step * 2 ))
done
make -s clean