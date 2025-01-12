#include <iostream>

using namespace std;

int main()
{
  int i ;

  cout<<"Inserisci un numero intero diverso da 0: " ;
  cin>>i ;

  /* Invertiamo il segno */
  i = -i ;
  /* Quindi procediamo come nell'esercizio 0_se_neg_1_se_pos.c */
  /* Ci riportiamo prima ad un numero intero uguale a 0 oppure 2 */
  /* Attenzione: cosa accadrebbe se i == 0 ? */
  i = i / abs(i) + 1;
  /* Quindi, dividiamo per 2, ottendo 0 oppure 1 */
  i /= 2 ;

  cout<<i<<endl ;

  return 0 ;
}
