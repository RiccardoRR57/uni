/* Scrivere un programma che, dato un numero intero, lo fattorizza
 * come prodotto di numeri primi, o comunica esplicitamente che il
 * numero e' primo.
 *
 * Esempi:
 *
 * Inserisci un numero: 23
 * 23 e' un numero primo
 *
 * Inserisci un numero: 24
 * 24 = 2*2*2*3
 */

#include <iostream>

using namespace std ;

int main()
{
    int i, numero, lavoro;

    
    cout<<"Inserisci un numero: " ;
    cin>>numero ;
    if (numero < 0) {
	    cout<<"Attenzione: numero negativo!"<<endl;
	    return 1;
    }
	    
    lavoro = numero ;
    cout<<numero ;
    
    for (i = 2 ; i < numero ; )
        if (lavoro % i == 0) {
                if (lavoro != numero)
                    cout<<"*" ;
                else
                    cout<<" = " ;
                cout<<i ;
                lavoro /= i ;
        }
        else 
                i++ ;
        
    if (lavoro == numero)
        cout<<" e' un numero primo" ;
    cout<<endl ;
    
    return 0;
}
