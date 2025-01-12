/*
  Scrivere un programma che definisca una matrice bidimensionale di interi di
  dimensioni stabilite a tempo di scrittura del programma e la
  inizializzi con valori letti da stdin. Successivamente stampi la
  matrice.  Infine calcoli e stampi il valore della somma degli
  elementi di ciascuna riga.

  La somma degli elementi di ciascuna riga va effettuata mediante una
  funzione che prende in ingresso un array di interi e ritorna il
  valore della somma degli elementi. La funzione non legge nulla da
  stdin e non scrive nulla su stdout.
*/

#include <iostream>
using namespace std ;

int calcola_somma(const int a[], int n)
{
	int somma = 0 ;
	for (int i = 0 ; i < n ; i++)
		somma += a[i] ;
	return somma ;
}

int main()
{
	const int M = 3, N = 2 ;
	int mat[M][N] ;

	cout<<"Inserire i "<<M*N<<" elementi della matrice:"<<endl ;
	for (int i = 0 ; i < M ; i++)
		for (int j = 0 ; j < N ; j++)
			cin>>mat[i][j] ;

	cout<<"Contenuto della matrice: "<<endl ;
	for (int i = 0 ; i < M ; i++) {
		for (int j = 0 ; j < N ; j++)
			cout<<mat[i][j]<<"\t" ;
		cout<<endl ;
	}
	
	cout<<endl ;
	for (int i = 0 ; i < M ; i++)
		cout<<calcola_somma(mat[i], N)<<endl ;

	return 0 ;
}
