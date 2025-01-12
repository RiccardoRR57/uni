#include <iostream>
using namespace std ;

main()
{  
    const int max_M = 5 ;
    int vett_uno[max_M] = { 100, 3, 200, 0, 300 } ;
    int vett_due[max_M];
    
    int conta=0;
    for (int i=0; i<max_M && vett_uno[i] != 0 ; i++)
      if (vett_uno[i]>=10 && vett_uno[i]<=500) {  
	      vett_due[conta]=vett_uno[i];
	      conta++;
      }
    if (conta < max_M) // altrimenti scriviamo "fuori"
	    vett_due[conta] = 0;
    cout<<"Sono stati copiati "<<conta<<" elementi"<<endl;
} 
