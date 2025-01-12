/*
Scrivere un programma che, dato un vettore di 10 numeri interi
(inizializzato a tempo di scrittura del programma),
. lo stampa a schermo
. stampa il valore massimo
. stampa il valore minimo
. lo ordina in senso crescente e lo stampa a schermo
. lo ordina in senso decrescente e lo stampa a schermo
*/

#include <iostream>

using namespace std ;

int main()
{
    int i ;
    int min, max ;
    int valori[10] = { 1, 6, 3, 10, 4, 246, 12, 32, 32, 5 } ;
    
    for (i = 0 ; i < 10 ; i++) 
        cout<<valori[i]<<" " ;
    cout<<endl ;
    
    min = max = valori[0] ;
    for (i = 1 ; i < 10 ; i++) {
      min = valori[i] < min ? valori[i] : min ;
      max = valori[i] > max ? valori[i] : max ;
    }
    cout<<"Valore minimo: "<<min<<endl ;
    cout<<"Valore massimo: "<<max<<endl ;
	
    /* 
     * per l'ordinamento dell'array, vi rimando al codice descritto
     * a lezione
     */
    return 0 ;
}    

