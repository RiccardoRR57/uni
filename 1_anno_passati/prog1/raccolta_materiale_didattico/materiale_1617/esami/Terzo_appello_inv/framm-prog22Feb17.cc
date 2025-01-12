#include <iostream>

using namespace std ;

int main()
{
	const char menu[] =
		"1. Modifica lunghezza massima\n"
		"2. Inserisci quadrilatero\n"
		"3. Stampa sequenza\n"
		"4. Salva stato\n"
		"5. Carica stato\n"
		"6. Controlla quadrilatero\n"
		"7. Esci\n";

	while (true) {
		cout<<menu<<endl ;

		int scelta ;
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
			return 0 ;
		default:
			cout<<"Scelta sbagliata"<<endl ;

		}
	}

	return 1 ;
}
