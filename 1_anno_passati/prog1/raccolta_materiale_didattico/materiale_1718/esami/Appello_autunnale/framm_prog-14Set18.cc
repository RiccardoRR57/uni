#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	const char menu[] =
		"1. Reinizializza sequenza\n"
		"2. Stampa grafico orizzontale\n"
		"3. Salva sequenza\n"
		"4. Carica sequenza\n"
		"5. Stampa barra verticale\n"
		"6. Stampa grafico verticale\n"
		"7. Esci\n";

	while (true) {
		cout<<menu<<endl ;

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
