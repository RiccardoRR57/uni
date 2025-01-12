#include <iostream>
using namespace std ;

main()
{   
     int max, pos_max;
     const int N = 10 ;
     int vettore[N];

     /* il vettore viene inizializzato in qualche modo con N
     elementi inseriti dalla posizione 0 alla posizione N-1. Es.
     vettore[0]=4; vettore[1]=-3;... */
     for (int i=0; i<N; i++)
	     cin>>vettore[i] ;

     max=vettore[0]; pos_max = 0;
     for (int i=1; i<N; i++)
	     if (vettore[i]>max) { max=vettore[i]; pos_max = i;}
     cout<<"Il massimo del vettore è "<<max<<", in posizione "<<pos_max<<endl;
}
