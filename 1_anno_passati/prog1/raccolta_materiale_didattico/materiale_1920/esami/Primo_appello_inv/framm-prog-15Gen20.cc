#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

int main()
{
	
	const char menu[] =
		"Menu:\n"
		"1. Inizializza-reinizializza magazzino\n"
		"2. Aggiungi pacco\n"
		"3. Stampa carico\n"
		"4. Salva stato\n"
		"5. Carica stato\n"
		"6. Copia carico\n"
		"7. Fondi scaffali\n"
		"8. Esci\n" ;
	
	while(true) {
		cout<<menu<<endl ;
		int scelta ;
		cin>>scelta ;

		cout<<endl; // questo accapo è importante per il tester!

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
			break;
		case 7:
			break;
		case 8:
			return 0;
		default:
			cout<<"Scelta sbagliata"<<endl ;
		}
	}


}
