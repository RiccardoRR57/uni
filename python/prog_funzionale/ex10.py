from  functools import partial 

def mul(a, b):
    return a*b

p = partial(mul, 5)


print(p(2343))

