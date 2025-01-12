/*
 * Scrivere un programma che legge in ingresso un numeri intero non
 * negativo a, e stampa sullo schermo tutti i numeri primi compresi
 * tra 0 ed a.  Realizzare il programma definendo ed utilizzando
 * almeno le due funzioni seguenti.  Una funzione che, dato un numero
 * intero passato come parametro, ritona true se il numero è primo,
 * false altrimenti.  Una funzione che, dato un numero intero n
 * passato come parametro, ritorna il il più piccolo numero primo
 * maggiore o uguale di n.  La seconda funzione DEVE utilizzare la
 * prima.  Per quanto sia possibile realizzare il programma invocando
 * solo la prima delle due funzioni nel main, per esercizio, nel main
 * DOVETE utilizzare solo la seconda funzione, e prima di definirla.
 */ 

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
