#include <iostream>
#include <fstream>

using namespace std ;

const int MAX_PRODOTTI = 10 ;
const char NOME_FILE[] = "magazzino.txt" ;

// descritto di un prodotto e del modello
struct descr_prodotto {
	char *codice ;
	double prezzo ;
} ;

struct descr_magazzino {
	descr_prodotto modello ;                // modello per la aggiungi
	descr_prodotto prodotti[MAX_PRODOTTI] ; // contenitore prodotti
	int num_prodotti ;                      // numero corrente di prodotti
} ;

// inizializza il magazzino m
void inizializza(descr_magazzino &m)
{
	m.modello.codice = 0 ;
	m.num_prodotti = 0 ;
}

/*
 * Modifica codice e prezzo del modello o prodotto mod, assegnando i
 * valori p e c. Ritorna falso in caso di fallimento.
 */
bool modifica_modello_prodotto(char *c, double p, descr_prodotto &mod) {
	if (p < 0)
		return false ;

	int nuova_lun = strlen(c) ;
	if (mod.codice != 0 && strlen(mod.codice) != nuova_lun) {
		delete [] mod.codice ;
		mod.codice = 0 ;
	}

	if (nuova_lun == 0)
		return true ; // certamente mod.codice a questo punto e' 0,
	                      // quindi non c'e' piu' niente da fare

	if (mod.codice == 0)
		mod.codice = new char[nuova_lun + 1] ;

	strcpy(mod.codice, c) ;
	mod.prezzo = p ;

	return true ;
}

/*
 * Scrive il prodotto mod sull'ostream os, utilizzando il formato
 * adatto alla scrittura su file nel caso in cui su_file sia vero.
 */
void scrivi_prodotto(const descr_prodotto &mod, ostream &os, bool su_file)
{
	if (mod.codice != 0) {
		if (su_file)
			os<<strlen(mod.codice)<<" " ;
		os<<mod.codice<<" "<<mod.prezzo<<endl ;
	}
}

/*
 * Aggiunge un prodotto al magazzino m. Ritorna vero in caso di
 * successo, falso altrimenti.
 */
bool aggiungi_prodotto(descr_magazzino &m) {
	if (m.num_prodotti == MAX_PRODOTTI || m.modello.codice == 0)
		return false ;
	
	descr_prodotto &prod = m.prodotti[m.num_prodotti] ;

	prod.codice = new char [strlen(m.modello.codice) + 1] ;
	strcpy(prod.codice, m.modello.codice) ;
	prod.prezzo = m.modello.prezzo ;
	
	m.num_prodotti++ ;
	return true ;
}

/*
 * Scrive il contenuto del magazzino m, piu' il modello, sull'ostream
 * os, utilizzando il formato adatto alla scrittura su file nel caso
 * in cui su_file sia vero. Ritorna vero in caso di successo, falso
 * altrimenti.
 */
bool scrivi_magazzino(const descr_magazzino &m, ostream &os, bool su_file)
{
	if (su_file)
		os<<m.num_prodotti<<endl ;

	for (int i = 0 ; i < m.num_prodotti; i++)
		scrivi_prodotto(m.prodotti[i], os, su_file) ;

	if (su_file)
		scrivi_prodotto(m.modello, os, su_file) ;

	return os ;
}

/*
 * Carica il contenuto del magazzino m, piu' il modello, dal
 * file. Ritorna vero in caso di successo, falso altrimenti.
 */
bool carica_magazzino(descr_magazzino &m)
{
	int lun ;
	char *buffer = 0 ;
	double prezzo ;

	ifstream f(NOME_FILE) ;

	int nuovo_num_prodotti ;

	f>>nuovo_num_prodotti ;

	if (!f)
		return false ;

	int num_prod_modificare =
		nuovo_num_prodotti < m.num_prodotti ?
				     nuovo_num_prodotti : m.num_prodotti ;
	
	for (int i = 0 ; i < num_prod_modificare ; i++) {
		f>>lun ;
		if (buffer == 0 || lun != strlen(buffer))
			buffer = new char [lun + 1] ;
		f>>buffer ;
		f>>prezzo ;

		modifica_modello_prodotto(buffer, prezzo, m.prodotti[i]) ;
		delete [] buffer ;
	}
	
	if (nuovo_num_prodotti < m.num_prodotti)
		// bisogna deallocare memoria per gli elementi in eccesso
		for (int i = nuovo_num_prodotti ; i < m.num_prodotti ; i++)
			delete [] m.prodotti[i].codice ;
	else
		// leggo gli elementi extra
		for (int i = m.num_prodotti ; i < nuovo_num_prodotti ; i++) {
			f>>lun ;
			/* 
			 * sicuramente l'array dinamico che dovra'
			 * contenere il codice del prodotto non e'
			 * attualmente allocato in memoria
			 */
			m.prodotti[i].codice = new char [lun + 1] ;
			f>>m.prodotti[i].codice ;
			f>>m.prodotti[i].prezzo ;
		}
	m.num_prodotti = nuovo_num_prodotti ;

	// modifico il modello
	f>>lun ;
	if (buffer == 0 || lun != strlen(buffer))
		buffer = new char [lun + 1] ;
	f>>buffer ;
	f>>prezzo ;
	modifica_modello_prodotto(buffer, prezzo, m.modello) ;
	delete [] buffer ;

	return f ;
}

int main()
{
	descr_magazzino magazzino ;
	inizializza(magazzino) ;

	const char menu[] =
		"1. Modifica modello\n"
		"2. Stampa modello\n"
		"3. Aggiungi prodotto\n"
		"4. Stampa prodotti\n"
		"5. Salva prodotti\n"
		"6. Carica prodotti\n"
		"7. Esci\n" ;

	while (true) {
		cout<<menu<<endl ;

		int scelta ;
		cin>>scelta ;
		
		switch(scelta) {
		case 1: {
			int lun ;
			double prezzo ;

			cout<<"Lunghezza massima nuovo codice: " ;
			cin>>lun ;
			char *buffer = new char[lun + 1] ;
			cout<<"Nuovo codice: " ;
			cin>>buffer ;
			cout<<"Nuovo prezzo: " ;
			cin>>prezzo ;

			modifica_modello_prodotto(buffer, prezzo,
						  magazzino.modello) ;
			delete [] buffer ;
			break ;}
		case 2:
			scrivi_prodotto(magazzino.modello, cout, false) ;
			break ;
		case 3:
			if (!aggiungi_prodotto(magazzino))
				cout<<"Aggiunta prodotto fallita"<<endl ;
			break ;
		case 4:
			scrivi_magazzino(magazzino, cout, false) ;
			break ;
		case 5: {
			ofstream f(NOME_FILE) ;
			if (!scrivi_magazzino(magazzino, f, true))
				cout<<"Scrittura su file fallita"<<endl ;
			break ;}
		case 6:
			if (!carica_magazzino(magazzino))
				cout<<"Scrittura su file fallita"<<endl ;
			break ;
		case 7:
			return 0 ;
		default:
			cout<<"Scelta sbagliata"<<endl ;
		}
	}
	
	return 1 ;
}
