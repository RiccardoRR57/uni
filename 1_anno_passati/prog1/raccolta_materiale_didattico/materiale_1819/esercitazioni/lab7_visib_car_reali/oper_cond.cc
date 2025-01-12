/*
 Senza utilizzare nè l'istruzione if nè l'istruzione switch nè le
 istruzioni cicliche, scrivere un programma che legge un numero intero
 da stdin e lo memorizza in una variabile n. Se il numero letto è
 minore di 0, nel programma si assegna forzatamente il valore 0 ad
 n. Infine si stampa il valore di n.
*/

#include <iostream>

using namespace std ;


main()
{
	int n ;
	cin>>n ;

	//n < 0 ? n=0 : 0 ;
	n = n >= 0 ? n : 0 ;
	cout<<n<<endl ;
}
