/*

Utilizzare quanto appreso nell'esercizio stampa_secondi.cc sull'espressione
time(0).

Utilizzare inoltre le seguenti informazioni: se si mandano all'oggetto cout
il carattere speciale "\r" seguito da caratteri o valori da stampare, ed infine
dal manipolatore flush, allora tali caratteri o valori saranno stampati 
all'inizio delle riga corrente (sovrascrivendo
il precedente contenuto della riga).
Ad esempio, l'istruzione
cout<<"\r"<<"prova"<<flush ; // equivalente a cout<<"\rprova"<<flush ;
stampa prova all'inizio della riga corrente, sovrascrivendo l'eventuale
precedente contenuto (solo) dei primi 5 caratteri di tale riga. Se al posto
del manipolatore flush si utilizza endl, si ottiene lo stesso risultato, solo
che poi, come sappiamo, si va anche a capo (inizio della prossima riga).

Scrivere un programma che stampa il numero di secondi trascorsi dal
suo avvio, in maniera tale che tale numero si aggiorni al passare del
tempo (quindi sempre sulla stessa riga). Il programma deve terminare
automaticamente quando è trascorso un numero di secondi scelto a tempo
di scrittura del prorgamma stesso.

*/

#include <ctime>
#include <stdlib.h>
#include <iostream>

using namespace std ;

int main()
{
    const int TEMPO_MASSIMO = 10 ;
    int tempo_iniziale = time(0) ;
    while(time(0) - tempo_iniziale < TEMPO_MASSIMO) {
	cout<<"\r"<<time(0) - tempo_iniziale<<flush ;
	system("sleep 1") ;
    }

    return 0 ;
}
