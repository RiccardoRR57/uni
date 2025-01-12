#include <iostream>

using namespace std;

int main()
{
	const char menu[] =
		"1. Inizializza insieme\n"
		"2. Noleggia auto\n"
		"3. Stampa stato\n"
		"4. Salva stato\n"
		"5. Carica stato\n"
		"6. Controlla auto\n"
		"7. Restituisci auto\n"
		"8. Esci\n";

	while (true) {
		cout<<menu<<endl;

		int scelta;
		cin>>scelta;

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
			break;
		default:
			cout<<"Scelta errata"<<endl;
		}
	}
	return 1;
}
