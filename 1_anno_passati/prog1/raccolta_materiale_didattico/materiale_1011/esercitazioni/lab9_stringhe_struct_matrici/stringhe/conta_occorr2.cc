/* 
 Scrivere un programma che conta le occorrenze di un carattere
 inserito da tastiera all'interno di una stringa, costituita da una
 sola parola, inserita anch'essa da tastiera. La lettura della stringa
 e del carattere devono avvenire nel main, mentre il numero di
 occorrenze deve essere ritornato da una funzione dedicata, a cui
 vengono passate sia la stringa che il carattere da cercare. La
 funzione non legge nulla da stdin e non scrive nulla su stdout.

 Inoltre la ricerca deve essere case-insensitive.  Gestire il problema
 delle maiuscole/minuscole sfruttando funzioni di libreria standard
 che operano sui caratteri. Trovare da soli quali sono tali funzioni e
 cosa bisogna includere per utilizzarle.
 A tal proposito ricordare che, dato un header file da includere per utilizzare
 un alcune funzioni ed oggetti della libreira standard del C, il nome del 
 corrispondente header file da includere in C++ si ottiene tipicamente 
 togliendo il suffisso .h ed aggiungendo il carattere c in testa al nome 
 dell'header file originario (es.: math.h in C diventa cmath in C++).

 Infine non bisogna sfruttare il controllo del terminatore per
 decidere quando fermare la ricerca nella stringa. Trovare da soli qualche
 funzione di libreria da utilizzare per evitare di dover effettuare tale 
 controllo e quale header file bisogna includere.

 -> il tipo size_t lo assumiamo equivalente a unsigned int
 -> la notazione <nome_tipo> * la assumiamo equivalente a <nome_tipo> []

 Esempio di output:

 Inserisci la parola in cui cercare: Pippo
 Stringa: Pippo
 Quale carattere devo cercare?
 P
 P compare 3 volte nella stringa "Pippo"
*/

#include<iostream>

using namespace std ;

// prende in ingresso il carattere da cercare e la stringa in cui cercarlo.
int occorrenze(char c, const char stringa[])
{
    int cont = 0 ;
    const char c_minuscolo = tolower(c) ;
    const lunghezza = strlen(stringa) ;
    for(unsigned int i = 0 ; i < lunghezza ; i++)
	if(tolower(stringa[i]) == c_minuscolo) 
	    cont++;
    return cont ;
}

int main()
{
    const int MAX_LUN = 10 ;
    char a, parola[MAX_LUN] ;
    cout<<"Inserisci la parola in cui cercare: " ;
    cin>>parola ;
    cout<<"Stringa: "<<parola<<endl ;
    cout<<"Quale carattere devo cercare?\n" ;
    cin>>a ;
    cout<<a<<" compare "<<occorrenze(a, parola)
	<<" volte nella stringa "<<parola<<endl ;
    return 0;
}
