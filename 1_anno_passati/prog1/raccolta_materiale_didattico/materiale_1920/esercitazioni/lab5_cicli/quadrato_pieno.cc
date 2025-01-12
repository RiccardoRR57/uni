/*
 * Scrivere un programma che richieda all'utente di inserire un numero intero
 * positivo non maggiore di una costante positiva a scelta, e
 * costruisca un quadrato pieno di lato pari al numero scelto e riempito col
 * carattere #
 * Esempio:
 *
 * Lato: 3
 * # # #
 * # # #
 * # # #
 *
 * Se avete difficolta', partite dallo stampare solo una riga.
*/

#include <iostream>

using namespace std ;

int main()
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
     for(int j = 0; j < lato; j++) // stampa i carat. che compongono la riga
		cout<<" #" ;
     cout<<endl ;  // vai a capo a fine riga
   }
  return 0;
}
