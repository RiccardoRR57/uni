#include <iostream>
#include <fstream>

using namespace std ;

int main()
{
    char menu[] =
	"1. Inizializza\n"
	"2. Aggiungi spostamento\n"
	"3. Stampa statistiche\n"
	"4. Salva stato\n"
	"5. Carica stato\n"
	"6. Stampa velocita' media\n"
	"7. Esci\n" ;

    while(true) {
	cout<<menu<<endl ;
	
	int scelta ;
	cin>>scelta ;
	switch(scelta) {
	case 7:
	    return 0 ;
	default:
	    cout<<"Scelta errata"<<endl ;
	}
    }
    return 1 ;
}
