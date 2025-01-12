#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std ;

// ritorna un numero casuale tra 1 e 5
char valore_casuale()
{
    return 1 + static_cast<int>(rand() / 
				(static_cast<double>(static_cast<unsigned int>
						     (RAND_MAX)+1)/5) ) ;
    
}

// ritorna casualmente vero o falso
bool da_corrompere()
{
    if (valore_casuale() > 4)
	return true ;
    return false ;
}

enum stato_cella {scritto, non_scritto} ;

struct cella_t {
    int val_memorizzato ;
    int val_corretto ;
    stato_cella stato ;
} ;

struct regione_t {
    cella_t *celle ;
    int num_celle ;
} ;

// da invocarsi per prima, ed una sola volta
void inizializza_regione(regione_t &r)
{
    r.celle = 0 ;
    r.num_celle = 0 ;
}

const int MIN_VAL = 1 ;
const int MAX_VAL = 20 ;
const char NOME_FILE[] = "regione.txt" ;
const int M = 2 ;

// reinizializza la regione r a contenere num_celle celle non scritte
// (distruggendo il vecchio contenuto)
void reinizializza(regione_t &r, int num_celle)
{
    // si forza il valore ad essere maggiore di zero (ridondante
    // rispetto al controllo gia' fatto nel main
    num_celle = num_celle > 0 ? num_celle : 1 ;
   
    if (num_celle != r.num_celle) {
	if (r.celle != 0)
	    delete[] r.celle ; // deallocazione precedente array
	r.celle = new cella_t[num_celle] ;
    }
    r.num_celle = num_celle ;

    for (int i = 0 ; i < num_celle ; i++)
	r.celle[i].stato = non_scritto ;
}

// scrive il valore nella cella c
void scrivi_cella(cella_t &c, int valore)
{
    c.val_corretto = valore ;
    c.val_memorizzato = valore ;
    if (da_corrompere())
	c.val_memorizzato += valore_casuale() ;
    c.stato = scritto ;
}

/*
 * scrive il vettore di valori nella regione r a partire
 * dall'idirizzo iniziale ind_iniz;
 * ritorna falso in caso di errore
 */
bool scrivi(regione_t &r, int ind_iniz, const int valori[], int num_valori)
{
    if (num_valori <= 0 || ind_iniz < 0 || ind_iniz + num_valori> r.num_celle)
	return false ;
    for (int i = 0 ; i < num_valori ; i++) {
	if (valori[i] < MIN_VAL || valori[i] > MAX_VAL)
	    return false ;
	scrivi_cella(r.celle[ind_iniz + i], valori[i]) ;
    }
    return true ;
}

// stampa il contenuto della regione r
void stampa(const regione_t &r)
{
    for (int i = 0 ; i < r.num_celle ; i++) {
	if (r.celle[i].stato == non_scritto)
	    cout<<"ns" ;
	else
	    cout<<"("<<r.celle[i].val_memorizzato<<", "
		<<r.celle[i].val_corretto<<")" ;
	if (i == r.num_celle - 1)
	    cout<<"."<<endl ;
	else
	    cout<<", " ;
    }
}

// salva la regione r su un file di testo: il file contiene una riga
// (solo) per ogni cella scritta, e ciascuna riga contiene l'indice
// della cella, il valore memorizzato nella cella ed il valore
// corretto che si sarebbe dovuto memorizzare nella cella
bool salva(const regione_t &r)
{
    ofstream f(NOME_FILE) ;
    if (!f) {
	cout<<"Errore in apertura del file per la scrittura"<<endl ;
	return false ;
    }
    f<<r.num_celle<<endl ;
    for (int i = 0 ; i < r.num_celle ; i++)
	if (r.celle[i].stato != non_scritto)
	    f<<i<<" "<<r.celle[i].val_memorizzato<<" "
	     <<r.celle[i].val_corretto<<endl ;
    if (!f) {
	cout<<"Errore durante la scrittura nel file"<<endl ;
	return false ;
    }
    return true ;
}

