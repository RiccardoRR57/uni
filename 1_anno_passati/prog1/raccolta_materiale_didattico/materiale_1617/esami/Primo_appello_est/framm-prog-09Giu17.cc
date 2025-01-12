#include <iostream>

using namespace std;

int main()
{
	const char menu[] =
		"1. Aggiungi parola\n"
		"2. Stampa parole\n"
		"3. Salva stato\n"
		"4. Carica stato\n"
		"5. Controlla se prefisso\n"
		"6. Esci\n";

	while (true) {
		cout<<menu<<endl;
		int scelta;
		cin>>scelta;

		switch(scelta) {
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
			return 0;
		default:
			cout<<"Scelta errata"<<endl;

		}


	}

	return 1;
}
