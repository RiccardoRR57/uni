/*
Realizzare un programma che legge in ingresso un intero e, se il
valore inserito appartiene all'insieme dei codici ASCII dei caratteri
stampabili, stampa il carattere corrispondente. Altrimenti stampa un
messaggio di errore.  Scrivere il programma supponendo di non
conoscere il codice ASCII dei caratteri, ma di sapere solo che i
codici dei caratteri stampabili appartengono all'intervallo che va dal
codice del carattere ' ' (spazio) al codice del carattere
'~'. Ovviamente non conosciamo neanche il codice dei due estremi,
ossia dei caratteri ' ' e '~'.

Scrivere il programma utilizzando una variabile di tipo int per
memorizzare il codice. Per gestire il caso in cui si stampi
effettivamente il carattere, realizzare la stampa assegnando tale
codice ad una seconda variabile di tipo char e stampando tale
variabile.

Assumere che in un assegnamento in cui si ha come lvalue (ossia a
sinistra dell'assegnamento) l'indirizzo di una variabile di tipo char,
NON SI POSSA avere come rvalue (ossia a destra dell'assegnamento) un
valore di tipo int.

Un possibile output sullo schermo e' il seguente:
Inserisci il codice ASCII di un carattere: 77
Il carattere corrispondente e':	M
*/

#include <iostream>

using namespace std ;

int main()
{
	int codice;
	char carattere;

	cout<<"Inserisci un codice ASCII " ;
	cin>>codice ;
	if (codice >= ' ' && codice <= '~') {
	    carattere = static_cast<char>(codice); // conversione
						   // prima
						   // dell'assegnamento
            cout<<"Il carattere corrispondente e' "<<carattere<<endl ;
	} else
            cout<<"Hai inserito il codice di un carattere non stampabile\n" ;

	return 0 ;
}
