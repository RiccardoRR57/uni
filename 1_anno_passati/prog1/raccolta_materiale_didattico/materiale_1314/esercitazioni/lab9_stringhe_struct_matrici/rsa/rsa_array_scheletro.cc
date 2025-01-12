#include <iostream>

using namespace std ;

int e = 5, d = 173, r = 323; // Chiave cifratura/decifratura

int main()
{
    const int NUM_ELEM = 5 ;
    int vettore[5] = {1, 2, 3, 4, 5} ;
    int i ;

    while (1) {
        int scelta ;

	cout<<"\tChiave attualmente in uso: ("<<e<<", "<<d<<", "<<r<<")\n" ;
	cout<<"\tContenuto attuale del vettore: " ;
	for (i = 0 ; i < NUM_ELEM ; i++)
	    cout<<vettore[i]<<" " ;
	cout<<"\n\t1 Cambiamento chiave RSA\n" ;
	cout<<"\t2 Cifratura vettore\n" ;
	cout<<"\t3 Decifratura vettore\n" ;
	cout<<"\t4 Uscita\n" ;
	cout<<"Scelta " ;
	cin>>scelta ;
	
	switch(scelta) {
	case 1:
	    cout<<"Inserisci e " ;
	    cin>>e ;
	    cout<<"Inserisci d " ;
	    cin>>d ;
	    cout<<"Inserisci r " ;
	    cin>>r ;
	    break;
	case 2:
	    cout<<"Attenzione: il vettore non e' stato criptato\n" ;
	    break;
	case 3:
	    cout<<"Attenzione: il vettore non e' stato decriptato\n" ;
	    break;
	case 4:
	    return 0;
	default:
	    cout<<"Scelta non valida\n" ;
	}
    }
    
    return 0;
}
