#! /bin/bash
#
if [ $# != 2 ]
then
    exit 
fi
make -s clean && make -s
throws=$1
throws_step=$throws
thread_num=$2
NEW_FILE="averages.txt"
rm -f ${NEW_FILE}
touch ${NEW_FILE}
echo "Running..."
for j in {1..4} 
do  
    throws=$throws_step
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
        [2]=0
        [3]=0
        )
        counter=0
        while IFS= read -r line
        do 
            for f in $line
            do    
                if [ $f == "#" ]
                then 
                    # echo "#" >> ${NEW_FILE}
                    break
                elif [ $f == $throws ]
                then
                    # echo $line >> ${NEW_FILE} 
                    break
                else
                    read -ra split <<< "$line"
                    if [ $(( counter % 2 )) == 0 ]
                    then
                        values[0]=$(echo ${values[0]} + ${split[0]} | bc -l | sed 's/^\./0./' )
                        values[1]=$(echo ${values[1]} + ${split[1]} | bc -l | sed 's/^\./0./' )
                    else
                        values[2]=$(echo ${values[2]} + ${split[0]} | bc -l | sed 's/^\./0./' )
                        values[3]=$(echo ${values[3]} + ${split[1]} | bc -l | sed 's/^\./0./' )
                    fi
                    break
                fi
            done
            (( counter++ ))
        done <"$FILE"
        for i in {0..3}
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