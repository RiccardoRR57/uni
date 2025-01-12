#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>

using namespace std ;

const int N = 10 ; // numero massimo di elementi nel magazzino
const int M = 10 ; // lunghezza massima codice prodotto
const char NOME_FILE[] = "magazzino.txt" ;

// descrittore di un prodotto
struct prodotto_t {
	char *codice ; 		// codice del prodotto
	int scaffale, ripiano ; // posizione del prodotto in magazzino
} ;

// descrittore magazzino: vettore di prodotti
struct magazzino_t {
	prodotto_t prodotti[N] ;
	int num_prodotti ;
} ;

// inizializza il magazzino m a vuoto
void inizializza(magazzino_t &m)
{
	m.num_prodotti = 0 ;
}

void resetta_e_svuota_riga()
{
	cin.clear() ;
	cin.ignore(std::numeric_limits
		   <std::streamsize>::max(), '\n') ;
}

/*
 * legge un codice dall'input stream is, memorizza tale codice in un array dinamico,
 * ritorna l'indirizzo dell'array mediante il parametro di uscita cod.
 * Ritorna falso in caso di fallimento.
 */
bool leggi_codice(char * &cod, istream &is)
{
	char buffer[M] ;
	int idx ;

	is>>skipws ; // per essere sicuri che non saranno inseriti
		      // spazi nel codice
	for (idx = 0 ; idx < M ; idx++) {
		is>>buffer[idx] ;
		if (buffer[idx] == '-') {
			if (idx == 0) {
				cout<<"Il codice deve contenere almeno "
				    <<"due caratteri"
				    <<endl ;
				idx = -1 ; // ricomincia dall'inizio
				continue ;
			}
			buffer[idx] = '\0' ;
			break ;
		}
	}
	if (idx == M) {
		resetta_e_svuota_riga() ;
		return false ;
	}

	cod = new char[idx + 1] ;
	strcpy(cod, buffer) ;

	return true ;
}

/*
 * Legge una codice ed una posizione dall'input stream is e li ritorna mediante
 * il parametro di uscita p. Questa funzione è utilizzata anche per caricare
 * il contenuto del magazzino dal file di testo. In tal caso, va utilizzata
 * passando il valore vero per il terzo parametro formale.
 * Ritorna falso in caso di fallimento.
 */
bool leggi_codice_posizione(prodotto_t &p, istream &is, bool da_file)
{
	if (!da_file)
		cout<<"Codice: " ;

	if (! leggi_codice(p.codice, is))
		return false ;

	if (!da_file)
		cout<<"Indice scaffale e ripiano: " ;
	is>>p.scaffale>>p.ripiano;

	if (p.scaffale < 0 || p.ripiano < 0)
		return false ;

	return true ;
}

// Inserisce il prodotto p nel magazzino m. Ritorna falso in caso di fallimento.
bool inserisci_prodotto(magazzino_t &m, const prodotto_t &p)
{
	if (m.num_prodotti == N)
		return false ;
	m.prodotti[m.num_prodotti] = p ;
	m.num_prodotti++ ;
	return true ;
}

/*
 * Scrive il contenuto del magazzino m sull'ostream os. Questa funzione è
 * utilizzata anche per salvare il contenuto del magazzino, ed in tal caso
 * è invocata passando vero per il terzo parametro formale.
 * Ritorna falso in caso di fallimento.
 */
bool scrivi_prodotti(const magazzino_t &m, ostream &os, bool su_file)
{
	if (su_file)
		os<<m.num_prodotti<<endl ;

	for (int i = 0 ; i < m.num_prodotti ; i++) {
		char buffer[M+1] ;
		strcpy(buffer, m.prodotti[i].codice) ;

		int lung = strlen(buffer) ;
		buffer[lung] = '-' ;
		buffer[lung + 1] = '\0' ;

		os<<setw(M+1)<<left<<buffer ;

		os<<m.prodotti[i].scaffale ;
		if (!su_file)
			os<<',' ;
		else
			os<<' ' ;
		
		os<<m.prodotti[i].ripiano<<endl ;
	}
	return os ;
}

