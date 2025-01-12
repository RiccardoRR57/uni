#include <iostream>

using namespace std ;

int main()
{
	const char menu[] =
		"1. Inserisci in cima\n"
		"2. Stampa contenuto pila\n"
		"3. Elimina della cima\n"
		"4. Salva pila\n"
		"5. Carica pila\n"
		"6. Fondi blocchi\n"
		"7. Esci\n" ;

	while (true) {
		cout<<menu<<endl ;

		int scelta ;
		cout<<"Scelta: " ;
		cin>>scelta ;

		switch (scelta) {
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
