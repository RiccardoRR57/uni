/*
Scrivere un programma che crei dinamicamente un array di int, di
dimensioni inserite dall'utente da tastiera, e che lo riempia con
valori anch'essi inseriti dall'utente. Quindi il programma stampa il
contenuto dell'array.

A questo punto, il programma conserva in memoria SOLO una parte degli
elementi iniziali dell'array. In particolare chiede all'utente di
inserire un numero naturale n non maggiore delle dimensioni dell'array
e conserva in memoria solo i primi n elementi dell'array.  Quindi
stampa il sotto-array conservato in memoria, lo dealloca e termina.

Esempio:

Dimensioni array? 4
Valore elemento 0/4? 3
Valore elemento 1/4? 2
Valore elemento 2/4? 1
Valore elemento 3/4? 2

Valore elemento 0/4: 3
Valore elemento 1/4: 2
Valore elemento 2/4: 1
Valore elemento 3/4: 2
Numero di elementi da preservare? 2

Sotto-array:
Valore elemento 0/2: 3
Valore elemento 1/2: 2

*/

#include <iostream>

using namespace std ;

int main()
{
    int *p ; // attenzione, per ora contiene un valore casuale !!!
    int dim = -1 ;

    do { // immissione dimensioni array
	cout<<"Dimensioni array? " ;
	cin>>dim ;
    } while (dim <= 0) ;

    p = new int[dim] ; /*
			* allocazione memoria sarebbe stato meglio
			* definire la variabile p all'atto
			* dell'allocazione della memoria, in modo da
			* poterla utilizzare solo dopo averla allocata
			*/

    for (int i = 0 ; i < dim ; i++) { // memorizzazione valori
	int val ;

	cout<<"Valore elemento "<<i<<"/"<<dim<<"? " ;
	cin>>val ;
	p[i] = val ;
    }
    
    cout<<endl ;
    for (int i = 0 ; i < dim ; i++) // stampa array
	cout<<"Valore elemento "<<i<<"/"<<dim<<": "<<p[i]<<endl ;

    do { // immissione dimensioni sotto-array
	cout<<"Numero di elementi da preservare? " ;
	cin>>dim ;
    } while (dim <= 0) ;
    
    int * p2 = new int[dim] ;

    for (int i = 0 ; i < dim ; i++) { // copia valori
	    p2[i] = p[i] ;
    }

    delete[] p ; // deallocazione memoria vecchio array

    cout<<"\nSotto-array:"<<endl ;
    for (int i = 0 ; i < dim ; i++) // stampa sotto-array
		cout<<"Valore elemento "<<i<<"/"<<dim<<": "<<p2[i]<<endl ;

    delete [] p2 ;
    return 0 ;
}
