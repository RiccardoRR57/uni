#include <iostream>

using namespace std;

int main()
{
    parete_t parete ;
    inizializza(parete) ;

    char menu[] =
	"1. Installa mensola\n"
	"2. Inserisci biglia\n"
	"3. Stampa parete\n"
	"4. Salva stato\n"
	"5. Carica stato\n"
	"6. Rimuovi mensola\n"
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
	default:
	    cout<<"Scelta non valida"<<endl ;
	}
    }
    return 0 ;
}
