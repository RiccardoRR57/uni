#include <iostream>

using namespace std ;

int main()
{
	const char menu[] =
		"1. Modifica sequenza giorni\n"
		"2. Aggiungi reperiblita'\n"
		"3. Stampa reperibilita'\n"
		"4. Salva reperibilita'\n"
		"5. Carica reperibilita'\n"
		"6. Equalizza reperibilita'\n"
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
			cout<<"Scelta sbagliata"<<endl ;
		}
	}
	return 1 ;
}
