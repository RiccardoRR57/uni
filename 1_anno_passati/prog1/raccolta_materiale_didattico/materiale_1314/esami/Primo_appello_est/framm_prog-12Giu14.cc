#include <iostream>

using namespace std ;

int main()
{
	const char menu[] =
		"1. Modifica modello\n"
		"2. Stampa modello\n"
		"3. Aggiungi prodotto\n"
		"4. Stampa prodotti\n"
		"5. Salva prodotti\n"
		"6. Carica prodotti\n"
		"7. Esci\n" ;

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
			return 0 ;
		default:
			cout<<"Scelta sbagliata"<<endl ;
		}
	}
	
	return 1 ;
}
