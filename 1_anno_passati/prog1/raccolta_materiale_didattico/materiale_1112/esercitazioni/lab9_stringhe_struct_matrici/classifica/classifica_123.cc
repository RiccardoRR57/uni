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

void stampa_primi_tre(const partecipante elenco[], int quanti)
{
    const char *posizione[] = {"Primo", "Secondo", "Terzo" } ;
    if (quanti == 0) {
       cout<<"Non ci sono partecipanti :-(\n" ;
       return ;
    }
    int classificato[3] = {-1, -1, -1 } ; // -1 sta per valore non
					  // significativo
    
    const int posti = quanti < 3 ? quanti : 3 ;
    for (int j = 0 ; j < posti ; j++ ) {
        for (int i = 0 ; i < quanti ; i++) {
            bool coincide = false ;
            /* 
             * se stiamo cercando il primo classificato (j == 0) dobbiamo
             * sicuramente verificare se l'-iesimo partecipante e' quello che
             * ha fatto registrare il tempo minimo;
             * se stiamo cercando il secondo classificato, allora
             * dobbiamo effettuare tale verifica solo se non siamo 
             * cascati sul primo classificato; 
             * se stiamo cercando il terzo classificato, allora
             * obbiamo effettuare tale verifica solo se non siamo 
             * cascati ne sul primo classificato, ne sul secondo 
             */
	        for (int k = j ; k > 0 ; k--) // se j==0 il ciclo non
					      // e' mai eseguito
	                 if (classificato[k - 1] == i)
	                         coincide = true ;

            if ( coincide == false  && 
                 (classificato[j] == -1 || 
                  elenco[i].tempo <= elenco[classificato[j]].tempo)
               )
				        classificato[j] = i ;
        } // fine ciclo di scansione della lista dei partecipanti
        
        int tempo = elenco[classificato[j]].tempo ;
        cout<<posizione[j]<<" classificato:\t" ;
        cout<<elenco[classificato[j]].nominativo<<"\t\t"<<tempo/60<<" min "
	    <<tempo%60 ;
        cout<<" sec \n" ;
    }
		    
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
        cout<<"4 Stampa i primi tre classificati\n" ;
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
                 stampa_primi_tre(elenco, num_iscritti) ;
                 break ;
            case 5:
                 return 0 ;
            default:
                 continue ;
        } // Fine switch
    } // Fine while
    return 0 ;
}

