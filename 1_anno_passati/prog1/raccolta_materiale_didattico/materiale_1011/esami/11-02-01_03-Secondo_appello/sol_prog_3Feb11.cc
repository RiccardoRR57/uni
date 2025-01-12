#include <iostream>
#include <fstream>

using namespace std ;

const int M = 3 ;
const int N = 4 ;

enum stato_cella {ACCESA, SPENTA} ;

// struttura dati per descrivere lo stato di una lavagna
struct lavagna_t {
    stato_cella celle[M][N] ;
    int seg_presenti ; // vero se è gia' presente almeno un segmento
} ;

// direzioni possibili nel disgeno dei segmenti
enum direz_t {DESTRA, BASSO} ;

/*
 * Inizializza lo stato della lavagna l
 */
void inizializza(lavagna_t &l)
{
    for (int i = 0 ; i < M ; i++)
	for (int j = 0 ; j < N ; j++)
	    l.celle[i][j] = SPENTA ;
    l.seg_presenti = false ;
}

/*
 * Funzione di supporto: legge da stdin i dati da apassare alle
 * funzioni di disegno dei segmenti
 */
void leggi_dati_segmento(int &x, int &y, int &lung, direz_t &dir)
{
    cout<<"Inserisci coordinate cella di partenza (riga e colonna): " ;
    cin>>y>>x ;
    do {
	cout<<"Inserisci numero di celle: " ;
	cin>>lung ;
    } while(lung <= 0) ;

    char dir_car ;
    do { 
	cout<<"Inserisci direzione [D=destra, B=basso]: " ;
	cin>>dir_car ;
    } while(dir_car != 'D' && dir_car != 'B') ;
    dir = dir_car == 'D' ? DESTRA : BASSO ;
}

/*
 * Funzione di supporto per le funzioni di disegno dei segmenti:
 * effettua il vero e proprio disegno
 */
bool disegna_segmento_base(lavagna_t &l, int x, int y, int lung, direz_t dir)
{
    for (int i = 0 ; i < lung ; i++) {
	l.celle[y][x] = ACCESA ;
	if (dir == DESTRA)
	    x++ ;
	else
	    y++ ;
    }

    l.seg_presenti = true ;

    return true ;
}

/*
 * Funzione di supporto per le funzioni di disegno dei segmenti:
 * ritorna vero solo se i valori passati in ingresso permettono
 * correttamente di disegnare un segmento sulla lavagna
 */
bool controlla_valori(lavagna_t &l, int x, int y, int lung, direz_t dir)
{
    int last_x = dir == DESTRA ? x + lung - 1 : x ;
    int last_y = dir == BASSO ? y + lung - 1 : y ;

    if (x < 0 || last_x >= N || y < 0 || last_y >= M)
	return false ;

    return true ;
}

/*
 * Disegna segmento, ritorna falso in caso di fallimento, vero altrimenti
 */
bool disegna_segmento(lavagna_t &l, int x, int y, int lung, direz_t dir)
{
    if (! controlla_valori(l, x, y, lung, dir))
	return false ;

    if (l.seg_presenti)
	inizializza(l) ;

    disegna_segmento_base(l, x, y, lung, dir) ;

    return true ;
}

/*
 * Funzione di supporto per disegna_segmento_2: ritorna vero se nella
 * posizione x o y o vicino a tale posizione vi è una cella acces
 */
bool cella_vicina_accesa(const stato_cella celle[][N], int x, int y)
{
    if (celle[y][x] == ACCESA ||
	(x > 0 && celle[y][x-1] == ACCESA) ||
 	(x < N - 1 && celle[y][x+1] == ACCESA) ||
 	(y > 0 && celle[y-1][x] == ACCESA) ||
 	(y < M - 1 && celle[y+1][x] == ACCESA))
	return true ;
    return false ;
}

/*
 * Disegna segmento 2, ritorna falso inc aso di fallimento, vero altrimenti
 */
bool disegna_segmento_2(lavagna_t &l, int x, int y, int lung, direz_t dir)
{
    if (! controlla_valori(l, x, y, lung, dir))
	return false ;

    for (int i = 0, tmp_x = x, tmp_y = y ; i < lung ; i++) {
	if (cella_vicina_accesa(l.celle, tmp_x, tmp_y))
	    return false ;
	if (dir == DESTRA)
	    tmp_x++ ;
	else
	    tmp_y++ ;
    }

    disegna_segmento_base(l, x, y, lung, dir) ;

    return true ;
}

