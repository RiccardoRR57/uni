/*

Se si inserisce la direttiva
#include <ctime>
si può utilizzare l'espressione time(0) nel proprio programma.

Ogni volta che viene valutata, tale espressione ritorna un
numero intero uguale al numero di secondi trascorsi dal 1 gennaio,
1970, GMT.

Quindi, per esempio, se si scrive l'istruzione
cout<<time(0);
allora, ogni volta che viene eseguita tale istruzione, si stampa su stdout
il numero di secondi trascorsi da 1970, GMT.

Utilizzando questa informazione scrivere un programma, che stampa, ogni
secondo, il numero di secondi trascorsi da 1970, GMT. Il programma va
avanti all'infinito.

*/

#include <ctime>
#include <stdlib.h>
#include <iostream>

using namespace std ;

int main()
{
    while(true) { // la condizione è sempre vera: ciclo infinito
	cout<<time(0)<<endl ;
	system("sleep 1") ;
    }

    // qui non si arriva mai
    return 0 ;
}
