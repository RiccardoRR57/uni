#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std ;

const int MAXLUNMESS = 128 ;

void leggi_riga(istream &is, char *riga)
{
	// consuma eventuali sequenze di newline, 
	// per evitare errori nella lettura di
	// una riga che si sta per effettuare
	while (is.peek() == '\n')
		is.get() ;
	
	is.get(riga, MAXLUNMESS) ; // legge una riga
	is.get() ; // consuma il newline che
	// segue la riga appena letta
}

int main()
{
	const char menu[] =
		"1. Scrivi messaggio\n"
		"2. Salva cronologia\n"
		"3. Carica cronologia\n"
		"4. Calcola lunghezza parola\n"
		"5. Stampa cronologia\n"
		"6. Esci\n" ;
	
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
			return 0 ;
		default:
			cout<<"Scelta errata"<<endl ;
		}
	}
}
