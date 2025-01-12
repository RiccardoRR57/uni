/* Esercizio
Scrivere un programma che calcoli le radici reali di equazioni di secondo 
grado.
In particolare il programma legge da tastiera quante equazioni
si vuole risolvere, e, per ognuna, legge i tre coefficienti e stampa il 
risultato.

inoltre, per ciascuna equazione, il programma segnala esplicitamente
se l'equazione è degenere, se ha una sola radice, se ha due radici
(eventualmente coincidenti) e se non ne ha.
*/

#include <iostream>
#include <cmath>

using namespace std ;

main() {
  int n;
  
  cout<<"\nQuante equazioni vuoi risolvere? " ;
  cin>>n ;
  
  for (int i=1; i<=n; i++) 
  {
    double a, b, c ;
  
    cout<<"\nScrivi i 3 coefficienti dell'equazione "<<i <<" :" ;
    cin>>a>>b>>c ;

    double delta = b*b-4*a*c;

    if (a==0 && b==0) {
      cout<<"\nL'equazione e' degenere.\n" ;
      continue ;
    } else if (a==0) {
	    cout<<"\nLa radice dell'equazione e': "<<-c/b<<endl ;
    } else {
      if (delta < 0)
	cout<<"\nL'equazione non ha radici reali.\n" ;
      else {
	delta = sqrt(delta);
	cout<<"\nLe radici dell'equazione sono: "<<(-b+delta)/(2*a)
	    <<" e "<<(-b-delta)/(2*a)<<endl ;
      }
    }
  } // fine ciclo for
}
