#include <iostream>
using namespace std ;

int main()
{  
	const int max_M = 100 ;
	double vett_temper[max_M];
	double media=0.;

	cout<<"Inserire i valori (immettere un valore negativo per terminare)"
	    <<endl ;
	for (int i = 0; i < max_M; i++) {
	    cin>>vett_temper[i];
	    if (vett_temper[i] < 0) {
		vett_temper[i] = -1 ; // inseriamo il terminatore
		break ;
	    }
	}
	/*
	 * Nota: se abbiamo inserito max_M valori non vi sarà alcun
	 * terminatore!
	 */

	int num_val_letti ; // in uscita dal ciclo conterra' il numero
			    // di valori letti
	for (num_val_letti = 0; num_val_letti < max_M &&
		     vett_temper[num_val_letti] >= 0
		     ; num_val_letti++)
		media += vett_temper[num_val_letti];

	media /= num_val_letti ;

	cout<<"Media: "<<media<<endl<<endl ;

	cout<<"Valori superiori alla media:"<<endl ;
	for (int i = 0 ; i < max_M && vett_temper[i] > 0 ; i++)
	    if (vett_temper[i] > media)
		cout<<vett_temper[i]<<endl ;

	return 0 ;

} 
