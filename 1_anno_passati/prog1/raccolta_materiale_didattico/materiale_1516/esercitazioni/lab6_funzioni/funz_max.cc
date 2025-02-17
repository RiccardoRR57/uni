/*
Scrivere un programma che stampi il massimo tra due numeri interi letti da 
stdin. Implementare il calcolo (e non la stampa) del massimo mediante una 
funzione. Implementare la lettura dei valori e la stampa del valore massimo
all'interno della funzione main

Esempio:
	Inserire i due numeri interi: 21 -3
	Il massimo tra 21 e -3 � 21
*/

#include <iostream>

using namespace std ;

int massimo(int a, int b)
{
	if (a > b)
		return a ; // ramo else inutile in termini di
			   // correttezza
	return b ;
}

int main()
{
	int a, b ; // hanno lo stesso nome dei parametri formali
			   // della funzione, necessario?
	cout<<"Inserisci due numeri interi: " ;
	cin>>a>>b ;
	cout<<"Il massimo tra "<<a<<" e "<<b<<" e' "
		<<massimo(a,b)<<endl ;
	return 0 ;
}
