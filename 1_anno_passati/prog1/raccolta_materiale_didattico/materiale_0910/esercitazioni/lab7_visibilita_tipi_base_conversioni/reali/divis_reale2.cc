/*
  Scrivere un programma che legga due numeri INTERI, e stampi il
  risultato della divisione REALE tra i due numeri.  Assumere che non
  si possa avere una espressione di tipo intero come rvalue in un
  assegnamento in cui a sinistra (lvalue) si ha una variabile di tipo
  reale.

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
	cout<<a<<" / "<<b<<" = "<<static_cast<double>(a)/b<<endl ;
}