/*
 * Stampa lo stato delle celle della lavagna
 */
void stampa_lavagna(const lavagna_t &l)
{
    for (int i = 0 ; i < M ; i++) {
	for (int j = 0 ; j < N ; j++)
	    if (l.celle[i][j] == SPENTA)
		cout<<"   " ;
	    else
		cout<<" * " ;
	cout<<endl ;
    }
}

/*
 * Salva lo stato della lavagna su un file binario, ritorna falso in
 * caso di fallimento
 */
bool salva_stato(const lavagna_t &l)
{
    ofstream f("stato_lavagna.dat") ;
    if (!f) {
	cout<<"Apertura del file in scrittua fallita\n" ;
	return false ;
    }
    f.write(reinterpret_cast<const char *>(&l), sizeof(l)) ;
    return true ;
}

/*
 * Carica lo stato della lavagna su un file binario, ritorna falso in
 * caso di fallimento. Lo stato precedente della lavagna e' perso.
 */
bool carica_stato(lavagna_t &l)
{
    ifstream f("stato_lavagna.dat") ;
    if (!f) {
	cout<<"Apertura del file in lettura fallita\n" ;
	return false ;
    }
    f.read(reinterpret_cast<char *>(&l), sizeof(l)) ;
    return true ;
}

/*
 * Ritorna vero se entrambe le celle della lavagna l appartengono allo
 * stesso segmento
 */
bool stesso_segmento(const lavagna_t &l, int x1, int y1, int x2, int y2)
{
    if (x1 < 0 || x1 >= M || y1 < 0 || y1 >= N ||
	x2 < 0 || x2 >= M || y2 < 0 || y2 >= N ||
	(x1 != x2 && y1 != y2)
	)
	return false ;

    if (x1 == x2) {
	int prima_y = y1 < y2 ? y1 : y2 ;
	int ultima_y = y1 < y2 ? y2 : y1 ;
	for (int y = prima_y ; y < ultima_y ; y++)
	    if (l.celle[y][x1] == SPENTA)
		return false ;
	return true ;
    } else {
	int prima_x = x1 < x2 ? x1 : x2 ;
	int ultima_x = x1 < x2 ? x2 : x1 ;
	for (int x = prima_x ; x < ultima_x ; x++)
	    if (l.celle[y1][x] == SPENTA)
		return false ;
	return true ;
    }
}

int main()
{
    lavagna_t lavagna ;

    inizializza(lavagna) ;

    const char menu[]=
	"1. Disegna segmento\n"
	"2. Stampa lavagna\n"
	"3. Salva stato\n"
	"4. Carica stato\n"
	"5. Disegna segmento 2\n"
	"6. Stesso segmento\n"
	"7. Uscita\n" ;
    
    while(true) {
	cout<<menu<<endl ;
	cout<<"Scelta? " ;

	int scelta ;
	cin>>scelta ;

	switch(scelta) {
	case 1:{
	    int x, y, lung ;
	    direz_t dir ;
	    leggi_dati_segmento(x, y, lung, dir) ;
	    if (! disegna_segmento(lavagna, x, y, lung, dir))
		cout<<"Disegno fallito\n" ;
	    break ;}
	case 2:
	    stampa_lavagna(lavagna) ;
	    break ;
	case 3:
	    salva_stato(lavagna) ;
	    break ;
	case 4:
	    carica_stato(lavagna) ;
	    break ;
	case 5:{
	    int x, y, lung ;
	    direz_t dir ;
	    leggi_dati_segmento(x, y, lung, dir) ;
	    if (! disegna_segmento_2(lavagna, x, y, lung, dir))
		cout<<"Disegno fallito\n" ;
	    break ;}
	case 6: {
	    int x1, x2, y1, y2 ;
	    cout<<"Inserisci coordinate prima cella (riga e colonna): " ;
	    cin>>y1>>x1 ;
	    cout<<"Inserisci coordinate seconda cella (riga e colonna): " ;
	    cin>>y2>>x2 ;
	    if (stesso_segmento(lavagna, x1, y1, x2, y2))
		cout<<"Le due celle appartengono allo stesso segmento"<<endl ;
	    break;}
	case 7:
	    return 0 ;
	default:
	    cout<<"Scelta errata\n"<<endl ;
	}
    }

    return 1 ;
}
