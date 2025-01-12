#include <iostream>

using namespace std;

int main()
{
	const char menu[] =
		"1. Inizializza insieme dei compiti\n"
		"2. Accendi compito\n"
		"3. Stampa stato\n"
		"4. Esegui prossimo compito\n"
		"5. Salva stato\n"
		"6. Carica stato\n"
		"7. Esegui prossimo compito 2\n"
		"8. Esci\n";

	while (true) {
		cout<<menu<<endl;

		int scelta;
		cout<<"Scelta: ";
		cin>>scelta;

		cout<<endl; // questo accapo è importante per il tester!

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
			break;
		case 8:
			return 0;
		default:
			cout<<"Scelta non valida"<<endl;
		}
	}

	return 1;
}
