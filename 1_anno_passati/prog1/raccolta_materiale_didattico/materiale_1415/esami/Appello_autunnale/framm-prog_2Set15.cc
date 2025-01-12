#include <iostream>
#include <fstream>

using namespace std ;

int main()
{
	const char menu[] =
		"1. Richiedi lettura\n"
		"2. Effettua lettura\n"
		"3. Libera contenitore\n"
		"4. Stampa stato\n"
		"5. Salva stato\n"
		"6. Carica stato\n"
		"7. Deframmenta\n"
		"8. Esci\n" ;
	
	while (true) {
		cout<<menu<<endl ;
		
		int scelta ;
		cin>>scelta ;
		switch(scelta) {
		case 1:
			break ;
		case 2:
			break ;
		case 3:
			break ;
		case 4:
			break ;
		case 5:
			break ;
		case 6:
			break ;
		case 7:
			break;
		case 8:
			return 0 ;
		default:
			cout<<"Scelta errata"<<endl ;
		}
	}
	return 1 ;
}
