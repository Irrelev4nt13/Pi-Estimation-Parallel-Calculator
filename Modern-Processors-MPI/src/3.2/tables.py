# importing the required module
import pandas as pd
import math

(rows, cols, i) = (m, n, z) = (2, 5, 6)
thread = ["1 Thread", "2 Thread", "4 Thread", "8 Thread", "16 Thread"]
appp = [[[0 for iol in range(i)] for col in range(cols)] for row in range(rows)]
values = []
minim = []
cols = 0
rows = 0
i = 0
reset = 0
with open('output.txt', 'r') as file:
    for line in file:
        str1 = line.split()
        if len(str1) == 0:
            break
        # Different number approach of the problem
        if str1[0] == '#':
            rows += 1
            cols = 0
            continue
        # Different thread test
        if str1[0] == '$':
            i += 1
            rows = 0
            cols = 0
            continue
        if len(str1) == 1:
            if rows == 0:
                values.append(str1[0])
            continue
        minim.clear()
        for elem in str1:
            minim.append(float(elem))
        minim.pop(0)
        appp[rows][cols][i] = min(minim)
        cols += 1
df = pd.DataFrame()
ls = [df]
i = 0
for x in appp:
    df = pd.DataFrame(x, thread, values)
    index = df.index
    if i == 0:
        index.name = "Per rows"
    else:
        index.name = "Per columns"
    df1 = pd.DataFrame([], [index.name])
    ls.append(df1)

    i += 1

    ls.append(df)

pd.concat(ls).to_csv('TIME.csv', index=True, header=True)
