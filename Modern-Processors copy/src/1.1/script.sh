#! /bin/bash
#
# if [ $# != 2 ]
# then
#     exit 
# fi
make -s clean && make -s
throws=$1
throws_step=$throws
thread_num=$2
NEW_FILE="averages.txt"
rm -f ${NEW_FILE}
touch ${NEW_FILE}
echo "Running..."
for j in {1..2} 
do  
    throws=$throws_step
    if [ $j == 2 ]
    then 
        throws=$(( $throws * 10 ))
        throws_step=$(( $throws_step * 10 ))
    fi
    for i in {1..10}
    do
        FILE="output.txt"
        rm -f ${FILE}
        touch ${FILE}
        echo "#" >> ${FILE}
        echo "$throws $thread_num" >> ${FILE}
        for i in {1..4}
        do
            ./exe $throws $thread_num >> ${FILE}
        done
        declare -a values=(
        [0]=0
        [1]=0
        )
        counter=0
        while IFS= read -r line
        do 
            for f in $line
            do    
                if [ $f == "#" ]
                then 
                    break
                elif [ $f == $throws ]
                then
                    break
                else
                    read -ra split <<< "$line"
                    values[0]=$(echo ${values[0]} + ${split[0]} | bc -l | sed 's/^\./0./' )
                    values[1]=$(echo ${values[1]} + ${split[1]} | bc -l | sed 's/^\./0./' )
                    break
                fi
            done
        done <"$FILE"
        for i in {0..1}
        do
            IFS='.'
            read -ra length <<< "${values[i]}"
            IFS=" "
            values[i]=$( echo " ${values[i]} / 4" | bc -l | sed 's/^\./0./' )
        done
        echo $throws $thread_num ${values[@]} >> ${NEW_FILE}
        throws=$(( $throws + $throws_step ))
    done
    thread_num=$(( $thread_num + 2 ))
    echo "#" >> ${NEW_FILE}
done
FILE="output.txt"
rm -f ${FILE}
make -s clean
