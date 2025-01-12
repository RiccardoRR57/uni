/*
Scrivere un programma che stampi il fattoriale di un numero intero
non negativo letto dallo stdin. Implementare il calcolo (e non la stampa)
del fattoriale mediante una funzione. Implementare la lettura del
valore e la stampa del fattoriale all'interno della funzione main.
*/

#include <iostream>

using namespace std ;

/*
 * Legge in ingresso un numero intero n, e ritorna il valore n!
 */
int fattoriale (int n)
{
  int fatt = 1 ; //definizione delle variabili locali
  for (int i = 1; i <= n; i++)
    fatt = fatt*i;
  return fatt;
}

int main ()
{
  int numero;
  do {
    cout<<"Immetti un numero intero positivo:\n" ;
    cin>>numero ;
  } while (numero<0);
  cout<<"Il valore del fattoriale del numero "
      <<numero<<" vale "<<fattoriale(numero)<<endl ;
  return 0;
}

