#include <iostream>

using namespace std ;

int main()
{
	const char menu[] =
		"1. Inizializza code\n"
		"2. Accoda utente\n"
		"3. Servi prossimo utente\n"
		"4. Stampa stato code\n"
		"5. Salva stato code\n"
		"6. Carica stato code\n"
		"7. Attiva modalita' numeri limitati\n"
		"8. Esci\n" ;

	while (true) {
		cout<<menu<<endl ;

		int scelta ;
		cout<<"Scelta: " ;
		cin>>scelta ;

		switch (scelta) {
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
			return 0 ;
		default:
			cout<<"Scelta sbagliata"<<endl ;
		}
	}

	return 1 ;
}
