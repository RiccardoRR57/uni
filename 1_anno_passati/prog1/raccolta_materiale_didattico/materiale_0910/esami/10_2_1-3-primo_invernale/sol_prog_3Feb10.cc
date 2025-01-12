#include <iostream>
#include <fstream>

using namespace std ;

// dimensioni matrice
const int N = 3 ;
// numero massimo parole da trovare
const int MAX_PAROLE = 10 ;
// nome del file persalvataggio/caricamenteo
const char NOME_FILE[] = "partita.txt" ;

// struttura dati per rappresentare il crucipuzzle
struct crucipuzzle_t {
    char lettere[N][N] ;           // matrice delle parole
    char parole[MAX_PAROLE][N+1] ; // array di stringhe utilizzato per
				   // rappresentare il vettore di parole
                                   // da trovare
    int num_parole ; // numero parole da trovare
} ;

// inizializza la matrice a contenere solo 'A' ed il vettore di parole
// a non contentere nulla
void inizializza(crucipuzzle_t &p)
{
    for(int i = 0 ; i < N ; i++)
	for(int j = 0 ; j < N ; j++)
	    p.lettere[i][j] = 'A' ;
    p.num_parole = 0 ;
}

// inizializza una nuova partita chiedendo all'utente il contenuto
// della matrice e le parole da trovare
void nuova_partita(crucipuzzle_t &p)
{
    cout<<"Inserire le lettere della matrice una riga dopo l'altra"<<endl ;
    for(int i = 0 ; i < N ; i++)
	for(int j = 0 ; j < N ; j++) {
	    cin>>p.lettere[i][j] ;
	    p.lettere[i][j] = toupper(p.lettere[i][j]) ;
	}
    do {
	cout<<"Numero di parole da trovare? " ;
	cin>>p.num_parole ;
    } while (p.num_parole <= 0) ;
    cout<<"Inserire le "<<p.num_parole<<" parole da trovare"
	" (di al piu' "<<N<<" lettere ciascuna)"<<endl ;
    for(int i = 0 ; i < p.num_parole ; i++) {
	cin>>p.parole[i] ;
	// non strettamente necessario: ci si assicura che lettere
	// siano tutte maiuscole
	for (unsigned int j = 0 ; j < strlen(p.parole[i]) ; j++)
	    p.parole[i][j] = toupper(p.parole[i][j]) ;
    }
}

// stampa/scrive su file la partita in corso
void stampa_partita(const crucipuzzle_t &p, ostream &os, bool su_file)
{
    for(int i = 0 ; i < N ; i++) {
	for(int j = 0 ; j < N ; j++)
	    os<<p.lettere[i][j] ;
	os<<endl ;
    }
    if (su_file)
	os<<p.num_parole<<endl ;
    else
	if (p.num_parole == 0) {
	    os<<endl<<"Partita finita"<<endl ;
	    return ;
	} else
	    os<<endl<<"Parole da cercare:"<<endl ;
    for(int i = 0 ; i < p.num_parole ; i++) {
	os<<p.parole[i]<<endl ;
    }
}

// caricala partita da file
void carica_partita(crucipuzzle_t &p, istream &is)
{
    for(int i = 0 ; i < N ; i++)
	for(int j = 0 ; j < N ; j++)
	    is>>p.lettere[i][j] ;
    is>>p.num_parole ;
    for(int i = 0 ; i < p.num_parole ; i++)
	is>>p.parole[i] ;
}

// tipo di dato per rappresentare le possibili direzioni in cui può
// apparire una parola nella matrice
enum dir_t {ORIZZONTALE, VERTICALE, DIAGONALE} ;

// confronta la parola par con la parola che appare nella matrice
// lettere a partire dalla posizione (pos_riga, pos_colonna) e nella
// direzione dir; ritorna vero se le due parole coincidono, falso
// altrimenti
bool confronta_parola(const char lettere[][N], const char par[], 
		      int pos_riga, int pos_colonna,
		      dir_t dir)
{
    int lun = strlen(par) ;
    bool orizz_oppure_diagonale =
	dir == ORIZZONTALE || dir == DIAGONALE ;
    bool vert_oppure_diagonale =
	dir == VERTICALE || dir == DIAGONALE ;

    // controlla che la parola non sia troppo lunga per poter apparire
    // nella posizione/direzione desiderati
    if ((orizz_oppure_diagonale && lun > N - pos_colonna)
	||
	(vert_oppure_diagonale && lun > N - pos_riga)
	)
	return false ;

    // effettua il confronto carattere per carattere nella direzione
    // desiderata
    switch(dir) {
    case ORIZZONTALE:
	for(int i = 0 ; i < lun ; i++)
	    if (lettere[pos_riga][pos_colonna + i] != toupper(par[i]))
		return false ;
	break ;
    case VERTICALE:
	for(int i = 0 ; i < lun ; i++)
	    if (lettere[pos_riga + i][pos_colonna] != toupper(par[i]))
		return false ;
	break ;
    case DIAGONALE:
	for(int i = 0 ; i < lun ; i++)
	    if (lettere[pos_riga + i][pos_colonna + i] != toupper(par[i]))
		return false ;
	break ;
    }
    return true ;
}

