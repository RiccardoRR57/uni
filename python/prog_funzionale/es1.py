import functools as ft

i = "iscbdiwbdciducniwecnwi"

res = filter(lambda c:c not in "aeiou", i)

res = map(lambda c:c.upper(), res)

print(''.join(res))
