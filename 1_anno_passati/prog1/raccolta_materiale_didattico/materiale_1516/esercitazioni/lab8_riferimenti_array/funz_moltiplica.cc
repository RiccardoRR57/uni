/*
Scrivere una funzione moltiplica, con due parametri formali, che
prenda in ingresso (parametro formale) per riferimento un oggetto di
tipo intero, e ne moltiplichi il valore per il valore del secondo
parametro formale. Il tipo di ritorno della funzione deve essere void
e la funzione non deve stampare nulla.
*/

#include <iostream>
using namespace std ;

void moltiplica(int &a, int n)
{
	a *= n ;
}

int main()
{
	int b, n ;
	cin>>b>>n ;
	moltiplica(b, n) ;
	cout<<b<<endl ;
	return 0 ;
}