// se la parola par appartiene all'elenco delle parole da trovare,
// controlla se e' presente nella posizione (pos_riga, pos_colonna) e
// lungo la direzione dir, e, in caso affermativo, elimina tale parola
// dall'elenco. Se l'elenco diventa vuoto, segnala l'avvenuta vittoria.
void trova_parola(crucipuzzle_t &p, const char par[], 
		  int pos_riga, int pos_colonna,
		  dir_t dir)
{
    int indice_parola = -1 ; // -1 vuol dire parola non presente nell'elenco
    // cerca par nell'elenco di parole da trovare
    for (int i = 0 ; i < p.num_parole ; i++)
	if (strcmp(p.parole[i], par) == 0) {
	    indice_parola = i ;
	    break ;
	}
    if (indice_parola == -1) {
	cout<<"Parola non presente nell'elenco"<<endl ;
	return ;
    }
    // effettua il confronto ed elimina par dall'elenco se trovata
    // nella matrice
    if (confronta_parola(p.lettere, par, pos_riga, pos_colonna, dir)) {
	cout<<"Trovata!"<<endl ;
	for (int i = indice_parola ; i < p.num_parole - 1 ; i++)
	    strcpy(p.parole[i], p.parole[i+1]) ;
	p.num_parole-- ;
    } else
	cout<<"Non e' qui"<<endl ;

    // comunica la vittoria
    if (p.num_parole == 0)
	cout<<"Hai vinto!"<<endl ;
}

// elenca tutte le posizioni in cui la parola par appare nella
// direzione dir
bool elenca_pos_parola(const char lettere[][N], const char par[],
		       dir_t dir)
{
    int lun = static_cast<int>(strlen(par)) - 1 ;
    // la ricerca e' da effettuare solo nelle posizioni contenute
    // nella sottomatrice che va dalla posizione (0, 0) alla posizione
    // (riga_max, colonna_max), i cui valori sono determinati in
    // funzione della direzione in cui deve apparire la parola
    int riga_max, colonna_max ;

    // calcolo di riga_max e colonna_max in funzione della direzione
    // in cui deve apparire la parola
    switch(dir) {
    case ORIZZONTALE:
	riga_max = N ;
	colonna_max = N - lun ;
	break ;
    case VERTICALE:
	riga_max = N - lun ;
	colonna_max = N ;
	break ;
    case DIAGONALE:
	riga_max = N - lun ;
	colonna_max = N - lun ;
	break ;
    }

    // stampa le posizioni in cui appare par
    for(int i = 0 ; i < riga_max ; i++)
	for(int j = 0 ; j < colonna_max ; j++)
	    if (confronta_parola(lettere, par, i, j, dir))
		cout<<i<<" "<<j<<endl ;
    return true ;
}

// funzione di servizio: legge una parola ed una direzione da stdin
void leggi_par_dir(char par[], dir_t &dir)
{
    cout<<"Parola? " ;
    cin>>par ;

    int dir_int ;
    do {
	cout<<"Inserire direzione (0 orizz, 1 vert, 2 diag): " ;
	cin>>dir_int ;
    } while (dir_int != ORIZZONTALE && dir_int != VERTICALE && 
	     dir_int != DIAGONALE) ;
    switch(dir_int) {
    case ORIZZONTALE:
	dir = ORIZZONTALE ;
	break ;
    case VERTICALE:
	dir = VERTICALE ;
	break ;
    case DIAGONALE:
	dir = DIAGONALE ;
	break ;
    }
}

// funzione di servizio: legge una parola, una posizione ed una
// direzione da stdin
void leggi_par_pos_dir(char par[], int &pos_riga, int &pos_colonna, dir_t &dir)
{
    leggi_par_dir(par, dir) ;

    cout<<"Inserire posizione (riga e colonna): " ;
    cin>>pos_riga>>pos_colonna ;
}

int main()
{
    const char menu[] =
	"\t1 Nuova partita\n"
	"\t2 Stampa partita\n"
	"\t3 Salva partita\n"
	"\t4 Carica partita\n"
	"\t5 Confronta parola\n"
	"\t6 Trova parola\n"
	"\t7 Elenca posizioni parola\n"
	"\t8 Uscita\n";
    crucipuzzle_t puzzle ;
    inizializza(puzzle) ;

    while(true) {
	cout<<endl<<menu<<endl ;
	int scelta ;
	cin>>scelta ;
	switch(scelta) {
	case 1:
	    nuova_partita(puzzle) ;
	    break ;
	case 2:
	    stampa_partita(puzzle, cout, false) ;
	    break ;
	case 3: {
	    ofstream f(NOME_FILE) ;
	    if (!f) {
		cout<<"Apertura del file in scrittura fallita"<<endl ;
		break ;
	    }
	    stampa_partita(puzzle, f, true) ;
	    if (!f)
		cout<<"Salvataggio fallito"<<endl ;
	    break ;}
	case 4: {
	    ifstream f(NOME_FILE) ;
	    if (!f) {
		cout<<"Apertura del file in lettura fallita"<<endl ;
		break ;
	    }
	    carica_partita(puzzle, f) ;
	    if (!f)
		cout<<"Caricamento fallito"<<endl ;
	    break ;}
	case 5: {
	    char par[N+1] ;
	    int pos_riga, pos_colonna ;
	    dir_t dir ;
	    leggi_par_pos_dir(par, pos_riga, pos_colonna, dir) ;
	    if (confronta_parola(puzzle.lettere, par, pos_riga, pos_colonna,
				 dir))
		cout<<"Parola presente"<<endl ;
	    else
		cout<<"Parola non presente"<<endl ;
	    break ;}
	case 6: {
	    char par[N+1] ;
	    int pos_riga, pos_colonna ;
	    dir_t dir ;
	    leggi_par_pos_dir(par, pos_riga, pos_colonna, dir) ;
	    trova_parola(puzzle, par, pos_riga, pos_colonna, dir) ;
	    break ;}
	case 7: {
	    char par[N+1] ;
	    dir_t dir ;
	    leggi_par_dir(par, dir) ;
	    elenca_pos_parola(puzzle.lettere, par, dir) ;
	    break ;}
	case 8:
	    return 0 ;
	}
    }

    // non si dovrebbe mai arrivare qui
    return 1 ;
}
