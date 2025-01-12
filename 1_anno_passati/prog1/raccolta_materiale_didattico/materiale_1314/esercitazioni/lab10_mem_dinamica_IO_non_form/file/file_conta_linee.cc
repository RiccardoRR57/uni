/*
  Scrivere un programma che, senza effettuare letture formattate:

  1) crei un file di testo di nome Testo.txt;

  2) chieda all'utente di inserire il contenuto del file, carattere
  per carattere (gestire opportunamente la comunicazione della fine
  dell'immissione dei caratteri da parte dell'utente e ricordarsi che
  si possono effettuare solo letture non formattate);

  3) chiuda il file;

  4) lo riapra in lettura;

  5) ne stampi il contenuto ed il numero di righe.

  */

#include <iostream>
#include <fstream>

using namespace std ;

int main()
{
 //Creazione e Apertura del file in scrittura
 ofstream f("Testo.txt");
 if (!f) {
	cerr<<"Errore in creazione del file\n" ;
 	return 1;
 }
 cout<<"Inserisci il contenuto del file "
     <<"(EOF per terminare l'input).\n";

 int c ;
 
   while((c=cin.get()) != EOF) 
       f<<static_cast<char>(c);

 // Chiusura file: garantisco l'avvenuta scrittura
 f.close();

 //Riapertura file in modalita' lettura
 ifstream f2("Testo.txt") ;
 if(!f2) {
	cerr<<"Errore in apertura file.\n" ;
	return 2;
 }

 cout<<"\nContenuto del file:\n" ;

 int nl = 0; // numero di linee del file

 // Rileggiamo il contenuto del file
 while((c=f2.get()) != EOF) {
     cout<<static_cast<char>(c);
      if(c=='\n')
           nl++;
   }

 cout<<"\nIl file contiene "<<nl<<" linee\n" ;

 return 0;
}
