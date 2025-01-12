import functools as ft

def concatenate_strings(*args, separator=''):
     return ft.reduce(lambda a, b: a+separator+b, args)


print(concatenate_strings("ciao", "cansocn", "wocid", separator='###'))


def create_multiplier(n):
    def mul(a):
        return n*a
    return mul

tre = create_multiplier(3)
print(tre(5))

print(list(i for i in range(26) if i%2==1))