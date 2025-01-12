#include <iostream>

using namespace std ;

int main()
{
	const char menu[] =
		"1. Aggiungi elemento\n"
		"2. Stampa vettore\n"
		"3. Salva vettore\n"
		"4. Carica vettore\n"
		"5. Aggiungi elemento con riallocazione\n"
		"6. Elimina elemento\n"
		"7. Partiziona vettore\n"
		"8. Esci\n" ;

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
			break ;
		case 8:
			return 0 ;
		default:
			cout<<"Scelta errata"<<endl ;
		}
	}
	return 1 ;
}
