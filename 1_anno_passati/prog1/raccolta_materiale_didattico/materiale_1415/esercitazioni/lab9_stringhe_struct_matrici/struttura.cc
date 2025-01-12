/*
 Scrivere un programma che chieda all'utente di inserire il nome di un
 partecipante ad una gara di SCI ed il tempo che ha fatto registrare,
 espresso in minuti e secondi. Il programma deve quindi memorizzare i
 dati del partecipante in un oggetto struttura che contenga una
 stringa (per memorizzarvi il nominativo) ed un valore intero, contenente il
 tempo in secondi. Infine il programma stampa a video
 i dati appena memorizzati, esprimendo di nuovo il tempo in minuti e
 secondi. Inoltre, il programma stampa a video la lunghezza della
 stringa contenuta nel campo nominativo. Esempio:

 Inserisci nominativo: Tomba
 Tempo di Tomba (minuti e secondi): 2 23
 Il vincitore e' Tomba, con il tempo di 2 minuti e 23 secondi
 Il nominativo contiene una stringa di 5 caratteri

*/

#include<iostream>

using namespace std ;

const int MAX_L = 40 ;

int main()
{
	int minuti, secondi ;

	struct partecipante {
		char nominativo[MAX_L] ;
		int tempo ;
	} ;
	partecipante vincitore ;

	cout<<"Inserisci nominativo: " ;
	cin>>vincitore.nominativo ;
	cout<<"Tempo di "<<vincitore.nominativo<<" (minuti e secondi): " ;
	cin>>minuti>>secondi ;
	vincitore.tempo = minuti * 60 + secondi ;

	cout<<"Il vincitore e' "<<vincitore.nominativo<<", con il tempo di "
	    <<vincitore.tempo/60<<" minuti e "<<vincitore.tempo%60
	    <<" secondi"<<endl ;
	cout<<"Il nominativo contiene una stringa di " ;
	cout<<strlen(vincitore.nominativo)<<" caratteri\n" ;
}

