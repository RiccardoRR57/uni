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
       printf("Errore: il numero da criptare "
             "e' fuori dall'intervallo consentito\n") ;
       exit(1) ;
    }
    return potenza_modulo(N, e);
}

int main()
{
    int MAX_ELEM = 1024 ;
    char *messaggio = "Miracles happen to those who believe in them";
    int vettore[MAX_ELEM] ;
    int i ;
    // copiamo la stringa in un vettore di interi
    for (i = 0 ; messaggio[i] != '\0' ; i++)
        vettore[i] = messaggio[i] ;
    vettore[i] = '\0' ; // terminiamo manualmente la stringa
    while (1) {
        int scelta ;

	cout<<"\tChiave attualmente in uso: ("<<e<<", "<<d<<", "<<r<<")\n" ;
	cout<<"\tMessaggio attuale: " ;
	for (int i = 0 ; vettore[i] != 0 ; i++)
	    cout<<static_cast<char>(vettore[i]) ;
	cout<<"\n\t1 Cambiamento chiave RSA\n" ;
	cout<<"\t2 Cifratura messaggio\n" ;
	cout<<"\t3 Decifratura messaggio\n" ;
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
	    for (int i = 0 ; vettore[i] != 0 ; i++)
		vettore[i] = cifra(vettore[i], e) ;
	    cout<<"Il messaggio e' stato criptato\n" ;
	    break;
	case 3:
	    for (int i = 0 ; vettore[i] != 0  ; i++) 
		vettore[i] = cifra(vettore[i], d) ;
	    cout<<"Il messaggio e' stato decriptato\n" ;
	    break;
	case 4:
	    return 0;
	default:
	    cout<<"Scelta non valida\n" ;
	}
    }
    
    return 0;
}
