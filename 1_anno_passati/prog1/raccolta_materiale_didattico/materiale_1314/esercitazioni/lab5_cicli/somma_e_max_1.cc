/*
 * Scrivere un programma che legga un numero intero n. Il numero n
 * viene di nuovo richiesto finché non è compreso tra 0 ed
 * una costante definita a tempo di scrittura del programma.
 * Successivamente si chiede l'immissione di n interi positivi e
 * se ne calcola e stampa la somma ed il valore massimo (il valore
 * piu' grande tra quelli inseriti). Realizzare il calcolo prima
 * utilizzando e poi senza utilizzare l'istruzione for.  Trascurare
 * problemi di overflow.
 *
*/

#include <iostream>

using namespace std ;

int main()
{
  int somma=0, max=0; //inizializzazione delle variabili somma e max
  int numero, i, n;
  
  /* 
   * Immissione e controllo del numero di contributi che si vogliono sommare. 
   * Tale numero deve essere compreso tra 0 e 10.
   */
  do {
    cout<<"Quanti numeri vuoi sommare (tra 0 e 10)? \n" ;
    cin>>n ;
    if (n < 0 || n > 10)
      cout<<"L'insieme di numeri che si vuole sommare e' vuoto oppure troppo grande\n" ;
  }
  while (n <= 0 || n >10);
  
  //Immissione dei numeri
  for (i=1;i<=n;i++) {
    cout<<"Prossimo numero : " ;
    cin>>numero ;
    //calcolo iterativo della somma
    somma += numero;
    //calcolo/aggiornamento del massimo
    if(numero>max)
      max = numero;
  }
  // miglioramenti: definire i nell'intestazione del for,
  // definire numero subito prima di utilizzarla, utilizzare
  // una costante con nome nel codice al posto del letterale
  // 10

  //utilizzando il ciclo while:
    i=1; //Inizializzazione della variabile controllo
    while (i<=n) {
      cout<<"Immetti il numero "<<i<<": \n" ;
      cin>>numero ;
      //calcolo iterattivo della somma
      somma += numero;
      //calcolo/aggiornamento del massimo
      if(numero>max)
        max = numero;
      i++; //Incremento della variabile controllo
    }
    
  cout<<"La somma dei "<<n<<" numeri inseriti e': "<<somma<<endl ;
  cout<<"Il massimo di tali numeri e': "<<max<<endl ;
  return 0; 
}
