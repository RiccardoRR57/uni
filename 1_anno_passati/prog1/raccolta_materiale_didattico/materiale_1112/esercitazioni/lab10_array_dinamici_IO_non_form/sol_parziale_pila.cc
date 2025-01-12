/*
  Per la traccia fare riferimento al file pila.cc
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
		  //inserimento(pila) ;
	      break ;
	  case 2:
	      cout<<"Quanti elementi vuoi estrarre?\n" ;
	      cin>>n ;
	      //estrazione_stampa(pila, n) ;
	      break ;
	  case 3:
	      cout<<"Quanti elementi vuoi riservare?\n" ;
	      cin>>n ;
              //riserva_memoria_stampa(pila, n) ;
	      break ;
	  case 4:
	      return 0;
	  default:
	      cout<<"Scelta non valida\n" ;
          }
    }
    return 0;
}
