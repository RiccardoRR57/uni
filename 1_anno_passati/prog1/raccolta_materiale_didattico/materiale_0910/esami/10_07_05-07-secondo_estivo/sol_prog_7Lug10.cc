#include <iostream>
#include <fstream>

using namespace std ;

// numero di valori dei due insiemi di carte
const int N = 3 ;
const char NOME_FILE[] = "partita.txt" ;

// struttura dati contenente le informazioni di una partita
struct partita_t {
    int sequenza_carte[2 * N] ; // sequenza di carte ancora da trovare
    int lung_sequenza ;         // lunghezza attuale delle sequenza:
				// se uguale a 0 non vi è nessuna
				// partita in corso
    int punteggio ;             // punteggio del giocatore
} ;

// inizializza la parita nello stato "nessuna partita in corso"
void inizializza_partita(partita_t &p)
{
    p.lung_sequenza = 0 ; // nessuna partita in corso
}

// inizia una nuova partita, posizionando le carte
void inizia_partita(partita_t &p)
{
    for (int i = 0 ; i < 2 * N ; i++) {
	do {
	    cout<<"Inserisci valore carta in posizione "<<i+1<<": " ;
	    cin>>p.sequenza_carte[i] ;
	} while (p.sequenza_carte[i] < 0 || p.sequenza_carte[i] > 2 * N) ;
    }
    p.lung_sequenza = 2 * N ;
    p.punteggio = 0 ;
}

// stampa le carte capovolte ed il punteggio corrente
void stampa_stato(const partita_t &p)
{
    if (p.lung_sequenza == 0) {
	cout<<"Nessuna partita in corso"<<endl ;
	return ;
    }
    for (int i = 0 ; i < p.lung_sequenza ; i++) {
	if (i > 0)
	    cout<<" " ;
	cout<<"X" ;
    }
    cout<<endl ;
    cout<<"Punteggio: "<<p.punteggio<<endl ;
}

/* 
 * funziona di supporto: controlla che la partita sia iniziata e le
 * posizioni inserite siano corrette, ritorna falso se una di queste
 * due condizioni non e' verificata
 */

bool controlla_posizioni(const partita_t &p, int x, int y)
{
    if (p.lung_sequenza == 0) {
	cout<<"Nessuna partita in corso"<<endl ;
	return false ;
    }
    if(x < 1 || x > p.lung_sequenza || y < 1 || y > p.lung_sequenza ||
       x == y) {
	cout<<"Posizioni errate"<<endl ;
	return false ;
    }
    return true ;
}

// ritorna vero se le carte nelle posizioni x ed y sono uguali
bool confronta_coppia(const partita_t &p, int x, int y)
{
    if (controlla_posizioni(p, x, y))
	return p.sequenza_carte[x-1] == p.sequenza_carte[y-1] ;
    else
	return false ;
}

// slava la partita in corso
bool salva_partita(const partita_t &p, ofstream &f)
{
    f<<p.lung_sequenza<<endl ;
    for (int i = 0 ; i < p.lung_sequenza ; i++) {
	if (i > 0)
	    f<<" " ;
	f<<p.sequenza_carte[i] ;
    }
    f<<endl<<p.punteggio<<endl ;
    return f ;
}

// carica la partita dal file
bool carica_partita(partita_t &p, ifstream &f)
{
    f>>p.lung_sequenza ;
    for (int i = 0 ; i < p.lung_sequenza ; i++) {
	f>>p.sequenza_carte[i] ;
    }
    f>>p.punteggio ;
    return f ;
}

/*
 * funzione di supporto: elimina l'elemento in posizione pos dalla
 * sequenza di carte da trovare
 */
void elimina_elemento(partita_t &p, int pos)
{
    for (int i = pos ; i < p.lung_sequenza - 1 ; i++)
	p.sequenza_carte[i] = p.sequenza_carte[i+1] ;
    p.lung_sequenza-- ;
}

/*
 * scopre le carte nelle posizioni x ed y ed aggiorna lo stato della
 * partita in funzione del fatto che abbiano lo stesso valore o meno
 */
void gioca_coppia(partita_t &p, int x, int y)
{
    if (! controlla_posizioni(p, x, y))
	return ;
    x-- ; y-- ; // decrementa i valori per evitare di dover scrivere
		// piu' volte x-1 ed y-1 nel resto della funzione
    cout<<"Scoperta la coppia di carte di valore: "
	<<p.sequenza_carte[x]<<" "<<p.sequenza_carte[y]<<endl ;

    if (p.sequenza_carte[x] == p.sequenza_carte[y]) {
	cout<<"Complimenti, trovata una coppia di carte uguali!"<<endl ;
	p.punteggio++ ;
	elimina_elemento(p, x) ;
	if (y > x) // se y segue x
	    y-- ;  // allora l'eliminazione dell'elemento in
		   // posizione x fa si che quello che era in posizione y
		   // passi in posizione y - 1
	elimina_elemento(p, y) ;
	if (p.lung_sequenza == 0) {
	    cout<<"Partita finita, punteggio: "<<p.punteggio<<endl ;
	    return ;
	}
    } else
	p.punteggio-- ;
    stampa_stato(p) ;
}

int main()
{
    partita_t partita ;
    // inizializza la partita nello stato "nessuna partita in corso"
    inizializza_partita(partita) ;

    const char menu[] =
	"1. Inizia partita\n"
	"2. Stampa stato\n"
	"3. Confronta coppia\n"
	"4. Salva partita\n"
	"5. Carica partita\n"
	"6. Gioca coppia\n"
	"7. Esci\n" ;
    while(true) {
	cout<<menu<<endl ;
	int scelta ;
	cin>>scelta ;

	switch(scelta) {
	case 1:
	    inizia_partita(partita) ;
	    break ;
	case 2:
	    stampa_stato(partita) ;
	    break ;
	case 3:{
	    int x, y ;
	    cout<<"Inserisci posizioni: " ;
	    cin>>x>>y ;
	    if (confronta_coppia(partita, x, y))
		cout<<"Coppia di carte uguali"<<endl ;
	    else
		cout<<"Non hai trovato una coppia di carte uguali"<<endl ;
	    break ;}
	case 4:{
	    ofstream f(NOME_FILE) ;
	    if (!f) {
		cout<<"Errore in apertura del file in scrittura"<<endl ;
		break ;
	    }
	    if (! salva_partita(partita, f))
		cout<<"Salvataggio fallito"<<endl ;
	    break;}
	case 5:{
	    ifstream f(NOME_FILE) ;
	    if (!f) {
		cout<<"Errore in apertura del file in lettura"<<endl ;
		break ;
	    }
	    if (! carica_partita(partita, f))
		cout<<"Caricamento fallito"<<endl ;
	    break;}
	case 6:{
	    int x, y ;
	    cout<<"Inserisci posizioni: " ;
	    cin>>x>>y ;
	    gioca_coppia(partita, x, y) ;
	    break ;}
	case 7:
	    return 0;
	default:
	    cout<<"Scelta errata"<<endl ;
	}
    }
    // non dovremmo mai arrivare qui
    return 1 ;
}
