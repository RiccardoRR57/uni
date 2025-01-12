#include <iostream>

using namespace std;

int main()
{
  int i ;

  cout<<"Inserisci un numero intero diverso da 0: " ;
  cin>>i ;

  /* Attenzione: cosa accadrebbe se i == 0 ? */
  cout<<i / abs(i)<<endl ;

  return 0 ;
}
