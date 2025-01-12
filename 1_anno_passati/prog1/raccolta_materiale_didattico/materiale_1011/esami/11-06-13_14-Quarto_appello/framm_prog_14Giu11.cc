#include <iostream>

using namespace std ;

int main()
{
    const char menu[] =
	"1. Aggiungi attivazione unica\n"
	"2. Stampa programmazione\n"
	"3. Salva programmazione\n"
	"4. Carica programmazione\n"
	"5. Aggiungi attivazione\n"
	"6. Incrementa ora\n"
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
	}
    }
    // qui non dovremmo arrivare mai
    return 1 ;
}
