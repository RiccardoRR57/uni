#include <iostream>
#include <fstream>

using namespace std ;

/*
 * In questa soluzione si utilizza una matrice per generare il grafico
 * della successione. Si puo' però disegnare il grafico anche
 * stampandolo direttamente, e senza memorizzarlo prima in alcuna
 * matrice. Questa seconda soluzione e' probabilmente concettualmente
 * un po' piu' complessa (ed e' questo il motivo per cui ho optato per
 * la prima soluzione). In ogni caso, se corretta e completa, anche
 * con la seconda soluzione si sarebbe ottenuto il voto massimo.
 */

const int N = 10 ;
const char NOMEFILE[] = "successione.bin";

// descrittore di una successione e del suo grafico
struct successione_t {
	int valori[N] ;
	char (*grafico)[N] ;
	unsigned int num_righe ;
} ;

// inizializza una successione a contenere solo zeri
void inizializza_vuota(successione_t &S)
{
	for (int i = 0 ; i < N ; i++)
		S.valori[i] = 0 ;
	S.grafico = 0 ;
}

// inizializza una successione da stdin
void inizializza(successione_t &S)
{
	for (int i = 0 ; i < N ; i++) {
		cout<<"Valore elemento "
		    <<i<<"/"<<(N-1)
		    <<": " ;
		cin>>S.valori[i] ;
	}
}

// funzione di servizio per riempire la matrice che rappresenta il grafico
void riempi_grafico(const int valori[], int n, int pos_zero, int num_righe,
		    char grafico[][N])
{
	for (int i = 0 ; i < num_righe ; i++)
		for (int j = 0 ; j < N ; j++)
			grafico[i][j] = ' ' ;
	
	for (int i = 0 ; i < N ; i++) {
		if (pos_zero != num_righe-1)
			grafico[pos_zero][i] = '-' ;
		
		grafico[pos_zero - valori[i]][i] = '*' ;
	}
}

/*
 * Inserisce, nei parametri di uscita mass e min, il valore massimo ed
 * il valore minimo contenuti nell'array valori.
 */
void trova_massimo_minimo(int valori[], int &mass, int &min)
{
	mass = min = valori[0] ;
	for (int i = 1 ; i < N ; i++) {
		if (valori[i] > mass)
			mass = valori[i] ;
		else if (valori[i] < min)
			min = valori[i] ;
	}
}

/*
 * Funzione generica per stampare il grafico della successione S. Se
 * controllo e' vero, allora stampa il grafico solo se i valori sono
 * nell'intervallo [0, 5].
 */
void stampa_grafico(successione_t &S, bool controllo)
{
	int massimo, minimo ;
	trova_massimo_minimo(S.valori, massimo, minimo) ;
	
	if (controllo && (minimo < 0 || massimo > 5)) {
		cout<<"Valori non ammessi per il grafico"<<endl ;
		return ;
	}
	int nuovo_num_righe = massimo + 1 ;
	int pos_zero = nuovo_num_righe - 1 ; // indice della riga in cui
				       // disegnare la sequenza di
				       // trattini, se uguale a S.num_righe-1,
				       // non si disegna alcuna
				       // sequenza di trattini

	if (minimo < 0) {
		nuovo_num_righe -= minimo ;
		pos_zero = nuovo_num_righe + minimo - 1 ;
	}

	if (S.grafico == 0 || S.num_righe != nuovo_num_righe) {
		if (S.grafico != 0)
			delete [] S.grafico ;
		S.grafico = new char[nuovo_num_righe][N] ;
		S.num_righe = nuovo_num_righe ;
	}
	
	riempi_grafico(S.valori, N, pos_zero, S.num_righe, S.grafico) ;
	
	for (int i = 0 ; i < S.num_righe ; i++) {
		for (int j = 0 ; j < N ; j++)
			cout<<S.grafico[i][j] ;
		cout<<endl ;
	}
}

/*
 * Salva la successione S in un file binario, ritorna true in caso di
 * successo, falso altrimenti.
 */
bool salva_successione(const successione_t &S)
{
	ofstream f(NOMEFILE) ;
	f.write(reinterpret_cast<const char*>(S.valori), sizeof(S.valori)) ;
	return f ;
}

/*
 * Carica la successione S da un file binario, ritorna true in caso di
 * successo, falso altrimenti.
 */
bool carica_successione(successione_t &S)
{
	ifstream f(NOMEFILE) ;
	f.read(reinterpret_cast<char*>(S.valori), sizeof(S.valori)) ;
	return f ;
}

int main()
{
	successione_t S ;
	inizializza_vuota(S) ;
	
	const char menu[] =
		"1. Inizializza successione\n"
		"2. Stampa grafico 1\n"
		"3. Salva successione\n"
		"4. Carica successione\n"
		"5. Stampa grafico 2\n"
		"6. Esci\n" ;
	
	while (true) {
		cout<<menu<<endl ;
		
		int scelta ;
		cin>>scelta ;
		switch(scelta) {
		case 1:
			inizializza(S) ;
			break ;
		case 2:
			stampa_grafico(S, true) ;
			break ;
		case 3:
			if (! salva_successione(S))
				cout<<"Salvataggio fallito"<<endl ;
			break ;
		case 4:
			if (! carica_successione(S))
				cout<<"Caricamento fallito"<<endl ;
			break ;
		case 5:
			stampa_grafico(S, false) ;
			break ;
		case 6:
			return 0 ;
		default:
			cout<<"Scelta errata"<<endl ;
		}
	}
	return 1 ;
}
