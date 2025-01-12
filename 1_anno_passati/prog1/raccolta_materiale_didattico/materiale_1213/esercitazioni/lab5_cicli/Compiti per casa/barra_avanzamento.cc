/* 
 * Nella soluzione del seguente esercizio si utilizza l'istruzione
 * for. Se non l'avete ancora vista a lezione, utilizzate invece
 * l'istruzione while. Riscrivete poi il programma utilizzando
 * l'istruzione for una volta che l'avrete vista a lezione, e
 * confrontate la vostra con la soluzione riportata in questo file.
 *
 * Spesso per rappresentare (anche al variare del tempo) quale porzione di un 
 * certo lavoro è stata completata (o ad esempio quale frazione della carica 
 * massima è presente in una batteria) si utilizza una barra di lunghezza 
 * proporzionale a tale porzione (la barra ha/raggiunge la lunghezza massima 
 * se/quando l'intero lavoro è completato o la carica della batteria è massima).
 *
 * Scrivere un programma che legga da stdin un valore percentuale 
 * (in centesimi) e la lunghezza massima della barra con cui 
 * rappresentare tale percentuale (attenzione al numero massimo di colonne 
 * che si suppone siano disponibili sul terminale). Il programma stampa quindi sullo 
 * schermo la barra nel formato mostrato nei seguenti esempi
 *
 * Esempi:
 *
 * Inserire la percentuale (in centesimi), e la lunghezza della barra: 20 40
 *  --------------------------------------
 * |XXXXXXX                               |
 *  --------------------------------------
 *
 * Inserire la percentuale (in centesimi), e la lunghezza della barra: 100 30
 * ----------------------------
 *|XXXXXXXXXXXXXXXXXXXXXXXXXXXX|
 * ----------------------------
 *
*/


#include <iostream>

using namespace std ;

main()
{
  int i, l_tot, l_compl ;
  const int COL = 60 ; /* Numero di colonne disponibili sul terminale */

  printf("\nInserire la percentuale (in centesimi), "
	 "e la lunghezza della barra: "); 
  /* In C/C++ le stringhe si possono spezzare come fatto sopra ... */
  cin>>i>>l_tot ;
  if (l_tot > COL)
    l_tot = COL ; /* Forzo a COL il valore massimo di l_tot */

  cout<<" " ;
  for (int j = 1; j <= l_tot - 2 ; j++)
    cout<<"-" ;
  cout<<"\n|" ;
  l_compl = i * (l_tot - 2) / 100 ;
  for (int j = 1; j <= l_compl ; j++)
    cout<<"X" ;
  for (int j = 1 ; j <= (l_tot - 2) - l_compl ; j++)
    cout<<" " ;
  cout<<"|\n "  ;
  for (int j = 1; j <= l_tot - 2 ; j++)
    cout<<"-" ;
  cout<<endl ;
}

