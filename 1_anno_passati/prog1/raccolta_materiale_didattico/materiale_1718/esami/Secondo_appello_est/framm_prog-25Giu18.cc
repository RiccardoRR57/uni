#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	const char menu[] =
		"1. Crea insieme\n"
		"2. Aggiungi codice\n"
		"3. Stampa insieme\n"
		"4. Salva insieme\n"
		"5. Carica insieme\n"
		"6. Stampa intersezione\n"
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
			cout<<"Scelta sbagliata"<<endl;
		}
	}

	return 1;

}
