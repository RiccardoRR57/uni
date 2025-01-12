#include <iostream>
#include <fstream>

using namespace std ;

const int MAXLUN = 256 ;
const int MAXNUMDOM = 10 ;
const char NOMEFILE[] = "elenco.bin" ;

// Descrittore della coppia (domanda, risposta)
struct dom_risp_t {
	char domanda[MAXLUN], risposta[MAXLUN] ;
    bool chiesta ; // utilizzato per implementare la partita
} ;

// contenitore delle coppie (domanda, risposta)
struct elenco_t {
	dom_risp_t dom_risp[MAXNUMDOM] ;
	int num_dom ;
} ;

void leggi_riga(istream &is, char *riga)
{
	/*
	 * consuma eventuali sequenze di newline, 
	 * per evitare errori nella lettura di
	 * una riga che si sta per effettuare
	 */
	while (is.peek() == '\n')
		is.get() ;

	is.get(riga, MAXLUN) ; // legge una riga
	is.get() ; // consuma il newline che segue la riga appena
		   // letta
}

// inizializza l'elenco el a non contenere alcuna domanda
void inizializza(elenco_t &el)
{
	el.num_dom = 0 ;
}

// aggiunge una coppia (comanda, risposta) all'elenco el
bool aggiungi_domanda_risposta(elenco_t &el)
{
	if (el.num_dom == MAXNUMDOM)
		return false ;

	cout<<"Inserisci domanda: " ;
	leggi_riga(cin, el.dom_risp[el.num_dom].domanda) ;

	cout<<"Inserisci riposta: " ;
	cin>>el.dom_risp[el.num_dom].risposta ;
	el.num_dom++ ;
	
	return true ;
}

// stampa l'elenco delle domande e riposte
void stampa_domande_risposte(const elenco_t &el)
{
	for (int i = 0 ; i < el.num_dom ; i++)
		cout<<el.dom_risp[i].domanda<<"? "
		    <<el.dom_risp[i].risposta<<endl ;
}

// salva l'elenco in un file binario
bool salva_elenco(const elenco_t &el)
{
	ofstream f(NOMEFILE) ;
	f.write(reinterpret_cast<const char *>(&el),
		sizeof(el)) ;
	return f ;
}

// carica l'elenco da un file binario; il precedente contenuto è perso
bool carica_elenco(elenco_t &el)
{
	ifstream f(NOMEFILE) ;
	f.read(reinterpret_cast<char *>(&el), sizeof(el)) ;
	return f ;
}

// possibili esiti dell'esecuzione della funzione poni_domanda
enum esito_t {RISP_GIUSTA, RISP_SBAGLIATA, INDICE_NON_VALIDO} ;

// pone la domanda di indice idx nell'elenco el, ritornando uno degli
// esiti possibili
esito_t poni_domanda(const elenco_t &el, int idx)
{
	if (idx < 0 || idx >= el.num_dom)
		return INDICE_NON_VALIDO ;

	cout<<el.dom_risp[idx].domanda<<" ? " ;
	char risposta[MAXLUN] ;
	cin>>risposta ;

	int i ;
	for (i = 0 ; risposta[i] != '\0' ; i++)
		if (tolower(risposta[i]) !=
		    tolower(el.dom_risp[idx].risposta[i]))
			return RISP_SBAGLIATA ;

	if ((el.dom_risp[idx].risposta[i] == '\0'))
	    return RISP_GIUSTA ;

	return RISP_SBAGLIATA ;
}

// esegue una intera partita utilizzando le coppie (domanda, risposta)
// nell'elenco el
bool esegui_partita(elenco_t &el)
{
	int punti_giocatore[2] = {0, 0};

	if (el.num_dom % 2 == 1)
		return false ;
	
	for (int i = 0 ; i < el.num_dom ; i++)
		el.dom_risp[i].chiesta = false ;

	for (int i = 0 ; i < el.num_dom ; i++) {
		int idx_domanda = rand() % el.num_dom ;

		while (el.dom_risp[idx_domanda].chiesta)
		    /*
		     * Incremento l'indice alla ricerca della prossima
		     * domanda non ancora chiesta. Utilizzo il modulo
		     * per far sì che, se arrivo in fondo alle
		     * domande, 'giro' e ricomincio a cercare dalla
		     * prima. Sicuramente prima o poi trovo una
		     * domanda non chiesta, perché, fino a che sono
		     * dentro al ciclo for, non ho ancora chiesto
		     * tutte le domande.
		     */
		    idx_domanda = (idx_domanda + 1) % el.num_dom ;

		el.dom_risp[idx_domanda].chiesta = true ;

		int idx_giocatore = i%2 ;
		cout<<"Domanda per giocatore "<<(idx_giocatore+1)<<endl ;
		if (poni_domanda(el, idx_domanda) == RISP_GIUSTA) {
			punti_giocatore[idx_giocatore]++ ;
			cout<<"Risposta giusta, nuovo punteggio: "
			    <<punti_giocatore[idx_giocatore]<<endl ;
		} else
			cout<<"Risposta sbagliata, il punteggio rimane: "
			    <<punti_giocatore[idx_giocatore]<<endl ;
	}

	if (punti_giocatore[0] > punti_giocatore[1])
		cout<<"Vince il giocatore 0"<<endl ;
	else if (punti_giocatore[0] < punti_giocatore[1])
		cout<<"Vince il giocatore 1"<<endl ;
	else
		cout<<"Pareggio"<<endl ;

	return true ;
}

int main()
{
	elenco_t elenco ;

	inizializza(elenco) ;
	srand(time(0)) ;

	const char menu[] =
		"1. Aggiungi coppia domanda risposta\n"
		"2. Stampa elenco domande e risposte\n"
		"3. Salva elenco\n"
		"4. Carica elenco\n"
		"5. Poni domanda\n"
		"6. Inizia partita\n"
		"7. Esci\n" ;

	while (true) {
		cout<<menu<<endl ;
		int scelta ;
		cin>>scelta ;

		switch(scelta) {
		case 1:
			if(!aggiungi_domanda_risposta(elenco))
				cout<<"Aggiunta domanda/risposta fallita"<<endl ;
			break ;
		case 2:
			stampa_domande_risposte(elenco) ;
			break ;
		case 3:
			if (!salva_elenco(elenco))
				cout<<"Salvataggio fallito"<<endl ;
			break ;
		case 4:
			if (!carica_elenco(elenco))
				cout<<"Caricamento fallito"<<endl ;
			break ;
		case 5:{
			cout<<"Indice domanda? " ;
			int idx ;
			cin>>idx ;
			switch (poni_domanda(elenco, idx)) {
			case INDICE_NON_VALIDO:
				cout<<"Indice non valido"<<endl ;
				break ;
			case RISP_GIUSTA:
				cout<<"Risposta giusta"<<endl ;
				break ;
			case RISP_SBAGLIATA:
				cout<<"Risposta sbagliata"<<endl ;
				break ;
			} ;
			break ;}
		case 6:
			if (!esegui_partita(elenco))
			    cout<<"Non posso eseguire la partita: "<
				<"numero domande dispari"<<endl ;
			break;
		case 7:
			return 0 ;
		default:
			cout<<"Scelta errata"<<endl ;
		}
	}
	return 1 ;
}
