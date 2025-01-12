/*
 * Scrivere un programma che legge in ingresso un numero intero non
 * negativo a, e stampa sullo schermo tutti i numeri primi compresi
 * tra 0 ed a.  Realizzare il programma definendo ed utilizzando
 * almeno le due funzioni seguenti.
 *
 * Una funzione che, dato un numero intero passato come parametro,
 * ritona true se il numero è primo, false altrimenti.
 *
 * Una funzione che, dato un numero intero n passato come parametro,
 * ritorna il il più piccolo numero primo maggiore o uguale di n.  La
 * seconda funzione DEVE utilizzare la prima.
 *
 * Se ci si riesce, realizzare il programma invocando solo la seconda
 * funzione dal main, e prima di definirla.
 */ 

#include <iostream>
#include <cmath>

using namespace std ; 

bool primo(int);
int prossimo_primo(int) ;

int main() 
{
  int i, j = 2 ;
  
  do {
      cout<<"Immetti un numero intero maggiore di 0:"<<endl ;
      cin>>i ; 
  } while (i <= 0) ;

  cout<<1<<endl ;

  if (i >= 2) {
      cout<<2<<endl ;
      j++ ;
  }
  for (; ;
       j += 2 // il numero primo ritornato da prossimo_primo nel corpo
	      // del ciclo è stato sicuramente dispari
       ) {
    j = prossimo_primo(j) ;
    if (j > i)
	break ;
    cout<<j<<endl ;
  } 
  return 0 ;
} 

/* Ritorna true se il numero n è primo, false altrimenti */
bool primo(int n)
{
   if (n>=1 && n<=3) return true;      /* 1,2,3 -> sì */
   if (n%2==0) return false;           /* no perché numero pari */
   int max_div = static_cast<int>(sqrt(n));
   for(int i=3; i<=max_div; i=i+2)			
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
    ; // ISTRUZIONE VUOTA
  return i ;
}
