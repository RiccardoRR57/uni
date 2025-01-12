i = [1, 2, 3, 4, 5, 6, 7, 8, 9]


print(list(filter(lambda n: n%4 == 0, map(lambda n: n**2, i))))