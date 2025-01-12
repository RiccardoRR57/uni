/*
  Una pila è una struttura dati che prevede due operazioni:

  1) push: inserimento di un elemento in cima alla pila. La pila ha una
  dimensione massima predefinita; se la si supera l'operazione di
  push fallisce;

  2) pop: estrazione di un elemento dalla cima della pila; se la pila
  è vuota l'operazione fallisce altrimenti viene ritornato il valore
  dell'elemento estratto
  
  Scrivere un programma che implementi una pila di elementi di tipo
  int. In particolare il programma deve offrire all'utente la
  possibilità di scegliere tra le seguenti operazioni:

  1) inserimento nella pila da stdin: si effettuano una serie di push
     successive finché la pila si riempie, o l'utente comunica la fine
     dell'input;

  2) estrazione e stampa dalla pila su stdout: si chiede all'utente
     quanti elementi si vuole estrarre dalla pila mediante una
     successione di pop, quindi si effettua una successione di
     estrazioni e stampe del valore su stdout, in numero pari al
     minimo tra il numero di elementi nella pila ed il numero di
     elementi che l'utente ha chiesto di estrarre/stampare

  3) inserimento nella pila da file: si effettuano una serie di push
     successive leggendo i valori da un file, il cui nome viene
     fornito dall'utente. L'inserimento procede finché la pila si
     riempie o si raggiunge la fine del file

  4) estrazione e stampa dalla pila su file: si chiede all'utente
     quanti elementi si vuole estrarre dalla pila mediante una
     successione di pop, ed il nome del file in cui scrivere i valori
     di tali elementi; quindi si effettua una successione di
     estrazioni e scritture del valore sul file, in numero pari al
     minimo tra il numero di elementi nella pila ed il numero di
     elementi che l'utente ha chiesto di estrarre/scrivere

     Come al solito potete definire la pila come variabile locale al
     main, o come variabile globale. La prima soluzione è un pò più
     complessa, ma più pulita, mentre la seconda è più semplice ma può
     rivelarsi peggiore in termini di visibilita' delle variabili.
*/

#include <iostream>
#include <fstream>

#include <iostream>

using namespace std ;

const int MAX_ELEM = 10 ;
const int MAX_LEN = 10 ;

struct pila_t {
    int elem[MAX_ELEM] ;
    int quanti ;
} ;

// ritorna false in caso di fallimento, true altrimenti
bool push(pila_t &p, int val)
{
    if (p.quanti < MAX_ELEM) {
	p.elem[p.quanti++] = val ;
	return true ;
    }
    return false ;
}

bool pop(pila_t &p, int &val)
{
    if (p.quanti > 0) {
	val = p.elem[--(p.quanti)] ;
	return true;
    }
    return false ;
}

void inserimento(istream &in, pila_t &p)
{
    int i ;
    while (in>>i) 
	    if (push(p, i) == false) {
		    cout<<"Pila piena!"<<endl ;
		    break ;
	    }
    in.clear() ; // altrimenti le letture successive falliranno
    cout<<"Contenuto pila: " ;
    for (int i = 0 ; i < p.quanti ; i++) {
	cout<<p.elem[i]<<" " ;
    }
    cout<<endl ;
}

void estrazione_stampa(ostream &os, pila_t &p, int n)
{
    int i ;

    for (i = 0 ; i < n ; i++) {
	int val ;
	if (pop(p, val) == 0) 
	    break ;
	os<<val<<" " ;
    }
    os<<endl ;
}


int main()
{
    pila_t pila ;
    pila.quanti = 0 ; // NON DIMENTICATE LE INIZIALIZZAZIONI !!!

    while (1) {
          int scelta ;
	  char nome[MAX_LEN] ;
	  int n ;

          cout<<"\t1 Inserimento in pila da stdin\n" ;
          cout<<"\t2 Estrazione e stampa su stdout\n" ;
          cout<<"\t3 Inserimento in pila da file\n" ;
          cout<<"\t4 Estrazione e stampa su file\n" ;
          cout<<"\t5 Esci\n" ;
          cout<<"Scelta: " ;
          cin>>scelta ;
          switch(scelta) {
	  case 1:
	      inserimento(cin, pila) ;
	      break ;
	  case 2:
	      cout<<"Quanti elementi vuoi estrarre?\n" ;
	      cin>>n ;
	      estrazione_stampa(cout, pila, n) ;
	      break ;
	  case 3:
	      cout<<"Nome file? " ;
	      cin>>nome ;
	      {
		      // Apertura del file in lettura
		      ifstream f(nome);
		      if (!f) {
			      cerr<<"Errore in apertura del file\n" ;
			      return 1;
		      }
		      inserimento(f, pila) ;
		      // qui f muore, quindi il file viene chiuso
	      }
	      break ;
	  case 4:
	      cout<<"Quanti elementi vuoi estrarre?\n" ;
	      cin>>n ;
	      //Creazione e Apertura del file in scrittura
	      cout<<"Nome file? " ;
	      cin>>nome ;
	      {
		      ofstream f(nome);
		      if (!f) {
			      cerr<<"Errore in creazione del file\n" ;
			      return 2;
		      }
		      estrazione_stampa(f, pila, n) ;
		      // qui f muore, quindi il file viene chiuso
	      }
	      break ;
	  case 5:
	      return 0;
	  default:
	      cout<<"Scelta non valida\n" ;
          }
    }
    return 0;
}
