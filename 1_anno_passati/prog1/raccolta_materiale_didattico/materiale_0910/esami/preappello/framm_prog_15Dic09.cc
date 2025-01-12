#include <iostream>
#include <cstdlib>

using namespace std ;

// ritorna un numero casuale tra 1 e 5
char valore_casuale()
{
    return 1 + static_cast<int>(rand() / 
				(static_cast<double>(static_cast<unsigned int>
						     (RAND_MAX)+1)/5) ) ;
    
}

// ritorna casualmente vero o falso
bool da_corrompere()
{
    if (valore_casuale() > 4)
	return true ;
    return false ;
}

int main()
{
    // inizializzazione seme per le funzioni di servizio
    srand(1) ;

    const char menu[] =
	"1. Reinizializza regione\n"
	"2. Scrivi sequenza di valori\n"
	"3. Stampa contenuto regione\n"
	"4. Salva contenuto regione\n"
	"5. Carica contenuto regione\n"
	"6. Scrivi sequenza valori con somma\n"
	"7. Esci\n" ;
    
    while(true) {
	cout<<menu ;
	int scelta ;
	cin>>scelta ;

	switch(scelta) {
	case 1:{
	    int num_celle ;
	    do {
		cout<<"Nuovo numero di celle? " ;
		cin>>num_celle ;
	    } while (num_celle <= 0 ) ;
	    break ;}
	case 2:{
	    int ind_iniziale ;
	    cout<<"Indirizzo cella da cui iniziare a scrivere? " ;
	    cin>>ind_iniziale ;
	    int num_valori ;
	    cout<<"Numero di valori da scrivere? " ;
	    cin>>num_valori ;
	    int * const valori = new int[num_valori] ;
	    cout<<"Sequenza di valori? " ;
	    for (int i = 0 ; i < num_valori ; i++)
		cin>>valori[i] ;
	    delete[] valori ;
	    break ;}
	case 3:
	    break ;
	case 4:
	    break ;
	case 5:
	    break ;
	case 6:{
	    int num_valori ;
	    cout<<"Numero di valori da scrivere? " ;
	    cin>>num_valori ;
	    int * const valori = new int[num_valori] ;
	    cout<<"Sequenza di valori? " ;
	    for (int i = 0 ; i < num_valori ; i++)
		cin>>valori[i] ;
	    delete[] valori ;
	    break ;}
	case 7:
	    return 0 ;
	default:
	    cout<<"Scelta errata"<<endl ;
	}
    }

    return 0 ;
}
