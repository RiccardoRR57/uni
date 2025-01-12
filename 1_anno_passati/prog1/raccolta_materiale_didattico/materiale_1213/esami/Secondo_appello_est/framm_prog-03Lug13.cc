#include <iostream>
#include <fstream>

using namespace std ;

const int MAXLUN = 100 ;

void leggi_riga(istream &is, char *riga)
{
	// consuma eventuali sequenze di newline per evitare poi
	// errori nella lettura di una riga
	while (is.peek() == '\n')
		is.get() ;

	is.get(riga, MAXLUN) ;
	is.get() ; // consuma anche il newline successivo
}

int main()
{
	const char menu[] =
		"1. Ricevi messaggio\n"
		"2. Stampa messaggi\n"
		"3. Salva messaggi\n"
		"4. Carica messaggi\n"
		"5. Ricevi messaggio 2\n"
		"6. Stampa messaggi 2\n"
		"7. Definisci regola\n"
		"8. Ricevi messaggio 3\n"
		"9. Esci\n" ;
	
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
			break ;
		case 7:
			break ;
		case 8:
			break ;
		case 9:
			return 0 ;
		default:
			cout<<"Scelta errata"<<endl ;
		}
	}

	return 1 ;
}
