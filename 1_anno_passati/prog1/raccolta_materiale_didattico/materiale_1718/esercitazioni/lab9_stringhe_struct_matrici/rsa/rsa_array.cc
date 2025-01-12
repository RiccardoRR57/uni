#include <iostream>

using namespace std ;

int e = 5, d = 173, r = 323; // Chiave cifratura/decifratura

int potenza_modulo(int N, int e)
{
  int ris = 1 ;
  for ( ; e > 0 ; e--)
    ris = (ris * N) % r ;
  return ris ;
}

int cifra(int N, int e)
{
    if (N <= 0 || N >= r) {
	    cout<<"Errore: il numero da criptare "
		<<"e' fuori dall'intervallo consentito\n" ;
       exit(1) ;
    }
    return potenza_modulo(N, e);
}

int main()
{
    const int NUM_ELEM = 5 ;
    int vettore[5] = {1, 2, 3, 4, 5} ;

    while (1) {
        int scelta ;

	cout<<"\tChiave attualmente in uso: ("<<e<<", "<<d<<", "<<r<<")\n" ;
	cout<<"\tContenuto attuale del vettore: " ;
	for (int i = 0 ; i < NUM_ELEM ; i++)
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
	    for (int i = 0 ; i < NUM_ELEM ; i++)
		vettore[i] = cifra(vettore[i], e) ;
	    cout<<"Il vettore e' stato criptato\n" ;
	    break;
	case 3:
	    for (int i = 0 ; i < NUM_ELEM ; i++)
		vettore[i] = cifra(vettore[i], d) ;
	    cout<<"Il vettore e' stato decriptato\n" ;
	    break;
	case 4:
	    return 0;
	default:
	    cout<<"Scelta non valida\n" ;
	}
    }
    
    return 0;
}
