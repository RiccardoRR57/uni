matrix= [[1, 2, 3], [4, 5, 6], [7, 8, 9]]

x=open('m', 'w')
x.write(str(matrix))

x.close()

x=open('m', 'r')

s=x.read()
