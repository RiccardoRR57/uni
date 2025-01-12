#include <iostream>
#include <fstream>

using namespace std ;

const int NUM_COLONNE = 6 ;
const int NUM_RIGHE = 3 ;
const char NOME_FILE[] = "matrice.txt" ;

// stati possibili degli elementi della matrice
enum stato {SPENTO, ACCESO} ;

// tipo di dato matrice per migliorare leggibilita'
typedef stato matrice_t[NUM_RIGHE][NUM_COLONNE] ;

// inizializza la matrice spegnedo tutti gli elementi
void inizializza(matrice_t m)
{
  for (int i = 0 ; i < NUM_RIGHE; i++)
    for (int j = 0 ; j < NUM_COLONNE; j++)
      m[i][j] = SPENTO ;
}

/*
 * accende un elemento purche' non adiacente, in orizzontale o
 * verticale, ad alcun altro elemento acceso; ritorna vero solo in
 * caso di successo
 */
bool disegna_punto(matrice_t m, int riga, int col)
{
  if (riga < 0 || col < 0 ||
      riga >= NUM_RIGHE || col >= NUM_COLONNE)
    return false ;
  
  if ((riga > 0 && m[riga - 1][col] == ACCESO) ||
      (riga < NUM_RIGHE - 1 && m[riga + 1][col] == ACCESO) ||
      (col > 0 && m[riga][col - 1] == ACCESO) ||
      (col < NUM_COLONNE - 1 && m[riga][col + 1] == ACCESO))
    return false ;

  m[riga][col] = ACCESO ;
  return true ;
}

/*
 * funzione di supporto per disegnare un nuovo rettangolo
 */
void disegna_nuovo_rettangolo(matrice_t m,
			      int riga, int col, int lar, int alt)
  
{
  int col_destra = col + lar - 1 ;

  // lato superiore ed inferiore
  int riga_inf = riga + alt - 1 ;
  for (int j = col ; j <= col_destra ; j++) {
      m[riga][j] = ACCESO ;
      m[riga_inf][j] = ACCESO ;
  }
  
  // lat sinistro e destro
  int max_riga = riga + (alt - 2) ;
  for (int i = riga + 1 ; i <= max_riga ; i++) {
    m[i][col] = ACCESO ;
    m[i][col_destra] = ACCESO ;
  }
}

/*
 * disegna un nuovo rettangolo dopo aver spento tutti gli elementi
 * della matrice; ritorna vero solo in caso di successo
 */
bool disegna_rettangolo(matrice_t m, int riga, int col, int lar, int alt)
{
  if (riga < 0 || col < 0 ||
      lar < 1 || alt < 1 ||
      riga + alt - 1 >= NUM_RIGHE || col + lar - 1 >= NUM_COLONNE)
    return false ;
  
  inizializza(m) ;
  disegna_nuovo_rettangolo(m, riga, col, lar, alt) ;
  return true ;
}

// Stampa la matrice sull'ostream passato in ingresso
bool stampa_matrice(const matrice_t m, ostream &os)
{
  for (int i = 0 ; i < NUM_RIGHE; i++)
    for (int j = 0 ; j < NUM_COLONNE; j++) {
      os<<(m[i][j] == ACCESO ? '*' : '-') ;
      os<<(j < NUM_COLONNE - 1 ? ' ' : '\n') ;
    }
  os<<endl ;

  return os ;
}


// carica la matrice dal file
bool carica_matrice(matrice_t m)
{
  ifstream f(NOME_FILE) ;
  if (! f)
    return false ;
  for (int i = 0 ; i < NUM_RIGHE; i++)
    for (int j = 0 ; j < NUM_COLONNE; j++) {
      char simbolo ;
      f>>simbolo ;
      m[i][j] = simbolo == '*' ? ACCESO : SPENTO ;
    }
  return f ;
}

/*
 * funzione di supporto: ritorna vero solo se nessun elemento del
 * rettangolo si sovrappone ad alcun elemento acceso della matrice
*
*/
bool controlla_rettangolo(const matrice_t m,
			  int riga, int col, int lar, int alt)
  
{
  int col_destra = col + lar - 1 ;

  // lato superiore ed inferiore
  int riga_inf = riga + alt - 1 ;
  for (int j = col ; j <= col_destra ; j++)
    if (m[riga][j] == ACCESO || m[riga_inf][j] == ACCESO)
      return false ;
  
  // lat sinistro e destro
  int max_riga = riga + (alt - 2) ;
  for (int i = riga + 1 ; i <= max_riga ; i++)
    if (m[i][col] == ACCESO || m[i][col_destra] == ACCESO)
      return false ;
  return true ;
}

/*
 * disegna un nuovo rettangolo purchè nessun elemento del rettangolo
 * si sovrapponga ad alcun elemento acceso della matrice; ritorna vero
 * solo in caso di successo
 */
bool disegna_rettangolo2(matrice_t m, int riga, int col, int lar, int alt)
{
  if (riga < 0 || col < 0 ||
      lar < 1 || alt < 1 ||
      riga + alt - 1 >= NUM_RIGHE || col + lar - 1 >= NUM_COLONNE)
    return false ;
  
  if (! controlla_rettangolo(m, riga, col, lar, alt))
    return false ;
  
  disegna_nuovo_rettangolo(m, riga, col, lar, alt) ;
  return true ;
}

int main()
{
  matrice_t matrice ;
  inizializza(matrice) ;

  const char menu[] =
    "1. Disegna punto\n"
    "2. Stampa matrice\n"
    "3. Salva matrice\n"
    "4. Carica matrice\n"
    "5. Disegna rettangolo\n"
    "6. Disegna rettangolo 2\n"
    "7. Esci\n";

  while(true) {
    cout<<menu<<endl ;

    int scelta ;
    cin>>scelta ;

    switch(scelta) {
    case 1:{
      int riga, col ;
      cout<<"Inserire indice riga ed indice colonna: " ;
      cin>>riga>>col ;
      if (! disegna_punto(matrice, riga, col))
	cout<<"Disegno punto fallito"<<endl ;}
      break;
    case 2:
      stampa_matrice(matrice, cout) ;
      break ;
    case 3:{
      ofstream f(NOME_FILE) ;
      if (! stampa_matrice(matrice, f))
	cout<<"Salvataggio fallito"<<endl ;}
      break ;
    case 4:
      carica_matrice(matrice) ;
      break ;
    case 5:{
      int riga, col, lar, alt ;
      cout<<"Inserire indice riga, indice colonna, base ed altezza: " ;
      cin>>riga>>col>>lar>>alt ;
      if (! disegna_rettangolo(matrice, riga, col, lar, alt))
	cout<<"Disegno rettangolo fallito"<<endl ;}
      break;
    case 6:{
      int riga, col, lar, alt ;
      cout<<"Inserire indice riga, indice colonna, base ed altezza: " ;
      cin>>riga>>col>>lar>>alt ;
      if (! disegna_rettangolo2(matrice, riga, col, lar, alt))
	cout<<"Disegno rettangolo fallito"<<endl ;}
      break;
    case 7:
      return 0 ;
    default :
      cout<<"Scelta errata"<<endl ;
    }
  }

}
