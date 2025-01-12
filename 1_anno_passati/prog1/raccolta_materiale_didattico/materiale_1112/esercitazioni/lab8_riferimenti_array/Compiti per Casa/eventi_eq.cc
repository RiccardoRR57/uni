/* 
    La simulazione e' una delle tecniche che si utilizzano per testare
    un qualcosa che non si puo' (o che, in un dato momento, non si
    vuole) costruire fisicamente. Per fare delle simulazioni e'
    necessario generare degli eventi in modo casuale.

    Scrivere una funzione "generatore di eventi", che generi due
    possibili eventi, un evento di tipo 0 oppure un evento di tipo 1.
    La probabilita' di generare un evento di tipo 0 e' la stessa di
    generare un evento di tipo 1.  Per implementare il generatore di
    eventi si puo' scrivere semplicemente una funzione che ritorni il
    valore 0 per rappresentare un evento di tipo 0 ed il valore 1 per
    rappresentare un evento di tipo 1.

    Per realizzare il generatore di eventi, utilizzare la funzione di libreria
    rand(), che genera un numero casuale compreso tra 0 e RAND_MAX.
    Tale funzione permette di generare una sequenza di numeri pseudocasuali. 
    Tali numeri si definiscono pseudocasuali perche', fissato il primo valore 
    della sequenza (chiamato seme), e' fissata tutta la sequenza di valori che 
    saranno generati nelle successive invocazioni della funzione rand().
    Pertanto, per ottenere sequenze diverse, bisogna cambiare il valore del
    seme. Per cambiare il valore del seme, si utilizza la funzione srand(n), 
    ove n e' il nuovo valore che si da al seme.
    Per utilizzare le funzioni rand() ed srand(n), bisogna includere il file 
    di intestazione "stdlib.h".

    Oltre alla funzione per la generazione degli eventi, scrivere un programma
    per testarne il funzionamento. In particolare il programma invoca la
    funzione di generazione eventi un numero N di volte, e poi stampa a schermo
    quante volte si e' verificato un evento di tipo 0 e quante volte si e' 
    verificato un evento di tipo 1 (sia in termini assoluti che in 
    percentuale).
    Un possibile output sullo schermo e' il seguente:

    Testo il generatore di eventi su 100000 eventi
    
    Eventi di tipo 0 -> quantita':  50047 percentuale:      50.047
    Eventi di tipo 1 -> quantita':  49953 percentuale:      49.953
*/

#include <cstdlib>
#include <iostream>

using namespace std ;

int gen_eventi()
{
  return rand() / (((unsigned int) RAND_MAX+1)/2) ;
}

int main()
{
  const int N = 100000 ;
  int i ;
  int num_eventi0 = 0 ;
  int num_eventi1 = 0 ;
  srand(1) ;
  
  cout<<"Testo il generatore di eventi su "<<N<<" eventi\n" ;
  for (i = 0 ; i < N ; i++) {
    int evento = gen_eventi() ;
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

