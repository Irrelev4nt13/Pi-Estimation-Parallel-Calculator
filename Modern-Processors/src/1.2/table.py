# importing the required module
import pandas as pd

(rows, cols, i) = (n, m, z) = (4, 3, 4)
values = ["8000000*8", "8000*8000", "8*8000000", "8*80000000"]
thread = [0 for k in range(rows)]
appp = [[[0 for iol in range(i)] for col in range(rows)]
        for row in range(cols)]
cols = 0
rows = 0
i = 0
with open('output.txt', 'r') as file:
    for line in file:
        str1 = line.split()
        if len(str1) == 0:
            break
        # Different number approach of the problem
        if str1[0] == '#':
            i = 0
            rows += 1
            continue
        # Different thread test
        if str1[0] == '$':
            cols += 1
            rows = 0
            i = 0
            continue
        if rows == 0:
            thread[cols] = str1[0] + " Threads"
        appp[rows][cols][i] = float(str1[3])
        i += 1
df = pd.DataFrame([], ["Original"])
ls = [df]
i = 0
for x in appp:
    df = pd.DataFrame(x, thread, values)
    index = df.index
    if i != 0:
        index.name = "Approach " + str(i)
        df1 = pd.DataFrame([], ["Approach " + str(i)])
        ls.append(df1)
    i += 1

    ls.append(df)

pd.concat(ls).to_csv('TIME.csv', index=True, header=True)
