#include <iostream>
#include <fstream>

using namespace std ;


int main()
{
  const char menu[] =
    "1. Disegna punto\n"
    "2. Stampa matrice\n"
    "3. Salva matrice\n"
    "4. Carica matrice\n"
    "5. Disegna rettangolo\n"
    "6. Disegna rettangolo 2\n"
    "7. Esci\n";

  while(true) {
    cout<<menu<<endl ;

    int scelta ;
    cin>>scelta ;

    switch(scelta) {
    case 1: {
      int riga, col ;
      cout<<"Inserire indice riga ed indice colonna: " ;
      cin>>riga>>col ;
      break;}
    case 2:
      break ;
    case 3:
      break ;
    case 4:
      break ;
    case 5:{
      int riga, col, lar, alt ;
      cout<<"Inserire indice riga, indice colonna, base ed altezza: " ;
      cin>>riga>>col>>lar>>alt ;
      break;}
    case 6:{
      int riga, col, lar, alt ;
      cout<<"Inserire indice riga, indice colonna, base ed altezza: " ;
      cin>>riga>>col>>lar>>alt ;
      break;}
    case 7:
      return 0 ;
    default :
      cout<<"Scelta errata"<<endl ;
    }
  }

}
