/*
  Scrivere un programma che legga due numeri reali da stdin, e stampi il 
  risultato della divisione reale tra i due numeri.

  Esempio:

  Inserisci due valori reali: 5.5 2
  5.5 / 2 = 2.75

*/

#include <iostream>

using namespace std ;

main()
{
	double a, b ; // equivalentemente float
	cout<<"Inserisci due valori reali: " ;
	cin>>a>>b ;
	cout<<a<<" / "<<b<<" = "<<a/b<<endl ;
}
