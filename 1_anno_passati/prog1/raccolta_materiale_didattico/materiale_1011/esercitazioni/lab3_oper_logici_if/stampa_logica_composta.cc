#include <iostream>
using namespace std;

main()
{
	int a, b, c ;

	cout<<"Inserisci i valori di a, b e c: " ;
	cin>>a>>b>>c;
	cout<<"Valore di ("
	    <<a<<" < "<<b
	    <<") || ("
	    <<a<<" < "<<c
	    <<"): "
	    <<((a < b) || (a < c))<<endl;
}
