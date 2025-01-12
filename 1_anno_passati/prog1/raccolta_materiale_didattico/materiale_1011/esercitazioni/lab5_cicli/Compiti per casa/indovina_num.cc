/*
Dato un numero immesso da un utente, scrivere l'algoritmo e la codifica di tale
algoritmo che verifichi quando un secondo numero intero � uguale al numero 
precedentemete inserito e indichi quanti tentativi sono necessari per indovinarlo
*/

/*Algoritmo risolutivo:
1- Immissione del numero da indovinare (num1);
2- Immetti un numero (num2);
3- se num1>num2 ==> il numero inserito e' piu' piccolo del numero da trovare ==> aumenta il numero di tentativi;
4- altrimenti se num1<num2 ==> il numero inserito e' piu' grande del numero da trovare ==> aumenta il numero di tentativi
5- ripeti le parti 2-3-4 fino a quando num2 e' diverso da num1  
*/

/*Codifica dell'algoritmo*/

#include <iostream>

using namespace std ;

int main()
{
  int num1, num2, cont=1;
    
  cout<<"Inserisci il numero intero che vuoi che sia indovinato:\n" ; 
  cin>>num1 ;
  cout<<"Prova ad indovinare il numero:\n" ;
  cin>>num2 ;
  while (num1 != num2)
   {
    if (num1>num2)
      {
       cout<<"il numero cercato e' piu' grande di quello inserito\n" ;
       cout<<"Prova ad indovinare il numero:\n" ;
       cin>>num2 ;
       cont++;
       }  
    else 
     if (num1<num2)
      {
       cout<<"il numero cercato e' piu' piccolo di quello inserito\n" ; 
       cout<<"Prova ad indovinare il numero:\n" ;
       cin>>num2 ;
       cont++;
       }
    }
  cout<<"Bravo! hai trovato il numero "<<num1<<" in "<<cont<<" tentativi\n" ;  
  return 0;   //esco dal programma comunicando che si e' concluso correttamente
}


/*
Variante_01: 
utiliziamo un avariabile ausiliaria che ci consenta di individuare se il numero e' stato individuato, tale variabile è individuata nella variabile trovato

#include <iostream>

using namespace std ;

int main()
{
  int num1, num2, cont=1;
  int trovato=0;  
  cout<<"Inserisci il numero intero che vuoi che sia indovinato:\n" ; 
  cin>>num1 ;
  while (trovato == 0)
   {cout<<"Prova ad indovinare il numero:\n" ;
    cin>>num2 ;
    if (num1>num2)
      {
       cout<<"il numero cercato e' piu' grande di quello inserito\n" ;
       cont++;
       }  
    else 
     if (num1<num2)
      {
       cout<<"il numero cercato e' piu' piccolo di quello inserito\n" ; 
       cont++;
       }
     else 
      {
       cout<<"Bravo! hai trovato il numero %d in %d tentativi\n", num1,cont ;
       trovato=1;
       }
    }  
return 0; //esco dal programma dicendo che si è concluso correttamente
}
*/

