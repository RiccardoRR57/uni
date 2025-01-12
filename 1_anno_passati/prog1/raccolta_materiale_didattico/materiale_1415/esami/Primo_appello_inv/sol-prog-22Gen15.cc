#include <iostream>
#include <fstream>

using namespace std ;

const int MAXLUN = 128 ;
const char NOME_FILE[] = "testo.txt" ;

// descrittore sequenza di parole
struct sequenza_t {
	char (* parole)[MAXLUN] ; // array dinamico di parole
	int num_parole ;          // numero di parole nella sequenza
} ;

void inizializza(sequenza_t &s)
{
	s.parole = 0 ;
	s.num_parole = 0 ;
}

/*
 * Funzione di servizio che alloca la sequenza di parole in memoria,
 * deducendo dal file il numero di elementi da allocare. Ritorna true
 * in caso di successo, falso altrimenti.
 */
bool alloca_parole(sequenza_t &s)
{
	ifstream f(NOME_FILE) ;

	if (!f)
		return false ;

	char parola[MAXLUN] ;
	int nuovo_num_parole = 0 ;
	
	while (f>>parola)
		nuovo_num_parole++ ;

	if (nuovo_num_parole != s.num_parole) {
		delete [] s.parole ;
		s.parole = 0 ;
		s.num_parole = 0 ;
	}

	if (nuovo_num_parole == 0)
		return true ;
	
	if (s.parole == 0) {
		s.parole = new char [nuovo_num_parole][MAXLUN] ;
		s.num_parole = nuovo_num_parole ;
	}

	return true ;
}

/*
 * Carica parole da file, ritorna verso in caso di successo, falso
 * altrimenti.
 */
bool carica_parole(sequenza_t &s)
{
	if (! alloca_parole(s))
		return false ;
	
	ifstream f(NOME_FILE) ;
	
	for (int i = 0 ; i < s.num_parole ; i++)
		f>>s.parole[i] ;
	
	return f ;
}

/*
 * Funzione di servizio che rimuove il j-esimo carattere dalla parola
 * passata in ingresso.
 */
void rimuovi_carattere(char parola[], int j)
{
	for (int i = j ; parola[i] != '\0' ; i++)
		parola[i] = parola[i+1] ;
}

/*
 * Funzione uguale a carica_parole, con in piu' la rimozione della
 * punteggiatura.
 */
bool carica_parole_2(sequenza_t &s)
{
	if (! alloca_parole(s))
		return false ;
	
	ifstream f(NOME_FILE) ;
	
	for (int i = 0 ; i < s.num_parole ; i++) {
		f>>s.parole[i] ;
		for (int j = 0 ; s.parole[i][j] != '\0' ; j++) {
			if (! isalpha(s.parole[i][j]) &&
			    s.parole[i][j] != '-' &&
			    s.parole[i][j] != '\'') {
				rimuovi_carattere(s.parole[i], j) ;
				j-- ;
			} else
				s.parole[i][j] = tolower(s.parole[i][j]) ;
		}
	}
	
	return f ;
}

/*
 * Funzione uguale a carica_parole_2, con in piu' l'ordinamento delle
 * parole.
 */
bool carica_parole_3(sequenza_t &s)
{
	if (! carica_parole_2(s))
		return false ;

	for (int i = 0 ; i < s.num_parole ; i++) {
		for (int j = i ; j < s.num_parole ; j++)
			if (strcmp(s.parole[i], s.parole[j]) > 0) {
				char buffer[MAXLUN] ;
				strcpy(buffer, s.parole[i]) ;
				strcpy(s.parole[i], s.parole[j]) ;
				strcpy(s.parole[j], buffer);
			}
	}

	return true ;
}

/*
 * Elimina le parole duplicate presenti nella sequenza, nell'ipotesi
 * che la sequenza stessa sia ordinata alfabeticamente.
 */
void elimina_duplicati(sequenza_t &s)
{
	
	if (s.num_parole == 0)
		return ;
	
	char (* parole_ordinate)[MAXLUN] = new char[s.num_parole][MAXLUN];

	int num_parole_distinte = 1 ;
	strcpy(parole_ordinate[0], s.parole[0]) ;
	for (int i = 1 ; i < s.num_parole ; i++)
		if (strcmp(parole_ordinate[num_parole_distinte - 1],
			   s.parole[i]) != 0) {
			strcpy(parole_ordinate[num_parole_distinte],
			       s.parole[i]) ;
			num_parole_distinte++ ;
		}

	if (num_parole_distinte != s.num_parole) {
		delete [] s.parole ;
		
		s.parole = new char [num_parole_distinte][MAXLUN] ;
		s.num_parole = num_parole_distinte ;

		for (int i = 0 ; i < s.num_parole ; i++)
			strcpy(s.parole[i], parole_ordinate[i]) ;
	}
	delete [] parole_ordinate ;
}		

/*
 * Stampa le parole contenute nella sequenza.
 */
void stampa_parole(const sequenza_t &s)
{
	for (int i = 0 ; i < s.num_parole ; i++) {
		cout<<s.parole[i] ;
		if (i + 1 < s.num_parole)
			cout<<" " ;
	}
	cout<<endl ;
}

int main()
{
	sequenza_t sequenza ;
	inizializza(sequenza) ;

	const char menu[] =
		"1. Carica parole\n"
		"2. Stampa parole\n"
		"3. Carica parole 2\n"
		"4. Carica parole 3\n"
		"5. Elimina duplicati\n"
		"6. Esci\n";
	
	while (true) {
		cout<<menu<<endl ;
		
		int scelta ;
		cin>>scelta ;
		
		switch(scelta) {
		case 1:
			if (! carica_parole(sequenza))
				cout<<"Caricamento fallito"<<endl ;
			break ;
		case 2:
			stampa_parole(sequenza) ;
			break ;
		case 3:
			if (! carica_parole_2(sequenza))
				cout<<"Caricamento fallito"<<endl ;
			break ;
		case 4:
			carica_parole_3(sequenza) ;
			break ;
		case 5:
			elimina_duplicati(sequenza) ;
			break ;
		case 6:
			return 0 ;
		default:
			cout<<"Scelta sbagliata"<<endl ;
		}
	}
}
