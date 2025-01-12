/* 
Determinare se un numero intero inserito 
dall'utente è multiplo di un numero dato in ingresso 

Algoritmo risolutivo:
- immettere il numero in ingresso;
- dividere il numero in immesso per il numero dato;
- controllare il resto della divisione;
- se il resto della divisione e' 0 allora il numero immesso è multiplo del 
  numero dato;
- altrimenti non è multiplo del numero dato  
*/



#include <iostream>
using namespace std;

int main()
{
  int numero, resto;
  const int num =2;			// ==> consideriamo come numero dato 2
  
  cout<<"Inserisci un numero intero\n"; 
  cin>>numero;
  resto = numero % num;		//  % ==> operatore modulo (resto della divisione intera)
  if (resto == 1)
	  cout<<"Il numero "<<numero<<" non e' multiplo di "<<num; 
     /* dato che l'istruzione che segue l'if è singola, 
     non ho bisogno di racchiuderla in un blocco, 
     cioè non ho bisogno delle parentesi graffe, ma posso
     comunque metterle se ciÃ² mi facilita la lettura del codice */
  else 
	  cout<<"Il numero "<<numero<<" e' multiplo di "<<num; 
  return 0; //esco dal programma dicendo che si è concluso correttamente
}


/* 
Variante.

Risolviamo lo stesso esercizio precedente ma dando la possibilità all'utente di decidere
i due numeri

#include <iostream>
int main()
{
  int numero; //non mi serve più la variabile resto
  int num;    //questa volta divisore lo facciamo immettere dall'utente
  
  cout<<"Inserisci il numero da usare per il controllo - il denominatore\n";
  cin>>num;

  cout<<"Inserisci un numero intero da controlare\n"; 
  cin>>numero;

  if (numero % num == 0) 
	  cout<<"Il numero "<<numero<<" e' multiplo di "<<num; 
  else 
	  cout<<"Il numero "<<numero<<" non e' multiplo di "<<num; 
  return 0;
}


*/

