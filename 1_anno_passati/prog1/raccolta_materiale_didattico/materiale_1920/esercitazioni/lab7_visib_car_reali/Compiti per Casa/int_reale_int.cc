/*
  Scrivere un programma che legga un numero intero e lo memorizzi in
  una variabile di tipo int, poi assegni il valore di tale variabile
  ad una variabile di tipo float (non double), infine assegni il
  valore della seconda variabile ad una terza varibile di tipo
  int. Infine stampi il valore di tutte e tre le variabili.  Usare
  conversioni esplicite per evitare warning.

  Scritto il programma, provare ad inserire ad esempio il numero
  214748364.  Viene segnalato qualche errore a tempo di esecuzione?
*/

#include <iostream>

using namespace std ;

int main()
{
	int a ;
	cout<<"Inserisci un valore intero: " ;
	cin>>a ;
	float b = static_cast<float>(a) ;
	int c = static_cast<int>(b) ;
	cout<<"prima intera == "<<a<<", reale == "<<b
	    <<", seconda intera == "<<c<<endl ;
	return 0 ;
}
