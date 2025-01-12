/*
  Scrivere un programma che definisca un array di interi di lunghezza
  prefissata (a tempo di scrittura del programma), lo inizializzi con
  valori casuali e lo stampi.

  Puo' tornarvi utile la funzione di libreria rand(), che genera un
  numero casuale intero compreso tra 0 e RAND_MAX (prefissata, e
  quindi non modificabile).  Essa permette di generare una sequenza di
  numeri pseudocasuali.  Tali numeri si definiscono pseudocasuali
  perche', fissato il primo valore della sequenza (chiamato seme), e'
  fissata tutta la sequenza di valori che saranno generati nelle
  successive invocazioni della funzione rand().  Infatti i numeri sono
  generati mediante una certa funzione f(x) che, dato l'ultimo valore
  x generato, genera il prossimo valore random.  Facciamo un esempio:
  supponiamo di aver dato come seme il valore 1. Allora il primo
  valore generato dalla funzione rand() sarà 41 (se la funzione
  rand() sulla vostra macchina e' basata sullo stesso algoritmo della
  funzione sulla mia macchina). La prossima volta che verra' invocata
  la funzione rand() si otterra' il valore f(41), che e' pari a
  18647. Alla successiva invocazione si otterra' il valore di
  f(18647), che e' pari a 6334, e cosi' via.  Pertanto, per ottenere
  sequenze diverse, bisogna cambiare il valore del seme. Per cambiare
  il valore del seme, si utilizza la funzione srand(n), ove n e' il
  nuovo valore che si vuol dare al seme.

  In definitiva, la funzione srand va invocata una sola volta, per
  decidere il seme, mentre la funzione rand va invocata ogni volta che
  si vuole ottenere il prossimo valore.

  Per utilizzare le funzioni rand() ed srand(n) (e la costante
  RAND_MAX), bisogna includere il file di intestazione "cstdlib".

  Per ottenere sequenze 'quasi' completamente casuali, si può tentare
  di dare al seme un valore casuale. A questo scopo si può ad esempio
  sfruttare il valore di ritorno della funzione time (per usare tale
  funzione bisogna includere ctime), che è uguale al numero di secondi
  trascorsi dal 1 gennaio, 1970, GMT.  La funzione time prende in
  ingresso un valore numerico, che poniamo uguale a 0. Si rimanda chi
  fosse interessato ad ulteriori dettagli alla documentazione su
  questa funzione di libreria.

*/

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std ;
     
int main()
{
  const int NUM_ELEM = 5 ;
  int a[NUM_ELEM] ;

  //generazione del seme del generatore di numeri casuali
  srand(time(0));

  /*inserimento dei numeri casuali nell'array */
  for(int i=0 ; i<NUM_ELEM ; i++) 
      a[i] = rand() ;

  //stampo l'array generato
  cout<<"Ecco l'array generato:\n" ;
  for (int i=0; i < NUM_ELEM ; i++)
    cout<<"Elemento "<<i+1<<": "<<a[i]<<endl ;
  return 0;
}
