/*
 * Scrivere un programma che legga un numero intero n. Il numero viene
 * di nuovo richiesto finché non è compreso tra 0 e
 * 10. Successivamente si chiede l'immissione di n numeri interi
 * strettamente positivi e se ne calcola e stampa la somma ed il
 * valore massimo.
 * L'inserimento di uno zero interrompe la sequenza di
 * inserimenti anche se non sono stati raggiunti gli n numeri. Invece,
 * l'inserimento di un numero negativo è semplicemente trascurato,
 * come se non fosse stato inserito nessun numero. 
 * Realizzare il calcolo senza utilizzare l'istruzione for
 * (altrimenti e' piu' difficile).
 * Trascurare problemi di overflow.
 *
*/

#include <iostream>

using namespace std ;

int main()
{
  int numero, somma=0, max=0, i;
  int n;
  
  // per il miglioramento della qualita' del codice fare
  // riferimento alla soluzione di somma_e_max_1.cc


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
  
  i = 1 ;
  while (i <= n)
    {    
      cout<<"Inserisci un numero intero positivo\nNumero "<<i<<": " ;
      cin>>numero ;
      if (numero == 0) // letto uno zero
		break ; // mi devo fermare
      if (numero < 0) 
		continue; // lo scarto e non incremento il contatore
      if (numero > max) 
		max = numero;
      somma += numero;
      i++;
    }

  cout<<"Somma "<<somma<<" massimo "<<max<<endl ;
  return 0;
}
