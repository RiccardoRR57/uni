#include <iostream>
#include <fstream>

using namespace std;

// enumerato per i due possibili stati degli ombrelloni
enum stato {LIBERO, OCCUPATO} ;

// numero di file e di colonne di ombrelloni
const int NUM_FILE = 3 ;
const int NUM_COLONNE = 5 ;

// nome del file in cui salvare e da cui caricare lo stato
const char NOME_FILE[] = "stato.txt" ;

// tipo di dato per memorizzare lo stato degli ombrelloni
typedef stato griglia_ombrelloni[NUM_FILE][NUM_COLONNE] ;

// inizializza tutti gli ombrelloni a libero
void inizializza(griglia_ombrelloni &o)
{
    for (int i = 0 ; i < NUM_FILE ; i++)
	for (int j = 0 ; j < NUM_COLONNE ; j++)
	    o[i][j] = LIBERO ;
}

/*
 * prova a noleggiare un ombrellone nella fila passata in ingresso: in
 * caso di successo ritorna vero e memorizza nel parametro di uscita
 * col la colonna in cui è presente l'ombrellone noleggiato, altrimenti
 * ritorna falso
 */
bool noleggia_ombrellone(griglia_ombrelloni &o, int fila, int &col)
{
    if (fila < 0 || fila > NUM_FILE - 1) {
	cout<<"Fila inesistente"<<endl ;
	return false ;
    }

    for (col = 0 ; col < NUM_COLONNE ; col++) {
	if (o[fila][col] == LIBERO) {
	    o[fila][col] = OCCUPATO ;
	    return true ;
	}
    }
    return false ;
}

/*
 * Scrive sull'ostream os lo stato degli ombrelloni, utilizzata sia
 * per stampare lo stato su stdout, che per salvarlo su file
 */
void stampa_stato(const griglia_ombrelloni &o, ostream &os)
{
    for (int i = 0 ; i < NUM_FILE ; i++) {
	for (int j = 0 ; j < NUM_COLONNE ; j++) {
	    if (j > 0)
		os<<" " ;
	    if (o[i][j] == LIBERO)
		os<<"L" ;
	    else
		os<<"O" ;
	}
	os<<endl ;
    }
}

/*
 * Carica lo stato degli ombrelloni, il proecedente stato è perso
 */
void carica_stato(griglia_ombrelloni &o)
{
    ifstream f(NOME_FILE) ;
    for (int i = 0 ; i < NUM_FILE ; i++) {
	for (int j = 0 ; j < NUM_COLONNE ; j++) {
	    char stato ;
	    f>>stato ;
	    if (stato == 'L')
		o[i][j] = LIBERO ;
	    else
		o[i][j] = OCCUPATO ;
	}
    }
    if (!f)
	cout<<"Errore in lettura dal file"<<endl ;
}

/*
 * prova a noleggiare un ombrellone non adiacente a nessun altro
 * ombrellone in orizzontale o in verticale: in caso di successo
 * ritorna vero e memorizza nei parametri di uscita i e j la posizione
 * dell'ombrellone noleggiato, altrimenti ritorna falso
 */
bool noleggia_isolato(griglia_ombrelloni &o, int &i, int &j)
{
    for (i = 0 ; i < NUM_FILE ; i++)
	for (j = 0 ; j < NUM_COLONNE ; j++) {
	    bool ombrellone_libero = o[i][j] == LIBERO ;
	    bool nessuno_sinistra = j == 0 || o[i][j-1] == LIBERO ;
	    bool nessuno_destra = j == NUM_COLONNE - 1 || o[i][j+1] == LIBERO ;
	    bool nessuno_sopra = i == 0 || o[i-1][j] == LIBERO ;
	    bool nessuno_sotto = i == NUM_FILE - 1 || o[i+1][j] == LIBERO ;
	    if (ombrellone_libero && nessuno_sinistra && nessuno_destra &&
		nessuno_sopra && nessuno_sotto) {
		o[i][j] = OCCUPATO ;
		return true ;
	    }
	}
    return false ;
}

