/*
 * Scrivere un programma che legga in ingresso una sequenza di tre numeri
 * interi e, se la sequenza � ordinata in senso crescente oppure decrescente,
 * comunica che la sequenza � ordinata. Altrimenti comunica che la sequenza non
 * � ordinata. Due esempi di esecuzione sono:
 *
 *   Inserisisci una sequenza di tre numeri: 3 6 8
 *   La sequenza � ordinata
 * 
 *   Inserisci una sequenza di tre numeri: 3 2 9
 *   La sequenza non � ordinata
 */

#include <iostream>
using namespace std;

int main()
{
  int a, b, c ;

  cout<<"Inserisisci una sequenza di tre numeri: " ;
  cin>>a>>b>>c ;
  if ((a < b && b < c) || (a > b && b > c))
	  cout<<"La sequenza � ordinata\n" ;
  else
          cout<<"La sequenza non � ordinata\n" ;
  return 0 ;
}
