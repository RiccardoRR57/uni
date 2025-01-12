#include <iostream>

using namespace std;

int main()
{
  int i, j ;

  cout<<"Inserisci il primo numero intero positivo: " ;
  cin>>i ;
  cout<<"Inserisci il secondo numero intero positivo: " ;
  cin>>j ;
  
  /* Possibile soluzione:
   * Calcolo il resto della divisione intera,sarà un numero compreso tra
   * 0 e j -1
   */
  int passo1 = i % j ;
  /* Sommo j - 1, ottenendo un numero compreso tra j - 1 e 2 * (j -1) */
  int passo2 = passo1 + (j - 1) ;
  /* Tale numero è minore di 2 * j. Lo divido per j,
   * ottenendo un numero compreso tra 0 ed 1.
   */
  int passo3 = passo2 / j ;
   /* Se passo1 == j - 1 (il che accade se e solo se i è multiplo di j), 
    * allora passo3 == 0, altrimenti passo3 == 1
    */

  // trasformo lo zero in 1 e viceversa
  passo3 = passo3 * (-1);
  passo3 = passo3 + 1;

  cout<<passo3<<endl ;

  return 0 ;
}
