#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdlib.h>

using namespace std ;

// descrittore di una sequenza
struct sequenza_t {
  int *elementi ; // puntatore all'array dinamico contenente gli elementi
  int num_elem ;  // numero di elementi nella sequenza
} ;

// nome del file in cui salvare la sequenza
const char NOME_FILE[] = "sequenza.dat" ;

// inizializza a struttura dati affinche' contenga una sequenza vuota
void inizializza_sequenza(sequenza_t &s)
{
  s.num_elem = 0 ;
}

/*
 * funzione di servizio che crea una nuova sequenza di N elementi non
 * inizializzati, distruggendo l'eventuale sequenza precedente
 */
void crea_sequenza(sequenza_t &s, int N)
{
  N = N > 0 ? N : 1 ;

  if (N != s.num_elem) {
    if (s.num_elem != 0)
      delete [] s.elementi ;
    s.elementi = new int[N] ;
    s.num_elem = N ;
  }
}

/*
 * crea una nuova sequenza di N elementi, distruggendo l'eventuale
 * sequenza precedente; inizializza gli elementi leggendo i valori da
 * stdin
 */
void nuova_sequenza(sequenza_t &s, int N)
{
  crea_sequenza(s, N) ;

  for (int i = 0 ; i < s.num_elem ; i++)
    do cin>>s.elementi[i] ;
    while (s.elementi[i] < -10 || s.elementi[i] > 10) ;
}

// stampa solo i vlori positivi della sequenza sotto forma di barre orizzontali
void stampa_sequenza(const sequenza_t &s)
{
  for (int i = 0 ; i < s.num_elem ; i++)
    if (s.elementi[i] > 0)
      cout<<setw(s.elementi[i])<<left<<setfill('*')<<""<<endl ;
}

// salva la sequenza in un file binario; ritorna falso in caso di
// fallimento dell'operazione, vero altirmenti
bool salva_sequenza(const sequenza_t &s)
{
  ofstream f(NOME_FILE) ;
  f.write(reinterpret_cast<const char *>(&s.num_elem), sizeof(int)) ;
  f.write(reinterpret_cast<const char *>(s.elementi),
	  s.num_elem * sizeof(int)) ;
  return f ;
}

/*
 * carica la sequenza dal file, distruggendo l'eventuale sequenza
 * precedente; ritorna falso in caso di fallimento dell'operazione,
 * vero altrimenti
 */
bool carica_sequenza(sequenza_t &s)
{
  ifstream f(NOME_FILE) ;
  int N ;
  f.read(reinterpret_cast<char *>(&N), sizeof(int)) ;
  if (N <= 0)
    return false ;
  
  crea_sequenza(s, N) ;

  f.read(reinterpret_cast<char *>(s.elementi), N * sizeof(int)) ;

  return f ;
}

// stamp i valori della sequenza sotto forma di barre verticali
void stampa_sequenza_2(const sequenza_t &s)
{
    /*
     * Stampiamo le barre negative riservando loro uno spazio costante
     * e pari a 10 caratteri. In pratica le barre negative sono
     * stampate allineate a destra all'interno dello spazio di 10
     * caratteri a loro riservato
     */
    for (int i = 0 ; i < s.num_elem ; i++)
	if (s.elementi[i] >= 0)
	    cout<<setw(10)<<setfill(' ')<<""
		<<setw(s.elementi[i])<<setfill('*')<<""<<endl ;
	else {
	    /*
	     * Stampiamo prima gli spazi bianchi di riempimento, poi
	     * gli asterischi di cui e' costituita la barra. Per
	     * esempio, se il valore e' -7, stampiamo 3 spazi bianchi,
	     * seguiti da 7 asterischi.
	     */ 
	    for (int j = 0 ; j < 10 + s.elementi[i] ; j++)
		cout<<' ' ;
	    for (int j = 0 ; j < abs(s.elementi[i]) ; j++)
		cout<<'*' ;
	    cout<<endl ;
	}
}

// stampa tutte le sotto-sequenze crescenti contenute nella sequenza
void stampa_crescenti(const sequenza_t &s)
{
    for (int i = 0 ; i < s.num_elem - 1 ; i++) {
	if (s.elementi[i] <= s.elementi[i + 1]) { // inizio di una
						 // sotto-sequenza
	    cout<<s.elementi[i] ; // stampiamo il primo elemento della
				  // sotto-sequenza
	    // stampiamo tutti gli elementi successivi della sotto-sequenza
	    int j ;
	    for (j = i + 1 ;
		 j < s.num_elem &&
		     s.elementi[j - 1] <= s.elementi[j] ;
		 j++)
		cout<<' '<<s.elementi[j] ;
	    cout<<endl ;
	    i = j ; // facciamo saltare i alla fine della
		    // sotto-sequenza appena stampata, in modo da non
		    // stampre piu' alcuno elemento di tale
		    // sotto-sequenza
	}
    }
}

int main()
{
  const char menu[] =
    "1. Crea nuova sequenza\n"
    "2. Stampa sequenza\n"
    "3. Salva sequenza\n"
    "4. Carica sequenza\n"
    "5. Stampa sequenza 2\n"
    "6. Stampa sotto-sequenze crescenti\n"
    "8. Esci\n";

  sequenza_t seq ;
  inizializza_sequenza(seq) ;

  while(true) {
    cout<<menu<<endl ;

    int scelta ;
    cin>>scelta ;
    switch(scelta) {
    case 1:{
      int N ;
      cout<<"Numero di elementi della sequenza? "<<endl ;
      cin>>N ;
      nuova_sequenza(seq, N) ;
      break ;}
    case 2:
      stampa_sequenza(seq) ;
      break ;
    case 3:
      if (! salva_sequenza(seq))
	cout<<"Salvataggio non riuscito"<<endl ;
      break ;
    case 4:
      if (! carica_sequenza(seq))
	cout<<"Caricamento non riuscito"<<endl ;
      break ;
    case 5:
      stampa_sequenza_2(seq) ;
      break ;
    case 6:
      stampa_crescenti(seq) ;
      break ;
    case 8:
      return 0 ;
    default:
      cout<<"Scelta errata"<<endl ;
    }
  }
  return 1 ;
}
