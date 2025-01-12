#include <iostream>

using namespace std;

int main()
{
	const char menu[] =
		"1. Reinizializza puzzle\n"
		"2. Stampa puzzle\n"
		"3. Salva puzzle\n"
		"4. Carica puzzle\n"
		"5. Trova parola in verticale\n"
		"6. Trova parola globalmente\n"
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
