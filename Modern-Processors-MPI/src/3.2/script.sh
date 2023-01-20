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
    echo "$step*$step" >> ${FILE}
    for i in {1..5}
    do
        declare -a values=([0]=0)
        if [ $i != 1 ]
        then
            echo >> ${FILE}
        fi
            echo -n "$thread_num " >> ${FILE}
        for i in {1..8}
        do 
            values[0]=$(echo $(mpiexec -n $thread_num exe_0 $step 1) | bc -l | sed 's/^\./0./')
            echo -n "${values[0]} " >> ${FILE}
        done
        
        # values[0]=$(echo " ${values[0]} / 4" | bc -l | sed 's/^\./0./' )
        
        # echo "$thread_num ${values[0]}" >> ${FILE}

        thread_num=$(( $thread_num * 2 ))
    done
    echo >> ${FILE}
    echo "#" >> ${FILE}
    thread_num=$1
    echo "$step*$step" >> ${FILE}
    for i in {1..5}
    do
        declare -a values=([0]=0)
        if [ $i != 1 ]
        then
            echo >> ${FILE}
        fi
            echo -n "$thread_num " >> ${FILE}

        for i in {1..8}
        do 
            values[0]=$(echo $(mpiexec -n $thread_num exe_1 $step 1) | bc -l | sed 's/^\./0./')
            echo -n "${values[0]} " >> ${FILE}
        done
        
        # values[0]=$(echo " ${values[0]} / 4" | bc -l | sed 's/^\./0./' )

        # echo "$thread_num ${values[0]}" >> ${FILE}

        thread_num=$(( $thread_num * 2 ))
    done
    echo >> ${FILE}
    echo "$" >> ${FILE}
    step=$(( $step * 2 ))
done
make -s clean