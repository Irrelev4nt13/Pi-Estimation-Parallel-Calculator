# importing the required module
import matplotlib.pyplot as plt
import fileinput as imp
import pandas as pd

# x axis values
# x = [1000000, 2000000, 3000000, 4000000, 5000000, 6000000, 7000000, 8000000, 9000000, 10000000]
(n, m) = rows, cols = (5, 10)

x = [[0 for i in range(cols)] for j in range(rows)]
arr = [[0.0 for i in range(cols)] for j in range(rows)]
thread = [0 for k in range(rows)]
thread[0] = 'Serial'
rows = 1
cols = 0
x[0] = [1000000, 2000000, 3000000, 4000000, 5000000, 6000000, 7000000, 8000000, 9000000, 10000000]
pic = [[0 for i in range(m)] for j in range(n)]
with open('template.txt', 'r') as file:
    for line in file:
        str = line.split()
        if len(str) == 0:
            break
        # Different number of threads
        if str[0] == '#':
            rows += 1
            cols = 0
            continue
        # Get the number of threads (First is always Serial)
        if cols == 0:
            thread[rows] = str[1] + ' Threads'
        # Figure
        arr[rows][cols] = float(str[5])
        x[rows][cols] = int(str[0])
        arr[0][cols] += float(str[3])
        # Array
        if rows == 1:
            pic[0][cols] = float(str[2])
        pic[rows][cols] = float(str[4])
        cols += 1
        # break
    # exit(0)
for i in range(10):
    arr[0][i] /= (n - 1)
i = 0
plt.style.use('ggplot')
for ls in arr:
    plt.plot(x[i], ls, label=thread[i], marker='o', linestyle=":", linewidth=2)
    i += 1
plt.legend(loc='best', framealpha=0)

font2 = {'family': 'serif', 'color': 'darkred', 'size': 15}
# naming the x axis
plt.xlabel('Throws', fontdict=font2)
# naming the y axis
plt.ylabel('Time', fontdict=font2)

# giving a title to my graph
plt.title('Monte-Carlo', loc='left')

plt.grid(axis='x')
# function to show the plot
plt.show()
xpi = ["{:.1e}".format(1000000), 2000000, 3000000, 4000000, 5000000, 6000000, 7000000, 8000000, 9000000, 1e6]

for i in range(10):
    xpi[i] = "{:.1e}".format((i + 1) * 1000000)
df = pd.DataFrame(pic, thread, xpi)
df.to_csv(r'data.csv', index=True, header=True)
# print(df)
