#include <iostream>
#include <fstream>

using namespace std ;
const int MAX_RIGHE = 10 ; // numero massimo di righe del documento
const int MAX_LUN_RIGHE = 61 ; // lunghezza massima righe
const char NOME_FILE[] = "documento.txt" ; // nome file di testo
typedef char matr_righe_t[MAX_RIGHE][MAX_LUN_RIGHE] ; // nome tipo per
						      // la matriche
						      // delle righe

// tipo di dato per descrivere un documento
struct documento_t {
  matr_righe_t matr_righe ; // matrice statica utilizzata per
			    // contenere la matrice dinamica che
			    // rappresenta il documento
  int num_righe ; // numero di righe della matrice dinamica (del
		  // documento)
} ;

/*
 * Modifica la riga di indice idx del documento doc con la riga
 * nuova_riga.  La nuova riga è invece aggiunta se idx è maggiore
 * dell'indice dell'ultima riga del documento.
 * Ritorna vero in caso di successo, falso altrimenti.
 */
bool modifica_aggiungi_riga(documento_t &doc, int idx, char *nuova_riga)
{
  idx = idx < 0 ? 0 : idx ;

  if (idx >= doc.num_righe) { // bisogna aggiungere una riga in fondo
			      // al documento
    if (doc.num_righe == MAX_RIGHE) // documento pieno
      return false ;
    idx = doc.num_righe ; // sposto idx all'indice della riga aggiuntiva
    doc.num_righe++ ; // trattandosi di una aggiunta, il numero di
		      // righe va incrementato
  }
  strcpy(doc.matr_righe[idx], nuova_riga) ; // aggiornamento della riga
  return true ;
}

// scrive il contenuto del documento doc sullo stream os
void scrivi_documento(ostream &os, const documento_t &doc)
{
  for (int i = 0 ; i < doc.num_righe ; i++)
    os<<doc.matr_righe[i]<<endl ;
}

/*
 * Sovrascrive il documento doc con il documento letto dallo stream is.
 * Il contenuto precedente del documento e' perso.
 */
void carica_documento(istream &is, documento_t &doc)
{
  doc.num_righe = 0 ;
  while(is.get(doc.matr_righe[doc.num_righe], MAX_LUN_RIGHE)) {
    // si va avanti finche' non finisce il file o non si incontra una
    // riga vuota (in entrambi i casi la funzione get manda lo stream
    // in stato di errore)
    doc.num_righe++ ;
    is.ignore() ; // rimuove il newline, che non e' rimosso dalla funzione get
  }
}

/*
 * Elimina la riga di indice idx dal documento doc.
 * Ritorna vero in caso di successo, falso altrimenti.
 */
bool elimina_riga(documento_t &doc, int idx)
{
  if (idx < 0 || idx >= doc.num_righe)
    return false ;
  for (int i = idx ; i < doc.num_righe - 1 ; i++)
    strcpy(doc.matr_righe[i], doc.matr_righe[i+1]) ;
  doc.num_righe-- ;
  return true ;
}

/*
 * Cerca la prossima occorrenza della parola all'interno del documento
 * doc, a partire dalla posizione pos_inizio all'interno della riga di
 * indice idx_inizio. In caso di successo, lascia nei parametri di
 * uscita idx e pos, l'indice della riga e la posizione nella riga in
 * cui e' presente tale occorrenza.
 * Ritorna vero in caso di successo, falso altrimenti.
 */
bool cerca_prossima_occorrenza(const documento_t &doc, const char parola[],
			       int idx_inizio, int pos_inizio,
			       int &idx, int &pos)
{
  if (idx < 0)
    return false ;
  int lun = strlen(parola) ;
  for(idx = idx_inizio ; idx < doc.num_righe ; idx++) {
    /*
     * se siamo nella prima riga da cui iniziare la ricerca,
     * l'effettiva posizione da cui iniziare la ricerca e' data dal
     * parametro di ingresso pos_inizio, altrimenti bisogna ovviamente
     * proseguire la ricerca dall'inizio della riga.
     */
    int pos_inizio_effettiva = idx > idx_inizio ? 0 : pos_inizio ;
    int lun_riga = strlen(doc.matr_righe[idx]) ;
    for (pos = pos_inizio_effettiva ; pos < lun_riga - lun + 1 ;
	 pos ++) {
      int num_uguali ;
      for (num_uguali = 0 ; num_uguali < lun ; num_uguali++)
	if (parola[num_uguali] != doc.matr_righe[idx][pos+num_uguali])
	  break ;
      if (num_uguali == lun) // trovata una sequenza di caratteri
			     // coincidenti lunga quanto l'intera
			     // parola
	return true ;
    }
  }
  return false ;
}

