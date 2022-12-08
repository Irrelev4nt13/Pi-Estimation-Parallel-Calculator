#! /bin/bash
#
if [ $# != 1 ]
then
    exit 
fi
cd 1.2
make -s clean && make all -s
thread_num=$1
echo "Running..."
FILE="output.txt"
rm -f ${FILE}
touch ${FILE}
for i in {1..4} 
do  
    echo "$thread_num 8000000 8 $(./exe_o $thread_num 8000000 8)" >> ${FILE}
    echo "$thread_num 8000 8000 $(./exe_o $thread_num 8000 8000)" >> ${FILE}
    echo "$thread_num 8 8000000 $(./exe_o $thread_num 8 8000000)" >> ${FILE}
    echo "$thread_num 8 80000000 $(./exe_o $thread_num 8 80000000)" >> ${FILE}
    echo "#" >> ${FILE}
    echo "$thread_num 8000000 8 $(./exe_1 $thread_num 8000000 8)" >> ${FILE}
    echo "$thread_num 8000 8000 $(./exe_1 $thread_num 8000 8000)" >> ${FILE}
    echo "$thread_num 8 8000000 $(./exe_1 $thread_num 8 8000000)" >> ${FILE}
    echo "$thread_num 8 80000000 $(./exe_1 $thread_num 8 80000000)" >> ${FILE}
    echo "#" >> ${FILE}
    echo "$thread_num 8000000 8 $(./exe_2 $thread_num 8000000 8)" >> ${FILE}
    echo "$thread_num 8000 8000 $(./exe_2 $thread_num 8000 8000)" >> ${FILE}
    echo "$thread_num 8 8000000 $(./exe_2 $thread_num 8 8000000)" >> ${FILE}
    echo "$thread_num 8 80000000 $(./exe_2 $thread_num 8 80000000)" >> ${FILE}
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