l = [1, 4, 63, 234, 151, 125, 134, 8]

pari = filter(lambda a: a % 2 == 0, l)

pari_val=[]
for x in pari:
    pari_val.append(x)

print(list(map(lambda x:x**2, pari_val)))

