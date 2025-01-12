/*
  Scrivere un programma in cui si dichiari un tipo struct studente,
  costituito da un campo nome, un campo cognome ed un campo numero di
  matricola. Si definiscano e si inizializzino quindi almeno due
  oggetti (variabili) di tipo struct studente e si memorizzino in
  forma binaria in un file. Si chiuda quindi il file, lo si riapra in
  lettura e se ne stampi il contenuto.

*/

#include <iostream>
#include <fstream>

using namespace std ;

const int MAX_LEN = 21 ;
struct studente{
	char nome[MAX_LEN];
	char cognome[MAX_LEN];
	int matricola;
};

int main()
{
 studente s1= {"Mario","Rossi",2345};
 studente s2= {"Dario","Bianchi",8488};

 //Creazione e apertura del file in scrittura contenente i record studente
 ofstream f1("Studenti.dat");
 if(!f1) {
 	cerr<<"Errore in creazione del file\n" ;
	return 1;
 }

 /*
   Scrittura sul file binario dei due record.
 */
 f1.write(reinterpret_cast<char *>(&s1), sizeof(studente));
 f1.write(reinterpret_cast<char *>(&s2), sizeof(studente));
 f1.close(); // per essere sicuro di scrivere nel file

 ifstream f2("Studenti.dat");
 if(!f2) {
 	cerr<<"Errore in apetura\n" ;
	return 2;
 }

 studente s3, s4 ;
 //leggiamo il contenuto del file
 f2.read(reinterpret_cast<char *>(&s3),sizeof(studente));
 f2.read(reinterpret_cast<char *>(&s4),sizeof(studente));

 /*Stampiamo su standard output il contenuto del file*/
 cout<<s3.matricola<<": "<<s3.nome<<" "<<s3.cognome<<endl ;
 cout<<s4.matricola<<": "<<s4.nome<<" "<<s4.cognome<<endl ;

 return 0;
}
