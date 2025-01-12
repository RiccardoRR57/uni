#include <iostream>
#include <fstream>

using namespace std ;

// lunghezza massima righe e numero massimo di messaggi
const int MAXLUN = 100, MAXMESS = 100 ;

const char NOMEFILE[] = "inbox.txt" ;

// descrittore di un messaggio
struct messaggio_t {
	char mittente[MAXLUN] ;
	char oggetto[MAXLUN] ;
	char corpo[MAXLUN] ;
} ;

// descrittore di una cartella
struct cartella_t {
    messaggio_t mess[MAXMESS] ; // array di messaggi
    int num_mess ;              // numero corrente di messaggi validi
} ;

// azioni possibili per la regola
enum azione_t {SPOSTA_IN_LOCALE, ELIMINA} ;

// descrittore di una regola
struct regola_t {
    char riga[MAXLUN] ; // riga con cui confrontare il mittente
    azione_t azione ;   // azione da compiere in caso la regola sia verificata
} ;

// descrittore della casella di posta
struct casella_t {
	cartella_t inbox ;
	cartella_t locale ;
	regola_t regola ;
} ;

// inizializza la casella di posta
void inizializza(casella_t &c)
{
	c.inbox.num_mess = c.locale.num_mess = 0 ;
	c.regola.riga[0] = '\0' ; // riga vuota => regola non ancora definita
}

void leggi_riga(istream &is, char *riga)
{
	// consuma eventuali sequenze di newline per evitare poi
	// errori nella lettura di una riga
	while (is.peek() == '\n')
		is.get() ;

	is.get(riga, MAXLUN) ;
	is.get() ; // consuma il newline della riga appena letta
}

bool leggi_messaggio(istream &is, messaggio_t &m)
{
	leggi_riga(is, m.mittente) ;
	leggi_riga(is, m.oggetto) ;
	leggi_riga(is, m.corpo) ;

	return is ;
}

// inserisce il messaggio m nella cartella c; ritorna vero in caso di
// successo, falso alrimenti
bool inserisci_messaggio_cartella(cartella_t &c, messaggio_t &m)
{
	if (c.num_mess == MAXMESS)
		return false ;

	c.mess[c.num_mess] = m ;
	c.num_mess++ ;

	return true ;
}

// inserisce il messaggio m nella cartella inbox della casella c;
// ritorna vero in caso di successo, falso alrimenti
bool inserisci_messaggio(casella_t &c, messaggio_t &m)
{
	return inserisci_messaggio_cartella(c.inbox, m) ;
}

// scrive i messaggi della cartella c sull'ostream os; ritorna vero in
// caso di successo, falso altrimenti
bool scrivi_messaggi(ostream &os, const cartella_t &c, bool su_file)
{
	if (su_file)
		os<<c.num_mess<<endl ;
	for (int i = 0 ; i < c.num_mess ; i++) {
		if (i > 0 && ! su_file)
			os<<endl ;
		os<<c.mess[i].mittente<<endl
		  <<c.mess[i].oggetto<<endl
		  <<c.mess[i].corpo<<endl ;
	}
	
	return os ;
}

// stampa su stdout i messaggi nella cartella inbox della casella c
void stampa_messaggi(const casella_t &c)
{
	scrivi_messaggi(cout, c.inbox, false) ;
	cout<<endl ;
}

// carica i messaggi da file; ritorna vero in
// caso di successo, falso altrimenti
bool carica_messaggi(istream &is, cartella_t &c)
{
	is>>c.num_mess ;
	for (int i = 0 ; i < c.num_mess ; i++)
		leggi_messaggio(is, c.mess[i]) ;
	
	return is ;

}

enum id_cartella_t {INBOX, LOCALE} ;

// inserisce il messaggio m nella casrtella id della casella c; ritorna vero in
// caso di successo, falso altrimenti
bool inserisci_messaggio2(casella_t &c, messaggio_t &m, id_cartella_t id)
{
	if (id == INBOX)
		return inserisci_messaggio_cartella(c.inbox, m) ;
	else
		return inserisci_messaggio_cartella(c.locale, m) ;
}

