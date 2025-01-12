#include <iostream>

using namespace std ;

int main()
{
  int scelta ;

  cout<<"1\tOpzione A\n" ;
  cout<<"3\tOpzione B\n" ;
  cout<<"4\tOpzione C\n" ;
  cout<<"5\tOpzione C\n" ;
  cout<<"6\tOpzione D\n" ;
  cout<<"\nScegli un'opzione: " ;

  cin>>scelta ;
  switch(scelta) {
  case 1:
    cout<<"Hai scelto l'opzione A\n" ;
    break ;
  case 3:
    cout<<"Hai scelto l'opzione B\n" ;
    break ;
  case 4:
  case 5:
    cout<<"Hai scelto l'opzione C\n" ;
    break ;
  case 6:
    cout<<"Hai scelto l'opzione D\n" ;
    break ;
  default:
    cout<<"Scelta non valida\n" ;
    break ;
  }

  return 0 ;
}
