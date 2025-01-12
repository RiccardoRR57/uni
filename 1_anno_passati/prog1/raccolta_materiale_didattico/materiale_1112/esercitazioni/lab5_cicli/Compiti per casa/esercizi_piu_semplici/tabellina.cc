/* 
 * Stampare su video i primi n multipli di un numero i, entrambi
 * letti da tastiera.
 *
 * Esempio:
 *
 * Inserire i ed n: 4 5
 *  4    *       1          =      4
 *  4    *       2          =      8
 *  4    *       3          =      12
 *  4    *       4          =      16
 *  4    *       5          =      20
 *
*/


#include <iostream>

using namespace std ;

main()
{
  int i, n;
  
  cout<<"\nInserire i ed n: " ;
  cin>>i>>n ;

  for (int j = 1; j <= n; j++)
     cout<<"\t"<<i<<"\t\t*\t"<<j<<"\t\t=\t\t"<<i*j<<endl ;
}

