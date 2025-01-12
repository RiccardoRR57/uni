/*

Data una matrice quadrata A di dimensione M (M righe ed M colonne)
(sia aij l'elemento individuato dalla riga i-esima e dalla colonna
j-esima), si dice trasposta di A una matrice quadrata B di dimensione
M (sia bnm l'elemento individuato dalla riga ennesima e dalla colonna
emmesima), tale che aij == bji ove 1 <= i <= M e 1 <= j <= M.  In
sostanza la trasposta fa corrispondere alla prima riga di A, la prima
colonna di B, alla seconda riga di A la seconda colonna di B e cosi'
via.  (Gli indici dei coefficienti utilizzati nella definizione sono
ovviamente quelli 'matematici': considerando, ad esempio, la prima
riga, il primo elemento ha indice 1 e l'ultimo ha indice N).  Ad
esempio, data la matrice

1 4 2
3 6 7
8 2 5

la trasposta e'

1 3 8 
4 6 2 
2 7 5 

Scrivere un programma che, data una matrice (quadrata) di interi, la
stampa, ne calcola la trasposta e stampa la nuova matrice cosi' ottenuta.
La matrice di partenza va definita a tempo di scrittura del programma.
Sia il calcolo della trasposta che la stampa devono essere implementate, 
rispettivamente, in due funzioni dedicate. 

*/

#include <iostream>

using namespace std ;

const int dim = 3 ;  // dimensioni della matrice quadrata

// calcolo della matrice trasposta: algoritmo iterativo
void trasposta(int m[][dim])
{
    /*
     * Quando i == 0, scorro la prima riga e ne scambio gli elementi
     * con quelli della prima colonna. Quando i>1, lavoro sulla
     * sottomatrice che parte dalla colonna e dalla riga di indice i,
     * e di nuovo scambio riga e colonna. Notare che lavoro sull'array
     * contenitore (quadrato) che contiene la matrice, ottenendo
     * implicitamente lo scambio riga/colonna della matrice contenuta.
     * Nel ciclo piu' interno parto da j=i+1 perche' sarebbe inutile
     * scambiare il primo elemento della (sottomatrice) con se stesso
     */
    for (int i = 0 ; i < dim ; i++)
        for (int j = i + 1 ; j < dim ; j++) {
	    /*
	     * Si può realizzare lo scambio con o senza variabile 
	     * ausiliaria. La versione con var. ausiliaria sarebbe stata:
	     * int tmp = a ;
	     * a = b ;
	     * b = tmp ;
	     */
	    
	    /*
	     * Versione senza variabile ausiliaria
	     * si sfruttano le proprieta' 'numeriche' del tipo intero
	     * Supponiamo che, all'inizio, a == x e b == y
	     */
	    m[i][j] -= m[j][i] ; // a == x - y
	    m[j][i] += m[i][j] ; // b == x
	    m[i][j] = -(m[i][j]-m[j][i]) ; // a == -(x-y-x) == -(-y) == y
	}
}


/* 
La seguente funzione è un pò più generale: può stampare anche matrici
non quadrate
*/
void stampa_matrice(int m[][dim], int r) {
    int i, j ;
    cout<<endl ; 
    for (i = 0 ; i < r ; i++) { 
	for (j = 0 ; j < dim ; j++) 
	    cout<<m[i][j]<<"\t" ; 
	cout<<endl ; 
    } 
    cout<<endl ; 
}

int main()
{

    int m[dim][dim] = { {1, 2, 8},
                    {4, 5, 3},
                    {7, 8, 4},
                    };

    cout<<"Matrice iniziale:\n" ;
    stampa_matrice(m, dim) ; // stampa della matrice originaria
    trasposta(m) ; // calcolo della matrice trasposta
    cout<<"Dopo la prima trasposizione:\n" ;
    stampa_matrice(m, dim) ; // stampa della matrice trasposta
    // con una nuova trasposizione riottengo la matrice originaria
    cout<<"Dopo una nuova trasposizione:\n" ;
    trasposta(m) ; // calcolo della trasposta con funzione ricorsiva
    stampa_matrice(m, dim) ; // stampa della matrice originaria

}

