# importing the required module
import pandas as pd

(rows, cols, i) = (n, m, z) = (3, 3, 4)
thread = ["1 Threads", "2 Threads", "4 Threads", "8 Threads"]
appp = [[[0 for iol in range(i)] for col in range(rows)]
        for row in range(cols)]
implementation = ["orig", "writers", "readers"]
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
        appp[cols][rows][i] = float(str1[1])
        i += 1

df = pd.DataFrame([], ["50% READS,25% INSERTS,25% DELETES"])
ls = [df]
i = 0
for x in appp:
    df = pd.DataFrame(x, implementation, thread)
    index = df.index
    if i == 1:
        index.name = "80% READS,10% INSERTS,10% DELETES"
        df1 = pd.DataFrame([], ["80% READS,10% INSERTS,10% DELETES"])
        ls.append(df1)
    elif i == 2:
        index.name = "20% READS,40% INSERTS,40% DELETES"
        df1 = pd.DataFrame([], ["20% READS,40% INSERTS,40% DELETES"])
        ls.append(df1)
    i += 1
    ls.append(df)

pd.concat(ls).to_csv('TIME.csv', index=True, header=True)
