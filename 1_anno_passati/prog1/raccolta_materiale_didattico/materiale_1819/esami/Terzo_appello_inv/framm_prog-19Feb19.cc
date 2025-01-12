#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	const char menu[] =
		"1. Reinizializza consuntivo\n"
		"2. Stampa consuntivo\n"
		"3. Salva catalogo\n"
		"4. Carica consuntivo\n"
		"5. Stampa consuntivi\n"
		"6. Esci\n";

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
			return 0;
		default:
			cout<<"Scelta non valida"<<endl;
		}
	}
}
