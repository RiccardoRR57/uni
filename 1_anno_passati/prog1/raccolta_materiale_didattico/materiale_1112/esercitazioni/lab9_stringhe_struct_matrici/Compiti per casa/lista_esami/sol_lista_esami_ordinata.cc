#include <iostream>

using namespace std ;

const int MAX_N = 5 ; // Numero massimo di iscritti
const int MAX_L = 40 ; // Lunghezza massima dei nominativi

// Ritorna 0 se e solo se fallisce. NON INCREMENTA quanti
int ins_elenco(char elenco[][MAX_L], char *nominativo, int quanti)
{
    int i, j ;

    if (quanti == MAX_N)
        return 0 ;
    /*
     * Cerco il primo nominativo nell'elenco che deve seguire
     * (in base all'ordinamento alfabetico) il nuovo nominativo
     * da inserire
     */
    for (i = 0 ; i < quanti && strcmp(nominativo, elenco[i]) > 0 ; i++) 
        ;

    /*
     * Sposto in basso di una posizione tutti i partecipanti con nominativo 
     * alfabeticamente successivo a quello del nuovo partecipante
     * In questo modo creo un 'buco' nella classifica
     * in cui potro' copiare il nominativo del nuovo partecipante
     */
    for (j = quanti ; j > i  ; j--)
	   strcpy(elenco[j], elenco[j-1]) ;
    strcpy(elenco[i], nominativo) ;
    
    return 1 ;
}

void stampa_elenco(char elenco[][MAX_L], int quanti)
{
    int i ;
    cout<<"\nNumero partecipanti: "<<quanti<<endl ;
    if (quanti == 0)
       return ;
    cout<<"Elenco partecipanti:\n" ;
    for (i = 0 ; i < quanti ; i++)
        cout<<elenco[i]<<endl ;
}

int main()
{
    int scelta ;
    char elenco[MAX_N][MAX_L] ;
    int num_iscritti = 0 ; // Numero attuale di iscritti

    while (1) {
	char nominativo[MAX_L] ;

        cout<<"\nGestione lista esami\n" ;
        cout<<"Menu\n" ;
        cout<<"1 Inserimento di un nuovo studente\n" ;
        cout<<"2 Stampa iscritti\n" ;
        cout<<"3 Uscita\n" ;
        cin>>scelta ;
        switch(scelta) {
            case 1:
                 cout<<"Inserisci nominativo: " ;
                 cin>>nominativo ;
                 if (!ins_elenco(elenco, nominativo, num_iscritti))
                     cout<<"Errore: elenco gia' pieno\n" ;
		 else 
		     num_iscritti++ ;
                 break ;
            case 2:
                 stampa_elenco(elenco, num_iscritti) ;
                 break ;
           case 3:
                 return 0 ;
           default:
	       cout<<"Valore errato\n" ;
	       continue ;
        } // Fine switch
    } // Fine while
    return 0 ;
}
