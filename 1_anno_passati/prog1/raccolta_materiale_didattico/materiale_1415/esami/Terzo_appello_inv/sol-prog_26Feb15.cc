#include <iostream>
#include <fstream>

using namespace std ;

const int MAXLUNMESS = 256 ;

const int LUNDATA = 6 ;
const int MAXLUNNOME = 10 ;
const int MAXNUMTURNI = 10 ;
const char NOMEFILE[] = "lista-turni.txt" ;

// descrittore turno per una data
struct turno_t {
	char data[LUNDATA] ;
	char nomi[MAXNUMTURNI][MAXLUNNOME] ;
	int num_nomi ;
} ;

// descrittore lista dei turni
struct lista_turni_t {
	turno_t *turni ; // array dinamico contenente i turni
	int num_turni ;  // numero attuale di turni
} ;

/*
 * Ritorna il numero di giorni del mese passato in ingresso, assumendo
 * che l'anno non sia bisestile.
 */
int calcola_giorni_mese(int mese)
{
	if (mese == 4 || mese == 6 || mese == 9 || mese == 11)
		return 30 ;
	else if (mese == 2)
		return 28 ;
	else
		return 31 ;
}

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

/*
 * Vettore di somme delle lunghezze dei mesi, utilizzato per
 * implementare a costo piu' basso la funzionalita' di conversione
 * della data. In dettaglio, l'elemento i-esimo del vettore contiene
 * la somma dei giorni dei mesi di indice 1, 2, ..., i.
 */
int somma_giorni[11] ;

void inizializza_somma_giorni()
{
	somma_giorni[0] = 0 ;
	for (int i = 1 ; i < 11 ; i++) {
		somma_giorni[i] = somma_giorni[i-1] +
			calcola_giorni_mese(i) ;
	}
}

// inizializza la lista dei turni l
void inizializza(lista_turni_t &l)
{
	l.num_turni = 0 ;
}

/*
 * Carica da file il contenuto della lista dei turni l. L'eventuale
 * precedente contenuto e' perso. Ritorna vero in caso di successo,
 * falso altrimenti.
 *
 */
bool carica_turni(lista_turni_t &l)
{
	ifstream f(NOMEFILE);
	int num_turni ;
	f>>num_turni ;

	if (num_turni != l.num_turni && l.num_turni != 0) {
		delete [] l.turni ;
		l.num_turni = 0 ;
	}
	if (num_turni != 0 && l.num_turni == 0) {
		l.turni = new turno_t[num_turni] ;
		l.num_turni = num_turni ;
	}
	for (int i = 0 ; i < num_turni ; i++) {
		f>>l.turni[i].data ;
		int num_nomi ;
		f>>num_nomi ;
		l.turni[i].num_nomi = num_nomi ;
		for (int j = 0 ; j < num_nomi ; j++)
			f>>l.turni[i].nomi[j] ;
	}
	return f ;
}

// stampa la lista dei turni
void stampa_turni(const lista_turni_t &l)
{
	for (int i = 0 ; i < l.num_turni ; i++) {
		cout<<l.turni[i].data ;
		int num_nomi ;
		num_nomi = l.turni[i].num_nomi ;
		for (int j = 0 ; j < num_nomi ; j++) {
			if (j == 0)
				cout<<" " ;
			else
				cout<<", " ;
			cout<<l.turni[i].nomi[j] ;
		}
		cout<<endl ;
	}
	cout<<endl ;
}

/*
 * Ritorna il giorno corrispondente alla data contenuta nella stringa
 * s, oppure 0 in caso di fallimento.
 */
int converti_data(const char s[])
{
	if (strlen(s) != LUNDATA-1 ||
	    !isdigit(s[0]) || !isdigit(s[1]) ||
	    s[2] != '/' ||
	    !isdigit(s[3]) || !isdigit(s[4]))
		return 0 ;
	
	int giorno = (s[0] - '0') * 10 + s[1] - '0' ;

	if (giorno == 0 || giorno > calcola_giorni(...))
		return 0 ;

	int mese = (s[3] - '0') * 10 + s[4] - '0' ;

	if (mese == 0 || mese > 12)
		return 0 ;

	if (mese > 1)
		giorno += somma_giorni[mese - 1] ;

	return giorno ;
}

/*
 * Modifica la data per il turno di indice idx della lista dei turni
 * l. Ritorna vero in caso di successo, falso altrimenti.
 */
bool cambia_data(lista_turni_t &l, int idx)
{
	if (idx < 0 || idx >= l.num_turni)
		return false ;
	cout<<"Nuovo valore data: " ;
	char buffer[MAXLUNMESS] ;
	leggi_riga(cin, buffer) ;

	int giorno = converti_data(buffer) ;
	if (giorno == 0)
		return false ;

	strcpy(l.turni[idx].data, buffer) ;

	for (int i = idx - 1 ; i >= 0 &&
		     converti_data(l.turni[i].data) > giorno ; i--)
	{
		turno_t tmp = l.turni[i] ;
		l.turni[i] = l.turni[i+1] ;
		l.turni[i+1] = tmp ;
	}
	return true ;
}

int main()
{
	inizializza_somma_giorni() ;

	lista_turni_t lista ;
	inizializza(lista) ;
	
	const char menu[] =
		"1. Carica turni\n"
		"2. Stampa turni\n"
		"3. Converti data\n"
		"4. Cambia data\n"
		"5. Esci\n" ; 
	
	while (true) {
		cout<<menu<<endl ;
		int scelta ;
		cin>>scelta ;
		
		switch(scelta) {
		case 1:
			carica_turni(lista) ;
			break ;
		case 2:
			stampa_turni(lista) ;
			break ;
		case 3:{
			cout<<"Data da convertire: " ;
			char buffer[MAXLUNMESS] ;
			leggi_riga(cin, buffer) ;
			cout<<"Data convertita: "
			    <<converti_data(buffer)
			    <<endl ;
			break ;}
		case 4: {
			cout<<"Indice turno? " ;
			int idx ;
			cin>>idx ;
			if (! cambia_data(lista, idx))
				cout<<"Cambiamento fallito"<<endl ;
			break ;
		}
		case 5:
			return 0 ;
		default:
			cout<<"Scelta errata"<<endl ;
		}
	}
	return 1 ;
}
