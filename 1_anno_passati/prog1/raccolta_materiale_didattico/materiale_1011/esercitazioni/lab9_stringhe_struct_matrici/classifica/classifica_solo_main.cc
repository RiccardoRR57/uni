#include <iostream>
using namespace std ;

int main()
{
    int scelta ;

    while (true) {
        cout<<"Gestione classifica\n" ;
        cout<<"Menu\n" ;
        cout<<"1 Inserimento di un nuovo partecipante\n" ;
        cout<<"2 Stampa elenco partecipanti\n" ;
        cout<<"3 Gara\n" ;
        cout<<"4 Stampa primo classificato\n" ;
        cout<<"5 Uscita\n" ;
        cin>>scelta ;
        switch(scelta) {

            case 1:
                 /*
                  * Le seguenti linee sono solo un suggerimento
                  * su come impostare il codice:
                  *
                  * cout<<"Inserisci nominativo (cognome): " ;
                  * cin>>... ;
                  * if (!ins_elenco(..., ..., ...))
                  *   cout<<"Errore: elenco gia' pieno\n" ;
		  *
		  * Oppure si possono fare stampare i messaggi di errore
		  * direttamente nella funzione ins_elenco
                 */
                 cout<<"Da implementare\n" ;
                 break ;
            case 2:
                 // stampa_elenco(..., ...) ;
                 cout<<"Da implementare\n" ;
                 break ;
            case 3:
                 cout<<"Da implementare\n" ;
                 break ;
            case 4:
                 // stampa_primo(..., ...) ;
                 cout<<"Da implementare\n" ;
                 break ;
            case 5:
                 return 0 ;
            default:
                 continue ;
        } // Fine switch
    } // Fine while
    return 0 ;
}