void inizializza_documento(documento_t &doc)
{
  doc.num_righe = 0 ;
}

int main()
{
  documento_t doc ;
  inizializza_documento(doc) ;

  const char menu[] =
    "1. Aggiungi/Modifica riga\n"
    "2. Stampa documento\n"
    "3. Salva documento\n"
    "4. Carica documento\n"
    "5. Elimina riga\n"
    "6. Cerca prossima occorrenza parola\n"
    "7. Esci\n" ;
  
  while(true) {
    cout<<menu<<endl ;
    int scelta ;
    cin>>scelta ;

    switch(scelta) {
    case 1:{
      int idx ;
      cout<<"Indice riga da modificare/aggiungere? " ;
      cin>>idx ;
      char riga[MAX_LUN_RIGHE] ;

      cout<<"Inserisci nuovo contenuto riga (di almeno un carattere)"<<endl ;
      do {
	cin.get(riga, MAX_LUN_RIGHE-1) ; /* 
					  * riversa nell'array di
					  * caratteri riga i caratteri
					  * presenti sullo stdin,
					  * fermandosi o dopo aver
					  * letto MAX_LUN_RIGHE-1
					  * caratteri, o quando
					  * incontra il carattere
					  * newline (che non viene ne'
					  * aggiunto dentro riga ne'
					  * estratto dallo stdin)
					  */
	if (riga[0] == '\0') { // letta una riga vuota
	  cin.clear() ; // riporto il cin in stato buono, perche' la
			// funzione get lo manda in stato cattivo nel
			// caso in cui legga una riga vuota
	  cin.ignore() ; // elimino il newline per evitare problemi
			 // nella prossima lettura di una riga (la
			 // funzione get non elimina il newline)
	}
      } while (riga[0] == '\0') ;
      cout<<riga<<endl ;
      if (!modifica_aggiungi_riga(doc, idx, riga))
	cout<<"Modifica/aggiunta riga fallita"<<endl ;
      break ;
    }
    case 2:
      scrivi_documento(cout, doc) ;
      break ;
    case 3:{
      ofstream f(NOME_FILE) ;
      scrivi_documento(f, doc) ;
      if (!f)
	cout<<"Salvataggio documento fallito"<<endl ;
      break ;
    }
    case 4:{
      ifstream f(NOME_FILE) ;
      if (!f) {
	cout<<"Errore in apertura del file "<<NOME_FILE<<endl ;
	break ;
      }
      carica_documento(f, doc) ;
      break ;
    }
    case 5: {
      int idx ;
      cout<<"Indice riga da eliminare: " ;
      cin>>idx ;
      if ( !elimina_riga(doc, idx) )
	cout<<"Eliminazione fallita"<<endl ;
      break ;
    }
    case 6: {
      int idx, pos ;
      char parola[MAX_LUN_RIGHE] ;
      cout<<"Inserisci parola da cercare: " ;
      cin>>parola ;
      cout<<"Inserisci indice riga e posizione: " ;
      cin>>idx>>pos ;
      if (cerca_prossima_occorrenza(doc, parola, idx, pos, idx, pos))
	cout<<"Occorrenza trovata in posizione "<<idx<<" "<<pos<<endl ;
      else
	cout<<"Nessuna occorrenza trovata"<<endl ;
      break ;
    }
    case 7:
      return 0 ;
    default:
      cout<<"Scelta errata"<<endl ;
    }
  }
  return 1 ;
}
