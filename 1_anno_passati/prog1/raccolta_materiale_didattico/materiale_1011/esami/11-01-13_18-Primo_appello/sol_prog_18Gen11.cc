#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std ;

const int MAX_BLOCCHI = 10 ;
const int MAX_RICHIESTE = 10 ;

// struttura dati contenente le informazioni per una richiesta
struct richiesta_t {
    int indici_blocchi[MAX_BLOCCHI] ; // indici dei blocchi da leggere
    int num_blocchi ; // numero di blocchi da leggere
} ;

// struttura dati contenente le informazioni per un insieme di
// richieste da servire
struct insieme_di_richieste_t {
    richiesta_t richieste[MAX_RICHIESTE] ; // lista delle richieste da servire
    int num_richieste ; // numero di richieste in attesa di servizio
    int ultimo_blocco_letto ; // uguale a 0 se non e' ancora letto nessun blocco
} ;

void inizializza_richieste(insieme_di_richieste_t &ins_ric)
{
    ins_ric.num_richieste = 0 ;
    ins_ric.ultimo_blocco_letto = 0 ;
}

// funzione di supporto alla funzionalita' di inserimento di una richiesta
void inserisci_in_ordine(int indice, int sequenza[], int &num_blocchi)
{
    int pos ; // posizione in cui verra' inserito l'elemento
    for (pos = 0 ; pos < num_blocchi && sequenza[pos] < indice ; pos++)
	;
    if (pos < num_blocchi && sequenza[pos] == indice)
	return ; // non inseriamo duplicati (e' solo una delle scelte possibili)
    
    // faccio posto all'elemento da inserire
    for (int i = num_blocchi ; i > pos ; i--)
	sequenza[i] = sequenza[i-1] ;

    sequenza[pos] = indice ;
    num_blocchi++ ;
}
			      
/*
 * Inserisce una richiesta nell'insieme di richieste ins_ric
 */
bool inserisci_richiesta(insieme_di_richieste_t &ins_ric)
{
    if (ins_ric.num_richieste == MAX_RICHIESTE)
	return false ;

    cout<<"Inserire gli indici dei blocchi in ordine qualsiasi: " ;

    // per semplificare il codice, definisco un riferimento al nuovo
    // elemento da inserire
    richiesta_t &r = ins_ric.richieste[ins_ric.num_richieste] ;
    r.num_blocchi = 0 ;
    
    for (int indice; r.num_blocchi < MAX_BLOCCHI && cin>>indice ;) {
	if (indice < 1)
	    cout<<"Indice "<<indice
		<<" non valido, i valori devono essere maggiori di 0"<<endl ;
	else
	    inserisci_in_ordine(indice, r.indici_blocchi, r.num_blocchi) ;
    }

    cin.clear() ;

    // aggiunge la richiesta solo se contiene almeno un blocco da leggere
    if (r.num_blocchi > 0)
	ins_ric.num_richieste++ ;

    return true ;
}

/*
 * Stampa le richieste sull'ostream os, utilizzando il formato opportuno
 * per il salvataggio dello stato nel caso in cui su_file sia true
 */
void stampa_richieste(const insieme_di_richieste_t &ins_ric,
		      ostream &os,
		      bool su_file)
{
    if (su_file)
	os<<ins_ric.ultimo_blocco_letto<<endl<<ins_ric.num_richieste<<endl ;
    
    for (int i = 0 ; i < ins_ric.num_richieste ; i++) {
	if (su_file)
	    os<<ins_ric.richieste[i].num_blocchi<<endl ;
	for (int j = 0 ; j < ins_ric.richieste[i].num_blocchi ; j++) {
	    os<<ins_ric.richieste[i].indici_blocchi[j] ;
	    if (j < ins_ric.richieste[i].num_blocchi - 1)
		os<<" " ;
	    else
		os<<endl ;
	}
    }
}

// carica lo stato, il precedente stato e' perso
void carica_stato(insieme_di_richieste_t &ins_ric, istream &is)
{
    is>>ins_ric.ultimo_blocco_letto>>ins_ric.num_richieste ;
    
    for (int i = 0 ; i < ins_ric.num_richieste ; i++) {
	is>>ins_ric.richieste[i].num_blocchi ;
	for (int j = 0 ; j < ins_ric.richieste[i].num_blocchi ; j++)
	    is>>ins_ric.richieste[i].indici_blocchi[j] ;
    }
}


