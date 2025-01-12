/*

Percorso
(Una versione semplificata è presente nell'esercizio percorso_semplificato.cc)


Un Percorso è formato da N caselle, ciascuna delle quali può assumere
il colore bianco od il colore nero. Nel percorso transitano pedine
bianche e pedine nere. Su ogni casella può sostare o transitare una
sola pedina alla volta, e solo se il colore di tale pedina è uguale al
colore di quella casella. Quando una pedina arriva sull'ultima
casella, esce dal percorso. Le operazioni che possono essere
effettuate su un percorso sono le seguenti:

·	inizializza(p, N, c);
Inizializza un percorso p di lunghezza N. Inizialmente, tutte le
caselle sono di colore c.

· inizializza_copia(p1, p); 

Inizializza il valore del percorso p1 col valore del percorso p.

·       immetti(p, c) 
Operazione che causa l'immissione di una nuova pedina nel percorso
p. Tale pedina ha colore c, e si porta nella casella più avanzata
possibile. L'immissione ha successo solo se la prima casella del
percorso p è vuota, ed ha colore c. Se una di queste condizioni non è
verificata, l'operazione lascia il percorso inalterato. Attenzione al
fatto che, se si immette una pedina di colore c in un percorso vuoto e
formato solo da caselle di colore c, allora la pedina si porta
direttamente nella posizione più avanzata ed esce dal percorso.

·	cambiaColore(p, i)
Operazione che cambia il colore della i-esima casella del percorso p,
se tale casella è libera. Questa operazione può causare il movimento
di una o più pedine. Ciascun pedina si porta nella casella più
avanzata possibile.

·	stampa(p)
Operatore di uscita per il tipo Percorso. L'uscita ha la forma seguente:
		bbBBBnBBNNb

Il carattere 'b' rappresenta una casella libera bianca, il carattere
'n' rappresenta una casella libera nera, il carattere 'B' rappresenta
una casella occupata da una pedina bianca, ed, infine, il carattere
'N' rappresenta una casella occupata da una pedina nera. 

Utilizzando il linguaggio C++, realizzare il tipo di dato Percorso,
definito dalle precedenti specifiche.

*/

#include <iostream>

using namespace std ;

enum colore {BIANCO, NERO} ;
enum stato {LIBERA, OCCUPATA} ;

struct casella {
    stato st;
    colore col;
} ;

void inizializza_casella(casella &cas, colore c) 
{
    cas.col = c; 
    cas.st = LIBERA;
}

void cambiaColore_cas(casella &cas) 
{
    cas.col = (cas.col == BIANCO) ? NERO : BIANCO;
}

void occupa(casella &cas) 
{
    cas.st = OCCUPATA;
}

void libera(casella &cas) 
{
    cas.st = LIBERA;
}

int seiOccupata(const casella &cas) 
{
    return cas.st == OCCUPATA;
}

colore qualeColore(const casella &cas) 
{
    return cas.col;
}

struct Percorso {
    casella * cc ;
    int lunghezza ;
};

void errore(const char* s)
{
    cout<<"Percorso: "<<s<<endl ;
    exit(1);
}

int avanza(Percorso &p, int i)
{
    int j ;
    for (j = i + 1; j < p.lunghezza && !seiOccupata(p.cc[j]) &&
	     qualeColore(p.cc[i]) == qualeColore(p.cc[j]); j++);
    return j - 1;
}

void inizializza(Percorso &p, int lungh, colore c)
{
    if (lungh < 1)
	errore("Lunghezza errata");
    p.lunghezza = lungh;
    p.cc = new casella[p.lunghezza] ;
    for (int i = 0; i < p.lunghezza; i++)
	inizializza_casella(p.cc[i], c) ;
}

void inizializza_copia(Percorso &p, const Percorso &p1)
{
    p.lunghezza = p1.lunghezza;
    p.cc = new casella[p.lunghezza] ;

    for (int i = 0; i < p.lunghezza; i++)
	p.cc[i] = p1.cc[i];
}

void immetti(Percorso &p, colore c)
{
    if (!seiOccupata(p.cc[0]) && qualeColore(p.cc[0]) == c) {
	int i = avanza(p, 0);
	if (i < p.lunghezza - 1)
	    occupa(p.cc[i]);
    }
}

void cambiaColore(Percorso &p, int i)
{
    if (i < 1 || i > p.lunghezza)
	errore("Numero di casella errato");
    --i;
    if (!seiOccupata(p.cc[i])) {
	int j, k ;
	cambiaColore_cas(p.cc[i]);
	for (j = i - 1; j >= 0 && seiOccupata(p.cc[j]) &&
		 qualeColore(p.cc[i]) == qualeColore(p.cc[j]); j--) {
	    libera(p.cc[j]);
	    k = avanza(p, j);
	    if (k < p.lunghezza - 1)
		occupa(p.cc[k]);
	}
    }
}

void stampa(const Percorso &p)
{
    int i ;

    for (i = 0; i < p.lunghezza; i++)
	if (seiOccupata(p.cc[i])) {
	    if (qualeColore(p.cc[i]) == BIANCO)
		cout<<"B" ;
	    else
		cout<<"N" ;
	}
	else {
	    if (qualeColore(p.cc[i]) == BIANCO)
		cout<<"b" ;
	    else
		cout<<"n"  ;
	}
}

void elimina(Percorso &p)
{
    free(p.cc) ;
}

int main()
{
	const char Menu[] = "\nComandi disponibili:\n"
"\tn (N) - per immettere una pedina nera in p1 (p2)\n"
"\tb (B) - per immettere una pedina bianca in p1 (p2)\n"
"\tc (C) - per cambiare il colore di una casella di p1 (p2)\n"
"\td     - per continuare con due nuovi percorsi\n"
"\tq     - per terminare\n";

	char comando;
	do {
	    struct Percorso p1;
	    struct Percorso p2;

	    cout<< "Inizializzo due percorsi p1 e p2.\n" ;
	    inizializza(p1, 10, NERO);
	    inizializza_copia(p2, p1);
	    cout<< "p1: " ;
	    stampa(p1) ;
	    cout<< "\np2: " ;
	    stampa(p2) ;
	    cout<<endl ;
	    cout<<Menu<<"\n\nComando? " ;
	    cin>>comando ;

	    while (comando != 'd' && comando != 'q') {
		switch (comando) {
		case 'n': 
		    immetti(p1, NERO);
		    break;
		case 'N': 
		    immetti(p2, NERO);
		    break;
		case 'b': 
		    immetti(p1, BIANCO);
		    break;
		case 'B': 
		    immetti(p2, BIANCO);
		    break;
		case 'c': {
		    cout<<"Posizione casella? " ;
		    int i;
		    cin>>i ;
		    cambiaColore(p1, i);
		    break;
		}
		case 'C': {
		    cout<<"Posizione casella? " ;
		    int i;
		    cin>>i ;
		    cambiaColore(p2, i);
		    break;
		}
		default:
		    cout<< "Comando "<<comando<<" non valido\n" ;
		}
		cout<< "p1: " ;
		stampa(p1) ;
		cout<< "\np2: " ;
		stampa(p2) ;
		cout<<endl ;
		cout<<Menu<<"\n\nComando? " ;
		cin>>comando ;
	    }
	    elimina(p1) ;
	    elimina(p2) ;
	} while (comando != 'q');
	cout<< "*\n" ;
}

