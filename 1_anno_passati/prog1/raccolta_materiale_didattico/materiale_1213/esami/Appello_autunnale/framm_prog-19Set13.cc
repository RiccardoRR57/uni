#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std ;


int main()
{
	const char menu[] =
		"1. Crea quadrato\n"
		"2. Stampa area\n"
		"3. Salva area\n"
		"4. Carica area\n"
		"5. Modifica quadrato\n"
		"6. Riempi sottoarea\n"
		"7. Stampa area 2\n"
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
			break ;
		case 8:
			return 0 ;
		default:
			cout<<"Scelta errata"<<endl ;
		}
	}


}
