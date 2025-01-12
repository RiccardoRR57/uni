#include <iostream>

using namespace std;

int main()
{
	const char menu[] =
		"1. Reinizializza catalogo\n"
		"2. Inserisci brano\n"
		"3. Scarica brano\n"
		"4. Stampa catalogo\n"
		"5. Salva catalogo\n"
		"6. Carica catalogo\n"
		"7. Stampa download per server\n"
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
		default:
			return 0;
		}
	}

	return 1;
}
