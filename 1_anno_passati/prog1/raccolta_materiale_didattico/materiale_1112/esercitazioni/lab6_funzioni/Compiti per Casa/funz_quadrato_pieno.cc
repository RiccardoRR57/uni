/*
 * Scrivere un programma che richieda all'utente un numero intero
 * positivo non maggiore di una costante positiva a scelta, e
 * costruisca un quadrato pieno di lato pari al numero scelto e riempito col
 * carattere #. Implementare la stampa del quadrato mediante una funzione.
 * Esempio:
 *
 * Lato: 3
 * # # #
 * # # #
 * # # #
*/

#include <iostream>

using namespace std ;

void stampa_quadrato(int dim)
{
  int i, j ;

  for(i = 0; i < dim; i++) // stampa un'intera riga e va a capo
   {
     for(j = 0; j < dim; j++) // stampa i caratteri che compongono la riga
	 cout<<" #" ;
     cout<<endl ;  // vai a capo a fine riga
   }
}

int main(void)
{
  const int max = 30 ;
  int dim;

  do
  {
    cout<<"Immetti la misura del lato del quadrato (tra 1 e "<<max<<")\n" ;
    cin>>dim ;   
  } while (dim < 1 || dim > max);

  stampa_quadrato(dim) ;

  return 0;
}
