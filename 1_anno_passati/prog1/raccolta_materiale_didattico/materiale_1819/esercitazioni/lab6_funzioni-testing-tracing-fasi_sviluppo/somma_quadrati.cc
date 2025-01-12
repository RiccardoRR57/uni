/*
 * Scrivere un programma che legge in ingresso un numero intero e
 * verifica se può essere ottenuto come somma di quadrati
 * interi. Implementare la verifica definendo ed utilizzando in prima
 * battuta una funzione che prenda in ingresso (attraverso parametri
 * formali) due numeri interi n ed i e, se esiste un numero intero non
 * negativo j tale che n == i*i + j*j, ritorna tale numero, altrimenti
 * ritorna -1.  NOTA: la funzione non legge i numeri da stdin e non li
 * stampa su stdout.
 *
 * Commento: Utilizzando la precedente funzione, la ricerca può essere
 * effettuata per tentativi successivi, ossia provando per i = 1, 2,
 * ...  In questo caso, si può notare che non è necessario che in
 * ciascuno di tali tentativi la funzione in questione prenda in
 * considerazione valori j < i, ma basta che consideri solo j >= i.
 *
 * Suggerimento: sfruttando il precedente commento, si può
 * implementare l'algoritmo in modo più efficiente definendo ed
 * utilizzando, al posto della precedente funzione, una funzione
 * simile, che, se esiste un numero intero non negativo j >= abs(i)
 * tale che n == i*i + j*j, ritorna tale numero, altrimenti ritorna
 * -1.  Se ci si riesce, definire ed utilizzare quest'ultima funzione
 * al posto di quella generale.
 */

#include <iostream>
#include <cstdlib>

using namespace std ; 

int SommaDiQuadrati(int, int);

int main(void) 
{
  int numero; 
  int i, j ;
  
  do
    {
      cout<<"Immetti un numero intero non negativo:\n" ;
      cin>>numero ; 
    } while (numero < 0);

  // tracing:
  cout<<"[main]: numero == "<<numero<<endl ;
  for (i = 0 ; 2*i*i <= numero ; i++) {
    // tracing:
    cout<<"\t[main]: invoco SommaDiQuadrati("<<numero<<", "<<i<<")\n" ;
    if ((j = SommaDiQuadrati(numero, i)) != -1) // Leggibilità ?
      {
	      cout<<"Il numero "<<numero<<" e' la somma dei quadrati di "
		  <<i<<" e "<<j<<endl ;
	      return 0 ;
      }
  }
  cout<<"Il numero "<<numero<<" non e' somma di quadrati\n" ; 
  return 0;
} 

/*
 * Legge due numeri interi n ed i in ingresso e, se esiste un numero
 * intero non negativo j >= abs(i) tale che n == i*i + j*j, ritorna il
 * valore di j, altrimenti ritorna -1.
 */

int SommaDiQuadrati(int n, int i) 
{
  int j=0, somma = 0 ;
  j = abs(i); /* se voglio includere anche la possibilità j=i, allora
	       * parto da abs(i), altrimenti j=abs(i)+1 se voglio che
	       * j != i
	       */
  // tracing:  
  cout<<"\t\t[SommaDiQuadrati]: letto in ingresso: "<<n<<" "<<i<<endl ;
  while ( somma <= n ) {
    // tracing:  
    cout<<"\t\t\t[SommaDiQuadrati]: provo j == "<<j<<endl ;
    somma = i*i + j*j ; 
    
    if (somma == n)
      return j ;
    j++ ;
  } 
  return -1 ;
}
