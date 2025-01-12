/*
Scrivere un programma che chieda all'utente di inserire un numero di
valori interi prefissato (a tempo di scrittura del programma),
li inserisca in un vettore, stampi il vettore risultante, lo ordini poi in
senso crescente, e lo stampi nuovamente.
Implementare l'ordinamento all'interno di una funzione a cui viene passato
sia l'array che le sue dimensioni.
*/

#include <iostream>

using namespace std ;

void selectionsort(int a[], int n)
{
  // ordino l'array col metodo del selection sort
  for(int j = 0; j < n - 1 ; j++)
    for(int i = j + 1 ; i < n ; i++)
      if(a[i] < a[j])
	{
	  //scambio a[i] con a[j]
	  int aux = a[i];
	  a[i] = a[j];
	  a[j] = aux;
	}
}

int main()
{
  const int NUM_ELEM = 5 ;
  int i, j, a[NUM_ELEM];

  /*inserimento elementi dell'array */
  for(i=0; i<NUM_ELEM; i++)
    {
      cout<<"Inserisci un intero positivo (elemento "<<i+1<<")\n" ;
      cin>>a[i] ;
    }
  //stampo l'array immesso
  cout<<"Ecco l'array immesso:\n" ;
  for (i=0; i<NUM_ELEM; i++)
    cout<<"Elemento "<<i+1<<": "<<a[i]<<endl ;

  cout<<"Ordino l'array\n" ;
  bubblesort(a, NUM_ELEM) ;

  //stampo l'array ordinato
  cout<<"Ecco l'array ordinato:\n" ;
  for (i=0; i < NUM_ELEM; i++)
    cout<<"Elemento "<<i+1<<": "<<a[i]<<endl ;
  return 0;
}