/*
 * Funzione di supporto per la funzione noleggia_vicini: assegna lo
 * stato occupato alla sequenza di n ombrelloni presente nella fila
 * passata in ingresso e terminante nella colonna ultima_col
 */
void noleggia_sequenza(griglia_ombrelloni &o, int n, int fila, int ultima_col)
{
    for (int i = 0 ; i < n ; i++)
	o[fila][ultima_col - i] = OCCUPATO ;
}

/*
 * prova a noleggiare una sequenza di n ombrelloni adiacenti lungo una
 * fila: in caso di successo ritorna vero e memorizza nei parametri di
 * uscita i e j la posizione del primo ombrellone della sequenza,
 * altrimenti ritorna falso
 */
bool noleggia_vicini(griglia_ombrelloni &o, int n, int &i, int &j)
{
    n = n < 1 ? 1 : n ;
    n = n > NUM_COLONNE ? NUM_COLONNE : n ;

    for (i = 0 ; i < NUM_FILE ; i++) {
	int num_liberi_consecutivi = 0 ;
	for (j = 0 ; j < NUM_COLONNE ; j++) {
	    if (o[i][j] == LIBERO)
		num_liberi_consecutivi++ ;
	    else
		num_liberi_consecutivi = 0 ;
	    if (num_liberi_consecutivi == n) {
		noleggia_sequenza(o, n, i, j) ;
		return true ;
	    }
	}
    }
    return false ;
}

int main()
{
    griglia_ombrelloni ombrelloni ;
    inizializza(ombrelloni) ;

    const char menu[]=
	"1. Noleggia ombrellone\n"
	"2. Stampa stato\n"
	"3. Salva stato\n"
	"4. Carica stato\n"
	"5. Noleggia ombrellone isolato\n"
	"6. Noleggia ombrelloni vicini\n"
	"7. Esci\n"
	;

    while(true) {
	cout<<menu<<endl ;
	int scelta ;
	cin>>scelta ;

	switch(scelta) {
	case 1:{
	    int fila, colonna ;
	    cout<<"Fila (contando a partire da 1)? " ;
	    cin>>fila ;
	    if (noleggia_ombrellone(ombrelloni, fila - 1, colonna))
		cout<<"Noleggiato ombrellone alla colonna "<<colonna+1<<endl ;
	    else
		cout<<"Nessuno ombrellone libero in questa fila"<<endl ;
	    break ;}
	case 2:
	    stampa_stato(ombrelloni, cout) ;
	    break ;
	case 3:{
	    ofstream f(NOME_FILE) ;
	    if (!f)
		cout<<"Errore in apertura del file in scritttura"<<endl ;
	    else
		stampa_stato(ombrelloni, f) ;
	    break ;}
	case 4:
	    carica_stato(ombrelloni) ;
	    break ;
	case 5:{
	    int fila, colonna ;
	    if (noleggia_isolato(ombrelloni, fila, colonna))
		cout<<"Noleggiato ombrellone nella posizione "<<fila + 1<<", "
		    <<colonna + 1<<endl ;
	    else
		cout<<"Nessun ombrellone isolato trovato"<<endl ;
	    break ;}
	case 6:{
	    int fila, colonna, n ;
	    cout<<"Numero ombrelloni? " ;
	    cin>>n ;
	    if (noleggia_vicini(ombrelloni, n, fila, colonna))
		cout<<"Noleggiata sequenza a partire dalla posizione "
		    <<fila + 1<<", "
		    <<colonna - n + 2<<endl ;
	    else
		cout<<"Nessuna sequenza libera trovata"<<endl ;
	    break ;}
	case 7:
	    return 0 ;
	default:
	    cout<<"Scelta errata"<<endl ;
	}
    }
    // non dovremmo mai arrivare qui
    return 1 ;
}
