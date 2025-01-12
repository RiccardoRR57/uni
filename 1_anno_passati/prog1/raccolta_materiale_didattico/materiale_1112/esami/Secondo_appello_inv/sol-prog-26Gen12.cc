#include <iostream>
#include <fstream>

using namespace std ;

const int NUM_RIGHE = 2 ;    // numero righe della matrice
const int NUM_COLONNE = 10 ; // numero di colonne della matrice
const char NOME_FILE[] = "matrice.bin";

enum stato_t {SPENTO, ACCESO} ; // stati possibili per gli elementi
				// della matrice
typedef stato_t matrice_stato[NUM_RIGHE][NUM_COLONNE] ; // nome del
							// tipo di
							// dato della
							// matrice

// spegne tutti gli elementi della matrice mat
void inizializza_matrice(matrice_stato mat)
{
	for (int i = 0 ; i < NUM_RIGHE ; i++)
		for(int j = 0 ; j < NUM_COLONNE ; j++)
			mat[i][j] = SPENTO ;
}

/*
 * cambia lo stato della riga di indice idx della matrice mat in
 * funzione del contenuto della stringa nuovo_st;
 * ritorna vero in caso di successo, falso altrimenti
 */
bool cambia_stato(matrice_stato mat, int idx, const char *nuovo_st)
{
	if (idx < 0 || idx >= NUM_RIGHE)
		return false ;
	int lun = strlen(nuovo_st) ;
	if (lun > NUM_COLONNE)
		return false ;
	int i ;
	for(i = 0 ; i < lun; i++)
		mat[idx][i] = nuovo_st[i] == '*' ? ACCESO : SPENTO ;
	for ( ; i < NUM_COLONNE ; i++)
		mat[idx][i] = SPENTO ;
	return true ;
}

void stampa_matrice(const matrice_stato mat)
{
	for (int i = 0 ; i < NUM_RIGHE ; i++) {
		for(int j = 0 ; j < NUM_COLONNE ; j++) {
			cout<<(mat[i][j] == ACCESO ? '*' : '-') ;
			if (j < NUM_COLONNE - 1)
				cout<<' ' ;
		}
		cout<<endl ;
	}
}

/*
 * salva la matrice matrice mat su di un file binario dal nome predefinito e
 * ritorna lo stato dello ostream alla fine dell'operazione
 */
bool salva_matrice(const matrice_stato mat)
{
	ofstream f(NOME_FILE) ;
	
	f.write(reinterpret_cast<const char *>(mat),
		sizeof(stato_t) * NUM_RIGHE * NUM_COLONNE) ;
	return f ;
}

/*
 * carica il contenuto della matrice mat da un file binario dal nome
 * predefinito; e ritorna lo stato dello ostream alla fine dell'operazione;
 * lo stato precedente della matrice e' perso
 */
bool carica_matrice(matrice_stato mat)
{
	ifstream f(NOME_FILE) ;
	
	f.read(reinterpret_cast<char *>(mat),
		sizeof(stato_t) * NUM_RIGHE * NUM_COLONNE) ;
	return f ;
}

/*
 * Modifica ciascuna riga della matrice mat in maniera tale da
 * lasciare al piu' una sequenza di elementi accesi contigui, di
 * lunghezza al piu' n; ritorna vero inc aso di successo, falso altrimenti
 */
bool riduci_elementi_accesi(matrice_stato mat, int n)
{
	if (n < 0)
		return false ;
	for (int idx_riga = 0 ; idx_riga < NUM_RIGHE; idx_riga++) {
		int idx_col_inizio ; // colonna da cui inizia, se
				     // presente, la prima riga di
				     // elementi accesi contigui
		for (idx_col_inizio = 0 ;
		     idx_col_inizio < NUM_COLONNE &&
			     mat[idx_riga][idx_col_inizio] == SPENTO ;
		     idx_col_inizio++)
			;
		int lun ; // lunghezza della sequenza
		for (lun = 0 ;
		     lun < n &&
			     idx_col_inizio + lun < NUM_COLONNE &&
			     mat[idx_riga][idx_col_inizio+lun] == ACCESO ;
		     lun++)
			;
		// spegne tutti gli elementi dalla fine della sequenza in poi
		for (int i = idx_col_inizio + lun ; i < NUM_COLONNE ; i++)
			mat[idx_riga][i] = SPENTO ;
	}
	return true ;
}

/*
 * Pre cisacuna riga e per ciascuna sequenza di elementi contigui
 * nella riga, stampa numero e stato degli elementi della sequenza.
 */
void stampa_sequenze_contigue(const matrice_stato mat)
{
	for (int idx_riga = 0 ; idx_riga < NUM_RIGHE; idx_riga++) {
		for (int idx_col_inizio = 0 ; idx_col_inizio < NUM_COLONNE ;) {
			// lo stato della sequenza e' dato dallo stato
			// del primo elemento della sequenza stessa
			stato_t stato_sequenza = mat[idx_riga][idx_col_inizio];
			int lun ; // lungheza della sequenza
			for (lun = 1 ;
			     idx_col_inizio + lun < NUM_COLONNE &&
				     mat[idx_riga][idx_col_inizio + lun] ==
				     stato_sequenza ;
			      lun ++)
				;

			cout<<lun<<' '<<(stato_sequenza == ACCESO ? '*' : '-');
			if (idx_col_inizio + lun < NUM_COLONNE)
				/*
				 * vi saranno altre sequenze di cui
				 * stampare lungheza e stato,
				 * quindi bisogna stampare la virgola
				 */
				cout<<", " ;
			/*
			 * inizia la possima iterazione a partire
			 * dall'elemento successivo all'ultimo
			 * elemento della sequenza
			 */
			idx_col_inizio += lun ;
		}
		cout<<endl ;
	}
}

int main()
{
	matrice_stato mat ;
	inizializza_matrice(mat) ;

	const char menu[] =
		"1. Cambia stato\n"
		"2. Stampa matrice\n"
		"3. Salva matrice\n"
		"4. Carica matrice\n"
		"5. Riduci elementi accesi\n"
		"6. Stampa seguenze contigue\n"
		"7. Esci\n" ;
	while(true) {
		cout<<menu<<endl ;

		int scelta ;
		cin>>scelta ;
		switch(scelta) {
		case 1: {
			int idx ;
			cout<<"Inserisci idx riga: " ;
			cin>>idx ;
			char nuovo_stato[NUM_COLONNE] ;
			cout<<"Inserisci nuovo stato: " ;
			cin>>nuovo_stato ;
			if (! cambia_stato(mat, idx, nuovo_stato))
				cout<<"Aggiornamento fallito"<<endl ;
		}
			break ;
		case 2:
			stampa_matrice(mat) ;
			break ;
		case 3:
			if (! salva_matrice(mat))
				cout<<"Salvataggio fallito"<<endl ;
			break ;
		case 4:
			if (! carica_matrice(mat))
				cout<<"Caricamento fallito"<<endl ;
			break ;
		case 5: {
			int n ;
			cout<<"Inserisci lunghezza massima sequenza: ";
			cin>>n ;
			if (! riduci_elementi_accesi(mat, n))
				cout<<"Operazione fallita"<<endl ;
		}
			break ;
		case 6:
			stampa_sequenze_contigue(mat) ;
			break ;
		case 7:
			return 0 ;
		default:
			cout<<"Scelta errata"<<endl ;
		}
	}
	return 1 ;
}
