/*
  Scrivere un programma che:

  1) definisca un array di reali di dimensioni definite a tempo di
  scrittura del programma, e chieda all'utente di inserirne i valori
  (oppure lo inizializza a tempo di scrittura del programma stesso);

  2) riversi il contenuto dell'array sia in un file di testo
     "dati.txt" mediante output formattato;

  3) chiuda il file;

  4) lo riapra in lettura;

  5) ristampi il contenuto del file.

  Provare a visualizzare il contenuto del file con un editor di testo o
  con comandi quali 
  cat <nome_file>

  */

#include <iostream>
#include <fstream>

using namespace std ;

int main()
{
	const int N = 3 ;
	double a[N] ;
	
	// Apertura del file di testo in scrittura
	ofstream tf("dati.txt");
	if (!tf) {
		cerr<<"Errore in creazione del file\n" ;
		return 1;
	}

	cout<<"Inserire i valori dei "<<N<<" elementi:"<<endl ;
	for (int i = 0 ; i < N ; i++) {
		cin>>a[i] ;
		tf<<a[i]<<" " ;
	}

	// Chiusura del file: garantisco l'avvenuta scrittura
	tf.close();

	// Riapertura del file in modalita' lettura
	ifstream f("dati.txt") ;
	if(!f)	{
		cerr<<"Errore in apertura file.\n" ;
		return 2;
	}

	cout<<"Contenuto file: "<<endl ;
	double d ;
	while (f>>d)
		cout<<d<<" " ;
	cout<<endl ;

	return 0;
}
