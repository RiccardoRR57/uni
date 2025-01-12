class Cane:
    n_istanze=0

    def __new__(cls):
        Cane.n_istanze +=1

    def __init__(self, sesso, zampe=4, coda=True, eta=0):
        self.zampe=zampe
        self.coda=coda
        self.eta=eta
        self.sesso=sesso
        self._malato=False
        self._spavaldo=False
        pass

    def __add__(self, other):
        pass

    @property
    def malato(self):
        if(self.spavaldo):
            return False
        else:
            return self._malato

    @malato.setter
    def nome(self, malato):
        self._malato=malato

    @property
    def spavaldo(self):
        return self._spavaldo

    @spavaldo.setter
    def nome(self, malato):
        self._spavaldo=malato

    def get_n_istanze():
        return Cane.n_istanze

    def abbaia():
        pass

    def cammina():
        pass

    def corri():
        pass


cleo = Cane('f')
print(cleo.zampe)
print(Cane.get_n_istanze())
