x = open("test.txt", 'w')

x.write('ciao')

x.close()

x = open('test.txt', 'r')

s = x.readline()

print(s)