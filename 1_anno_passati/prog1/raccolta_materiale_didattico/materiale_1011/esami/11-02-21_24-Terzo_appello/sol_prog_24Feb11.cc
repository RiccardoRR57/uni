#include <iostream>
#include <fstream>

using namespace std;

enum stato {VUOTA, MENSOLA, BIGLIA} ;

const unsigned int NUM_RIGHE = 4, NUM_COLONNE = 5 ;
typedef stato parete_t[NUM_RIGHE][NUM_COLONNE] ;

const char NOMEFILE[] = "parete.txt" ;

void inizializza(parete_t p)
{
    for (unsigned int i = 0 ; i < NUM_RIGHE ; i++)
	for (unsigned int j = 0 ; j < NUM_COLONNE ; j++)
	    p[i][j] = VUOTA ;
}

bool installa_mensola(parete_t &p, unsigned int r, unsigned int c,
		      unsigned int num_piastrelle)
{
    if (r >= NUM_RIGHE ||
	c + num_piastrelle > NUM_COLONNE)
	return false ;
	
    // controllo distanza da mensole gia' presenti
    bool mensola_sinistra = c > 0 && p[r][c - 1] == MENSOLA ;
    bool mensola_destra = c + num_piastrelle < NUM_COLONNE &&
	p[r][c + num_piastrelle] == MENSOLA ;
    
    if (mensola_sinistra || mensola_destra)
	return false ;
    for (unsigned int i = 0 ; i < num_piastrelle ; i++) {
	bool mensola_stessa_pos = p[r][c + i] == MENSOLA ;
	bool mensola_sopra = r > 0 && p[r - 1][c + i] == MENSOLA ;
	bool mensola_sotto = r < NUM_RIGHE - 1 &&
	    p[r + 1][c + i] == MENSOLA ;
	
	if (mensola_stessa_pos || mensola_sopra || mensola_sotto)
	    return false ;
    }
   for (unsigned int i = 0 ; i < num_piastrelle ; i++)
       p[r][c + i] = MENSOLA ;
   return true ;
}

void stampa_parete(const parete_t &p, ostream &os, bool to_file)
{
    for (unsigned int i = 0 ; i < NUM_RIGHE ; i++) {
	for (unsigned int j = 0 ; j < NUM_COLONNE ; j++)
	    switch(p[i][j]) {
	    case VUOTA:
		if (! to_file)
		    os<<" " ;
		else
		    os<<"X" ;
		break ;
	    case MENSOLA:
		os<<"-" ;
		break ;
	    case BIGLIA:
		os<<"*" ;
		break ;
	    }
	os<<endl ;
    }
}

bool carica_stato(parete_t &p)
{
    ifstream f(NOMEFILE) ;

    if (!f)
	return false ;

    for (unsigned int i = 0 ; i < NUM_RIGHE ; i++)
	for (unsigned int j = 0 ; j < NUM_COLONNE ; j++) {
	    char car ;
	    f>>car ;
	    switch(car) {
	    case 'X':
		p[i][j] = VUOTA ;
		break ;
	    case '-':
		p[i][j] = MENSOLA ;
		break ;
	    case '*':
		p[i][j] = BIGLIA ;
		break ;
	    }
	}
    return f ;
}

bool inserisci_biglia(parete_t &p, unsigned int r, unsigned int c)
{
    if (r >= NUM_RIGHE - 1 || c >= NUM_COLONNE ||
	p[r][c] != VUOTA ||
	p[r+1][c] != MENSOLA)
	return false ;
    p[r][c] = BIGLIA ;
    return true ;
}

bool rimuovi_mensola(parete_t &p, unsigned int r, unsigned int c)
{
    if (r >= NUM_RIGHE || c >= NUM_COLONNE ||
	p[r][c] != MENSOLA)
	return false ;

    // determinazione punto di inizio mensola
    int inizio ;
    for (inizio = c ; inizio >= 0 && p[r][inizio] == MENSOLA ; inizio--)
	;
    inizio++ ;

    // rimozione mensola
    unsigned int i ;
    for (i = inizio ; i < NUM_COLONNE && p[r][i] == MENSOLA ;
	 i++)
	p[r][i] = VUOTA ;
    
    unsigned int fine = i ;

    if (r == 0)
	return true ;

    // spostamento biglie
    for(unsigned int col = inizio ; col < fine ; col++) {
	if (p[r-1][col] != BIGLIA)
	    continue ;
	p[r-1][col] = VUOTA ;
	for (unsigned int riga = r + 1 ; riga < NUM_RIGHE - 1 ; riga++) {
	    if (p[riga][col] == VUOTA && p[riga + 1][col] == MENSOLA) {
		p[riga][col] = BIGLIA ;
		break ;
	    }
	}
    }

    return true ;
}

void leggi_riga_colonna(unsigned int &riga, unsigned int &colonna)
{
    cout<<"Inserisci indici di riga e di colonna: " ;
    cin>>riga>>colonna ;
}

int main()
{
    parete_t parete ;
    inizializza(parete) ;

    char menu[] =
	"1. Installa mensola\n"
	"2. Inserisci biglia\n"
	"3. Stampa parete\n"
	"4. Salva stato\n"
	"5. Carica stato\n"
	"6. Rimuovi mensola\n"
	"7. Esci\n" ;

    while(true) {
	cout<<menu<<endl ;

	int scelta ;
	cin>>scelta ;
	switch(scelta) {
	case 1:{
	    unsigned int riga, col, num_piastrelle ;
	    leggi_riga_colonna(riga, col) ;
	    cout<<"Larghezza in numero di piastrelle? " ;
	    cin>>num_piastrelle ;
	    if (! installa_mensola(parete, riga, col, num_piastrelle))
		cout<<"Installazione mensola fallita"<<endl ;
	    break ;}
	case 2:{
	    unsigned int riga, col ;
	    leggi_riga_colonna(riga, col) ;
	    if (! inserisci_biglia(parete, riga, col))
		cout<<"Inserimento biglia fallito"<<endl ;
	    break ;}
	case 3:
	    stampa_parete(parete, cout, false) ;
	    break ;
	case 4:{
	    ofstream f(NOMEFILE) ;
	    stampa_parete(parete, f, true) ;
	    if (!f)
		cout<<"Scrittura su file fallita"<<endl ;
	    break ;}
	case 5:
	    carica_stato(parete) ;
	    break ;
	case 6:{
	    unsigned int riga, col ;
	    leggi_riga_colonna(riga, col) ;
	    if (! rimuovi_mensola(parete, riga, col))
		cout<<"Rimozione mensola fallita"<<endl ;
	    break ;}
	case 7:
	    return 0 ;
	default:
	    cout<<"Scelta non valida"<<endl ;
	}
    }
    return 0 ;
}
