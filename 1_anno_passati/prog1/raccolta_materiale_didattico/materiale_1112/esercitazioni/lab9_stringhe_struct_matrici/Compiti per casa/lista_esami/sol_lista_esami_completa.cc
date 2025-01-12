#include <iostream>

using namespace std ;

const int MAX_N = 5 ; // Numero massimo di iscritti
const int MAX_L = 40 ; // Lunghezza massima nominativo

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

// Ritorna 0 se e solo se fallisce. NON DECREMENTA quanti
int estrai_da_elenco(char elenco[][MAX_L], char *nominativo, int quanti)
{
     int i, j ;
     // cerco l'elemento da eliminare
     for (i = 0 ; i < quanti && strcmp(nominativo, elenco[i]) > 0 ; i++)
          ;
     // posso fallire per due motivi
     // 1 l'elenco contiene solo nominativi che precedono (alfabeticamente)
     //   quello che voglio eliminare => arrivo in fondo all'array => in uscita
     //   dal ciclo i == quanti
     // 2 l'elenco non contiene il nominativo che cerco, ma contiene anche
     //   nominativi che lo seguono (alfabeticamente)
     if (i == quanti || strcmp(elenco[i], nominativo) != 0)
        return 0 ;
     for (j = i ; j < quanti - 1 ; j++)
	   strcpy(elenco[j], elenco[j+1]) ;
     return 1 ;
}


/* 
 * Converte una stringa alfabetica nel formato
 * Prima lettera maiuscola
 * Tutte le lettere successive minuscole
 */
void converti(char nome[])
{
    nome[0] = toupper(nome[0]) ;
    for (unsigned i = 1 ; i < strlen(nome) ; i++)
	nome[i] = tolower(nome[i]) ;
}

/*
 * Legge da tastiera due stringhe: nome e cognome.
 * Copia il cognome in nominativo, inserisce uno spazio ed aggiunge
 * il nome
 */

void leggi_nominativo(char nominativo[])
{
    int OK = 0 ;

    do {
	char nome [MAX_L] ;
	char cognome [MAX_L] ;

	cout<<"Nome studente ? " ;
	cin>>nome ;
	cout<<"Cognome studente ? " ;
	cin>>cognome ;
	/*
	 * Il motivo del valore MAX_L - 2 e' il seguente: la lunghezza massima
	 * che abbiamo stabilito per gli array di caratteri e' MAX_L, cio'
	 * implica che la lunghezza massima delle stringhe rappresentabili
	 * e' MAX_L - 1, perche' abbiamo bisogno di un elemento per 
	 * memorizzarvi il carattere nullo '\0' che fa da terminatore alla
	 * stringa. Inoltre nel nominativo dobbiamo anche inserire uno spazio
	 * tra il cognome ed il nome.
	 */
	if (strlen(nome) + strlen(cognome) > MAX_L - 2) {
	    cout<<"Errore: stringhe inserite troppo lunghe.\n" ;
	    continue ;
	}
	// Convertiamo il nome ed il cognome nel formato corretto
	converti(nome) ;
	converti(cognome) ;
	// Copiamo il cognome nel nominativo
	strcpy(nominativo, cognome) ;
	/*
	 * Ora dobbiamo inserire uno spazio subito dopo il cognome. Inserendo
	 * lo spazio subito dopo l'ultimo carattere del cognome andiamo a 
	 * sovrascrivere il carattere nullo. La stringa si allunga pertanto di
	 * un carattere (lo spazio). Il problema e' che nessuno ci assicura
	 * che, dopo lo spazio, nell'array vi sia un valore nullo, pertanto
	 * lo inseriamo da noi
	 */
	nominativo[strlen(nominativo) + 1] = '\0' ; // Carattere nullo in fondo
	nominativo[strlen(nominativo)] = ' ' ; 
	// Ora posso agiungere il nome in fondo al nominativo costruito finora
	strcat(nominativo, nome) ;
	OK = 1 ;
    } while (!OK) ; // Se tutto e' andato bene finisco, altrimenti ricomincio
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
        cout<<"2 Eliminazione (non fisica) di un iscritto\n" ;
        cout<<"3 Stampa iscritti\n" ;
        cout<<"4 Uscita\n" ;
        cin>>scelta ;

        switch(scelta) {
            case 1:
                 leggi_nominativo(nominativo) ;
                 if (!ins_elenco(elenco, nominativo, num_iscritti))
                      cout<<"Errore: elenco gia' pieno\n" ;
		 else 
		     num_iscritti++ ;
                  break ;
            case 2:
                 leggi_nominativo(nominativo) ;
                 if (!estrai_da_elenco(elenco, nominativo, num_iscritti))
                     cout<<"Errore: nominativo non trovato o elenco vuoto\n" ;
                 else {
                     cout<<nominativo<<" correttamente eliminato\n" ;
		     num_iscritti-- ;
		 }
                 break ;
            case 3:
                 stampa_elenco(elenco, num_iscritti) ;
                 break ;
            case 4:
                 return 0 ;
            default:
                 continue ;
        } // Fine switch
    } // Fine while
    return 0 ;
}
