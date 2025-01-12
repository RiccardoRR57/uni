from collections import Counter

stringa = 'soidwoienfewvwnidncwiowlenw'

res = map(lambda c: c.upper(), filter(lambda c: c not in 'aeiou', stringa))

res = Counter(res)

print(res)