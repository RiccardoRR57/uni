#include <iostream>

using namespace std ;

main()
{
  int i ;
  do {
    cout<<"Inserisci un numero intero positivo: "  ;
    cin>>i ;
    if (i < 0)
      cout<<"Attenzione: il numero inserito è negativo\n" ;
  } while (i < 0) ;
  cout<<"In base 16: "<<hex<<i<<endl ;
}
