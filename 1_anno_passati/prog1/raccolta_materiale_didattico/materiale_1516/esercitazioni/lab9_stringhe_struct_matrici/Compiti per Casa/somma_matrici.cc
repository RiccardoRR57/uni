/* 
   Scrivere un programma che chieda all'utente di inserire il valore
   degli elementi di due matrici, in generale non quadrate, e di
   dimensioni predefinite (a tempo di scrittura del programma),
   effettui la somma di tali matrici e stampi la matrice risultante.

   L'inserimento dei valori in ciascuna delle due matrici deve essere
   effettuato mediante una funzione che prenda in ingresso la matrice
   (una sola) da inizializzare e tutte le eventuali altre informazioni
   necessarie.

   La stampa dei valori di ciascuna delle due matrici deve essere
   effettuata mediante una funzione che prenda in ingresso una (sola)
   matrice e tutte le eventuali altre informazioni necessarie.

   La somma deve essere effettuata da una funzione che prende in
   ingresso due matrici e tutte le eventuali altre informazioni
   necessarie, e mette il risultato in una terza matrice.
*/  

#include <iostream>

using namespace std ;

const int NUM_C = 2 ;

void riempi_matrice(int mat[][NUM_C], int m)
{
    for(int i=0; i<m; i++)	
	for(int j=0; j<NUM_C; j++)  {
	    cout<<"Inserisci valore di riga "<<i+1<<" colonna "<<j+1<<":\n" ;
	    cin>>mat[i][j] ;
	} 
}

void stampa_matrice(const int mat[][NUM_C], int m)
{
	for(int i=0; i<m; i++) {
	    for(int j=0; j<NUM_C; j++) 
		    cout<<mat[i][j]<<"\t" ;
	    cout<<endl ;	
	}		
} 


void somma_matrici(const int A[][NUM_C], const int B[][NUM_C], 
		   int ris[][NUM_C], int m)
{
    for(int i=0; i<m; i++)	
	for(int j=0; j<NUM_C; j++) 
	    ris[i][j]=A[i][j] + B[i][j];

}

int main()
{
    const int NUM_R = 3 ;
    int mat1[NUM_R][NUM_C], mat2[NUM_R][NUM_C], mats[NUM_R][NUM_C];
    cout<<"Caricamento matrice 1\n" ;
    riempi_matrice(mat1, NUM_R) ;
    cout<<"Caricamento matrice 2\n" ;
    riempi_matrice(mat2, NUM_R) ;
    
    /*Visualizzazione*/
    cout<<"Matrice 1:\n" ;
    stampa_matrice(mat1, NUM_R) ;
    cout<<"Matrice 2:\n" ;
    stampa_matrice(mat2, NUM_R) ;

    /*Calcolo della matrice somma*/
    somma_matrici(mat1, mat2, mats, NUM_R) ;

    /*Visualizzazione della matrice somma*/
    cout<<"Matrice somma:\n" ;
    stampa_matrice(mats, NUM_R) ;
    return 0;
}
