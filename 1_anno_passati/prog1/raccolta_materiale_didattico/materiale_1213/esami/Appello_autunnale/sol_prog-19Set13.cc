#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std ;

const int M = 6, N = 10 ;
const char NOME_FILE[] = "area.bin" ;

// descrittore quadrato
struct quadrato_t {
	int angolo_riga, angolo_col ; // coordinate angolo superiore sinistro
	int lunghezza ;		      // lunghezza lato del quadrato
	char car ;		      // carattere di riempimento quadrato
} ;

// descrittore area in cui viene visualizzato il quadrato
struct area_t {
	quadrato_t quadrato ;        // quadrato da visualizzare
	char carattere_riempimento ; // eventuale riempimento
} ;

// inizializza l'area a vuota
void inizializza_area(area_t &area)
{
	area.quadrato.lunghezza = 0 ;      // nessun quadrato
	area.carattere_riempimento = ' ' ; // area vuota riempita con spazi
}

/*
 * funzione di supporto per inizializzare un quadrato da passare poi
 * alle funzioni di creazione e modifica del quadrato
 */
void inizializza_quadrato(quadrato_t &q)
{
	cout<<"Coordinate origine quadrato (riga e colonna): " ;
	cin>>q.angolo_riga>>q.angolo_col ;

	do {
		cout<<"Lunghezza quadrato: " ;
		cin>>q.lunghezza ;
	} while (q.lunghezza <= 0) ;

	cout<<"Carattere quadrato: " ;
	cin>>q.car ;
}

// crea un quadrato q nell'area a, eliminando l'eventuale quadrato gia' presente
bool crea_quadrato(area_t &a, const quadrato_t &q)
{
	if (q.angolo_riga < 0 || q.angolo_col < 0 || q.lunghezza < 0 ||
	    q.angolo_riga + q.lunghezza > M || q.angolo_col + q.lunghezza > N)
		return false ;

	a.quadrato = q ;
	return true ;
}

// stampa l'area a, incluso il riempimento esterno se riemp è vero
void stampa(const area_t &a, bool riemp)
{
	char car_riemp = riemp ? a.carattere_riempimento : ' ' ;
	int prima_riga_quad ;
	if (a.quadrato.lunghezza == 0)
		prima_riga_quad = M ; // se il quadrato non c'è, il
				      // seguente ciclo va avanti fino
				      // alla fine dell'area
	else
		prima_riga_quad = a.quadrato.angolo_riga ;
	
	// stampa porzione dell'area sopra il quadrato
	int riga_corrente ;
	for(riga_corrente = 0 ; riga_corrente < prima_riga_quad ;
	    riga_corrente++) {
		cout<<setfill(car_riemp)<<setw(N)<<"" ;
		cout<<endl ;
	}
	
	int ultima_riga_quad ;
	if (prima_riga_quad == M) // se il quadrato non c'e', abbiamo finito
		return ;
	else
		ultima_riga_quad = a.quadrato.angolo_riga +
			a.quadrato.lunghezza - 1 ;

	// calcolo del numero di colonne a sinistra ed a destra del quadrato
	int riemp_sinistra = a.quadrato.angolo_col ;
	int riemp_destra = N - (a.quadrato.angolo_col + a.quadrato.lunghezza) ;

	// stampa del quadrato e dell'area alla sua sinistra ed alla sua destra
	for(; riga_corrente <= ultima_riga_quad ; riga_corrente++) {
		cout<<setfill(car_riemp)<<setw(riemp_sinistra)<<"" ;
		cout<<setfill(a.quadrato.car)<<setw(a.quadrato.lunghezza)<<"" ;
		cout<<setfill(car_riemp)<<setw(riemp_destra)<<"" ;
		cout<<endl ;
	}

	// stampa della porzione dell'area sotto il quadrato
	for(; riga_corrente < M ; riga_corrente++) {
		cout<<setfill(car_riemp)<<setw(N)<<"" ;
		cout<<endl ;
	}
}

