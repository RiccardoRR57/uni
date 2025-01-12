#include <iostream>

using namespace std ;

int main()
{
  int scelta ;

  cout<<"1\tOpzione A"<<endl ;
  cout<<"3\tOpzione B"<<endl ;
  cout<<"4\tOpzione C"<<endl ;
  cout<<"5\tOpzione C"<<endl ;
  cout<<"6\tOpzione D"<<endl ;
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
