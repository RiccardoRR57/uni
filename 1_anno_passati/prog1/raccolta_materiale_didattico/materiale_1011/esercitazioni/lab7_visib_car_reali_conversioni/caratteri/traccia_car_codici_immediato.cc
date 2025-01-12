/*
Partendo dal frammento di programma di seguito fornito, scrivere un
programma che legge e stampa i codici di tutti i caratteri letti in
ingresso, senza dover aspettare l'imissione del newline, finche' non
viene immesso il carattere -

Un possibile output sullo schermo e' il seguente:
Inserisci un carattere e
Il codice ASCII del carattere e' 101
Inserisci un carattere  
Il codice ASCII del carattere e' 32
Inserisci un carattere ,
Il codice ASCII del carattere e' 44
Inserisci un carattere 

Il codice ASCII del carattere e' 10
Inserisci un carattere -
Il codice ASCII del carattere e' 45
*/

/*
 * Segue il frammento di programma da cui partire
 *
 * Per lo svolgimento dell'esercizio non e' di nessuna importanza
 * capire come si ottiene il cambio di modalita' del terminale.  I
 * dettagli su tali operazioni si vedranno in corsi futuri. Quello che
 * va fatto e' solo scrivere le righe mancanti!
 *
 * La soluzione dell'esercizio e' nel file sol_car_codici_immediato.cc
 */

#include <iostream>
#include <stdio.h>
#include <termios.h>
#include <fcntl.h>
#include <stdlib.h>

using namespace std ;

/*
 * Configura il terminale in modo non canonico
 */
void vai_in_modo_non_canonico() 
{
    struct termios nuovo ;
    if (tcgetattr(STDIN_FILENO, &nuovo) < 0) {
	cout<<"Salvataggio modo terminale fallito"<<endl ;
	exit(1) ;
    }

    nuovo.c_lflag &= ~ICANON ;

    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &nuovo) < 0) {
	cout<<"Settaggio modo terminale fallito"<<endl ;
	exit(1) ;
    }

}

void salva_modo_terminale(termios &modo)
{
    if (tcgetattr(STDIN_FILENO,  &modo) < 0) {
	cout<<"Salvataggio modo terminale fallito" ;
	exit(1) ;
    }
}

void assegna_modo_terminale(termios &modo)
{
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &modo) < 0) {
	cout<<"Salvataggio modo terminale fallito" ;
	exit(1) ;
    }
}

int main()
{
    termios vecchio_modo_terminale ;
    // si salva la modalita' corrente per ripristinarla al termine del
    // programma
    salva_modo_terminale(vecchio_modo_terminale) ;

    vai_in_modo_non_canonico() ;
    
    // inserire qui il codice per leggere i caratteri e terminare
    // quando si incontra il carattere -

    // qui il terminale viene riportato nella modalita' precedente
    assegna_modo_terminale(vecchio_modo_terminale) ;

    return 0 ;
}
