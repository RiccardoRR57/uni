#include <iostream>

using namespace std;

int main()
{
    const char menu[]=
	"1. Noleggia ombrellone\n"
	"2. Stampa stato\n"
	"3. Salva stato\n"
	"4. Carica stato\n"
	"5. Noleggia ombrellone isolato\n"
	"6. Noleggia ombrelloni vicini\n"
	"7. Esci\n"
	;

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
    // non dovremmo mai arrivare qui
    return 1 ;
}
