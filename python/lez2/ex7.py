import string

testo = input()
occ = {}

for a in string.ascii_lowercase:
    #print(a)
    occ[a]= testo.count(a)

occ = {k: v for k, v in sorted(occ.items(), key=lambda x: x[1])}
print(occ)