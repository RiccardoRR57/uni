/*
 * Realizzare una variante del gioco verbosity in cui due squadre A e
 * B, di almeno due giocatori ciascuna, si alternano nel pensare ad
 * una parola segreta o nell'indovinare la parola segreta pensata
 * dall'altra squadra. Per parola si intende una sequenza di caratteri
 * non separati da spazi.
 *
 * Supponiamo che tocchi dapprima alla squadra A pensare alla parola
 * segreta: i giocatori della squadra hanno due minuti a disposizione
 * per decidere la parola segreta e scriverla in un file di testo. Nel
 * frattempo la squadra B decide quali dei propri giocatori si
 * occuperanno di indovinare la parola segreta, chiamiamoli la
 * (sotto)squadra B1, e quali giocatori, chiamiamoli la (sotto)squadra
 * B2, leggeranno subito la parola segreta ed avranno il compito di
 * scrivere piu' indizi possibili per aiutare i compagni ad indovinare
 * la parola segreta.
 *
 * In particolare, la squadra A ha due minuti per pensare alla parola
 * segreta e scriverla nel file, dopodiché la squadra B1 ha due minuti
 * di tempo per scrivere, nello stesso file, e di seguito alla parola
 * segreta, tutti gli indizi a cui riesce a pensare. Per esempio, se
 * la squadra A avesse pensato alla parola albero, e la squadra B1
 * agli indizi fusto, foglie e radici, allora il contenuto finale del
 * file sarebbe:
 *
 * albero
 * fusto
 * foglie
 * radici
 *
 * Una volta compilato il file, si fa partire il programma del gioco,
 * che legge il file e mostra alla squadra B1 solo gli indizi ed il
 * punteggio iniziale (50 punti). Il programma chiede ripetutamente di
 * immettere la parola segreta, finche' non viene indovinata. Ogni
 * volta che si immette una parola tentativo sbagliata si perde un
 * punto. La squadra B1 ha due minuti di tempo per indovinare la
 * parola segreta, altrimenti perde e le viene assegnato un punteggio
 * di -10. Il tempo trascorso non e' controllato dal programma, ma dai
 * giocatori stessi.
 *
 * Come aiuto, ogni volta che viene immessa una parola tentativo
 * sbagliata il programma mostra quali lettere della parola immessa
 * appaiono NELLO STESSO ORDINE nella parola segreta. Se la parola
 * segreta fosse albero, seguono alcuni esempi di quali lettere
 * verrebbero ristampate dal programma in funzione della parola
 * tentativo immessa:
 *
 * pianta -> a
 * platano -> lo
 * ulivo -> lo
 * arbusto -> arbo
 *
 * In altri termini, data ciascuna lettera della parola tentativo, il
 * programma cerca tale lettera nella parola segreta; ma non la cerca
 * partire dall'inizio della parola segreta, bensi' a partire dalla
 * posizione, nella parola segreta, in cui era stata eventualmente
 * trovata la precedente lettera. Ovviamente, finché non e' ancora
 * stata trovata nessuna lettera a comune, la ricerca inizia sempre
 * dall'inizio della parola segreta. Per esempio, quando si immette
 * platano, si controlla se ciascuna lettera della parola tentativo
 * appare in albero e si scopre che che c'e' la l. Da quel momento in
 * poi, ciascuna delle successive lettere di platano, ossia 'a', 't',
 * 'a', 'n', ed 'o', non verranno cercate in tutta la stringa albero,
 * ma nella sottostringa bero.
 *
 * Una volta indovinata la parola segreta o scaduto il tempo, le
 * squadre si invertono. Supponendo che prima di iniziare il gioco le
 * squadre abbiano deciso il numero totale di parole segrete da
 * indovinare (e quindi il numero totale di turni di gioco), vince la
 * squadra che alla fine di tutti i turni ha totalizzato il punteggio
 * piu' alto.
 *
 * --------------------
 *
 * Realizzare il programma di supporto del gioco precedentemente
 * descritto. In aggiunta alle specifiche fornite finora, il programma
 * deve salvare separatamente la parola segreta e gli indizi in due
 * file di testo distinti. Questo permette per esempio alla squadra B2
 * di leggere gli indizi con un editor o un visualizzatore di file di
 * testo nel caso siano per esempio spariti dal terminale su cui sta
 * giocando.
 *
 * Le funzionalità di lettura del file di input e creazione dei due
 * file devono essere realizzate in una funzione che non legge nulla
 * da stdin.  Lo stesso vale per la funzionalità di stampa delle
 * parole indizio.  Decidere a tempo di scrittura del programma i nomi
 * di tutti i file letti o scritti. Bisogna infine gestire
 * opportunamente tutte le situazioni di errore, ed applicare tutti i
 * principi di ingegneria del codice visti a lezione.
 *
 * Non appena si finisce la scrittura ed il collaudo del proprio
 * programma, ci si sposta verso il collega o gruppo di colleghi che
 * si preferisce, e si collabora con loro nel completamento del loro
 * programma. Quindi, se si e' gia' in numero sufficiente per iniziare
 * una partita (ossia si e' almeno in quattro), si inizia a giocare,
 * altrimenti ci si sposta verso un nuovo collega o gruppo di
 * collleghi, e cosi' via.  Ogni turno deve essere giocato utilizzando
 * un programma diverso tra tutti quelli realizzati dai componenti
 * delle due squadre.
 *
 * -----------------------------------------------------------------
 *
 * ESTENSIONI PER CASA (meglio realizzarle dopo aver visto il
 * costrutto struct a lezione)
 *
 * . Aggiungere tutto quello che e' necessario per gestire una intera
 *   partita, ossia tutti i turni decisi dalle squadre
 *
 * . Fare scegliere casualmente al programma la parola segreta, tra
 *   quelle memorizzate in un file di testo dato
 */


