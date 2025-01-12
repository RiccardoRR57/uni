/*
  Una pila è una struttura dati che prevede due operazioni:

  1) push: inserimento di un elemento di un dato valore (da passare alla 
  funzione)in cima alla pila. La pila ha una dimensione massima predefinita; 
  se la si supera l'operazione di push fallisce;

  2) pop: estrazione di un elemento dalla cima della pila; se la pila
  è vuota l'operazione fallisce altrimenti viene ritornato il valore
  dell'elemento estratto (una volta estratto l'elemento, è necessario
  modificarne il valore all'interno della pila?)
  
  Scrivere un programma che implementi una pila di elementi di tipo
  int. In particolare il programma deve offrire all'utente la
  possibilità di scegliere tra le seguenti operazioni:

  1) inserimento nella pila da stdin: si aggiunge un elemento in cima
     alla pila e si stampa il nuovo contenuto dell'intera pila

  2) estrazione e stampa dalla pila su stdout: si chiede all'utente
     quanti elementi si vuole estrarre dalla pila mediante una
     successione di pop, quindi si effettua una successione di
     estrazioni e stampe del valore su stdout, in numero pari al
     minimo tra il numero di elementi nella pila ed il numero di
     elementi che l'utente ha chiesto di estrarre/stampare

     Come al solito potete definire la pila come variabile locale al
     main, o come variabile globale. La prima soluzione è un pò più
     complessa, ma più pulita, mentre la seconda è più semplice ma
     è peggiore in termini di visibilita' delle variabili ed effetti
     collaterali.
  
  Finite le precedenti due operazioni, realizzare l'operazione:

  3) Riserva memoria: si passa il numero di elementi che si intende
     riservare a partire dalla cima (come se si fossero fatte delle
     push, ma senza cambiare valore agli elementi)


  Aggiungere la possibilità per l'utente di riservare memoria con la
  precedente operazione. In particolare, in conseguenza della
  richiesta di riservare memoria, stampare il valore degli elementi
  riservati

  A questo punto testare il progranmma nel suo insieme facendo un
  pò di inserimenti, seguiti da altrettante estrazioni. Scegliere
  infine di riservare memoria, e controllare il contenuto degli
  elementi riservati. Sono valori fissi o dipendono dalla precedente
  sequenza di inserimenti ed estrazioni?

  Possibile estensione:
  
  4) Operazione di rilascio memoria: si passa il numero di elementi
     che si intende rilasciare a partire dalla cima della pila.
*/

#include <iostream>

using namespace std ;

const int MAX_ELEM = 10 ;


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


void inserimento(pila_t &p)
{
    cout<<"Valore da aggiungere? ";

    int i ;
    cin>>i;
    if (push(p, i) == false)
	    cout<<"Pila piena!"<<endl ;

    cout<<"Contenuto pila: " ;
    for (int i = 0 ; i < p.quanti ; i++) {
	cout<<p.elem[i]<<" " ;
    }
    cout<<endl ;
}

void estrazione_stampa(pila_t &p, int n)
{
    int i ;

    for (i = 0 ; i < n ; i++) {
		int val ;
		if (pop(p, val) == false) 
			break ;
		cout<<val<<" " ;
    }
    cout<<endl ;
}

void riserva_memoria(pila_t &p, int &n)
{
    int max_n = MAX_ELEM - p.quanti ;
    n = n > max_n ? max_n : n ;
    p.quanti += n ;
}

void riserva_memoria_stampa(pila_t &p, int n)
{
    int vecchio = p.quanti ; 
    riserva_memoria(p, n) ;
    cout<<"Valore elementi riservati: " ;
    for (int i = vecchio ; i < p.quanti ; i++) {
	cout<<p.elem[i]<<" " ;
    }
    cout<<endl ;
}

int main()
{
    // definizione di un oggetto di tipo pila
    pila_t pila ;
    pila.quanti = 0 ; // NON DIMENTICATE LE INIZIALIZZAZIONI !!!

    while (true) {
          int scelta ;
	  int n ;

          cout<<"\t1 Inserimento in pila da stdin\n" ;
          cout<<"\t2 Estrazione e stampa su stdout\n" ;
          cout<<"\t3 Riserva memoria e stampa su stdout\n" ;
          cout<<"\t4 Uscita\n" ;
          cout<<"Scelta: " ;
          cin>>scelta ;
          switch(scelta) {
	  case 1:
	      inserimento(pila) ;
	      break ;
	  case 2:
	      cout<<"Quanti elementi vuoi estrarre?\n" ;
	      cin>>n ;
	      estrazione_stampa(pila, n) ;
	      break ;
	  case 3:
	      cout<<"Quanti elementi vuoi riservare?\n" ;
	      cin>>n ;
              riserva_memoria_stampa(pila, n) ;
	      break ;
	  case 4:
	      return 0;
	  default:
	      cout<<"Scelta non valida\n" ;
          }
    }
    return 0;
}
