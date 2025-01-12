#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std ;


int main()
{
    const char menu[] =
	"1. Modifica capienza\n"
	"2. Inserisci valore\n"
	"3. Stampa insieme\n"
	"4. Salva insieme\n"
	"5. Carica insieme\n"
	"6. Stampa contenuto ordinato\n"
	"7. Esci\n" ;
    
    while (true) {
	cout<<menu<<endl;

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
	    return 0 ;
	default:
	    cout<<"Scelta errata"<<endl ;
	}
    }

    return 1 ;
}
