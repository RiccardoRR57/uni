#include <iostream>

using namespace std ;

int main()
{
	const char menu[] =
		"1. Crea vettore\n"
		"2. Inserisci consumo\n"
		"3. Stampa vettore\n"
		"4. Salva vettore consumi\n"
		"5. Carica vettore consumi\n"
		"6. Calcola consumo medio\n"
		"7. Valuta risparmio\n"
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
		case 8:
			return 0 ;
		default:
			cout<<"Scelta errata"<<endl ;
		}
	}
	return 1 ;
}
