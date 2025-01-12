#include <iostream>
using namespace std;

int main()
{
  int i, j ;
  cout<<"Inserisci due numeri interi: " ;
  cin>>i>>j ;
    
  cout<<"Il massimo tra "<<i<<" e "<<j<<" è " ;
  if (i > j)
	  cout<<i ;
  else
	  cout<<j ;
  cout<<endl ;

  return 0 ;
}
