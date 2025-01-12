#include <iostream>

using namespace std;

int main()
{
	const char menu[] =
		"1. Inizializza sequenza\n"
		"2. Alloca blocchi\n"
		"3. Stampa stato\n"
		"4. Salva stato\n"
		"5. Carica stato\n"
		"6. Stampa blocchi liberi da indice\n"
		"7. Cerca ed alloca blocchi\n"
		"8. Cerca ed alloca blocchi 2\n"
		"9. Esci\n";

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
			break;
		case 9:
			return 0;
		default:
			cout<<"Scelta errata"<<endl;
		}
	}
}
