/*
Scrivere un programma in cui sia definita ed utilizzata una funzione
che, preso un vettore di numeri interi in ingresso, raddoppia il valore degli
elementi del vettore. La funzione non legge da stdin e non scrive su stdout.

Il vettore viene modificato dalla funzione?

C'è concreto rischio overflow se si riempie il vettore con numeri
completamente casuali?
*/

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std ;

void raddoppia(int [], int);

int main()
{  
	const int M = 10; 
	int A[M];

	// generazione del seme del generatore di numeri casuali
	srand(time(0));
	
	// inserimento dei numeri casuali nell'array e stampa
	for(int i=0 ; i<M ; i++) {
		A[i] = rand() % 1000 ; // per ridurre rischio overflow
				       // nella somma
		cout<<"Elemento "<<i<<": "<<A[i]<<endl ;
	}

	raddoppia(A,M);

	// stampa nuovo contenuto
	cout<<endl<<"Dopo il raddoppio:"<<endl ;
	for(int i=0 ; i<M ; i++) {
		cout<<"Elemento "<<i<<": "<<A[i]<<endl ;
	}

	return 0 ;
} 

void raddoppia(int vett[], int N)
{ 
	for (int i=0; i<N; i++)
	    vett[i] *= 2 ;
}
