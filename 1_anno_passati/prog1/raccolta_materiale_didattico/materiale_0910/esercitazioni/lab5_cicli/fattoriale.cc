/* 
   Calcolare il fattoriale di un numero intero immesso da un utente
   Il fattoriale di un numero N è calcolabile come:
   N *(N-1)*(N-2)*...*2*1
   inoltre, per definizione:
   1!=1 
   0!=1

   Trascurare problemi di overflow
*/

#include <iostream>

using namespace std ;

int main()
{
 int n; // Numero immesso dall'utente
 int fat;
 
 // Immissione del numero di cui si vuole calcolare il fattoriale
 cout<<"Immetti un numero intero diverso da 0 \n" ;
 cin>>n ;

 // Controllo del numero di cui si vuole calcolare il fattoriale
 while (n==0)
 {
  cout<<"Il numero immesso deve essere diverso da 0.\n" ;  
  cout<<"Immetti un nuovo numero intero diverso da 0 \n" ;
  cin>>n ;
 }
 
 // Inizializzazione della variabile fat
 fat = n;
 
 // Ciclo for() per il calcolo del fattoriale
 for (int m = n - 1 ; m >= 1; m--)
   fat *= m ;
 
 // Stampa del risultato 
 cout<<"Il fattoriale del numero "<<n<<": è "<<fat<<endl ;
 return 0;
}
