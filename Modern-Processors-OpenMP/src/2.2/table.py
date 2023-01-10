# importing the required module
import pandas as pd
import math

(rows, cols, i) = (m, n, z) = (19, 3, 6)
values = ["8000000*8", "8000*8000", "8*8000000", "8*80000000", "schedule_type", "chunk_size"]
thread = [0 for k in range(cols)]
appp = [[[math.inf for iol in range(i)] for col in range(cols)] for row in range(rows)]

min = [[" " for colq in range(i)] for rowq in range(cols)]
cols = 0
rows = 0
i = 0
reset = 0
with open('Output_tests/output.txt', 'r') as file:
    for line in file:
        str1 = line.split()
        if len(str1) == 0:
            break
        if str1[0] == '%':
            rows += 1
            cols = 0
            i = 0
            reset = rows
            continue
        # Different number approach of the problem
        if str1[0] == '#':
            i = 0
            rows += 1
            continue
        # Different thread test
        if str1[0] == '$':
            cols += 1
            rows = reset
            i = 0
            continue
        appp[rows][cols][i] = float(str1[3])
        if rows == 0 or rows == 1:
            appp[rows][cols][4] = "-"
            appp[rows][cols][5] = "-"
            thread[cols] = str1[0] + " Threads"
        else:
            appp[rows][cols][4] = str1[4]
            appp[rows][cols][5] = str1[5]
            if appp[rows][cols][i] < appp[18][cols][i]:
                appp[m - 1][cols][i] = appp[rows][cols][i]
                min[cols][i] = str1[4] + " " + str1[5]

        i += 1
# for x in appp:
#     print(x)

for i in range(n):
    appp[m - 1][i][4] = "-"
    appp[m - 1][i][5] = "-"
    for j in range(z):
        appp[m - 1][i][j] = str(appp[m - 1][i][j]) + " " + min[i][j]
df = pd.DataFrame([], ["Original"])
ls = [df]
i = 0
for x in appp:
    df = pd.DataFrame(x, thread, values)
    index = df.index
    if i != 0:
        if i < 2:
            index.name = "Approach " + str(i)
        elif i < 18:
            index.name = "Chunk size " + str(appp[i][0][5])
        else:
            index.name = "Fastest schedule type and chunk size"
        df1 = pd.DataFrame([], [index.name])
        ls.append(df1)
    i += 1

    ls.append(df)

pd.concat(ls).to_csv('Output_tests/TIME.csv', index=True, header=True)
