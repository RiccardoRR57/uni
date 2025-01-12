#include <iostream>
using namespace std;

main()
{
	int a, b, x ;

	cout<<"Inserisci i valori di a, b e x: " ;
	cin>>a>>b>>x;
	cout<<"Valore di ("
	    <<a<<" <= "<<x<<" <= "<<b
	    <<"): "
	    <<( (a <= x) && (x <= b) )<<endl;
}
