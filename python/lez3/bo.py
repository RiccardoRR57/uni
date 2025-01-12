lista = [ [1, 2, 3] , [ 4, 5, 6], [ 7, [8, 9]]]

def appiattire(lista):
    if not hasattr(lista, '__iter__'):
        return [lista]
    res = []
    for l in lista:
        res.extend(appiattire(l))
    return res



print(appiattire(lista))