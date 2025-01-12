/*
  Scrivere una funzione che, presi in ingresso due array, ed assunto
  il primo contenere una stringa, memorizza nel secondo la stringa che
  si ottiene invertendo l'ordine dei caratteri contenuti nella prima
  stringa. Il funzione comunica inoltre se la stringa di partenza è
  palindroma o meno (ossia se è uguale alla sua inversa).  Utilizzare
  un enumerato per il tipo di ritorno della funzione.  Scrivere una
  funzione principale che definisca una stringa e la stampi, quindi,
  utilizzando la precedente funzione, ne calcoli l'inversa e comunichi
  se la stringa è palindroma o meno.

*/


#include<iostream>
#include<cstring>

using namespace std ;

const int MAX_LUN = 20 ;

enum tipo_t {PALINDROMA, NON_PALINDROMA} ;

tipo_t inverti(const char str1[], char str2[])
{
    int destra = strlen(str1) ; // indice del terminatore
    int sinistra = 0 ;
    enum tipo_t tipo = PALINDROMA ;

    while(--destra >= 0) {
	if (sinistra < destra && tipo == PALINDROMA && 
	    str1[sinistra] != str1[destra])
		tipo = NON_PALINDROMA ;
	str2[sinistra++] = str1[destra] ;
    }
    str2[sinistra] = '\0' ; // termino la stringa di destinazione

    return tipo ;
}
		      
int main()
{
 char parola[]="Programma";
 char inversa[MAX_LUN] ;
 enum tipo_t tipo ;

 cout<<"Stringa originale: "<<parola<<endl ;
 tipo = inverti(parola, inversa) ;
 cout<<"Inversa: "<<inversa<<endl ;
 cout<<"La stringa "<<parola<<" "<<((tipo == PALINDROMA) ? "" : "non")
     <<" è palindroma"<<endl ;
 return 0;
}
