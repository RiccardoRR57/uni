/*
   Scrivere un programma che legga un carattere da stdin, ne
   incrementi il valore di 1 e lo stampi su stdout.

   Esempi:
   Immettere un carattere: r
   Dopo l'incremento: s

   Immettere un carattere: 2
   Dopo l'incremento: 3

 */

#include <iostream>

using namespace std ;

main()
{
	char c ;
	cout<<"Immettere un carattere: " ;
	cin>>c ;
	cout<<"Dopo l'incremento: "<<++c<<endl ;
}
