/*
Scrivere un programma che stampi il massimo tra due numeri interi letti dallo 
stdin. Implementare il calcolo (e non la stampa) del massimo mediante una 
funzione. Implementare la lettura dei valori e la stampa del valore massimo
all'interno del main

Esempio:
	Inserire i due numeri interi: 21 -3
	Il massimo tra 21 e -3 è 21
*/

#include <iostream>

using namespace std ;

int massimo(int a, int b)
{
	if (a > b)
		return a ;
	return b ;
}

int main()
{
	int a, b ;
	cout<<"Inserisci due numeri interi: " ;
	cin>>a>>b ;
	cout<<"Il massimo tra "<<a<<" e "<<b<<" e' "<<massimo(a,b)<<endl ;
	return 0 ;
}
