#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	const char menu[] =
		"1. Inserisci giocatore\n"
		"2. Stampa Doodle\n"
		"3. Salva Doodle\n"
		"4. Carica Doodle\n"
		"5. Scegli serata\n"
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
