diz = {1:'dispari', 0:'pari'}

for i in range(101):
    print(diz.get(i%2))