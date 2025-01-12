/*
  Programma di esempio da usare per creare due file, uno di testo
  e l'altro binario, che contengono un array di tre interi.

  */

#include <iostream>
#include <fstream>
using namespace std ;

int main()
{
	const int N = 3 ;
	int a[N] = {5, 18990, 1923412} ;
	// Apertura del file di testo in scrittura
	ofstream tf("dati.txt");
	if (!tf) {
		cerr<<"Errore in creazione del file\n" ;
		return 1;
	}
	for (int i = 0 ; i < N ; i++)
		tf<<a[i]<<" " ;
	// Apertura del file binario in scrittura
	ofstream bf("dati.dat");
	if (!bf) {
		cerr<<"Errore in creazione del file\n" ;
		return 1;
	}
	bf.write(reinterpret_cast<const char *>(a), sizeof(int) * N) ;
	return 0;
}
