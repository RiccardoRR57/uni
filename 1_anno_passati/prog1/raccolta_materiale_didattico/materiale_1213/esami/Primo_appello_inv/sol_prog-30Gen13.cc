#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std ;

const int NUM_PILE = 3 ;
const char NOME_FILE[] = "insieme.txt" ;

struct pila_t {
    int *elementi ;
    int num_elem ;
} ;

// descrittore insieme di pile
struct insieme_t {
	pila_t pile[NUM_PILE] ; // array contenente le pile
	int capienza ;  // capienza corrente delle pile
	int vett_indici[NUM_PILE] ; /* vettore statico, il cui i-esimo
				     * elemento contiente l'indice
				     * della pila nella i-esima
				     * posizione in termini di
				     * lunghezza: il primo elemento
				     * contiene l'indice della pila
				     * col numero minimo di elementi,
				     * il secondo elemento contiene
				     * l'indice della pila con numero
				     * di elementi minimo tra le pile
				     * rimanenti, e così via.
				     */
} ;

// inizializza l'insieme a capienza nulla
void inizializza(insieme_t &ins)
{
    ins.capienza = 0 ;
    for (int i = 0 ; i < NUM_PILE ; i ++)
	ins.pile[i].num_elem = 0 ;
}

void scambia(int &a, int &b) {
    int temp = a ;
    a = b ;
    b = temp ;
}

bool stampa_insieme(const insieme_t &ins, ostream &os, bool su_file);

// inserisce il valore v nella pila di indice idx dell'insieme ins,
// ritorna vero in caso di successo, falso altrimenti
bool inserisci_valore(insieme_t &ins, int v, int idx)
{
    if (idx < 0 || idx >= NUM_PILE || ins.capienza == 0 ||
	ins.pile[idx].num_elem == ins.capienza)
	return false ;

    ins.pile[idx].elementi[ins.pile[idx].num_elem++] = v;

    // il numero di elementi della pila e' cambiato, riposizioniamola nel
    // vettore degli indici

    // cerchiamo la posizione attuale della pila nel vettore
    int pos ;
    for (pos = 0 ; pos < NUM_PILE && ins.vett_indici[pos] != idx; pos++)
	;

    // spostiamola, con degli scambi successivi, nella nuova posizione corretta
    for (int pross = pos + 1 ;
	 pross < NUM_PILE &&
	     ins.pile[ins.vett_indici[pross]].num_elem <
	     ins.pile[idx].num_elem ;
	 pross++)
	scambia(ins.vett_indici[pross], ins.vett_indici[pross - 1]) ;
    
    return true ;
}

// cambia la capienza delle pile in n, eliminando il contenuto precedente;
// ritorna vero in caso di successo, falso altrimenti
bool modifica_capienza(insieme_t &ins, int n)
{
    if (n <= 0)
	return false ;

    if (ins.capienza != n) {
	if (ins.capienza != 0)
	    for (int i = 0 ; i < NUM_PILE ; i ++)
		delete ins.pile[i].elementi ;

	for (int i = 0 ; i < NUM_PILE ; i ++)
	    ins.pile[i].elementi = new int[n] ;
    }
    for (int i = 0 ; i < NUM_PILE ; i ++) {
	ins.pile[i].num_elem = 0 ;
	ins.vett_indici[i] = i ;
    }
    ins.capienza = n ;

    return true ;
}

// scrive il contenuto dell'insieme ins sul'ostream passato in ingresso,
// utilizzando un formato opportuno per salvare lo stato su file nel caso
// in cui su_file sia vero; ritorna vero in caso di successo, falso altrimenti
bool stampa_insieme(const insieme_t &ins, ostream &os, bool su_file)
{
    if (! su_file)
	os<<"Capienza: " ;
    os<<ins.capienza<<endl ;
    for (int i = 0 ; i < NUM_PILE ; i ++) {
	if (su_file)
	    os<<ins.pile[i].num_elem<<'\t' ;
	for (int j = ins.pile[i].num_elem - 1 ; j >= 0 ; j--) {
	    os<<ins.pile[i].elementi[j] ;
	    if (j < ins.pile[i].num_elem)
		os<<'\t' ;
	}
	os<<endl ;
    }

    return os ;
}

// stampa il contenuto dell'insieme in ordine crescente di lunghezza delle pile
void stampa_insieme_ordinato(const insieme_t &ins)
{
    for (int i = 0 ; i < NUM_PILE ; i ++) {
	int idx = ins.vett_indici[i] ;
	cout<<idx<<": " ;
	for (int j = ins.pile[idx].num_elem - 1 ; j >= 0 ; j--) {
	    if (j < ins.pile[idx].num_elem)
		cout<<'\t' ;
	    cout<<ins.pile[idx].elementi[j] ;
	}
	cout<<endl ;
    }
}

// carica lo stato dell'insieme da file, il precedente contenuto dell'insieme
// e' perso; ritorna vero in caso di successo, falso altrimenti
bool carica_insieme(insieme_t &ins)
{
    ifstream f(NOME_FILE) ;
    int capienza ;

    f>>capienza ;
    modifica_capienza(ins, capienza) ;

    for (int i = 0 ; i < NUM_PILE ; i ++) {
	int num_elem ;
	f>>num_elem ;
	for (int j = 0 ; j < num_elem ; j++) {
	    int v ;
	    f>>v ;
	    inserisci_valore(ins, v, i) ;
	}
    }

    return f ;
}

int main()
{
    insieme_t insieme ;
    inizializza(insieme) ;

    const char menu[] =
	"1. Modifica capienza\n"
	"2. Inserisci valore\n"
	"3. Stampa insieme\n"
	"4. Salva insieme\n"
	"5. Carica insieme\n"
	"6. Stampa contenuto ordinato\n"
	"7. Esci\n" ;
    
    while (true) {
	cout<<menu<<endl;

	int scelta ;
	cin>>scelta ;
	switch (scelta) {
	case 1: {
	    int N;
	    cout<<"Nuova capienza pile? " ;
	    cin>>N ;
	    if (!modifica_capienza(insieme, N))
		cout<<"Modifica fallita"<<endl ;
	    break ;}
	case 2: {
	    int idx, v ;
	    cout<<"Indice pila e valore da inserire? " ;
	    cin>>idx>>v ;
	    if (!inserisci_valore(insieme, v, idx))
		cout<<"Inserimento fallito"<<endl ;
	    break ;}
	case 3:
	    stampa_insieme(insieme, cout, false) ;
	    break ;
	case 4:{
	    ofstream f(NOME_FILE);
	    if (! stampa_insieme(insieme, f, true))
		cout<<"Salvataggio fallito"<<endl ;
	    break ;}
	case 5:
	    if (! carica_insieme(insieme))
		cout<<"Caricamento fallito"<<endl ;
	    break ;
	case 6:
	    stampa_insieme_ordinato(insieme) ;
	    break ;
	case 7:
	    return 0 ;
	default:
	    cout<<"Scelta errata"<<endl ;
	}
    }

    return 1 ;
}
