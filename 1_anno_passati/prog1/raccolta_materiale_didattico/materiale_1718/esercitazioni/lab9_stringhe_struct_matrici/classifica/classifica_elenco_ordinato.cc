#include <iostream>
using namespace std ;

const int MAX_N = 5 ; // Numero massimo di iscritti
const int MAX_L = 40 ; // Lunghezza massima nominativo

struct partecipante {
    char nominativo[MAX_L] ;
    int tempo ;
} ;

bool ins_elenco(partecipante elenco[], const char nominativo[], int &quanti)
{
    int i ;

    if (quanti == MAX_N)
        return false ;
    /*
     * Cerco il primo nominativo nell'elenco che deve seguire
     * (in base all'ordinamento alfabetico) il nuovo nominativo
     * da inserire
     */
    for (i = 0 ; i < quanti && strcmp(nominativo, elenco[i].nominativo) > 0 ;
    	 i++) 
	    	 ;
    /*
     * Sposto in basso di una posizione tutti i partecipanti con nominativo 
     * alfabeticamente successivo a quello del nuovo partecipante
     * In questo modo creo un 'buco' nella classifica
     * in cui potro' copiare il nominativo del nuovo partecipante
     */
    for (int j = quanti ; j > i  ; j--)
	   elenco[j] = elenco[j-1] ;
    strcpy(elenco[i].nominativo, nominativo) ;
    
    quanti++ ;
    return true ;
}

void stampa_elenco(const partecipante elenco[], int quanti)
{
    cout<<"\nNumero partecipanti: "<<quanti<<'\n' ;
    if (quanti == 0)
       return ;
    cout<<"Elenco partecipanti:\n" ;
    for (int i = 0 ; i < quanti ; i++)
        cout<<elenco[i].nominativo<<'\n' ;

}

void stampa_primo(const partecipante elenco[], int quanti)
{
     if (quanti == 0) {
       cout<<"Non ci sono partecipanti :-(\n" ;
       return ;
    }
    // alla fine della ricerca la seguente variabile conterra' l'indice
    // del primo classificato nell'elenco dei partecipanti
    int vincitore = 0 ; // inizializzo con l'indice del primo partecipante
    for (int i = 1 ; i < quanti ; i++) {
	    if (elenco[i].tempo <= elenco[vincitore].tempo)
	         // l'i-esimo partecipante ha fatto un tempo migliore di quello 
             // a cui punta attualmente la variabile vincitore:
             vincitore = i ; // aggiorno la variabile vincitore di conseguenza
    }		
    int tempo = elenco[vincitore].tempo ;
    cout<<"Primo classificato: " ;
    cout<<elenco[vincitore].nominativo<<"\t\t"<<tempo/60<<" min "<<tempo%60 ;
    cout<<" sec \n" ;
		    
}

int main()
{
    int scelta ;
    partecipante elenco[MAX_N] ;
    int num_iscritti = 0 ; // Numero attuale di iscritti

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
            char nominativo[MAX_L] ;
	    int min, sec ;

            case 1:
                 cout<<"Inserisci nominativo: " ;
                 cin>>nominativo ;
                 if (!ins_elenco(elenco, nominativo, num_iscritti))
                     cout<<"Errore: elenco gia' pieno\n" ;
                 break ;
            case 2:
                 stampa_elenco(elenco, num_iscritti) ;
                 break ;
            case 3:
                 for (int i = 0 ; i < num_iscritti ; i++) {
                     cout<<"Tempo di "<<elenco[i].nominativo ;
		     cout<<" (minuti e secondi) ? " ;
                     cin>>min ;
                     cin>>sec ;
		     elenco[i].tempo = min * 60 + sec ;
                 }
                 break ;
            case 4:
                 stampa_primo(elenco, num_iscritti) ;
                 break ;
            case 5:
                 return 0 ;
            default:
                 continue ;
        } // Fine switch
    } // Fine while
    return 0 ;
}
