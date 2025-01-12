/*
Scrivere un programma in cui sia definita ed utilizzata una funzione
che, preso un vettore di numeri interi in ingresso, ne calcola la
somma degli elementi. La funzione non legge da stdin e non scrive su stdout.

Il vettore viene modificato dalla funzione?

C'è concreto rischio overflow se si riempie il vettore con numeri
completamente casuali?
*/

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std ;

int somma(const int [], int );

main()
{  
	const int M = 10;  
	int ris, A[M];

	// generazione del seme del generatore di numeri casuali
	srand(time(0));
	
	// inserimento dei numeri casuali nell'array e stampa
	for(int i=0 ; i<M ; i++) {
		A[i] = rand() / 1000 ; // per ridurre rischio overflow
				     // nella somma
		cout<<"Elemento "<<i<<": "<<A[i]<<endl ;
	}

	ris = somma(A,M);
	cout<<"Somma elementi = "<<ris<<endl ;
} 

int somma(const int vett[], int N)
{ 
	int acc=0;
	for (int i=0; i<N; i++)
	    acc += vett[i]; // per semplicità trascuriamo problemi di overflow
	return acc;   
}
