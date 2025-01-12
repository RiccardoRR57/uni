valori=[]

while True:
    val = input()
    if  val == '#' :
        break
    valori.append(val)


def fun(val):
    print(val)

list(map(fun, valori))