/*
 * Scrivere un programma che legga in ingresso un numero intero a ed un 
 * esponente intero non negativo i, e stampi il valore di a^i.
 * Se l'esponente immesso dall'utente non fosse positivo il programma stampa 
 * un messaggio d'errore ed esce
 *
 * Esempio:
 *
 * Immettere un numero intero: 3
 * Immettere un esponente non negativo: 2
 * 3 ^ 2 = 9
 *
 * Domanda: utilizzando esponenti molto grandi, possono sorgere problemi di 
 * overflow? Provare a far calcolare 5 ^ 213
 */

#include <iostream>

using namespace std ;

int main()
{
    int a, i, j, ris ;
	
    cout<<"Immettere un numero intero: " ;
    cin>>a ;

    cout<<"Immettere un esponente non negativo: " ;
    cin>>i ;
    
    if (i < 0) {
        cout<<"Esponente negativo non ammesso\n" ;
        return 1 ;
    }
    j = 1 ;
    ris = 1 ;
    while (j <= i) {
      ris *= a ;
      j++ ;
    }
        
    cout<<a<<" ^ "<<i<<" = "<<ris<<endl ;
	
    return 0 ;
}
