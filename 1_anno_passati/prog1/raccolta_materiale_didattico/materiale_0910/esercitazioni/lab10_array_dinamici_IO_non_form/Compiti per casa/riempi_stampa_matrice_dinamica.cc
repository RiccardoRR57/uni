/*
  Scrivere un programma che definisca una matrice dinamica di interi
  di dimensioni lette da stdin a tempo di esecuzione e la inizializzi
  con valori letti anch'essi da stdin. Infine stampi il contenuto
  della matrice.
 */

#include <iostream>
using namespace std ;

int main()
{
	const int N = 2 ;

	int M ;
	
	do { // immissione righe matrice
		cout<<"Numero di righe? " ;
		cin>>M ;
	} while (M < 0) ;
	
	int (*mat)[N] = new int[M][N] ;

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

	delete[] mat ;

	return 0 ;
}
