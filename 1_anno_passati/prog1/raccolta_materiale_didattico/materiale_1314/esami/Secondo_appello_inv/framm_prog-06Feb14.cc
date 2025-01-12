#include <iostream>
#include <fstream>

using namespace std ;

const int MAXLUN = 256 ;

void leggi_riga(istream &is, char *riga)
{
	/*
	 * consuma eventuali sequenze di newline, 
	 * per evitare errori nella lettura di
	 * una riga che si sta per effettuare
	 */
	while (is.peek() == '\n')
		is.get() ;

	is.get(riga, MAXLUN) ; // legge una riga
	is.get() ; // consuma il newline che segue la riga appena
		   // letta
}

int main()
{
	const char menu[] =
		"1. Aggiungi coppia domanda risposta\n"
		"2. Stampa elenco domande e risposte\n"
		"3. Salva elenco\n"
		"4. Carica elenco\n"
		"5. Poni domanda\n"
		"6. Inizia partita\n"
		"7. Esci\n" ;

	while (true) {
		cout<<menu<<endl ;
		int scelta ;
		cin>>scelta ;

		switch(scelta) {
		case 1:
			break ;
		case 2:
			break ;
		case 3:
			break ;
		case 4:
			break ;
		case 5:
			break ;
		case 6:
			break;
		case 7:
			return 0 ;
		default:
			cout<<"Scelta errata"<<endl ;
		}
	}
	return 1 ;
}
