#include <iostream>

using namespace std ;

int main()
{
	const char menu[] =
		"1. Inizializza successione\n"
		"2. Stampa grafico 1\n"
		"3. Salva successione\n"
		"4. Carica successione\n"
		"5. Stampa grafico 2\n"
		"6. Esci\n" ;
	
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
			return 0 ;
		default:
			cout<<"Scelta errata"<<endl ;
		}
	}
	return 1 ;
}
