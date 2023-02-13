#! /bin/bash
#
make -s clean && make all -s
echo "Running..."
FILE="output.txt"
rm -f ${FILE}
touch ${FILE}
for j in {1..3}
do
    if [ $j == 1 ]
    then
        path="inputs/50percent.txt"
    elif [ $j == 2 ]
    then
        path="inputs/80percentread.txt"
    else
        path="inputs/80percentwrite.txt"
    fi
    thread_num=1
    for k in {1..4} 
    do  
        declare -a values=(
        [0]=0
        )
        for i in {1..4}
        do 
            values[0]=$(echo ${values[0]} + $(./exe_1 $thread_num < ${path} ) | bc -l | sed 's/^\./0./')
        done
        
        values[0]=$(echo " ${values[0]} / 4" | bc -l | sed 's/^\./0./' )
        
        echo "$thread_num ${values[0]}" >> ${FILE}

        thread_num=$(( $thread_num * 2 ))
    done
        echo "#" >> ${FILE}

    thread_num=1
    for k in {1..4} 
    do  
        declare -a values=(
        [0]=0
        )
        for i in {1..4}
        do 
            values[0]=$(echo ${values[0]} + $(./exe_2 $thread_num r < ${path} ) | bc -l | sed 's/^\./0./')
        done
        
        values[0]=$(echo " ${values[0]} / 4" | bc -l | sed 's/^\./0./' )
        
        echo "$thread_num ${values[0]}" >> ${FILE}

        thread_num=$(( $thread_num * 2 ))
    done
        echo "#" >> ${FILE}

    thread_num=1
    for k in {1..4} 
    do  
        declare -a values=(
        [0]=0
        )
        for i in {1..4}
        do 
            values[0]=$(echo ${values[0]} + $(./exe_2 $thread_num w < ${path} ) | bc -l | sed 's/^\./0./')
        done
        
        values[0]=$(echo " ${values[0]} / 4" | bc -l | sed 's/^\./0./' )
        
        echo "$thread_num ${values[0]}" >> ${FILE}

        thread_num=$(( $thread_num * 2 ))
    done
    echo "$" >> ${FILE}
done
make -s clean