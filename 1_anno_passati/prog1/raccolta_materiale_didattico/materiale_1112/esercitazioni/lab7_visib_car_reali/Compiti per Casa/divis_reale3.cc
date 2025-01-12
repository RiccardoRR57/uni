/*
  Scrivere un programma che legga due numeri INTERI, e stampi il
  risutato della divisione REALE tra i due numeri.  Non utilizzare la
  conversione esplicita per realizzare il programma.

  Esempio:

  Inserisci due valori interi: 5 2
  5 / 2 = 2.5

*/

#include <iostream>

using namespace std ;

main()
{
	int a, b ;
	cout<<"Inserisci due valori interi: " ;
	cin>>a>>b ;
	double c = b ;
	cout<<a<<" / "<<b<<" = "<<a/c<<endl ;
}
