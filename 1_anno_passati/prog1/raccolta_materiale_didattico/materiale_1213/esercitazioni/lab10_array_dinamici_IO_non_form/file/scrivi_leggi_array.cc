/*
  Scrivere un programma che:

  1) definisca un array di reali di dimensioni definite a tempo di scrittura del programma, e chieda all'utente di inserirne i valori;

  2) riversi il contenuto dell'array sia in un file binario "dati.dat"
     mediante output non formattato, che in un file di testo
     "dati.txt" mediante output formattato;

  3) chiuda entrambi i file;

  4) li riapra in lettura;

  5) ristampi il contenuto di entrambi i file (in termini di numeri reali).

  Provare a visualizzare e confrontare il contenuto dei due file con
  un editor di testo o con comandi quali 
  cat <nome_file>

  */

#include <iostream>
#include <fstream>

using namespace std ;

int main()
{
	const int N = 1 ;
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

	// Apertura del file binario in scrittura
	ofstream bf("dati.dat");
	if (!bf) {
		cerr<<"Errore in creazione del file\n" ;
		return 1;
	}
	
	bf.write(reinterpret_cast<const char *>(a), sizeof(double) * N) ;

	// Chiusura dei file: garantisco l'avvenuta scrittura
	tf.close();
	bf.close();

	// Riapertura dei file in modalita' lettura
	ifstream f1("dati.dat") ;
	ifstream f2("dati.txt") ;
	if(!f1 || !f2)	{
		cerr<<"Errore in apertura file.\n" ;
		return 2;
	}

	cout<<"Contenuto file di testo: "<<endl ;
	double d ;
	while (f2>>d)
		cout<<d<<" " ;
	cout<<endl ;

	cout<<"Contenuto file binario: "<<endl ;
	double buf[N] ;
	f1.read(reinterpret_cast<char *>(buf), sizeof(double) * N) ;
	
	for (int i = 0 ; i < N ; i++)
		cout<<buf[i]<<" " ;
	cout<<endl ;

	return 0;
}
