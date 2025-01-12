/* 
   Scrivere una funzione contavolte che conta quante volte un elemento
   e' presente in un vettore v di n elementi. La funzione riceve come
   parametri x, v, n. Utilizzare contavolte dentro una seconda
   funzione creaunici, per memorizzare, a partire da un vettore v1, in
   un secondo vettore v2 solo gli elementi unici di v1, cioe' presenti
   una sola volta in v1. La funzione restituisce il numero degli
   elementi in v2. 

   Esempio: 
   v1: 2 4 3 2 7 1 3 5 1 8 9 
   v2: 4 7 5 8 9

   Scrivere la funzione creaunici in maniera tale che possa lavorare
   su vettori di dimensione qualsiasi.
   
   Infine scrivere una funzione principale che definisca due vettori
   di int, ed utilizzi la funzione creaunici per memorizzare nel
   secondo vettore solo gli elementi unici di v1. La funzione stampa i
   due vettori.

*/


#include<iostream>

using namespace std ;

int creaunici(const int v1[], int v2[], int N);
int contavolte(int x, const int v[], int n);

int main()
{
    int v1[] = {2, 4, 3, 2, 7, 1, 3, 5, 1, 8, 9};
    int v2[11];

    cout<<"Array originale\n" ;
    for(int i=0; i<11; i++)
	cout<<v1[i]<<" " ;
    cout<<"\nArray unici\n" ;
    int lun = creaunici(v1, v2, 11);
    for(int i=0; i<lun; i++)
	cout<<v2[i]<<" " ;
    cout<<endl ;
    return 0;
}

int creaunici(const int v1[], int v2[], int N)
{	
    int num_elem = 0 ;

    for(int i=0; i<N; i++) 
	{
	    if(contavolte(v1[i], v1, N) == 1)
		v2[num_elem++] = v1[i] ;
	}
    return num_elem ;
}

int contavolte(int x, const int v[], int n)
{
    int volte = 0 ;

    for(int i=0; i<n; i++)
	if (v[i] == x) 
	    volte++;
    return volte;
}
		