// stampa su stdout i messaggi in entrambe le cartella della casella c
void stampa_messaggi2(const casella_t &c)
{
	cout<<"Contenuto cartella inbox:"<<endl ;
	scrivi_messaggi(cout, c.inbox, false) ;
	cout<<endl ;
	cout<<"Contenuto cartella locale:"<<endl ;
	scrivi_messaggi(cout, c.locale, false) ;
	cout<<endl ;
}

// inizializza la regola r leggendo da stdin; ritorna vero in
// caso di successo, falso altrimenti
bool definisci_regola(regola_t &r)
{
	cout<<"Inserire riga:"<<endl ;
	leggi_riga(cin, r.riga) ;
	cout<<"Scegliere azione (1 -> sposta in locale, 2 -> elimina): " ;
	int idx_azione ;
	cin>>idx_azione ;
	if (idx_azione == 1)
		r.azione = SPOSTA_IN_LOCALE ;
	else
		r.azione = ELIMINA ;

	return cin ;
}

// inserisce il messaggio m nella casella c, applicando la regola in c
// se definita; ritorna vero in caso di successo, falso altrimenti
bool inserisci_messaggio3(casella_t &c, messaggio_t &m)
{
	if (c.regola.riga[0] != '\0' && ! strcmp(m.mittente, c.regola.riga)) {
		if (c.regola.azione == ELIMINA)
			return true ;
		return inserisci_messaggio_cartella(c.locale, m) ;
	}
	return inserisci_messaggio_cartella(c.inbox, m) ;
}

int main()
{
	casella_t casella ;

	inizializza(casella) ;

	const char menu[] =
		"1. Ricevi messaggio\n"
		"2. Stampa messaggi\n"
		"3. Salva messaggi\n"
		"4. Carica messaggi\n"
		"5. Ricevi messaggio 2\n"
		"6. Stampa messaggi 2\n"
		"7. Definisci regola\n"
		"8. Ricevi messaggio 3\n"
		"9. Esci\n" ;
	
	while (true) {
		cout<<menu<<endl ;
		int scelta ;
		cin>>scelta ;

		switch(scelta) {
		case 1: {
			struct messaggio_t m ;
			if (! leggi_messaggio(cin, m)) {
				cout<<"Errore nella lettura del messaggio"
				    <<endl ;
				break ;
			}
			if (! inserisci_messaggio(casella, m))
				cout<<"Inserimento messaggio fallito"<<endl ;
			break ;}
		case 2:
			stampa_messaggi(casella) ;
			break ;
		case 3: {
			ofstream f(NOMEFILE) ;
			scrivi_messaggi(f, casella.inbox, true) ;
			if (!f)
				cout<<"Salvataggio fallito"<<endl ;
			break ;}
		case 4: {
			ifstream f(NOMEFILE) ;
			carica_messaggi(f, casella.inbox) ;
			if (!f)
				cout<<"Caricamento fallito"<<endl ;
			break ;}
		case 5:{
			struct messaggio_t m ;
			if (! leggi_messaggio(cin, m)) {
				cout<<"Errore nella lettura del messaggio"<<endl ;
				break ;
			}
			cout<<"Quale cartella (1 -> inbox, 2 -> locale) ?" ;
			int idx_cartella ;
			cin>>idx_cartella ;
			id_cartella_t id_cartella ;

			if (idx_cartella == 1)
				id_cartella = INBOX ;
			else if(idx_cartella == 2)
				id_cartella = LOCALE ;
			else  {
				cout<<"Indice cartella errato"<<endl ;
				break ;
			}
				
			if (! inserisci_messaggio2(casella, m, id_cartella))
				cout<<"Inserimento messaggio fallito"<<endl ;
			break ;}
		case 6:
			stampa_messaggi2(casella) ;
			break ;
		case 7:
			definisci_regola(casella.regola) ;
			break ;
		case 8: {
			struct messaggio_t m ;
			if (! leggi_messaggio(cin, m)) {
				cout<<"Errore nella lettura del messaggio"<<endl ;
				break ;
			}
			if (! inserisci_messaggio3(casella, m))
				cout<<"Inserimento messaggio fallito"<<endl ;
			break ;}
		case 9:
			return 0 ;
		default:
			cout<<"Scelta errata"<<endl ;
		}
	}

	return 1 ;
}
