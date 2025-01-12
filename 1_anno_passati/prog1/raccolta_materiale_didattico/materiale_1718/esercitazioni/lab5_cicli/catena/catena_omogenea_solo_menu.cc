/*
Possibile impelementazione del solo menu di scelta per il programma
catena_omogenea.cc
*/


#include <iostream>

using namespace std ;

int main(){
    while (true) {
        int scelta, i, pos;

        cout<<"\n \n Gestione di una catena \n"
                "Inserisci: \n"
                "1 - per inserire un anello \n"
                "2 - per estrarre un anello \n"
                "3 - per stampare la catena \n"
                "4 - per terminare \n\n"
                "Scelta \n? ";
        cin>>scelta ;
        switch (scelta) {
            case 1 :
                cout<<"Posizione? " ;
                cin>>pos ;
                break;
            case 2:
                cout<<"Posizione? " ;
                cin>>pos ;
               break;
            case 3:
                cout<<"Hai scelto di stampare la catena\n" ;
			break ;
	case 4:
		return 0 ; /* termine programma */
	default:
		cout<<"Scelta errata\n" ;

	} /* Fine switch */

    } /* Fine while */

    return 0; /* Questa istruzione non dovrebbe essere mai raggiunta */
 }
