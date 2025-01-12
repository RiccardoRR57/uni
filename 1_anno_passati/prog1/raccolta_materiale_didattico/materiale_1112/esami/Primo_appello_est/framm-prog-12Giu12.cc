#include <iostream>
#include <stdlib.h>

using namespace std ;

int main()
{
  const char menu[] =
    "1. Crea nuova sequenza\n"
    "2. Stampa sequenza\n"
    "3. Salva sequenza\n"
    "4. Carica sequenza\n"
    "5. Stampa sequenza 2\n"
    "6. Stampa sotto-sequenze crescenti\n"
    "8. Esci\n";

  while(true) {
    cout<<menu<<endl ;

    int scelta ;
    cin>>scelta ;
    switch(scelta) {
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
    case 8:
      return 0 ;
    default:
      cout<<"Scelta errata"<<endl ;
    }
  }
  return 1 ;
}
