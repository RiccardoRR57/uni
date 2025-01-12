#include <iostream>

using namespace std;

int main()
{
	lista_operazioni_t l;
	inizializza(l);

	const char menu[] =
		"1. Inizializza contenitori\n"
		"2. Inserisci operazione\n"
		"3. Stampa lista operazioni\n"
		"4. Salva lista operazioni\n"
		"5. Carica lista operazioni\n"
		"6. Inserisci operazione 2\n"
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
		}
	}

	return 1;
}
