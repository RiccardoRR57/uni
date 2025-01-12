#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	const char menu[] =
		"1. Aggiungi partecipante\n"
		"2. Stampa sondaggio\n"
		"3. Salva sondaggio\n"
		"4. Carica sondaggio\n"
		"5. Trova giorno migliore\n"
		"6. Esci\n";

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
			return 0;
		default:
			cout<<"Scelta errata"<<endl;
		}
	}

	return 1;
}
