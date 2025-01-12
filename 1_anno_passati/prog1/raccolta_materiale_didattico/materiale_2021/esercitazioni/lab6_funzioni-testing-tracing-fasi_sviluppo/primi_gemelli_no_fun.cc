#include <iostream>
#include <cmath>
using namespace std ;

int main()
{
    int n1, n2 ; cin>>n1>>n2 ;
    bool n1_is_prime = false,
		     n2_is_prime = false ;
    if (n1>=1 && n1<=3) n1_is_prime = true ;
    else if (n1%2 != 0) {
	int i, max_div = static_cast<int>(sqrt(n1));
	for(i=3; i<=max_div; i=i+2)			
	    if (n1%i==0) break ;
	if (i > max_div)
	    n1_is_prime=true ;
    }
    if (n2>=1 && n2<=3) n2_is_prime = true ;
    else if (n1%2 != 0) {
	int i, max_div = static_cast<int>(sqrt(n2));
	for(i=3; i<=max_div; i=i+2)			
	    if (n2%i==0) break ;
	if (i > max_div)
	    n2_is_prime=true ;
    }
    if (n1_is_prime && n2_is_prime)
	if (n1 == n2 - 2 || n2 == n1 - 2)
	    cout<<"n1 ed n2 sono due primi gemelli"<<endl ;
    
    return 0 ;

}
