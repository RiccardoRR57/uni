#include <iostream>

using namespace std ;

const int MAX_N = 5 ; // Numero massimo di iscritti

// Lunghezza massima dei nominativi
const int MAX_L = 40 ;

struct partecipante {
    char nominativo[MAX_L] ;
    int tempo ;
} ;

// ritorna il nuovo numero di iscritti
// si poteva equivalentemente passare quanti per riferimento e sfruttare
// il valore di ritorno per fornire una indicazione di successo/fallimento
int ins_elenco(partecipante elenco[], char nominativo[], int quanti,
	       int max)
{
    if (quanti == max) { // elenco pieno
	cout<<"Errore: elenco gia' pieno\n" ;
        return quanti ;
    }
    strcpy(elenco[quanti].nominativo, nominativo) ;
    quanti++ ;
    return quanti ;
}

void stampa_elenco(const partecipante elenco[], int quanti)
{
    int i ;
    cout<<"\nNumero partecipanti: "<<quanti<<endl ;
    if (quanti == 0)
       return ;
    cout<<"Elenco partecipanti:\n" ;
    for (i = 0 ; i < quanti ; i++)
       cout<<elenco[i].nominativo<<endl ;
}

int main()
{
    int scelta ;
    partecipante elenco[MAX_N] ;
	// mediante il seguente contatore si implementa il vettore dinamico di iscritti
    int num_iscritti = 0 ; // Numero attuale di iscritti
	
	/*
	  * In merito al vettore dinamico elenco, sarebbe stato meglio dichiarare
	  * un ulteriore tipo struct contenente sia l'array che il contatore,
	  * ma per il momento non lo facciamo, per mantenere più semplice la
	  * notazione in questo primo esercizio sugli array di struct
	  */

    while (true) {
        char nominativo[MAX_L] ;

        cout<<"\nGestione classifica\n" ;
        cout<<"Menu\n" ;
        cout<<"1 Inserimento di un nuovo partecipante\n" ;
        cout<<"2 Stampa elenco partecipanti\n" ;
        cout<<"3 Uscita\n" ;
        cin>>scelta ;
        switch(scelta) {
            case 1:
                 cout<<"Inserisci nominativo: " ;
                 cin>>nominativo ;
                 num_iscritti = ins_elenco(elenco, nominativo, 
					   num_iscritti, MAX_N) ;
                 break ;
            case 2:
                 stampa_elenco(elenco, num_iscritti) ;
                 break ;
            case 3:
                 return 0 ;
            default:
                 continue ;
        } // Fine switch
    } // Fine while
    return 0 ;
}
