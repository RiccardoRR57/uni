/* Esercizio. Scrivere la funzione:

int quadratomagico(int q[][N]);

che verifica se una matrice quadrata di interi di ordine N e' un
quadrato magico, ovvero se la somma degli elementi di ogni riga, di
ogni colonna e delle diagonali è identica.

La funzione ritorna "1" se la matrice è un quadrato magico, "0" altrimenti.

Esempio di quadrato magico 3x3:
 2 9 4
 7 5 3
 6 1 8


scrivere anche un semplice main() che:
a) definisce una matrice NxN;
b) richiede l'immissione da tastiera degli elementi della matrice;
c) richiama la funzione, passandole come parametro la matrice;
d) stampa il risultato della computazione.

*/


#include <iostream>

using namespace std ;

const int N = 3;

bool quadratomagico(int q[][N]) {
    int somma = 0;
    
    // Inizializzazione di somma
    
    for (int j=0; j<N; j++)
	somma += q[0][j];
    
    // Verifica righe
    
    for (int i=1; i<N; i++) 
	{
	    int s = 0;
	    for (int j=0; j<N; j++)	
		    s += q[i][j];
	    if (s != somma)	return 0;
	}
    
    // Verifica colonne
    
    for (int j=0; j<N; j++)
	{
	    int s = 0;
	    for (int i=0; i<N; i++) 
		s += q[i][j];
	    if (s != somma)	
		return false ;
	}
    
    // Verifica diagonale principale
    
    int s = 0;
    for (int i=0; i<N; i++) 
	s += q[i][i];
    if (s != somma)	
	    return false ;
    
    //Verifica diagonale secondaria
    
    s = 0;
    for (int i=0; i<N; i++) s += q[i][N-1-i];
    if (s != somma)
	return false ;
    
    return true ;
}

void stampa (int mat[][N])
{
    for (int i=0; i<N; i++)
    {
	cout<<endl ;
	for (int j=0; j<N; j++) 
	    cout<<mat[i][j]<<"\t" ;
    }
    cout<<endl ;
}


main() {
    int m[N][N] ;
    
    cout<< "Inizializzazione del quadrato "<<N<<"x"<<N<<":\n" ;
    
    for (int i=0; i<N; i++)
	for (int j=0; j<N; j++) 
	    cin>>m[i][j] ;
    
    cout<< "\nIl quadrato:"<<endl ;
    stampa(m);
    cout<<(quadratomagico(m) ? "\n" : "\nnon ")<<"e' un quadrato magico."<<endl ;
}





