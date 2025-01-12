#include <iostream>
using namespace std;

int main()
{
  int sec, min ;

  cout<<"Minuti ? " ;
  cin>>min ;
  
  cout<<"Secondi ? " ;
  cin>>sec ;
  
  cout<<"Equivalgono a "<<min * 60 + sec<<" secondi"<<endl ;

  return 0 ;
}
