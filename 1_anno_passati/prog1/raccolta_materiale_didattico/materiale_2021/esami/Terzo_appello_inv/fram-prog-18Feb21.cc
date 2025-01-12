#include <iostream>

using namespace std;

int main()
{
	const char menu[] =
		"1. Inizializza codice\n"
		"2. Stampa codice\n"
		"3. Salva codice\n"
		"4. Carica codice\n"
		"5. Stampa carattere\n"
		"6. Ruota codice\n"
		"7. Esci\n";

	while (true) {
		cout<<menu<<endl;
		int scelta;
		cin>>scelta;

		cout<<endl ; // per il corretto funzionamento del tester

		switch (scelta) {
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
		case 7:
			return 0;
		default:
			cout<<"Scelta errata"<<endl;
		}
	}

	return 1;
}
