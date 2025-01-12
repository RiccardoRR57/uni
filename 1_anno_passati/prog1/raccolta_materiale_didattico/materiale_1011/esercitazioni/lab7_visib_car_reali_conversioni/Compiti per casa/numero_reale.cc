/*
Scrivere un programma che legga da tastiera un numero reale e
lo ristampi in formato mantissa*10^esponente. La mantissa deve essere un
numero reale minore di 1.

Possibili output:

Inserisci un numero: 35
0.35*10^2

Inserisci un numero: 2
0.2*10

Inserisci un numero reale: -123
-0.123*10^3

Inserisci un numero: 0.5
0.5

(va bene anche il formato 0.123e3)

*/

#include <iostream>

using namespace std ;

int main()
{
    int i;
    double d;

    cout<<"Inserisci un numero reale: " ;
    cin>>d ;
    if (d<0) {
        d *= -1 ;
        cout<<"-" ;
    }
    for (i = 0 ; d >= 1 ; i++)
        d /= 10 ;

    cout<<d ;
    if (i>0)
       cout<<"*10" ;
    if (i>1)
       cout<<"^"<<i ;
    cout<<endl ;

    return 0;
}
