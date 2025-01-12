#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std ;

const int MAXLUNMESS = 128 ; // max lunghezza di ciascun messaggio
const int MAXNUMMESS = 10 ;  // max numero messaggi in cronologia
const char NOMEFILE[] = "cronologia.txt" ;

enum utente_t {EVA, LEO} ; // utenti del messenger

// descrittore di un messaggio
struct messaggio_t {
	utente_t utente ;		// utente che ha scritto il messaggio
	char testo[MAXLUNMESS + 1] ; 	// testo del messaggio
} ;

// descrittore della cronologia
struct cronologia_t {
	messaggio_t messaggi[MAXNUMMESS] ;	// contenitore dei messaggio
	int num_mess ;				// numero attuale messaggi
} ;

// legge una riga dall'input stream is e la inserisce nel buffer riga
void leggi_riga(istream &is, char *riga)
{
	// consuma eventuali sequenze di newline, 
	// per evitare errori nella lettura di
	// una riga che si sta per effettuare
	while (is.peek() == '\n')
		is.get() ;
	
	is.get(riga, MAXLUNMESS) ; // legge una riga
	is.get() ; // consuma il newline che
	// segue la riga appena letta
}

// inizializza la cronologia c
void inizializza(cronologia_t &c)
{
	c.num_mess = 0 ;
}

/*
 * Legge un messaggio da stdin, assumendo che sia stato inserito
 * dall'utente passato in ingresso, e lo inserisce in fondo alla
 * cronologia. Ritorna vero in caso di successo, falso altrimenti.
 */
bool scrivi_messaggio(cronologia_t &c, utente_t utente)
{
	if (c.num_mess == MAXNUMMESS)
		return false ;

	leggi_riga(cin, c.messaggi[c.num_mess].testo) ;

	if (strlen(c.messaggi[c.num_mess].testo) == 0)
		return false ;
	
	c.messaggi[c.num_mess].utente = utente ;
	c.num_mess++ ;

	return true ;
}

/*
 * Salva la cronologia c in un file di testo. Ritorna vero in caso di
 * successo, falso altrimenti.
 *
 */
bool salva_messaggi(const cronologia_t &c)
{
	ofstream f(NOMEFILE) ;

	if (!f)
		return false ;

	f<<c.num_mess<<endl ;
	for (int i = 0 ; i < c.num_mess ; i++) {
		f<<(c.messaggi[i].utente == EVA ? 'E' : 'L')<<endl ;
		f<<c.messaggi[i].testo<<endl ;
	}
	return f ;
}

/*
 * Carica la cronologia c dal file di testo. Ritorna vero in caso di
 * successo, falso altrimenti.
 */
bool carica_messaggi(cronologia_t &c)
{
	ifstream f(NOMEFILE) ;

	if (!f)
		return false ;

	f>>c.num_mess ;
	for (int i = 0 ; i < c.num_mess ; i++) {
		char iniziale ;
		utente_t utente = EVA ;
		f>>iniziale ;
		if (iniziale != 'E')
			utente = LEO ;
		c.messaggi[i].utente = utente ;
		
		leggi_riga(f, c.messaggi[i].testo) ;
	}
	
	return f ;
}

/*
 * Ritorna la lunghezza della parola presente nella stringa a partire
 * dalla posizione i.
 */
int lunghezza_parola(const char stringa[], int i)
{
	int num_caratteri ;
	for (num_caratteri = 0 ;
	     stringa[i + num_caratteri] != ' ' &&
		     stringa[i + num_caratteri] != '\0' ;
	     num_caratteri++)
		;
	return num_caratteri ;
}

/*
 * Funzione di servizio che stampa il messaggio m, assumendo che sia
 * stato inserito dall'utente u.
 */
void stampa_messaggio(utente_t u, const char m[])
{
	int offset = 0 ; // colonna da cui inizia la stampa
	if (u != EVA) // i messaggi di EVA iniziano dalla colonna 0
		offset = 21 ; // i messaggi di LEO iniziano dalla colonna 21

	for (int i = 0, col = 0 ; ; i++) {
		if (col == 0) // siamo all'inizio di una riga
			cout<<setw(offset)<<"" ; // stampa degli spazi
						 // necessari per fare
						 // iniziare il
						 // messaggio
						 // dall'offset
		
		// stampa prossima parola
		for ( ; m[i] != ' ' && m[i] != '\0' ; i++, col++)
			cout<<m[i] ;

		if (m[i] == ' ') {  	// se siamo su uno spazio,
			cout<<' ' ;     // stampa lo spazio
			col++ ;		// ed incrementa il contatore col
		} else if (m[i] == '\0')
			break ;
		
		if (col + lunghezza_parola(m, i + 1) >= 20) {
			cout<<endl ;
			col = 0 ;
		}
	}
	cout<<endl ;
}

// stampa i messaggi presenti nella cronologia
void stampa_messaggi(const cronologia_t &c)
{
	for (int i = 0 ; i < c.num_mess ; i++)
		stampa_messaggio(c.messaggi[i].utente, c.messaggi[i].testo) ;
	cout<<endl ;
}

int main()
{
	cronologia_t cronologia ;

	inizializza(cronologia) ;
	
	const char menu[] =
		"1. Scrivi messaggio\n"
		"2. Salva cronologia\n"
		"3. Carica cronologia\n"
		"4. Calcola lunghezza parola\n"
		"5. Stampa cronologia\n"
		"6. Esci\n" ;
	
	while (true) {
		cout<<menu<<endl ;

		int scelta ;
		cin>>scelta ;
		switch(scelta) {
		case 1:{
			cout<<"Utente (E = Eva, L = Leo)? " ;
			char iniziale ;
			cin>>iniziale ;
			utente_t utente = EVA ;
			if (iniziale != 'E')
				utente = LEO ;
			if (!scrivi_messaggio(cronologia, utente))
				cout<<"Scrittura messaggio fallita"<<endl;
			break ;}
		case 2:
			if (!salva_messaggi(cronologia))
				cout<<"Salvataggio fallito"<<endl ;
			break ;
		case 3:
			if (!carica_messaggi(cronologia))
				cout<<"Caricamento fallito"<<endl ;
			break ;
		case 4:{
			char riga[MAXLUNMESS] ;
			int i ;
			cout<<"Inserire una riga:"<<endl ;
			
			leggi_riga(cin, riga) ;
			
			cout<<"Riga letta:"<<riga<<endl ;
			
			cout<<"Posizione per cui valutare la "
			    <<"lunghezza della parola? " ;
			cin>>i ;
			cout<<"Lunghezza parola: "
			    <<lunghezza_parola(riga, i)
			    <<endl ;
			break ;}
		case 5:
			stampa_messaggi(cronologia) ;
			break ;
		case 6:
			return 0 ;
		default:
			cout<<"Scelta errata"<<endl ;
		}
	}
}
