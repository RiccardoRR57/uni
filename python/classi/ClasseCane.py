import io


class Animale:
    Specie = " "
    Colore = " "
    zampe = 4
    coda = True
    età = 0
    sesso = 'M'
    __malato = False
    __spavaldo = False

    def __init__(self, Specie, Colore, malato, spavaldo, zampe, coda, età, sesso):
        self.Specie = Specie
        self.Colore = Colore
        self.__malato = malato
        self.__spavaldo = spavaldo
        self.zampe = zampe
        self.coda = coda
        self.età = età
        self.sesso = sesso

    @property
    def set_malato(self, malato):
        if self.__spavaldo == True:
            self.__malato = False
        else:
            self.__malato = malato

    @property
    def set_spavaldo(self, spavaldo):
        self.__spavaldo = spavaldo

    @property
    def get_malato(self):
        return self.__malato

    @property
    def get_spavaldo(self):
        return self.__spavaldo

    def faiVerso(self):
        x = True

        if x == isinstance(self, Cane):
            print("WOF WOF")
        elif x == isinstance(self, Gatto):
            print("MIAO MIAO")
        else:
            print("Questo animale non ha un verso predefinito")


class Cane(Animale):
    razza = " "
    volte = 1 #Attributo di classe che conta quante volte la casse è stata istanziata


    def __init__(self, razza, malato, spavaldo, Specie, Colore, zampe, coda, età, sesso ):
        self.razza = razza
        Cane.volte = Cane.volte + 1 #ogni volta che il metodo __init__ viene chiamato aumentiamo di 1 l'attributo
        #volte di classe
        super().__init__(Specie, Colore, malato, spavaldo, zampe, coda, età, sesso)

    def abbaia(self):
        super().faiVerso()

    def cammina(self):
        print("PADRONE ANDIAMO A CAMMINARE TI PREGO")

    def corri(self):
        print("CORRIAMO PADRONE CORRIAMO WOF WOF")

    def volteChiamate(self): #metodo che ritorna il numero di volte che la classe è stata istanziata.
        return Cane.volte

    def __add__(self, other):
        if (self.età > 15):
            print("Il cane è troppo vecchio per fare figli")
        elif (self.età < 1):
            print("Il cane è troppo piccolo per fare figli")
        elif (self.sesso == other.sesso):
            print("I cani non possono esser ")
        else:
            return Cane(4,True, 0, 'M', False, True)

class Gatto(Animale):
    razza = " "

    def __init__(self, razza, malato, spavaldo, Specie, Colore, zampe, coda, età, sesso):
        self.razza = razza
        super().__init__(Specie, Colore, malato, spavaldo, zampe, coda, età, sesso)

    def miagola(self):
        super().faiVerso()

GoldenRetriever = Cane("GoldenRetriever", False, True, 'Canis', 'Panna', 4, True, 10, 'M' )
print(GoldenRetriever.volteChiamate())
Bassotto = Cane("Bassotto",True,False,'Canis', "Marrone", 4, True, 5, 'F')
print(Bassotto.volteChiamate())
Sfinge = Gatto("Sfinge", False, True, "Felis", "Marroncino", 4, True, 3, 'F')

Sfinge.faiVerso()

a = 0
while(a != 7):
    print("Inserisci: \n \t 1 per vedere gli attributi del cane \n \t 2 per farloa abbaiare \n \t 3 per farlo camminare \n \t 4 per falro correre \n \t 5 per sapere lo stato del cane \n \t 6 per creare un cucciolo \n \t 7 per uscire")
    a = int(input())
    if a == 1:
        print("Il cane in questione ha: ")
        print(GoldenRetriever.zampe)
        print("zampe, ha la coda? " )
        print(GoldenRetriever.coda)
        print(" É di anni: ")
        print(GoldenRetriever.età)
        print("e di sesso è: ")
        print(GoldenRetriever.sesso)
        print("Razza: ")
        print(GoldenRetriever.razza)
        print("Specie: ")
        print(GoldenRetriever.razza)
        print("Colore: ")
        print(GoldenRetriever.Colore)

    elif a == 2:
        print(GoldenRetriever)
        GoldenRetriever.faiVerso()
    elif a == 3:
        GoldenRetriever.cammina()
    elif a == 4:
        GoldenRetriever.corri()
    elif a == 5:
        
        print(GoldenRetriever.get_malato())
        print(GoldenRetriever.get_spavaldo())
    elif a == 6:
        print("Stiamo creando il tuo nuovo cane...")

        GoldenRetriever.__add__(Bassotto)


    elif a == 7:
        print("Buona gioranta padrone")
    else:
        print("Il valore inserito non è valido")