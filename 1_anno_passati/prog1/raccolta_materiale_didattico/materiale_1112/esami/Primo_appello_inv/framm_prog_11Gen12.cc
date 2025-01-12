#include <iostream>
#include <fstream>

using namespace std ;
const int MAX_LUN_RIGHE = 61 ; // lunghezza massima righe

int main()
{
	const char menu[] =
		"1. Aggiungi/Modifica riga\n"
		"2. Stampa documento\n"
		"3. Salva documento\n"
		"4. Carica documento\n"
		"5. Elimina riga\n"
		"6. Cerca prossima occorrenza parola\n"
		"7. Esci\n" ;
  
	while(true) {
		cout<<menu<<endl ;
		int scelta ;
		cin>>scelta ;

		switch(scelta) {
		case 1:{
			int idx ;
			cout<<"Indice riga da modificare/aggiungere? " ;
			cin>>idx ;
			char riga[MAX_LUN_RIGHE] ;

			// rimuoviamo il newline dallo stdin, e siamo
			// cosi' pronti a leggere una nuova riga con
			// la funzione get (se avessimo lasciato il
			// newline, la funzione get avrebbe poi letto
			// una riga vuota)
			cin.ignore() ;

			cout<<"Inserisci nuovo contenuto riga "
			    <<"(di almeno un carattere)"<<endl ;
			do {
				/* 
				 * riversa nell'array di caratteri
				 * riga i caratteri presenti sullo
				 * stdin, fermandosi o dopo aver letto
				 * MAX_LUN_RIGHE-1 caratteri, o quando
				 * si incontra il carattere newline (che
				 * non viene ne' aggiunto dentro riga
				 * ne' estratto dallo stdin)
				 */
				cin.get(riga, MAX_LUN_RIGHE-1) ;
				if (riga[0] == '\0') { // letta una riga vuota
					// riporto il cin in stato
					// buono, perche' la funzione
					// get lo manda in stato
					// cattivo nel caso in cui
					// legga una riga vuota
					cin.clear() ;
					// elimino il newline per
					// evitare problemi nella
					// prossima lettura di una
					// riga (la funzione get non
					// elimina il newline)
					cin.ignore() ;
				}
			} while (riga[0] == '\0') ;
			cout<<riga<<endl ;
			break ;
		}
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
			return 0 ;
		default:
			cout<<"Scelta errata"<<endl ;
		}
	}
	return 1 ;
}
