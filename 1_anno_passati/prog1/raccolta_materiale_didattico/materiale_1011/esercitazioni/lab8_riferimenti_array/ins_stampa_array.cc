/*

Scrivere un programma che chieda all'utente di inserire un numero di
valori interi prefissato (a tempo di scrittura del programma), 
li inserisca in un vettore e stampi il vettore risultante.

Un possibilie output è il seguente:

Inserisci un intero positivo (elemento 1 / 3): 2
Inserisci un intero positivo (elemento 2 / 3): 5
Inserisci un intero positivo (elemento 3 / 3): 1
Ecco l'array immesso:
Elemento 1: 2
Elemento 2: 5
Elemento 3: 1

*/
#include <iostream>

using namespace std ;

int main()
{
  const int NUM_ELEMENTI = 3 ;
  int a[NUM_ELEMENTI];

  /*inserimento elementi dell'array */
  for(int i=0; i < NUM_ELEMENTI ; i++) {
      cout<<"Inserisci un intero positivo (elemento "<<i+1
	  <<" / "<<NUM_ELEMENTI<<"): " ;
      cin>>a[i] ;
  }
  
  //stampo l'array immesso
  cout<<"Ecco l'array immesso:\n" ;
  for (int i=0; i < NUM_ELEMENTI ; i++)
      cout<<"Elemento "<<i+1<<": "<<a[i]<<endl ;
  return 0;
}
