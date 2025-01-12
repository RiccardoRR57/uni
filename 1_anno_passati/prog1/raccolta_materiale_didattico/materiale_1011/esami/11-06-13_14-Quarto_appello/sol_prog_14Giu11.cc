#include <iostream>
#include <fstream>

using namespace std ;

// nnumero di sezioni
const int NUM_SEZIONI = 3 ;

// nome del file di testo in cui salvare lo stao
const char NOME_FILE[] = "programmazione.txt" ;

// comandi possibili per ogni singola sezione
enum singolo_comando_t {NESSUNO, ACCENSIONE, SPEGNIMENTO} ;

// programmazione delle sezioni per una data ora
struct programmazione_sezioni_t {
    singolo_comando_t comando[NUM_SEZIONI] ;
} ;

// tipo di dato per definire delle programmazioni giornaliere
typedef programmazione_sezioni_t programmazione_t[24] ;

// stati possibili per una sezione
enum stato_sezione_t {ACCESA, SPENTA} ;

// descrittore di un controllore
struct controllore_t {
    programmazione_t programmazione ; // programmazione giornaliera attuale
    int ora_corrente ;                // ora corrente
    stato_sezione_t stato_sezioni[NUM_SEZIONI] ; // stato attuale delle sezioni
} ;

// inizializza un controllore
void inizializza(controllore_t &c)
{
    for (int i = 0 ; i < 24 ; i++)
	    for (int j = 0 ; j < NUM_SEZIONI ; j++)
		c.programmazione[i].comando[j] = NESSUNO ;
    c.ora_corrente = 0 ;
    for (int j = 0 ; j < NUM_SEZIONI ; j++)
	c.stato_sezioni[j] = SPENTA ;
}

/*
 * Aggiunge una attivazione per la sezione num_sez alla programmazione prog,
 * dalla ora ora_attiv alla ora ora_spegn, dopo aver eliminato ogni precedente
 * attivazione/disattivazione per tale sezione.
 * Ritorna falso in caso di fallimento, vero altrimenti.
 */
bool aggiungi_attivazione_unica(programmazione_t &prog,
				int num_sez, int ora_attiv, int ora_spegn)
{
    if (num_sez < 0 || num_sez >= NUM_SEZIONI
	|| ora_attiv < 0 || ora_attiv > 23
	|| ora_spegn <= ora_attiv || ora_spegn > 23)
    return false ;
    
    // eliminazione di tutte le attivazioni
    for (int i = 0 ; i < 24 ; i++)
	prog[i].comando[num_sez] = NESSUNO ;

    // inserimento della attivazione desiderata
    prog[ora_attiv].comando[num_sez] = ACCENSIONE ;
    prog[ora_spegn].comando[num_sez] = SPEGNIMENTO ;

    return true ;
}

/*
 * Aggiunge una attivazione per la sezione num_sez alla programmazione prog,
 * dalla ora ora_attiv alla ora ora_spegn. La nuova attivazione non deve
 * avere alcuna intersezione, ne' essere contigua rispetto ad eventuali
 * programmazioni preesistenti per la stessa sezione.
 * Ritorna falso in caso di fallimento, vero altrimenti.
 */
bool aggiungi_attivazione(programmazione_t &prog,
			   int num_sez, int ora_attiv, int ora_spegn)
{
    if (num_sez < 0 || num_sez >= NUM_SEZIONI
	|| ora_attiv < 0 || ora_attiv > 23
	|| ora_spegn <= ora_attiv || ora_spegn > 23)
    return false ;
    
    // controllo della presenza di intersezioni/contiguita'
    bool sezione_accesa = false ; // messo a falso all'inizio
    for (int i = 0 ; i <= ora_spegn ; i++) {
	if (prog[i].comando[num_sez] == ACCENSIONE)
	    sezione_accesa = true ;
	if (i >= ora_attiv && sezione_accesa)
	    /*
	     * La sezione risulta accesa all'interno del periodo di
	     * attivazione che vorremmo aggiungere, quindi siamo certi
	     * che non si puo' effettuare l'aggiunta
	     */
	    break ;
	if (prog[i].comando[num_sez] == SPEGNIMENTO)
	    sezione_accesa = false ;
    }
    if (sezione_accesa)
	/*
	 * In base alla programmazione preesistente, la sezione risulta ancora
	 * accesa nell'ora di spegnimento che vogliamo aggiungere, quind
	 */
	return false ;

    // aggiungiamo l'attivazione
    prog[ora_attiv].comando[num_sez] = ACCENSIONE ;
    prog[ora_spegn].comando[num_sez] = SPEGNIMENTO ;

    return true ;
}

