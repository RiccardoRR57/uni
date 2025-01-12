/*
    Per le indicazioni generali sulla generazione dei numeri casuali,
    fare riferimento all'esercizio eventi_eq.cpp.
    Scrivere un programma che contenga una funzione "generatore di eventi" ,
    che generi due possibili eventi, un evento di tipo 0 oppure un evento di 
    tipo 1. 

    Per implementare il generatore di eventi si puo' scrivere
    semplicemente una funzione che ritorni il valore 0 per
    rappresentare un evento di tipo 0 ed il valore 1 per rappresentare
    un evento di tipo 1.  La funzione prende in ingresso la
    probabilita' con cui deve generare un evento di tipo 0. Tale
    probabilita' e' espressa in percentuale da 0 a 100: ad esempio,
    percentuale 0 vuol dire che non si deve mai generare un evento di
    tipo 0, percentuale 100 vuol dire che si deve sempre generare un
    evento di tipo 0.

    Il programma testa il funzionamento del generatore di eventi. 
    In particolare il programma invoca la funzione di generazione eventi 
    un numero N di volte, e poi stampa a schermo
    quante volte si e' verificato un evento di tipo 0 e quante volte si e' 
    verificato un evento di tipo 1 (sia in termini assoluti che in 
    percentuale).
    Un possibile output e' il seguente:

    Inserire probabilita' (tra 0 e 100) dell'evento di tipo 1: 30

    Testo il generatore di eventi su 100000 eventi
    Eventi di tipo 0 -> quantita':  29723 percentuale:      29.723
    Eventi di tipo 1 -> quantita':  70277 percentuale:      70.277
*/

#include <cstdlib>
#include <iostream>

using namespace std ;

// il parametro formale perc e' un numero tra 0 e 100 che indica
// la probabilita' (misurata tra 0 e 100) desiderata per gli eventi
// di tipo 1
int gen_eventi(int perc)
{
  if (perc == 100)
    return 1 ;
  perc = 100 - perc ;

  // Se ci ragionate sopra, dovrebbe tornarvi che la seguente espressione
  // generi un numero casuale compreso tra 0 e 99.
  // Come mai c'è la conversione a intero prima di effettuare
  // l'assegnamento?
  // Provare ad eliminarla e controllare i messaggi del compilatore.
  // Inoltre RAND_MAX è convertito ad unsigned int prima di sommare 1, perché
  // altrimenti il numero risultante potrebbe non stare su un int
  int res = static_cast<int>(rand() / 
			     (static_cast<double>(static_cast<unsigned int>
						  (RAND_MAX)+1)/100) ) ;
  
  // numero uguale a 0 se res e' sotto perc
  res /= perc ;
  return res ;
}

int main()
{
  const int N = 100000 ;
  int num_eventi0 = 0 ;
  int num_eventi1 = 0 ;
  int perc ;
  
  srand(1) ;
  
  cout<<"Inserire probabilita' (tra 0 e 100) dell'evento di tipo 1: " ;
  cin>>perc ;
  cout<<"Testo il generatore di eventi su "<<N<<" eventi\n" ;
  for (int i = 0 ; i < N ; i++) {
    int evento = gen_eventi(perc) ;
    if (evento == 0)
      num_eventi0++ ;
    else
      num_eventi1++ ;
  }
  cout<<"Eventi di tipo 0 -> quantita':\t"<<num_eventi0 ;
  cout<<" percentuale:\t"<<static_cast<double>(num_eventi0)*100/N<<endl ;
  cout<<"Eventi di tipo 1 -> quantita':\t"<<num_eventi1 ;
  cout<<" percentuale:\t"<<static_cast<double>(num_eventi1)*100/N<<endl ;
  
  return 0 ;
}    