#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>

using namespace std ;

const int MAX_LUN = 1024 ;

/*
 * Stampa il messaggio e fa uscire dal programma.
 *
 */
void errore(const char messaggio[])
{
    cerr<<messaggio<<endl ;
    exit(1) ;
}

void leggi_stampa_file(const char nome_file[])
{
    ifstream f(nome_file) ;
    if (! f)
	errore("Errore nell'apertura del file da stampare") ;

    char parola[MAX_LUN] ;
    while(f>>parola)
	cout<<parola<<endl ;
}

/*
 * Crea due file chiamati nome_file_parola_segreta e nome_file_indizi,
 * in cui memorizza, rispettivamente, la parola segreta e gli
 * indizi. Tali informazioni sono lette dal file nome_input_file.
 * Memorizza la parola segreta nella stringa passata come ultimo
 * parametro.
 */
void crea_i_file(const char nome_input_file[],
		  const char nome_file_parola_segreta[],
		  const char nome_file_indizi[],
		  char parola_segreta[])
{
    char parola[MAX_LUN] ;
    ifstream input_fstream(nome_input_file) ;
    if (! input_fstream)
	errore("Errore nell'apertura del file di input") ;
    if (! (input_fstream>>parola))
	errore("Errore nella lettura dal file di input");

    // le assegniamo la parola letta dal file
    strcpy(parola_segreta, parola) ;

    // creiamo il file contenente la sola parola segreta
    ofstream fstream_parola_segreta(nome_file_parola_segreta) ;
    if (! fstream_parola_segreta)
	errore("Errore creazione del file contenente la parola da indovinare") ;
    fstream_parola_segreta<<parola<<endl ;

    // creiamo il file degli indizi
    ofstream fstream_indizi(nome_file_indizi) ;
    if (! fstream_indizi)
	errore("Errore creazione del file contenente le indizi") ;
    while(input_fstream>>parola) // per semplificare il codice, manca controllo
	                          // di errore in lettura dal file
	fstream_indizi<<parola<<endl ;

}


/*
 * Stampa le lettere della parola_tent che appaiono nella parola
 * segreta nello stesso ordine.
 *
 */
void stampa_lettere_comuni(const char *parola_segreta, const char *parola_tent)
{
    for (unsigned int i = 0, j = 0 ; i < strlen(parola_tent) ; i++)
	for (unsigned int k = j ; k < strlen(parola_segreta) ; k++)
	    if (parola_tent[i] == parola_segreta[k]) {
		cout<<parola_tent[i] ;
		j++ ;
		break ;
	    }
}

int main()
{
    const char NOME_INPUT_FILE[] = "input.txt" ;
    const char NOME_FILE_PAROLA_SEGRETA[] = "parola_segreta.txt" ;
    const char NOME_FILE_INDIZI[] = "indizi.txt" ;

    char parola_segreta[MAX_LUN] ;
 
    crea_i_file(NOME_INPUT_FILE, NOME_FILE_PAROLA_SEGRETA,
		NOME_FILE_INDIZI, parola_segreta) ;
    
    cout<<"Indovina la parola segreta basandoti sulle seguenti parole-indizio:"
	<<endl ;
    leggi_stampa_file(NOME_FILE_INDIZI) ;

    cout<<endl<<"Trovi gli indizi anche nel file "<<NOME_FILE_INDIZI<<endl ;

    int punteggio = 100 ;
    cout<<endl<<"Punteggio iniziale "<<punteggio<<endl<<endl ;

    char parola[MAX_LUN] ;
    cout<<"Parola segreta: " ;
    while(cin>>parola) {
	if (strcmp(parola, parola_segreta) == 0) {
	    cout<<"Hai vinto, totalizzando "<<punteggio<<" punti"<<endl<<endl ;
	    return 0 ;
	} else { // parola tentativo diversa dalla parola segreta
	    cout<<"Sbagliato, "
		<<"lettere presenti nella parola segreta nello stesso ordine: "
		<<endl<<"\t" ;
	    stampa_lettere_comuni(parola_segreta, parola) ;
	    cout<<endl<<"Riprova, punteggio "<<--punteggio<<endl ;
	}
	cout<<"Parola segreta: " ;
    }
    return 0 ;
}