// salva l'area a in un file binario
bool salva(const area_t &a)
{
	ofstream f(NOME_FILE) ;
	f.write(reinterpret_cast<const char *>(&a), sizeof(a)) ;
	return f ;
}

// carica l'area a dal file binario
bool carica(area_t &a)
{
	ifstream f(NOME_FILE) ;
	f.read(reinterpret_cast<char *>(&a), sizeof(a)) ;
	return f ;
}

/*
 * funzione di supporto: ritorna vero se il punto di coordinate (riga,
 * col) si trova sul quadrato q
 */
bool sul_quadrato(int riga, int col, const quadrato_t &q)
{
	if (riga >= q.angolo_riga && riga < q.angolo_riga + q.lunghezza &&
	    col >= q.angolo_col && col < q.angolo_col + q.lunghezza)
		return true ;

	return false ;
}

/*
 * Se il punto di coordinate (riga, col) si trova su un quadrato
 * all'interno dell'area a, allora modifica tale quadrato facendolo
 * diventare uguale al quadrato q. Ritorna vero solo se la modifica è
 * effettuata con successo.
 */
bool modifica_quadrato(area_t &a, int riga, int col, const quadrato_t &q)
{
	if (! sul_quadrato(riga, col, a.quadrato))
		return false ;

	return crea_quadrato(a, q) ;
}

/*
 * Riempie la sottoarea attorno al punto di coordinate (riga, col) col
 * carattere car. Ritorna vero solo se il riempimento ha successo.
 */
bool riempi_sottoarea(area_t &a, int riga, int col, char car_riemp)
{
	if (sul_quadrato(riga, col, a.quadrato)) {
		a.quadrato.car = car_riemp ;
		return true ;
	}
	if (riga >= 0 && riga < M && col >= 0 && col < N) {
		a.carattere_riempimento = car_riemp ;
		return true ;
	}
	return false ;
}

int main()
{
	area_t area ;
	inizializza_area(area) ;

	const char menu[] =
		"1. Crea quadrato\n"
		"2. Stampa area\n"
		"3. Salva area\n"
		"4. Carica area\n"
		"5. Modifica quadrato\n"
		"6. Riempi sottoarea\n"
		"7. Stampa area 2\n"
		"8. Esci\n" ;

	while (true) {
		cout<<menu<<endl ;
		int scelta ;
		cin>>scelta ;

		switch(scelta) {
		case 1:{
			quadrato_t q ;
			inizializza_quadrato(q) ;
			if (!crea_quadrato(area, q))
				cout<<"Creazione quadrato fallita"<<endl ;
			break ;}
		case 2:
			stampa(area, false) ;
			break ;
		case 3:
			if (! salva(area))
				cout<<"Salvataggio fallito"<<endl ;;
			break ;
		case 4:
			if (! carica(area))
				cout<<"Salvataggio fallito"<<endl ;;
			break ;
		case 5:{
			quadrato_t q ;
			cout<<"Nuove caratteristiche quadrato"<<endl ;
			inizializza_quadrato(q) ;
			int riga, colonna ;
			cout<<"Riga e colonna punto: " ;
			cin>>riga>>colonna ;

			if (!modifica_quadrato(area, riga, colonna, q))
				cout<<"Modifica quadrato fallita"<<endl ;
			break ;}
		case 6:{
			int riga, colonna ;
			cout<<"Riga e colonna punto: " ;
			cin>>riga>>colonna ;

			cout<<"Carattere riempimento: " ;
			char car ;
			cin>>car ;

			if (!riempi_sottoarea(area, riga, colonna, car))
				cout<<"Riempimento sottoarea fallitp"<<endl ;
			break ;}
		case 7:
			stampa(area, true) ;
			break ;
		case 8:
			return 0 ;
		default:
			cout<<"Scelta errata"<<endl ;
		}
	}


}
