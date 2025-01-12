#include <iostream>
#include <fstream>

using namespace std ;

const int MAXLUNMESS = 256 ;

/*
 * Ritorna il numero di giorni del mese passato in ingresso, assumendo
 * che l'anno non sia bisestile.
 */
int calcola_giorni_mese(int mese)
{
	if (mese == 4 || mese == 6 || mese == 9 || mese == 11)
		return 30 ;
	else if (mese == 2)
		return 28 ;
	else
		return 31 ;
}

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
		"1. Carica turni\n"
		"2. Stampa turni\n"
		"3. Converti data\n"
		"4. Cambia data\n"
		"5. Esci\n" ; 
	
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
			return 0 ;
		default:
			cout<<"Scelta errata"<<endl ;
		}
	}
	return 1 ;
}
