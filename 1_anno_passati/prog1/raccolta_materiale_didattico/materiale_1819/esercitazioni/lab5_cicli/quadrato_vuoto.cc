/*
 * Scrivere un programma che richieda all'utente di inserire un numero intero
 * positivo non maggiore di una costante positiva a scelta, e
 * costruisca un quadrato vuoto di lato pari al numero scelto e riempito col
 * carattere #
 * Esempio:
 *
 * Lato: 4
 * # # # #
 * #     #
 * #     #
 * # # # #
*/

#include <iostream>

using namespace std ;

int main(void)
{
  const int lato_max = 30 ;
  int lato;

  do
  {
    cout<<"Immetti la misura del lato del quadrato (tra 1 e "<<lato_max<<")\n";
    cin>>lato ;   
  } while (lato < 1 || lato > lato_max);

  for(int i = 0; i < lato; i++) // stampa un'intera riga e va a capo
   {
     for(int j = 0; j < lato; j++) // stampa i caratt. che compongono la riga
       if (i == 0 || i == lato - 1 || j == 0 || j == lato - 1)
	 cout<<" #" ;
       else
	 cout<<"  " ;
     cout<<endl ;  // vai a capo a fine riga
   }
  return 0;
}
