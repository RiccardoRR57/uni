/*
 * Scrivere un programma che richieda all'utente un numero intero
 * positivo non maggiore di una costante positiva a scelta, e
 * costruisca un quadrato pieno di lato pari al numero scelto e riempito col
 * carattere #. Utilizzare un unico ciclo non nidificato
 * Esempio:
 *
 * Lato: 3
 * # # #
 * # # #
 * # # #
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

  for(int i = 0; i < lato * lato ; i++) // stampa una riga e va a capo
   {
     cout<<" #" ;
     if ((i + 1) % lato == 0)
       cout<<endl ;  // vai a capo a fine riga
   }
  return 0;
}
