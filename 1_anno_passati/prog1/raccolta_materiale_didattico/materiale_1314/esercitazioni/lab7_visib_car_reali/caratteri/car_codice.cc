/*
Scrivere un programma che chieda all'utente di inserire un carattere
e stampi a schermo il codice ASCII del carattere inserito

Assumere che in un assegnamento in cui si ha come lvalue (ossia a
sinistra dell'assegnamento) l'indirizzo di una variabile di tipo int,
NON SI POSSA avere come rvalue (ossia a destra dell'assegnamento) un
valore di tipo char.

Un possibile output sullo schermo e' il seguente:
Inserisci un carattere: M
Il codice corrispondente e': 77
*/

#include <iostream>

using namespace std ;

int main()
{
	char carattere;

	cout<<"Inserisci un carattere " ;
	cin>>carattere ;
	int i = static_cast<int>(carattere) ; // converto prima di assegnare
	cout<<"Il codice ASCII del carattere e' "<<i<<endl ;

	return 0 ;
}
