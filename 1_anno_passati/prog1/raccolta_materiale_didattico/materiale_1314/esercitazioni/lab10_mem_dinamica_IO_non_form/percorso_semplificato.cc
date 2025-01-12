/*

Percorso Semplificato

Un Percorso è formato da N caselle, ciascuna delle quali può assumere
il colore bianco od il colore nero. Le operazioni che possono essere
effettuate su un percorso sono le seguenti:

·	inizializza(p, N, c);
Inizializza un percorso p di lunghezza N. Inizialmente, tutte le
caselle sono di colore c.

· 	inizializza_copia(p1, p); 

Inizializza il valore del percorso p1 col valore del percorso p.

·	cambiaColore(p, i)
Operazione che cambia il colore della i-esima casella del percorso p.

·	stampa(p)
Operatore di uscita per il tipo Percorso. L'uscita ha la forma seguente:
		bbnnnb

Il carattere 'b' rappresenta una casella bianca, il carattere
'n' rappresenta una casella nera.

Utilizzando il linguaggio C++, realizzare il tipo di dato Percorso,
definito dalle precedenti specifiche.

Quale soluzione intermedia, un possibile main per questo esercizio si
trova nel file percorso_semplificato_solo_main.cc.

*/

#include <iostream>

using namespace std ;

enum colore {BIANCO, NERO} ;

void cambiaColore_cas(colore &cas)
{
    cas = (cas == BIANCO) ? NERO : BIANCO;
}

struct Percorso {
	colore *cc ; // puntatore ad array dinamico
    int lunghezza ;
} ;

void errore(const char s[])
{
    cout<<"Percorso: \n"<<s ;
    exit(1);
}

void inizializza(Percorso &p, int lungh, colore c)
{
    if (lungh < 1)
	errore("Lunghezza errata");
    p.lunghezza = lungh;
    p.cc = new colore[p.lunghezza] ;
    for (int i = 0; i < p.lunghezza; i++)
	p.cc[i] = c ;
}

void inizializza_copia(Percorso& p, const Percorso &p1)
{
    p.lunghezza = p1.lunghezza;
    p.cc = new colore[p.lunghezza] ;

    for (int i = 0; i < p.lunghezza; i++)
	p.cc[i] = p1.cc[i];
}

void cambiaColore(Percorso &p, int i)
{
    if (i < 1 || i > p.lunghezza)
	errore("Numero di casella errato");
    --i;
    cambiaColore_cas(p.cc[i]);
}

void stampa(const Percorso& p)
{
    for (int i = 0; i < p.lunghezza; i++)
	if (p.cc[i] == BIANCO)
	    cout<<"b" ;
	else
	    cout<<"n"  ;
}

void elimina(Percorso &p)
{
    delete[] p.cc ;
}

int main()
{
	const char Menu[] = "\nComandi disponibili:\n"
		"\tc (C) - per cambiare il colore di una casella di p1 (p2)\n"
		"\td     - per continuare con due nuovi percorsi\n"
		"\tq     - per terminare\n";

	char comando;
	do {
	    Percorso p1, p2;

	    cout<<"Inizializzo due percorsi p1 e p2.\n" ;
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

