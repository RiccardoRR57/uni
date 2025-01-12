/*

Questo file contiene solo un possibile main per l'esercizio
percorso_semplificato.cc

*/
#include <iostream>
using namespace std ;

int main()
{
	const char Menu[] = "\nComandi disponibili:\n"
		"\tc (C) - per cambiare il colore di una casella di p1 (p2)\n"
		"\td     - per continuare con due nuovi percorsi\n"
		"\tq     - per terminare\n";

	char comando;
	do {
	    cout<< "Definisco due percorsi p1 e p2.\n" ;
	    // inizializza(&p1, 10, NERO);
	    // inizializza_copia(&p2, &p1);
	    cout<< "p1: " ;
	    // stampa(&p1) ;
	    cout<< "\np2: " ;
	    // stampa(&p2) ;
	    cout<<endl ;
	    cout<<Menu<<"\n\nComando? " ;
	    cin>>comando ;

	    while (comando != 'd' && comando != 'q') {
		switch (comando) {
		case 'c': {
		    cout<<"Posizione casella? " ;
		    int i;
		    cin>>i ;
		    // cambiaColore(&p1, i);
		    break;
		}
		case 'C': {
		    cout<<"Posizione casella? " ;
		    int i;
		    cin>>i ;
		    // cambiaColore(&p2, i);
		    break;
		}
		default:
			cout<< "Comando "<<comando<<" non valido\n" ;
		}
		cout<< "p1: " ;
		// stampa(&p1) ;
		cout<< "\np2: " ;
		// stampa(&p2) ;
		cout<<endl ;
		cout<<Menu<<"\n\nComando? " ;
		cin>>comando ;
	    }
	    // elimina(&p1) ;
	    // elimina(&p2) ;
	} while (comando != 'q');
	cout<< "*\n" ;
}
