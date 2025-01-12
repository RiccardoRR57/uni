#include <iostream>

using namespace std ;

int main()
{
	const char menu[] =
		"1. Cambia stato\n"
		"2. Stampa matrice\n"
		"3. Salva matrice\n"
		"4. Carica matrice\n"
		"5. Riduci elementi accesi\n"
		"6. Stampa seguenze contigue\n"
		"7. Esci\n" ;
	while(true) {
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
			return 0 ;
		default:
			cout<<"Scelta errata"<<endl ;
		}
	}
	return 1 ;
}
