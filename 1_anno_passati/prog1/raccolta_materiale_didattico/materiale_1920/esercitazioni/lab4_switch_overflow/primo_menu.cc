#include <iostream>

using namespace std ;

int main()
{
  int scelta ;

  cout<<"1\tOpzione A"<<endl ;
  cout<<"2\tOpzione B"<<endl ;
  cout<<"3\tOpzione C"<<endl ;
  cout<<"4\tOpzione D"<<endl ;
  cout<<"\nScegli un'opzione: " ;
  cin>>scelta ;
  switch(scelta) {
  case 1:
    cout<<"Hai scelto l'opzione A\n" ;
    break ;
  case 2:
    cout<<"Hai scelto l'opzione B\n" ;
    break ;
  case 3:
    cout<<"Hai scelto l'opzione C\n" ;
    break ;
  case 4:
    cout<<"Hai scelto l'opzione D\n" ;
    break ;
  default:
    cout<<"Scelta non valida\n" ;
    break ; // non necessario, ma utile nel caso in futuro si aggiungesse
            // un altro ramo
  }

  return 0 ;
}
