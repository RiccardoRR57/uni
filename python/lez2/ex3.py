

voc = ['red', 'blue', 'green']



# try:
#     print(voc[intero-1])
# except:
#     print('errore')


dizionario = {"1":'red', '2':'blue', '3':'green'}

while(True) :
    input1 = input()
    if(input1=='fine'):
        exit()
    print(dizionario.get(input1, 'errore'))
