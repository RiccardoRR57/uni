#include <iostream>
#include <fstream>
#include <cstring>

using namespace std ;

// descrittore contatore
struct contatore_t {
	char *nome ; // una parola
	int valore ; // valore del contatore
	int redir ;  // indice di un eventuale redirezionamento 
} ;

const int MAX_CONT = 10 ; // numero massimo contatori
// descrittore insieme di contatori
struct ins_contatori_t {
	contatore_t contatori[MAX_CONT] ; // array contenente i contatori
	int num_cont ; // numero corrente di contatori nell'insieme
} ;

const char NOME_FILE[] = "insieme.txt" ;
// lunghezza massima stringhe per le letture da stdin e da file
const int MAXLEN = 512 ;

// inizializza l'insieme ins a vuoto
void inizializza(ins_contatori_t &ins)
{
    ins.num_cont = 0 ;
}

// aggiunge un contatore, il cui campo nome è dato dal secondo
// parametro formale, all'insieme ins; ritorna vero in caso di
// successo, falso altrimenti
bool aggiungi_contatore(ins_contatori_t &ins, const char nome[])
{
    if (ins.num_cont == MAX_CONT || nome[0] == '\0')
	return false ;

    ins.contatori[ins.num_cont].nome = new char[strlen(nome) + 1] ;
    strcpy(ins.contatori[ins.num_cont].nome, nome) ;

    ins.contatori[ins.num_cont].valore = 0 ;
    ins.contatori[ins.num_cont].redir = ins.num_cont ;

    ins.num_cont++ ;
    return true ;
}

// incrementa il contatore di indice i dell'insieme ins; ritorna vero in caso di
// successo, falso altrimenti
bool incrementa_contatore(ins_contatori_t &ins, int i)
{
    if (i < 0 || i >= ins.num_cont)
	return false ;

    ins.contatori[i].valore++ ;

    return true ;
}

// scrive il contenuto dell'insieme ins sull'ostream os; ritorna vero
// in caso di successo, falso altrimenti
bool scrivi_contatori(const ins_contatori_t &ins, ostream &os, bool su_file)
{
    if (su_file)
	os<<ins.num_cont<<endl ;
    for (int i = 0 ; i < ins.num_cont ; i ++)
	os<<ins.contatori[i].nome<<"\t\t\t"<<ins.contatori[i].valore<<endl ;

    return os ;
}

// carica il nuovo lo stato dell'insieme ins dal file associato
// all'istream f, eliminando il precedente contenuto dell'insieme;
// ritorna vero in caso di successo, falso altrimenti
bool carica_insieme(ins_contatori_t &ins, ifstream &f)
{
    for (int i = 0 ; i < ins.num_cont ; i++)
	delete[] ins.contatori[i].nome ;

    f>>ins.num_cont ;
    for (int i = 0 ; i < ins.num_cont ; i ++) {
	char nome[MAXLEN] ;
	f>>nome ;

	ins.contatori[i].nome = new char[strlen(nome) + 1] ;
	strcpy(ins.contatori[i].nome, nome) ;
	
	f>>ins.contatori[i].valore ;
	ins.contatori[i].redir = i ;
    }

    return f ;
}

// redireziona il contatore di indice i1 dell'insieme ins verso il
// contatore di indice i2; ritorna vero in caso di successo, falso
// altrimenti
bool redireziona(ins_contatori_t &ins, int i1, int i2)
{
    if (i1 < 0 || i1 >= ins.num_cont ||
	i2 < 0 || i2 >= ins.num_cont ||
	ins.contatori[i2].redir == i1)
	return false ;
	
    ins.contatori[i1].redir = i2 ;
    return true ;
}

// incrememnta il contatore di indice i dell'insieme ins tenendo conto
// dei redirezionamenti; ritorna vero in caso di successo, falso
// altrimenti
bool incrementa_contatore2(ins_contatori_t &ins, int i)
{
    if (i < 0 || i >= ins.num_cont)
	return false ;
    
    int i_finale = ins.contatori[i].redir ;
    // il ciclo si ferma se il contatore corrente e' uguale a quello
    // di partenza o non e' redirezionato verso alcun altro contatore
    while(i_finale != i && ins.contatori[i_finale].redir != i_finale) {
	cout<<"finale "<<i_finale<<" redir "<<ins.contatori[i_finale].redir
	    <<endl ;
	i_finale = ins.contatori[i_finale].redir ;
    }

    ins.contatori[i_finale].valore++ ;

    return true ;
}

int main()
{
    ins_contatori_t insieme ;
    inizializza(insieme) ;

    const char menu[] =
	"1. Aggiungi contatore\n"
	"2. Incrementa contatore\n"
	"3. Stampa contatori\n"
	"4. Salva insieme\n"
	"5. Carica insieme\n"
	"6. Redireziona\n"
	"7. Incrementa contatore 2\n"
	"8. Esci\n" ;

    while (true) {
	cout<<menu<<endl ;
	int scelta ;
	cin>>scelta ;
	switch (scelta) {
	case 1:{
	    char nome[MAXLEN] ;
	    cout<<"Nome del tipo di richieste: " ;
	    cin>>nome ;
	    if (! aggiungi_contatore(insieme, nome))
		cout<<"Aggiunta fallita"<<endl ;
	    break ;}
	case 2:{
	    int i ;
	    cout<<"Indice contatore da incrementare: " ;
	    cin>>i ;
	    if (! incrementa_contatore(insieme, i))
		cout<<"Incremento fallito"<<endl ;
	    break ;}
	case 3:
	    scrivi_contatori(insieme, cout, false) ;
	    break ;
	case 4: {
	    ofstream f(NOME_FILE) ;
	    if (! scrivi_contatori(insieme, f, true))
		cout<<"Salvataggio fallito"<<endl ;
	    break ;}
	case 5: {
	    ifstream f(NOME_FILE) ;
	    if (! carica_insieme(insieme, f))
		cout<<"Caricamente fallito"<<endl ;
	    break ;}
	case 6: {
	    int i1, i2 ;
	    cout<<"Indici i1 ed i2: " ;
	    cin>>i1>>i2 ;
	    if (! redireziona(insieme, i1, i2))
		cout<<"Redirezionamento fallito"<<endl ;
	    break ;}
	case 7:{
	    int i ;
	    cout<<"Indice contatore da incrementare: " ;
	    cin>>i ;
	    if (! incrementa_contatore2(insieme, i))
		cout<<"Incremento fallito"<<endl ;
	    break ;}
	case 8:
	    return 0 ;
	default:
	    cout<<"Scelta errata"<<endl ;
	}
    }

    return 0 ;
}

