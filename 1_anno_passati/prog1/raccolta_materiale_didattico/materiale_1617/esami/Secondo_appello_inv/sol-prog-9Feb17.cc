#include <iostream>
#include <fstream>

using namespace std ;

const int DIM_PILA = 10; // massimo numero di blocchi nella pila
const char NOMEFILE[] = "pila.txt";

// descrittore di un blocco
struct blocco_t {
	int *valori ; // array dinamico degli interi contenuti nel blocco
	int quanti ; // numero di elementi del blocco
} ;

// descrittore della pila
struct pila_t {
	blocco_t blocchi[DIM_PILA]; // elementi nella pila
	int cima; // indice dell'ultimo elemento inserito
} ;

// inizializza la pila p, con la convenzione che -1 indica pila vuota
void inizializza(pila_t &p)
{
	p.cima = -1;
}

// inserisce un blocco in cima alla pila p; ritorna vero in caso di
// successo o falso in caso di fallimento.
bool inserisci_blocco(pila_t &p, const int valori[], int quanti)
{
	if (p.cima == DIM_PILA - 1)
		return false ;

	p.cima++ ;
	p.blocchi[p.cima].valori = new int[quanti] ;
	for (int i = 0 ; i < quanti ; i++)
		p.blocchi[p.cima].valori[i] = valori[i] ;

	p.blocchi[p.cima].quanti = quanti ;

	return true ;
}

// elimina un blocco dalla cima della pila p; ritorna vero in caso di
// successo o falso in caso di fallimento.
bool elimina_blocco(pila_t &p)
{
	if (p.cima == -1)
		return false ;

	delete [] p.blocchi[p.cima].valori ;
	p.cima-- ;
	return true ;
}

// scrive il contenuto della pila p sull'ostream os; ritorna vero in
// caso di successo o falso in caso di fallimento.
bool scrivi_pila(const pila_t &p, ostream &os, bool su_file)
{

	if (su_file)
		os<<(p.cima+1)<<endl ;

	for (int i = p.cima ; i >= 0 ; i--) {
		if (su_file)
			os<<p.blocchi[i].quanti<<endl ;
		for (int j = 0 ; j < p.blocchi[i].quanti ; j++) {
			if (j > 0)
				os<<" " ;
			os<<p.blocchi[i].valori[j] ;
		}
		os<<endl ;
	}

	return os ;
}

// carica il contenuto della pila p
bool carica_pila(pila_t &p)
{
	ifstream f(NOMEFILE) ;

	if (!f)
		return false ;

	while (elimina_blocco(p))
		;

	int num_blocchi ;
	f>>num_blocchi ;

	for (int i = 0 ; i <= num_blocchi ; i++) {
		int quanti ;
		f>>quanti ;

		int *valori = new int[quanti] ;

		for (int j = 0 ; j < quanti ; j++)
			f>>valori[j] ;

		inserisci_blocco(p, valori, quanti) ;
		delete [] valori ;
	}

	return f ;
}

// fonde il massimo numero di blocchi enlla pila p, a partire dalla in
// cima, tali che la somma del numero dei loro elementi e' uguale al
// piu' ad M
void fondi_blocchi(pila_t &p, int M)
{

	int somma = 0 ;
	int indice_min ;
	for (indice_min = p.cima;
	     indice_min >= 0 && somma + p.blocchi[indice_min].quanti <= M ;
	     indice_min--)
		somma += p.blocchi[indice_min].quanti ;

	if (somma == 0)
		return ;
	indice_min++ ;

	int *valori = new int[somma] ;

	int indice_somma = 0 ;
	for (int i = p.cima ; i >= indice_min ; i--) {
		for (int j = 0 ; j < p.blocchi[p.cima].quanti ; j++) {
			valori[indice_somma] = p.blocchi[p.cima].valori[j] ;
			indice_somma++ ;
		}
		elimina_blocco(p) ;
	}

	inserisci_blocco(p, valori, somma);
	delete [] valori ;
}

int main()
{
	const char menu[] =
		"1. Inserisci in cima\n"
		"2. Stampa contenuto pila\n"
		"3. Elimina della cima\n"
		"4. Salva pila\n"
		"5. Carica pila\n"
		"6. Fondi blocchi\n"
		"7. Esci\n" ;

	pila_t pila ;
	inizializza(pila) ;

	while (true) {
		cout<<menu<<endl ;

		int scelta ;
		cout<<"Scelta: " ;
		cin>>scelta ;

		switch (scelta) {
		case 1: {
			int quanti ;
			do {
				cout<<"Quanti elementi? " ;
				cin>>quanti;
			} while (quanti < 1);

			int *valori = new int[quanti] ;
			for (int i = 0 ; i < quanti ; i++)
				cin>>valori[i] ;

			if (!inserisci_blocco(pila, valori, quanti))
				cout<<"Inseriemnto fallito"<<endl ;
			delete [] valori ;
			break ;}
		case 2:
			scrivi_pila(pila, cout, false) ;
			break ;
		case 3:
			elimina_blocco(pila) ;
			break ;
		case 4: {
			ofstream f(NOMEFILE) ;
			if (!scrivi_pila(pila, f, true))
				cout<<"Salvataggio fallito"<<endl ;
			break ;}
		case 5:
			if (!carica_pila(pila))
				cout<<"Caricamento fallito"<<endl ;
			break ;
		case 6:{
			int M ;
			cout<<"Valore massimo della somma? " ;
			cin>>M ;
			fondi_blocchi(pila, M) ;
			break ;}
		case 7:
			return 0 ;
		default:
			cout<<"Scelta sbagliata"<<endl ;
		}
	}

	return 1 ;
}