// Carica il contenuto del magazzino da file. Ritorna falso in caso di fallimento.
bool carica_prodotti(magazzino_t &m)
{
	ifstream f(NOME_FILE) ;
	
	if (! f)
		return false ;

	for (int i ; i < m.num_prodotti ; i++)
		delete [] m.prodotti[i].codice ;
	
	f>>m.num_prodotti ;

	for (int i = 0 ; i < m.num_prodotti ; i++)
		leggi_codice_posizione(m.prodotti[i], f, true) ;

	return f ;
}

/*
 * Elimina dal magazzino m tutti i prodotti di codice cod.
 *
 * Utilizza il seguente algoritmo di costo O(N): crea un vettore
 * temporaneo in cui copia solo gli elementi da non eliminare, poi
 * riversa il contenuto di tale vettore nel vettore dei prodotti
 * originario. Durante la fase iniziale di copia, dealloca gli array
 * contenenti i codici dei prodotti da eliminare.
 *
 */
void elimina_codice_prodotto(magazzino_t &m, const char *cod)
{
	prodotto_t *tmp = new prodotto_t[m.num_prodotti] ;

	int nuovo_num_prod = 0 ;
	for (int i = 0 ; i < m.num_prodotti ; i++)
		if (strcmp(cod, m.prodotti[i].codice) != 0) {
			tmp[nuovo_num_prod] = m.prodotti[i] ;
			nuovo_num_prod++ ;
		} else
			delete m.prodotti[i].codice ;

	for (int i = 0; i < nuovo_num_prod ; i++) {
		m.prodotti[i] = tmp[i] ;
		cout<<"Copiato prodotto: "<<m.prodotti[i].codice<<endl ;
	}

	m.num_prodotti = nuovo_num_prod ;
	delete [] tmp ;
}

int main()
{
	magazzino_t magazzino ;

	inizializza(magazzino) ;

	const char menu[] =
		"1. Leggi codice e posizione\n"
		"2. Inserisci prodotto\n"
		"3. Stampa prodotti\n"
		"4. Salva prodotti\n"
		"5. Carica prodotti\n"
		"6. Elimina prodotto da codice\n"
		"7. Esci\n" ;

	while(true) {
		cout<<menu<<endl ;

		int scelta ;
		cin>>scelta ;
		switch(scelta) {
		case 1: {
			prodotto_t p ;
			if (! leggi_codice_posizione(p, cin, false)) {
				cout<<"Lettura fallita"<<endl ;
				break ;
			}
			cout<<"Codice letto: "<<p.codice<<'-'<<endl ;
			cout<<"Scaffale e ripiano: "
			    <<p.scaffale<<" "<<p.ripiano<<endl ;
			break ;}
		case 2: {
			prodotto_t p ;
			if (!leggi_codice_posizione(p, cin, false) ||
			    !inserisci_prodotto(magazzino, p))
				cout<<"Inserimento fallito"<<endl ;
			break ;}
		case 3: {
			scrivi_prodotti(magazzino, cout, false) ;
			break ;}
		case 4: {
			ofstream f(NOME_FILE) ;
			if (!scrivi_prodotti(magazzino, f, true))
				cout<<"Scrittura su file fallita"<<endl ;
			break ;}
		case 5: {
			if (!carica_prodotti(magazzino))
				cout<<"Caricamento fallito"<<endl ;
			break ;}
		case 6: {
			char *codice ;
			cout<<"Codice prodotto da eliminare: " ;
			leggi_codice(codice, cin) ;
			elimina_codice_prodotto(magazzino, codice) ;
			break ;
		}
		case 7:
			return 0 ;
		default:
			cout<<"Scelta errata"<<endl ;
		}
	}

}
