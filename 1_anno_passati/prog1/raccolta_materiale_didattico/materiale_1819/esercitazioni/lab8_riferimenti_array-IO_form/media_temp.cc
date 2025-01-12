#include <iostream>
using namespace std ;

int main()
{  
	const int max_M = 100 ; // dimensioni array statico
	int M; // numero di elementi del vettore dinamico
	double vett_temper[max_M]; // array statico
	double media = 0.;

	do  cin>>M;  while ((M<=0) || (M>max_M));

	for (int i=0; i<M; i++)
		do  cin>>vett_temper[i];  while (vett_temper[i]<0);

	// questo ciclo si poteva immergere nel precedente
	for (int i=0; i<M; i++)
		media += vett_temper[i];

	media /= M ;

	cout<<"Media: "<<media<<endl<<endl ;
	cout<<"Valori superiori alla media:"<<endl ;
	for (int i = 0 ; i < M ; i++)
	    if (vett_temper[i] > media)
		cout<<vett_temper[i]<<endl ;

	return 0 ;
}
