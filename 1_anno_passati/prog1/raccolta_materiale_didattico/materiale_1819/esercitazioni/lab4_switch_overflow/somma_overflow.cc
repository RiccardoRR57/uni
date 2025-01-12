#include <iostream>

using namespace std ;

int main()
{
	int a, b ;
	const int MAXINT = 2147483647 ;
	const int MININT = -MAXINT -1 ;

	cout<<"Inserisci i due numeri da sommare: " ;
	cin>>a>>b ;
        cout<<a<<" + "<<b<<" = "<<a+b<<endl ;

	if ((a > 0 && b < 0) 
	    || 
	    (a < 0 && b > 0) ) /* se sono di segno opposto non c'è problema */
	  return 0 ; // il programma termina qui
	  
        if ( (a > 0 && b > MAXINT - a) || (a < 0 && b < (MININT - a)))
            cout<<"Attenzione: c'e' stato overflow\n" ; 
   
	return 0 ;
}
