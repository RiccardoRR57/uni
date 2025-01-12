#include <iostream>

using namespace std;

int main()
{
	const char menu[] =
		"1. Reinizializza sequenza\n"
		"2. Stampa sequenza\n"
		"3. Salva sequenza\n"
		"4. Carica sequenza\n"
		"5. Stampa occupazione memoria\n"
		"6. Controlla sequenza\n"
		"7. Esci\n";

	while (true) {
		cout<<menu<<endl;
		int scelta;
		cin>>scelta;

		cout<<endl ; // per il corretto funzionamento del tester

		switch (scelta) {
		case 1: {
			cout<<"Lunghezza della sequenza: ";
			int N;
			cin>>N;

			cout<<"Sequenza: ";
		}
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
