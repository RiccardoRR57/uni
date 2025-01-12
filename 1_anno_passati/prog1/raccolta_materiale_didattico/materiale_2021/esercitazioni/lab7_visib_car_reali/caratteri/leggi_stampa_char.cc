/*
   Scrivere un programma che legga un carattere da stdin e lo stampi
   su stdout.

   Esempi:
   Immettere un carattere: r
   Hai immesso il carattere r

   Immettere un carattere: 2
   Hai immesso il carattere 2

 */

#include <iostream>

using namespace std ;

int main()
{
	char c ;
	cout<<"Immettere un carattere: " ;
	cin>>c ;
	cout<<"Hai immesso il carattere "<<c<<endl ;

	return 0;
}
