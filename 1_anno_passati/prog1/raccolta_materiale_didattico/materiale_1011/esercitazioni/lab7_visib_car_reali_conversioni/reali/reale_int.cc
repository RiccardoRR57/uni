/*
  Scrivere un programma che legga in ingresso un numero reale e lo
  memorizzi in una variabile reale, quindi assegni il valore di tale
  variabile ad una variabile di tipo int, infine stampi il valore di
  entrambe le variabili.  

  Assumere che in un assegnamento in cui si ha come lvalue (ossia a
  sinistra dell'assegnamento) l'indirizzo di una variabile di tipo
  int, NON SI POSSA avere come rvalue (ossia a destra
  dell'assegnamento) un valore di tipo reale.
*/

#include <iostream>

using namespace std ;

main()
{
	double a ;
	cout<<"Inserisci un valore reale: " ;
	cin>>a ;
	int b = static_cast<int>(a) ; // converto prima di assegnare
	cout<<"reale == "<<a<<", intero == "<<b<<endl ;
}
