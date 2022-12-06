#! /bin/bash
#
if [ $# != 2 ]
then
    exit 
fi

cd 1.1

FILE="output.txt"
rm -f ${FILE}
touch ${FILE}

make clean && make
throws=$1
thread_num=$2
echo "#" >> ${FILE}
echo "$throws $thread_num" >> ${FILE}

for i in {1..4}
do
    echo "Running monte carlo for the $i time..."
    ./exe $1 $2 >> ${FILE}
done
NEW_FILE="averages.txt"
rm -f ${NEW_FILE}
touch ${NEW_FILE}
while IFS= read -r line
do 
    # echo $line
    for f in $line
    do    
        if [ $f == "#" ]
        then 
            break
        elif [ $f == $throws ]
        then
            echo $line >> ${NEW_FILE} 
            break
        else
            echo $line
        fi
    done
done <"$FILE"

make clean