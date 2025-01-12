/* 
 * Attenzione: richiede cicli nidificati
 *
 * Stampare su video la tavola pitagorica di ordine n (n dato da 
 * tastiera).
 *
*/


#include <iostream>

using namespace std ;

main()
{
  int i, j, n;
  
  cout<<"\nInserire l'ordine della tavola pitagorica: " ;
  cin>>n ;

  for (i=1; i<=n; i++)
  {
   for (j=1; j<=n; j++) 
     cout<<""<<i*j<<"\t\t" ;
   cout<<endl ;
  }

}

