/*
 * Chiamiamo gemelli due numeri primi p1 e p2 tlai che p1 == p2 + 2,
 * ossia c'è un solo numero a separare p1 e p2.
 *
 * Scrivere un programma che legge in ingresso due numeri interi non
 * negativi a e b, e stampa sullo schermo tutti i numeri primi gemelli
 * compresi tra a e b.  
 *
 */ 

#include <iostream>
#include <cmath>

using namespace std ; 

bool primo(int);
int prossimo_primo(int) ;

int main() 
{
  int minimo, massimo ;
  
  do {
      cout<<"Immetti un numero intero maggiore di 0:"<<endl ;
      cin>>minimo ; 
  } while (minimo <= 0) ;

  do {
      cout<<"Immetti un numero intero maggiore di "<<minimo<<":"<<endl ;
      cin>>massimo ; 
  } while (massimo <= minimo) ;

  for (int prossimo = minimo ;
       ;
       prossimo += 2 // il numero primo ritornato da prossimo_primo
		     // nel corpo del ciclo è stato sicuramente dispari
       ) 
  {
    prossimo = prossimo_primo(prossimo) ;
    if (prossimo > massimo)
      break ;
    int possibile_gemello = prossimo_primo(prossimo + 2) ;
    if (possibile_gemello == prossimo + 2)
	cout<<prossimo<<" "<<possibile_gemello<<endl ;
  } 
  return 0 ;
} 

/* Ritorna true se il numero n è primo, false altrimenti */
bool primo(int n)
{
   int max_div, i;
   if (n>=1 && n<=3) return(1);     /* 1,2,3 -> sì */
   if (n%2==0) return false;           /* no perché numero pari */
   max_div = (int) sqrt(n);		
   for(i=3; i<=max_div; i=i+2)			
     if (n%i==0) return false;         /* no perché è stato trovato
				       un divisore */
  return true;
} 

/* Ritorna il più piccolo numero primo maggiore o uguale di n */
int prossimo_primo(int n)
{
  int i ;

  if (n % 2 == 0) // n è pari
    n++ ;    // salto subito al numero successivo
  for (i = n ; !primo(i) ; i += 2) 
    ; // ISTRUZIONE VUOTA: ATTENZIONE !!!
  return i ;
}
