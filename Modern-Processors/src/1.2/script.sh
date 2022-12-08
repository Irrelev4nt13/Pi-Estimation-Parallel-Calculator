#! /bin/bash
#
if [ $# != 1 ]
then
    exit 
fi
make -s clean && make all -s
thread_num=$1
echo "Running..."
FILE="output.txt"
rm -f ${FILE}
touch ${FILE}
for i in {1..4} 
do  
    declare -a values=(
        [0]=0
        [1]=0
        [2]=0
        [3]=0
        )
    for i in {1..4}
    do 
        values[0]=$(echo ${values[0]} + $(./exe_o $thread_num 8000000 8) | bc -l | sed 's/^\./0./')
        values[1]=$(echo ${values[1]} + $(./exe_o $thread_num 8000 8000) | bc -l | sed 's/^\./0./')
        values[2]=$(echo ${values[2]} + $(./exe_o $thread_num 8 8000000) | bc -l | sed 's/^\./0./')
        values[3]=$(echo ${values[3]} + $(./exe_o $thread_num 8 80000000) | bc -l | sed 's/^\./0./')
    done
    for i in {0..3}
    do
        values[i]=$(echo "scale=6; ${values[i]} / 4" | bc -l | sed 's/^\./0./' )
    done
    echo "$thread_num 8000000 8 ${values[0]}" >> ${FILE}
    echo "$thread_num 8000 8000 ${values[1]}" >> ${FILE}
    echo "$thread_num 8 8000000 ${values[2]}" >> ${FILE}
    echo "$thread_num 8 80000000 ${values[3]}" >> ${FILE}

    echo "#" >> ${FILE}

    declare -a values=(
        [0]=0
        [1]=0
        [2]=0
        [3]=0
        )
    for i in {1..4}
    do 
        values[0]=$(echo ${values[0]} + $(./exe_1 $thread_num 8000000 8) | bc -l | sed 's/^\./0./')
        values[1]=$(echo ${values[1]} + $(./exe_1 $thread_num 8000 8000) | bc -l | sed 's/^\./0./')
        values[2]=$(echo ${values[2]} + $(./exe_1 $thread_num 8 8000000) | bc -l | sed 's/^\./0./')
        values[3]=$(echo ${values[3]} + $(./exe_1 $thread_num 8 80000000) | bc -l | sed 's/^\./0./')
    done
    for i in {0..3}
    do
        values[i]=$(echo "scale=6; ${values[i]} / 4" | bc -l | sed 's/^\./0./' )
    done
    echo "$thread_num 8000000 8 ${values[0]}" >> ${FILE}
    echo "$thread_num 8000 8000 ${values[1]}" >> ${FILE}
    echo "$thread_num 8 8000000 ${values[2]}" >> ${FILE}
    echo "$thread_num 8 80000000 ${values[3]}" >> ${FILE}

    echo "#" >> ${FILE}

    declare -a values=(
        [0]=0
        [1]=0
        [2]=0
        [3]=0
        )
    for i in {1..4}
    do 
        values[0]=$(echo ${values[0]} + $(./exe_2 $thread_num 8000000 8) | bc -l | sed 's/^\./0./')
        values[1]=$(echo ${values[1]} + $(./exe_2 $thread_num 8000 8000) | bc -l | sed 's/^\./0./')
        values[2]=$(echo ${values[2]} + $(./exe_2 $thread_num 8 8000000) | bc -l | sed 's/^\./0./')
        values[3]=$(echo ${values[3]} + $(./exe_2 $thread_num 8 80000000) | bc -l | sed 's/^\./0./')
    done
    for i in {0..3}
    do
        values[i]=$(echo "scale=6; ${values[i]} / 4" | bc -l | sed 's/^\./0./' )
    done
    echo "$thread_num 8000000 8 ${values[0]}" >> ${FILE}
    echo "$thread_num 8000 8000 ${values[1]}" >> ${FILE}
    echo "$thread_num 8 8000000 ${values[2]}" >> ${FILE}
    echo "$thread_num 8 80000000 ${values[3]}" >> ${FILE}

    echo "$" >> ${FILE}
    if [ $i == 2 ]
    then
        thread_num=$(( $thread_num + 2 ))
    elif [ $i == 3 ]
    then
        thread_num=$(( $thread_num + 4 ))
    else
        thread_num=$(( $thread_num + 1 ))
    fi
done
make -s clean