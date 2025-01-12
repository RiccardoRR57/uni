#include <iostream>

using namespace std ;

int main()
{
    const char menu[]=
	"1. Disegna segmento\n"
	"2. Stampa lavagna\n"
	"3. Salva stato\n"
	"4. Carica stato\n"
	"5. Disegna segmento 2\n"
	"6. Stesso segmento\n"
	"7. Uscita\n" ;
    
    while(true) {
	cout<<menu<<endl ;
	cout<<"Scelta? " ;

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
	    break;
	case 7:
	    return 0 ;
	default:
	    cout<<"Scelta errata\n"<<endl ;
	}
    }

    return 1 ;
}
