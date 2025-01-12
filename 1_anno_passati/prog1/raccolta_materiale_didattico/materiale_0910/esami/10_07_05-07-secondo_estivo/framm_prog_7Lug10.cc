#include <iostream>

using namespace std ;

int main()
{
    const char menu[] =
	"1. Inizia partita\n"
	"2. Stampa stato\n"
	"3. Confronta coppia\n"
	"4. Salva partita\n"
	"5. Carica partita\n"
	"6. Gioca coppia\n"
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
	    break;
	case 5:
	    break;
	case 6:
	    break ;
	case 7:
	    return 0;
	default:
	    cout<<"Scelta errata"<<endl ;
	}
    }
    // non dovremmo mai arrivare qui
    return 1 ;
}
