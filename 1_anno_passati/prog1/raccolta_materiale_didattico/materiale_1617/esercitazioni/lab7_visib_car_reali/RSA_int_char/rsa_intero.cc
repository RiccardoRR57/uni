#include <iostream>

using namespace std ;

int e = 5, d = 173, r = 323; // Chiave cifratura/decifratura

int potenza_modulo(int N, int e)
{
  int ris = 1 ;
  for ( ; e > 0 ; e--) // risparmiata una variabile locale, ma uso
		       // poco leggibile di un parametro in ingresso
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
  while (true) {
    int scelta ;
    
    cout<<"\tChiave attualmente in uso: ("<<e<<", "<<d<<", "<<r<<")\n" ;
    cout<<"\n\t1 Cambiamento chiave RSA\n" ;
    cout<<"\t2 Cifratura di un numero\n" ;
    cout<<"\t3 Decifratura di un numero\n" ;
    cout<<"\t4 Uscita\n" ;
    cout<<"Scelta " ;
    cin>>scelta ;
    
    switch(scelta) {
      
      int N;
      
    case 1:
      cout<<"Inserisci e " ;
      cin>>e ;
      cout<<"Inserisci d " ;
      cin>>d ;
      cout<<"Inserisci r " ;
      cin>>r ;
      break;
    case 2:
      cout<<"Inserisci il numero da cifrare " ;
      cin>>N ;
      cout<<"Il numero cifrato e' "<< cifra(N, e)<<"\n\n" ;
      break;
    case 3:
      cout<<"Inserisci il numero da decifrare " ;
      cin>>N ;
      cout<<"Il numero decifrato e' "<<cifra(N, d)<<"\n\n" ;
      break;
    case 4:
      return 0;
    default:
      cout<<"Scelta non valida\n" ;
    }
  }
  
  return 0;
}
