#! /bin/bash
#
make -s clean && make all -s
echo "Running..."
FILE="output.txt"
rm -f ${FILE}
touch ${FILE}
declare -a chunk=(
[0]=1
[1]=4
[2]=8
[3]=100
)
for m in {0..3}
do
    thread_num=1
    for j in {1..4}
    do
        for k in {1..4}
        do
            declare -a values=(
            [0]=0
            [1]=0
            )
            # if [ $k != 4]
            # then
                for i in {0..4}
                do 
                    values[0]=$(echo ${values[0]} + $(./exe $thread_num 10000 $k ${chunk[$m]} 1) | bc -l | sed 's/^\./0./')
                    values[1]=$(echo ${values[1]} + $(./exe $thread_num 10000 $k ${chunk[$m]} 0) | bc -l | sed 's/^\./0./')
                done
            # else
            #     for i in {0..3}
            #     do 
            #         values[0]=$(echo ${values[0]} + $(./exe 10000 $thread_num $k ${chunk[$m]} 1) | bc -l | sed 's/^\./0./')
            #         values[1]=$(echo ${values[1]} + $(./exe 10000 $thread_num $k ${chunk[$m]} 0) | bc -l | sed 's/^\./0./')
            #     done
            # fi
            for i in {0..1}
            do
                values[i]=$(echo " ${values[i]} / 4" | bc -l | sed 's/^\./0./' )
            done
            if [ $k == 1 ]
            then
                echo "$thread_num 10000 ${values[0]} static ${chunk[$m]} rows" >> ${FILE}
                echo "$thread_num 10000 ${values[1]} static ${chunk[$m]} cols" >> ${FILE}
                echo "#" >> ${FILE}
            elif [ $k == 2 ]
            then
                echo "$thread_num 10000 ${values[0]} dynamic ${chunk[$m]} rows" >> ${FILE}
                echo "$thread_num 10000 ${values[1]} dynamic ${chunk[$m]} cols" >> ${FILE}
                echo "#" >> ${FILE}
            elif [ $k == 3 ]
            then
                echo "$thread_num 10000 ${values[0]} guided ${chunk[$m]} rows" >> ${FILE}
                echo "$thread_num 10000 ${values[1]} guided ${chunk[$m]} cols" >> ${FILE}
                echo "#" >> ${FILE}
            else
                echo "$thread_num 10000 ${values[0]} auto rows" >> ${FILE}
                echo "$thread_num 10000 ${values[1]} auto cols" >> ${FILE}
                echo "$" >> ${FILE}
            fi
        done
        thread_num=$(( $thread_num * 2 ))
    done
done
make -s clean