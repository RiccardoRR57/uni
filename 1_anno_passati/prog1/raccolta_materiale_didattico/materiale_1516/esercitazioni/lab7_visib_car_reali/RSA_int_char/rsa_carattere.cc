#include <iostream>

using namespace std ;

int e = 5, d = 173, r = 323; // Chiave cifratura/decifratura

/*
 * versione ricorsiva mostrata per chi conosce l'argomento, altrimenti
 * considerate semplicemente che questa versione e' equivalente a
 * quella iterativa riportata in rsa_intero.cc
 */
int potenza_modulo(int N, int e)
{
    if (e == 0)
       return 1;
    return (N * potenza_modulo(N, e - 1)) % r ;
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
  while (1) {
    int scelta ;
    
    cout<<"\tChiave attualmente in uso: ("<<e<<", "<<d<<", "<<r<<")\n" ;
    cout<<"\n\t1 Cambiamento chiave RSA\n" ;
    cout<<"\t2 Cifratura di un carattere\n" ;
    cout<<"\t3 Decifratura di un carattere\n" ;
    cout<<"\t4 Uscita\n" ;
    cout<<"Scelta " ;
    cin>>scelta ;
    
    switch(scelta) {
      
      char c;
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
      cout<<"Inserisci il carattere da cifrare " ;
      cin>>c ;
      cout<<"Il carattere cifrato vale "<<cifra(c, e)<<"\n\n"  ;
      break;
    case 3:
      cout<<"Inserisci il numero da decifrare come carattere " ;
      cin>>N ;
      cout<<"Il carattere decifrato e' "<<static_cast<char>(cifra(N, d))
	  <<"\n\n"  ;
      break;
    case 4:
      return 0;
    default:
      cout<<"Scelta non valida\n" ;
    }
  }
  
  return 0;
}
