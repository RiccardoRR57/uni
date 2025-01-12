#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	const char menu[] =
		"1. Inserisci comando\n"
		"2. Esegui prossimo comando\n"
		"3. Stampa comandi\n"
		"4. Salva stato\n"
		"5. Carica stato\n"
		"6. Cerca parola\n"
		"7. Esci\n";

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
			return 0;
		default:
			cout<<"Scelta errata"<<endl;
		}
	}
	return 1;
}
