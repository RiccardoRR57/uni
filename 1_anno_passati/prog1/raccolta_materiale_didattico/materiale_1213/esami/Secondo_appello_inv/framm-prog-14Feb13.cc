#include <iostream>

using namespace std ;


int main()
{
    const char menu[] =
	"1. Aggiungi contatore\n"
	"2. Incrementa contatore\n"
	"3. Stampa contatori\n"
	"4. Salva insieme\n"
	"5. Carica insieme\n"
	"6. Redireziona\n"
	"7. Incrementa contatore 2\n"
	"8. Esci\n" ;

    while (true) {
	cout<<menu<<endl ;
	int scelta ;
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
	    break ;
	case 8:
	    return 0 ;
	default:
	    cout<<"Scelta errata"<<endl ;
	}
    }

    return 0 ;
}

