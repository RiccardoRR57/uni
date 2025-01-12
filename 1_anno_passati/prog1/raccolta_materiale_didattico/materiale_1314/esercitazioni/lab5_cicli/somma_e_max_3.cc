/*
 * Scrivere un programma che legga un numero intero n. Il numero viene
 * di nuovo richiesto finché non è compreso tra 0 e
 * 10. Successivamente si chiede l'immissione di n numero interi
 * strettamente positivi e se ne calcola e stampa la somma ed il
 * valore massimo. 
 * L'inserimento di uno zero interrompe la sequenza di
 * inserimenti anche se non sono stati raggiunti gli n numeri. Invece,
 * l'inserimento di un numero negativo è semplicemente trascurato,
 * come se non fosse stato inserito nessun numero. 
 * Realizzare il calcolo utilizzando l'istruzione for ed incrementando la 
 * variabile contatore nell'intestazione del for.
 * Trascurare problemi di overflow.
 *
*/

#include <iostream>

using namespace std ;

int main()
{
  int numero, somma=0, max=0;
  int n;
  
  /* 
   * Immissione e controllo del numero di contributi che si vogliono sommare. 
   * Tale numero deve essere compreso tra 0 e 10.
   */
  do {
    cout<<"Quanti numeri vuoi sommare (tra 0 e 10)? \n" ;
    cin>>n ;
    if (n < 0 || n > 10)
      cout<<"L'insieme di numeri che si vuole sommare e' troppo grande\n" ;
  }
  while (n <0 || n >10);
  
  for(int i=0; i<n ; i++)
    {    
      cout<<"Inserisci un numero intero positivo\nNumero "<<i+1<<": " ;
      cin>>numero ;
      if (numero < 0) 
	{ //se il numero è negativo lo scarto non incrementando il contatore
	  i--;
	  continue;
	}
      if (numero == 0) // se l'utente digita 0 fermo il ciclo
	break;
      if (numero > max) 
	max = numero;
      somma += numero;
    }
  
  cout<<"Somma "<<somma<<" massimo "<<max<<endl ;
  return 0;
}
