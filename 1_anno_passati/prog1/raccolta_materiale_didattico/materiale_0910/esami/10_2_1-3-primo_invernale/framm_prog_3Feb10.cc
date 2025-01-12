#include <iostream>
#include <fstream>

using namespace std ;

int main()
{
    const char menu[] =
	"\t1 Nuova partita\n"
	"\t2 Stampa partita\n"
	"\t3 Salva partita\n"
	"\t4 Carica partita\n"
	"\t5 Confronta parola\n"
	"\t6 Trova parola\n"
	"\t7 Elenca posizioni parola\n"
	"\t8 Uscita\n";

    while(true) {
	cout<<endl<<menu<<endl ;
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
	}
    }

    // non si dovrebbe mai arrivare qui
    return 1 ;
}