// carica la regione r da un file di testo, il precedente contenuto e'
// perso
bool carica(regione_t &r)
{
    ifstream f(NOME_FILE) ;

    int num_celle ;
    f>>num_celle ;
    // per brevita' controlliamo il successo della lettura solo qui
    // (ovviamente affinche' la seguente lettura abbia successo, anche
    // il file deve essere stato apero con successo)
    if (!f) {
	cout<<"Errore in lettura dal file, regione non modificata"<<endl ;
	return false ;
    }
    if (num_celle != r.num_celle) {
	if (r.celle != 0)
	    delete[] r.celle ; // deallocazione precedente array
	r.celle = new cella_t[num_celle] ;
    }
    r.num_celle = num_celle ;

    int indice_cella ;
    f>>indice_cella ;
    for (int i = 0 ; i < r.num_celle ; i++)
	if (i == indice_cella) {
	    f>>r.celle[i].val_memorizzato>>r.celle[i].val_corretto ;
	    r.celle[i].stato = scritto ;
	    f>>indice_cella ;
	} else
	    r.celle[i].stato = non_scritto ;
    return true ;
}

/*
 * scrive il vettore di valori nella regione r a partire dalla prima
 * cella ed inserendo un ulteriore valore somma ogni M valori; ritorna
 * falso in caso di errore
 */
bool scrivi_con_somma(regione_t &r, const int valori[], int num_valori)
{
    int num_somme = num_valori / M ;
    if (num_valori <= 0 || num_valori + num_somme > r.num_celle)
	return false ;
    int idx_celle = 0 ;
    for (int somma = 0, idx_valori = 0 ; idx_celle < num_valori + num_somme ;
	 idx_celle++, idx_valori++) {
	if (valori[idx_valori] < MIN_VAL || valori[idx_valori] > MAX_VAL)
	    return false ;
	scrivi_cella(r.celle[idx_celle], valori[idx_valori]) ;
	somma += valori[idx_valori] ;
	if ((idx_valori + 1) % M == 0) {
	    idx_celle++ ;
	    scrivi_cella(r.celle[idx_celle], somma) ;
	    somma = 0 ;
	}
    }
    for (int j = idx_celle ; j < r.num_celle ; j++)
	r.celle[j].stato = non_scritto ;
    return true ;
}

int main()
{
    // inizializzazione seme per le funzioni di servizio
    srand(1) ;

    regione_t regione ;
    inizializza_regione(regione) ;

    const char menu[] =
	"1. Reinizializza regione\n"
	"2. Scrivi sequenza di valori\n"
	"3. Stampa contenuto regione\n"
	"4. Salva contenuto regione\n"
	"5. Carica contenuto regione\n"
	"6. Scrivi sequenza valori con somma\n"
	"7. Esci\n" ;
    
    while(true) {
	cout<<menu ;
	int scelta ;
	cin>>scelta ;

	switch(scelta) {
	case 1:{
	    int num_celle ;
	    do {
		cout<<"Nuovo numero di celle? " ;
		cin>>num_celle ;
	    } while (num_celle <= 0 ) ;
	    reinizializza(regione, num_celle) ;
	    break ;}
	case 2:{
	    int ind_iniziale ;
	    cout<<"Indirizzo cella da cui iniziare a scrivere? " ;
	    cin>>ind_iniziale ;
	    int num_valori ;
	    cout<<"Numero di valori da scrivere? " ;
	    cin>>num_valori ;
	    int * const valori = new int[num_valori] ;
	    cout<<"Sequenza di valori? " ;
	    for (int i = 0 ; i < num_valori ; i++)
		cin>>valori[i] ;
	    if (! scrivi(regione, ind_iniziale, valori, num_valori))
		cout<<"Errore in fase di scrittura"<<endl ;
	    delete[] valori ;
	    break ;}
	case 3:
	    stampa(regione) ;
	    break ;
	case 4:
	    if (! salva(regione))
		cout<<"Salvataggio fallito"<<endl ;
	    break ;
	case 5:
	    if (! carica(regione))
		cout<<"Caricamento fallito"<<endl ;
	    break ;
	case 6:{
	    int num_valori ;
	    cout<<"Numero di valori da scrivere? " ;
	    cin>>num_valori ;
	    int * const valori = new int[num_valori] ;
	    cout<<"Sequenza di valori? " ;
	    for (int i = 0 ; i < num_valori ; i++)
		cin>>valori[i] ;
	    if (! scrivi_con_somma(regione, valori, num_valori))
		cout<<"Errore in fase di scrittura"<<endl ;
	    delete[] valori ;
	    break ;}
	case 7:
	    return 0 ;
	default:
	    cout<<"Scelta errata"<<endl ;
	}
    }

    return 0 ;
}
