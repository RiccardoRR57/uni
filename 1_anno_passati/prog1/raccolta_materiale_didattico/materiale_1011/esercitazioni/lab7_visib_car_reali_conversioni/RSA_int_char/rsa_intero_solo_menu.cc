#include <iostream>

using namespace std ;

int cifra(int N, int e, int r)
{
    cout<<"Attenzione: funzione non ancora impelementata!!!\n" ;
    cout<<"Ritorno 0\n" ;
    return 0;
}

int main()
{
  int e = 5, d = 173, r = 323; // Chiave cifratura/decifratura
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
      cout<<"Il numero cifrato e' "<<cifra(N, e , r)<<"\n\n" ;
      break;
    case 3:
      cout<<"Inserisci il numero da decifrare " ;
      cin>>N ;
      cout<<"Il numero decifrato e' "<< cifra(N, d, r)<<"\n\n" ;
      break;
    case 4:
      return 0;
    default:
      cout<<"Scelta non valida\n" ;
    }
  }
  
  return 0;
}
