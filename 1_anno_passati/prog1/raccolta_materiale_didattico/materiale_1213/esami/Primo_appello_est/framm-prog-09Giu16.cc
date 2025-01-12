#include <iostream>
#include <fstream>

using namespace std ;

int main()
{
	const char menu[] =
		"1. Crea magazzino\n"
		"2. Aggiungi cavo\n"
		"3. Stampa magazzino\n"
		"4. Salva magazzino\n"
		"5. Carica magazzino\n"
		"6. Estrai cavo\n"
		"7. Estrai cavi\n"
		"8. Esci\n" ;
	
	while (true) {
		cout<<endl<<menu<<endl ;
		
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
			return 0;
		default:
			cout<<"Scelta errata"<<endl ;
		}
	}
	return 1 ;
}