// funzione di supporto per l'eliminazione delle richieste
void elimina_richiesta(insieme_di_richieste_t &ins_ric, int ric_da_eliminare)
{
    for (int i = ric_da_eliminare ; i < ins_ric.num_richieste - 1 ; i++)
	ins_ric.richieste[i] = ins_ric.richieste[i+1] ;
    ins_ric.num_richieste-- ;
}

/*
 * Ritorna l'indice della richiesta servita (e quindi eliminata), oppure 0
 * se nessuna richiesta e' stata servita
 */
int servi_richiesta(insieme_di_richieste_t &ins_ric)
{
    if (ins_ric.num_richieste == 0)
	return 0 ;

    int idx_ric_da_servire = 0 ;
    for (int ric_idx = 1 ; ric_idx < ins_ric.num_richieste ; ric_idx++) {
	/*
	 * Se ultimo_blocco_letto == 0, il seguente controllo restituisce
	 * la richiesta il cui primo blocco ha indice minimo
	 */
	if (abs(ins_ric.richieste[ric_idx].indici_blocchi[0]
		- ins_ric.ultimo_blocco_letto) <
	    abs(ins_ric.richieste[idx_ric_da_servire].indici_blocchi[0] -
		ins_ric.ultimo_blocco_letto))
	    idx_ric_da_servire = ric_idx ;
    }

    richiesta_t &ric_da_servire = ins_ric.richieste[idx_ric_da_servire] ;


    // aggiorna il valore dell'ultimo blocco letto
    int idx_ultimo_blocco = ric_da_servire.num_blocchi - 1 ;
    ins_ric.ultimo_blocco_letto =
	ric_da_servire.indici_blocchi[idx_ultimo_blocco] ;

    /*
     * simula il servizio della richiesta con la stampa del suo indice e del
     * suo contenuto
     */
    cout<<"Servita la richiesta "<<idx_ric_da_servire<<": " ;
    for (int i = 0 ; i < ric_da_servire.num_blocchi ; i++) {
	cout<<ric_da_servire.indici_blocchi[i] ;
	if (i < ric_da_servire.num_blocchi - 1)
	    cout<<" " ;
    }
    cout<<"Ultimo blocco letto: "<<ins_ric.ultimo_blocco_letto<<endl ;
    cout<<endl ;
	    
    // elimina la richiesta
    elimina_richiesta(ins_ric, idx_ric_da_servire) ;
    
    return idx_ric_da_servire ;
}

int main()
{
    insieme_di_richieste_t ins_ric ;
    inizializza_richieste(ins_ric) ;

    const char menu[] =
	"1. Inserisci Richiesta\n"
	"2. Stampa Richieste\n"
	"3. Salva stato\n"
	"4. Carica stato\n"
	"5. Servi richiesta\n"
	"6. Esci\n" ;

    while(true) {
	cout<<endl<<menu ;

	int scelta ;
	cin>>scelta ;
	switch(scelta) {
	case 1:
	    if (!inserisci_richiesta(ins_ric))
		cout<<"Inserimento fallito"<<endl ;
	    else
		cout<<"Inserimento riuscito"<<endl ;
	    break ;
	case 2:
	    stampa_richieste(ins_ric, cout, false) ;
	    break ;
	case 3:{
	    ofstream f("insieme_richieste.txt") ;
	    if (!f)
		cout<<"Errore in apertura del file"<<endl ;
	    else
		stampa_richieste(ins_ric, f, true) ;}
	    break ;
	case 4:{
	    ifstream f("insieme_richieste.txt") ;
	    if (!f)
		cout<<"Errore in apertura del file"<<endl ;
	    else
		carica_stato(ins_ric, f) ;}
	    break ;
	case 5:
	    servi_richiesta(ins_ric) ;
	    break ;
	case 6:
	    return 0 ;
	default:
	    cout<<"Scelta non valida"<<endl ;
	}
    }
}
