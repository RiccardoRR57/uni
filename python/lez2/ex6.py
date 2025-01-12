rubrica = {}

while True:
    print('1:\tAdd Number\n2:\tRemove Number\n3:\tPrint\n4:\tExit')
    a=input()
    if(int(a)==1):
        print('Name: ')
        name=input()
        print('Number:')
        num=input()
        rubrica[name] = num
    elif(int(a)==2):
        print('Name: ')
        name=input()
        rubrica.pop(name)
    elif(int(a)==3):
        print(rubrica)
    elif(int(a)==4):
        exit()