#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>

using namespace std ;

int main()
{

    const char menu[] =
	"1. Reinizializza tabella\n"
	"2. Inserisci coppia\n"
	"3. Stampa tabella\n"
	"4. Salva tabella\n"
	"5. Carica tabella\n"
	"6. Stampa valore\n"
	"7. Esci\n" ;

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
	case 7:
	    return 0;
	
	default:
	    cout<<"Scelta errata"<<endl ;
	}
    }

    return 1 ;
}
