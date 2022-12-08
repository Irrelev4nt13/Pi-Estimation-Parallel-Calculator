#! /bin/bash
#
if [ $# != 1 ]
then
    exit 
fi
cd 1.2
make -s clean && make -s
thread_num=$1
echo "Running..."
FILE="output.txt"
rm -f ${FILE}
touch ${FILE}
for i in {1..4} 
do  
    value=$(./exe $thread_num 8000000 8)
    echo "$thread_num 8000000 8 $value" >> ${FILE}
    value=$(./exe $thread_num 8000 8000)
    echo "$thread_num 8000 8000 $value" >> ${FILE}
    value=$(./exe $thread_num 8 8000000)
    echo "$thread_num 8 8000000 $value" >> ${FILE}
    value=$(./exe $thread_num 8 80000000)
    echo "$thread_num 8 80000000 $value" >> ${FILE}
    if [ $i == 2 ]
    then
        thread_num=$(( $thread_num + 2 ))
    elif [ $i == 3 ]
    then
        thread_num=$(( $thread_num + 4 ))
    else
        thread_num=$(( $thread_num + 1 ))
    fi
    echo "#" >> ${FILE}
done
make -s clean