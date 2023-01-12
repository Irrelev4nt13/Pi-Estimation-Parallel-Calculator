# importing the required module
import matplotlib.pyplot as plt
import pandas as pd

(n, m) = rows, cols = (5, 10)

x = [[0 for i in range(cols)] for j in range(rows)]
arr = [[0.0 for i in range(cols)] for j in range(rows)]
thread = [0 for k in range(rows)]
rows = 0
cols = 0
pic = [[0 for i in range(m)] for j in range(n)]
with open('outputs/averages8.txt', 'r') as file:
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
        if rows == 1 and cols == 0:
            mult = int(str[0])
        # Figure
        arr[rows][cols] = float(str[3])
        x[rows][cols] = int(str[0])
        # Array
        pic[rows][cols] = float(str[2])
        cols += 1
# for i in range(10):
#     arr[0][i] /= (n - 1)
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
plt.savefig('plot.png')
plt.show()
xpi = [0 for i in range(m)]
for i in range(m):
    xpi[i] = "{:.1e}".format((i + 1) * mult)
df = pd.DataFrame(pic, thread, xpi)
df1 = pd.DataFrame(arr, thread, xpi)
df.to_csv(r'PI.csv', index=True, header=True)
df1.to_csv(r'TIME.csv', index=True, header=True)
