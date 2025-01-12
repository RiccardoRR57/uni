#include <iostream>

using namespace std;

int main()
{
	const char menu[] =
		"1. Vendi biglietto\n"
		"2. Stampa biglietti venduti\n"
		"3. Salva biglietti venduti\n"
		"4. Carica biglietti venduti\n"
		"5. Stampa vincitore\n"
		"6. Stampa primi n vincitori\n"
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
