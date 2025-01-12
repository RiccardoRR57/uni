#include <iostream>
using namespace std ;

int main()
{
    const int indice_server1 = 1 ; // num. da stampare se si sceglie il server 1
    const int indice_server2 = 2 ; // num. da stampare se si sceglie il server 2

    const int tempo_veloce_server1 = 3600 ; // per quanti secondi va veloce
    const int velocita_alta_server1 = 200 ; // KB/sec
    const int velocita_bassa_server1 = 50 ; // KB/sec
    const int velocita_server2 = 100 ; // KB/sec
    const int lungh_trasf_veloce = 
	tempo_veloce_server1 * velocita_alta_server1; // quanti byte
						      // sono
						      // trasferiti
						      // prima che la
						      // velocità alta
						      // finisca
    
    int lungh_film ; // in KB
    cout<<"Lunghezza film (KB)? " ;
    cin>>lungh_film ;

    int tempo_minimo, indice_server_da_usare ;
    if (lungh_trasf_veloce >= lungh_film) {
	tempo_minimo = lungh_film / velocita_alta_server1 ;
	indice_server_da_usare = indice_server1 ;
    } else {
	// calcolo tempo per il primo server
	int lungh_residua = lungh_film - lungh_trasf_veloce ;
	// per risparmiare una variabile e non replicare il codice
	// provo ad assegnare il tempo del server1 al tempo minimo
	// (non mi definisco cioe' una ulteriore variabile tempo_server1)
	tempo_minimo = tempo_veloce_server1 +
	    lungh_residua / velocita_bassa_server1 ;

	// calcolo tempo per il secondo server
	int tempo_server2 = lungh_film / velocita_server2 ;

	if (tempo_minimo < tempo_server2)
	    indice_server_da_usare = indice_server1 ;
	else {
	    tempo_minimo = tempo_server2 ;
	    indice_server_da_usare = indice_server2 ;
	}
    }

    cout<<"Tempo minimo: "<<tempo_minimo/60<<" min "<<tempo_minimo%60<<" sec, "
	<<"usando il server "<<indice_server_da_usare<<endl ;
    return 0 ;
}
