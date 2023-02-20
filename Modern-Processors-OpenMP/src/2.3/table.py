**# importing the required module
import pandas as pd
import math

(rows, cols, i) = (m, n, z) = (17, 4, 4)
values = ["rows", "cols", "schedule_type", "chunk_size"]

appp = [[[math.inf for iol in range(i)] for col in range(cols)] for row in range(rows)]

mina = [[" " for colq in range(i)] for rowq in range(cols)]
cols = 0
rows = 0
i = 0
reset = 0
with open('Output_tests/output.txt', 'r') as file:
    for line in file:
        str1 = line.split()
        if len(str1) == 0:
            break
        # Different number approach of the problem
        if str1[0] == '#':
            i = 0
            cols += 1
            continue
        # Different thread test
        if str1[0] == '$':
            rows += 1
            cols = reset
            i = 0
            continue
        appp[rows][cols][i] = float(str1[2])

        appp[rows][cols][2] = str1[3]
        if str1[3] == "auto":
            appp[rows][cols][3] = "-"
        else:
            appp[rows][cols][3] = str1[4]
        i += 1

df = pd.DataFrame([], ["Chunk size " + str(appp[i][0][3])])
ls = [df]
# for x in appp:
#     print(x)
# exit()
i = 0
k = 1
for x in appp:
    if i % 4 == 3:
        k = 8
    elif i % 4 == 2:
        k = 4
    elif i % 4 == 1:
        k = 2
    else:
        k = 1
    print(k, x)
    if i != 16:
        for y in x:
            minim = min(y[0], y[1])
            if y[0] == minim:
                impl = "rows"
            else:
                impl = "cols"
            if minim < appp[m - 1][i % 4][0]:
                appp[m - 1][i % 4][0] = minim
                appp[m - 1][i % 4][1] = y[2]
                appp[m - 1][i % 4][2] = y[3]
                appp[m - 1][i % 4][3] = impl
    thread = [k, k, k, k]

    if i == 16:
        thread = [1, 2, 4, 8]
    df = pd.DataFrame(x, thread, values)
    index = df.index
    if i != 0:
        if i < 16:
            index.name = "Chunk size " + str(appp[i][0][3])
        else:
            index.name = "Fastest schedule type and chunk size"
        df1 = pd.DataFrame([], [index.name])
        ls.append(df1)
    i += 1

    ls.append(df)

pd.concat(ls).to_csv('Output_tests/TIME.csv', index=True, header=True)
