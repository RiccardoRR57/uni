/* 
 Scrivere un programma che conti le occorrenze di un carattere
 inserito da tastiera all'interno di una stringa definita a tempo di
 scrittura del programma.

 Esempio di output:

 Stringa: Analisi dei requisiti
 Quale carattere devo cercare?
 i
 i compare 6 volte nella stringa "Analisi dei requisiti"

*/

#include<iostream>

using namespace std ;

int main()
{
  char a, frase[]="Analisi dei requisiti";
  int i=0, cont=0;
  cout<<"Stringa: "<<frase<<endl ;
  cout<<"Quale carattere devo cercare?\n" ;
  cin>>a ;
  while(frase[i] != '\0')
    if(frase[i++] == a) 
	    cont++;
  cout<<a<<" compare "<<cont<<" volte nella stringa "<<frase<<endl ;
  return 0;
}
