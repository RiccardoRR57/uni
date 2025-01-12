import functools as ft

i = ['123', '456', '789']

print(ft.reduce(lambda a, b: a+b , map(lambda s: int(s), i)))