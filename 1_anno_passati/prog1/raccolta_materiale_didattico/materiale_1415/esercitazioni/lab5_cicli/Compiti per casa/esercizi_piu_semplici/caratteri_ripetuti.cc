/* 
 * Scrivere un programma che legga da stdin un numero intero n, e poi stampi 
 * sullo schermo n asterischi
 * Esempio:
 *
 * Inserire un numero intero: 5
 * *****
 *
 */


#include <iostream>
using namespace std;

main()
{
  int i, n ;

  cout<<"\nInserire un numero intero: " ;

  cin>>n ;

  i = 1 ;
  while (i <= n ) {
	  cout<<"*" ;
	  i++ ;
  }
  cout<<endl ;

}


