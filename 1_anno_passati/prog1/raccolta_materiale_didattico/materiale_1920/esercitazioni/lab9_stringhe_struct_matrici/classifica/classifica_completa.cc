#include <iostream>
using namespace std ;

const int MAX_N = 5 ; // Numero massimo di iscritti
const int MAX_L = 40 ; // Lunghezza massima nominativo

struct partecipante {
    char nominativo[MAX_L] ;
    int tempo ;
    int prossimo ;
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

void gara(partecipante elenco[], int num_iscritti, int &primo)
{
    // inizializzazione della classifica immersa nella lista dei partecipanti
    for (int i = 0 ; i < num_iscritti ; i++) 
        /*
         * -1 vuol dire partecipante non ancora inserito nella classifica
         * immersa
         */
        elenco[i].prossimo = -1 ; 
    
    // immissione del tempo di ciascun partecipante
    for (int i = 0 ; i < num_iscritti ; i++) {
        int min, sec ;
        
        cout<<"Tempo di "<<elenco[i].nominativo ;
	    cout<<" (minuti e secondi) ? " ;
        cin>>min ;
        cin>>sec ;
	    elenco[i].tempo = min * 60 + sec ;
    }

    int prec ;
    for (int j = 0 ; j < num_iscritti ; j++) {

        int indice = -1 ; // indice del prossimo classificato
        for (int i = 0 ; i < num_iscritti ; i++) {
            /* 
             * a meno che stia cercando il primo classificato (j == 0),
             * considero solo i partecipanti non ancora inseriti nella
             * classifica (ossia quelli con il campo prossimo settato a -1)
             */
            if ( ( j == 0 || elenco[i].prossimo == -1 ) && 
                (indice == -1 || elenco[i].tempo < elenco[indice].tempo)
               )
                   indice = i ;
        } // fine ricerca del prossimo classificato

        if (j == 0) { // trovato il primo classificato
            prec = primo = indice ;
        } else { // trovato uno dei successivi classificati
           elenco[prec].prossimo = indice ;
           prec = indice ;
        }
        /*
         * metto temporaneamente a zero il campo prossimo per indicare che
         * questo partecipante e' stato gia' inserito nella classifica immersa
         * (e quindi non va piu' considerato per la ricerca del prossimo
         * classificato;
         * il campo sara' settato al valore definitivo non appena trovato
         * il prossimo classificato (nella prossima iterazione)
         */
        elenco[prec].prossimo = 0 ; 

    } // fine ciclo costruzione classifica
}

void stampa_classifica(const partecipante elenco[], int quanti, int primo)
{
    int prossimo = primo ;
    
    if (quanti == 0) {
       cout<<"Non ci sono partecipanti :-(\n" ;
       return ;
    }

    if (primo == -1) {
       cout<<"La gara ancora non c'e' ancora stata :-(\n" ;
       return ;
    }

    cout<<"Classifica:\n" ;
    
    for (int j = 0 ; j < quanti ; j++ ) {
        int tempo = elenco[prossimo].tempo ;
        cout<<elenco[prossimo].nominativo<<"\t\t"<<tempo/60<<" min "
	    <<tempo%60 ;
        cout<<" sec \n" ;
        prossimo = elenco[prossimo].prossimo ;
    }
		    
}

int main()
{
    int scelta ;
    partecipante elenco[MAX_N] ;
    int num_iscritti = 0 ; // Numero attuale di iscritti
    /* 
     * indice del primo classificato (-1 vuol dire che la gara non
     * c'e' ancora stata)
     */
    int primo = -1 ;
    
    while (true) {
        cout<<"Gestione classifica\n" ;
        cout<<"Menu\n" ;
        cout<<"1 Inserimento di un nuovo partecipante\n" ;
        cout<<"2 Stampa elenco partecipanti\n" ;
        cout<<"3 Gara\n" ;
        cout<<"4 Stampa classifica\n" ;
        cout<<"5 Uscita\n" ;
        cin>>scelta ;
        switch(scelta) {
            char nominativo[MAX_L] ;

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
                 gara(elenco, num_iscritti, primo) ;
                 break ;
            case 4:
                 stampa_classifica(elenco, num_iscritti, primo) ;
                 break ;
            case 5:
                 return 0 ;
            default:
                 continue ;
        } // Fine switch
    } // Fine while
    return 0 ;
}
