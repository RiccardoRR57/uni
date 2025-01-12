/* 
 Scrivere una funzione che riceve in ingresso due stringhe, copia la
 prima nella seconda, e ritorna la nuova lunghezza della stringa di
 destinazione.
*/

#include<iostream>

using namespace std ;

int copia_stringa(char dest[], const char sorg[])
{
    int i ;
    for(i=0; sorg[i] != '\0' ; i++)
	dest[i] = sorg[i];
    dest[i] = '\0' ; // che succedeve se si dimentcava questa istruzione?
    return i ;
}

int main()
{
  const char frase[] = "Da copiare" ;
  char copia[10] ;
  copia_stringa(copia, frase) ;
  cout<<"\noriginale: "<<frase<<"** \ncopia: "<<copia<<"**\n" ;
  /* 
   * si sono stampati gli asetrischi aggiuntivi come aiuto per capire
   * dove finiscono le due stringhe 
  */
  return 0;
}
