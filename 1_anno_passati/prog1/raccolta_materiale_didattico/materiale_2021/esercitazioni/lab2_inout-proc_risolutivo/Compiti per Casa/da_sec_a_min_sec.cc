#include <iostream>

using namespace std;

int main()
{
  int sec, min ;

  cout<<"Tempo in secondi? " ;
  cin>>sec ;
  min = sec / 60 ;
  sec = sec % 60 ;

  cout<<"Equivalgono a "<<min<<" min, "<<sec<<" sec"<<endl ;

  return 0 ;
}