// stampa la programmazione prog
void stampa_programmazione(const programmazione_t &prog)
{
    for (int i = 0 ; i < 24 ; i++) {
	int num_sez_non_programmate = 0 ;
	for (int j = 0 ; j < NUM_SEZIONI ; j++)
	    if (prog[i].comando[j] == NESSUNO)
		num_sez_non_programmate++ ;
	if (num_sez_non_programmate == NUM_SEZIONI)
	    continue ;
	cout<<"[ "<<i<<" ]" ;
	for (int j = 0 ; j < NUM_SEZIONI ; j++)
	    switch (prog[i].comando[j]) {
	    case NESSUNO:
		break ;
	    case ACCENSIONE:
		cout<<" "<<j<<": "<<"ACCENSIONE" ;
		break ;
	    case SPEGNIMENTO:
		cout<<" "<<j<<": "<<"SPEGNIMENTO" ;
		break ;
	    }
	cout<<endl ;
   }
}

// salva la programmazione prog
bool salva_programmazione(const programmazione_t &prog)
{
    ofstream f(NOME_FILE) ;
    for (int i = 0 ; i < 24 ; i++) {
	for (int j = 0 ; j < NUM_SEZIONI ; j++)
	    switch (prog[i].comando[j]) {
	    case NESSUNO:
		f<<'N'<<" " ;
		break ;
	    case ACCENSIONE:
		f<<'A'<<" " ;
		break ;
	    case SPEGNIMENTO:
		f<<'S'<<" " ;
		break ;
	    }
	f<<endl ;
    }
    return f ;
}

// carica la programmazione prog
bool carica_programmazione(programmazione_t &prog)
{
    ifstream f(NOME_FILE) ;
    for (int i = 0 ; i < 24 ; i++) {
	for (int j = 0 ; j < NUM_SEZIONI ; j++) {
	    char comando ;
	    f>>comando ;
	    if (!f)
		return false ;
	    switch (comando) {
	    case 'N':
		prog[i].comando[j] = NESSUNO ;
		break ;
	    case 'A':
		prog[i].comando[j] = ACCENSIONE ;
		break ;
	    case 'S':
		prog[i].comando[j] = SPEGNIMENTO ;
		break ;
	    }
	}
    }
    return f ;
}

// incrementa l'ora del controllore c e cambia lo stato delle sezioni
void incrementa_ora(controllore_t &c)
{
    c.ora_corrente = (c.ora_corrente + 1) % 24 ;
    cout<<c.ora_corrente<<" -> " ;
    for (int j = 0 ; j < NUM_SEZIONI ; j++) {
	switch (c.programmazione[c.ora_corrente].comando[j]) {
	case NESSUNO:
	    break ;
	case ACCENSIONE:
	    c.stato_sezioni[j] = ACCESA ;
	    break ;
	case SPEGNIMENTO:
	    c.stato_sezioni[j] = SPENTA ;
	    break ;
	}
	if (j > 0)
	    cout<<", " ;
	cout<<j<<": " ;
	if (c.stato_sezioni[j] == ACCESA)
	    cout<<"ACCESA" ;
	else
	    cout<<"SPENTA" ;
    }
    cout<<endl ;
}

int main()
{
    controllore_t controllore ;
    programmazione_t & prog = controllore.programmazione ;
    inizializza(controllore) ;

    const char menu[] =
	"1. Aggiungi attivazione unica\n"
	"2. Stampa programmazione\n"
	"3. Salva programmazione\n"
	"4. Carica programmazione\n"
	"5. Aggiungi attivazione\n"
	"6. Incrementa ora\n"
	"7. Esci\n" ;

    while(true) {
	cout<<menu<<endl ;
	int scelta ;
	cin>>scelta ;

	switch(scelta) {
	case 1:{
	    int num_sez, ora_attiv, ora_spegn ;
	    cout<<"Inserire numero sezione, ora di attivazione ed "
		<<"ora di spegnimento: " ;
	    cin>>num_sez>>ora_attiv>>ora_spegn ;
	    if (! aggiungi_attivazione_unica(prog, num_sez, ora_attiv,
					     ora_spegn))
		cout<<"Aggiunta attivazione fallita"<<endl ;
	    break ;}
	case 2:
	    stampa_programmazione(prog) ;
	    break ;
	case 3:
	    if (! salva_programmazione(prog))
		cout<<"salvataggio fallito"<<endl ;
	    break ;
	case 4:
	    if (! carica_programmazione(prog))
		cout<<"salvataggio fallito"<<endl ;
	    break ;
	case 5:{
	    int num_sez, ora_attiv, ora_spegn ;
	    cout<<"Inserire numero sezione, ora di attivazione ed "
		<<"ora di spegnimento: " ;
	    cin>>num_sez>>ora_attiv>>ora_spegn ;
	    if (! aggiungi_attivazione(prog, num_sez, ora_attiv, ora_spegn))
		cout<<"Aggiunta attivazione fallita"<<endl ;
	    break ;}
	case 6:
	    incrementa_ora(controllore) ;
	    break ;
	case 7:
	    return 0 ;
	}
    }
    // qui non dovremmo arrivare mai
    return 1 ;
}
