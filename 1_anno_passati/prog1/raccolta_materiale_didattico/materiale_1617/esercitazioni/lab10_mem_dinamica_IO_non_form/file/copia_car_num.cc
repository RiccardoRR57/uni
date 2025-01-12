/*
Scrivere un programma che apra un file di testo (il cui nome è
stabilito a tempo di scrittura del programma), e crei un secondo file
(anch'esso con nome stabilito a tempo di scrittura del programma) contenente
solo i caratteri numerici (cifre da 0 a 9) contenuti nel primo file, e
l'indicazione del numero totale di occorrenze di tali caratteri. 
Un esempio di contenuto del secondo file e' il seguente:

6       3       7       3       1
Il numero di caratteri numerici letti e' 5

*/

#include <iostream>
#include <fstream>

using namespace std ;

int main()
{
 int n=0; //variabile in cui memorizzare il numero di occorrenze dei
	  //caratteri numerici

 //Apertura file in lettura
 ifstream f1("File_prova.txt") ;

 if(!f1) {
	cerr<<"Errore in Apertura\n" ;
	return 1;
 }

 //Creazione file
 ofstream f2("File_risultato.txt") ;
 if(!f2) {
	cerr<<"Errore in creazione del file\n" ;
 	return 2;
 }

 int c ;
 while((c=f1.get()) != EOF)
 {
 	if (c >= '0' && c <= '9') {
		f2<<c<<"\t" ;
		n++;
	}
 }

 f2<<"\nIl numero di caratteri numerici letti e\' "<<n<<endl ;

 return 0;
}
