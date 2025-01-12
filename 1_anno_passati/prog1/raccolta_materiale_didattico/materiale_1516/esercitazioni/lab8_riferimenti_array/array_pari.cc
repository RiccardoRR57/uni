/*
  Scrivere un programma che definisca un vettore di interi di
  lunghezza prefissata (a tempo di scrittura del programma) e lo
  inizializzi con valori casuali compresi tra due valori interi
  introdotti dall'utente. Il programma riversa quindi in un secondo
  vettore i soli elementi di valore pari contenuti nel primo, infine
  stampa il contenuto dei due vettori.  Il riversamento DEVE essere
  effettuato da una funzione dedicata.  La funzione deve o non deve
  ritornare il numero di elementi copiati?
*/

#include <stdlib.h>
#include <iostream>

using namespace std ;
#include <time.h>

const int DIM = 20 ; // cattiva scelta

// ritorna il numero di elementi del secondo vettore
int riversa(const int a[], int pari[])
{
  int lung_pari, i ;
 
  for(i=0, lung_pari = 0 ; i<DIM; i++) 
      if((a[i]%2) == 0)
	{
	  pari[lung_pari]=a[i];
	  lung_pari++;	
	}
  return lung_pari ;
}

int main()
{
  int min, max ;
  int i,lung_pari, a[DIM], pari[DIM];
  srand(time(0));
  cout<<"Inserire il valore minimo e massimo: " ;
  cin>>min>>max ;

  /*inserimento elementi dell'array */
  for(i=0 ; i<DIM; i++) 
      a[i] = min + 
		static_cast<int>((static_cast<double>(rand())/RAND_MAX)
	      * (max - min));
		// variante: min + rand() % (max - min + 1) ;

  lung_pari = riversa(a, pari) ; // come mai non passo la dimensione?
  //stampo l'array immesso
  cout<<"Array iniziale generato:\n" ;
  for (i=0; i<DIM; i++)
    cout<<"Elemento "<<i+1<<": "<<a[i]<<endl ;
  /*stampo l'array dei numeri pari*/
  cout<<"Array dei numeri pari:\n" ;
  for(i=0; i < lung_pari; i++) 
    cout<<"Elemento "<<i+1<<": "<<pari[i]<<endl ;  
  return 0;
}

