/*
  Scrivere un programma che definisca una matrice bidimensionale di
  interi di dimensioni stabilite a tempo di scrittura del programma ed
  assegni ad ogni elemento un valore letto da stdin. Infine stampi il
  contenuto della matrice.
 */

#include <iostream>
using namespace std ;

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

	return 0 ;
}
