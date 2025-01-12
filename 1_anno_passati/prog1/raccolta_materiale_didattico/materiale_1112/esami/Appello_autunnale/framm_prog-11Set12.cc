#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    char menu[] =
	"1. Aggiungi sequenza all'insieme\n"
	"2. Stampa insieme delle sequenze\n"
	"3. Salva insieme delle sequenze\n"
	"4. Carica insieme delle sequenze\n"
	"5. Aggiungi sequenza intersezione all'insieme\n"
	"6. Esci\n";

    while(true) {
	cout<<menu<<endl;

	int scelta;
	cin>>scelta ;
	switch(scelta) {
	case 1:
	    break;
	case 2:
	    break;
	case 3:
	    break;
	case 4:
	    break;
	case 5:
	    break;
	case 6:
	    return 0;
	    break;
	default:
	    cout<<"Scelta errata"<<endl;
	}
    }
}
