/*
 * Soluzione dell'esercizio la cui traccia è in traccia_disegno.cc.
 *
 * Per lo svolgimento dell'esercizio non e' di nessuna importanza
 * capire come si ottiene il cambio di modalita' del terminale.  I
 * dettagli su tali operazioni si vedranno in corsi futuri.
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

const int M = 20 ;

void inizializza_tavola(char tav[][M])
{
    for(int i = 0 ; i < M ; i++)
	for(int j = 0 ; j < M ; j++)
	    tav[i][j] = ' ' ;
}

void ridisegna_tavola(const char tav[][M])
{
    system("clear") ;
    cout<<"j->sinistra, l->destra, i->alto, k->basso"<<endl ;
    cout<<"u->disegna, o->cancella, n->solo sposta"<<endl<<endl ;
    cout<<"q->esci"<<endl<<endl ;
    for(int i = 0 ; i < M ; i++) {
	for(int j = 0 ; j < M ; j++)
	    cout<<tav[i][j] ;
	cout<<endl ;
    }
}

void aggiorna_car_sotto_punt(char &da_rimostrare, char &sotto_punt,
			     char &da_coprire, char car_punt)
{
    da_rimostrare = sotto_punt ;
    sotto_punt = da_coprire ;
    da_coprire = car_punt ;
}

int main()
{
    termios vecchio_modo_terminale ;
    // si salva la modalita' corrente per ripristinarla al termine del
    // programma
    salva_modo_terminale(vecchio_modo_terminale) ;

    vai_in_modo_non_canonico() ;
    
    char tavola[M][M] ;
    int pos_punt_x = M/2, pos_punt_y = M/2 ;
    enum modo_punt_t {SOLO_SPOSTA = 0, DISEGNA, CANCELLA} ;
    modo_punt_t modo_puntatore = SOLO_SPOSTA ;
    const char simbolo_punt[3] = {'X', '+', '-'} ;

    inizializza_tavola(tavola) ;
    char car_sotto_punt = tavola[pos_punt_y][pos_punt_x] ;
    
    tavola[pos_punt_y][pos_punt_x] = simbolo_punt[modo_puntatore] ;
    
    char tasto ;
    do {
	int prec_pos_punt_x = pos_punt_x, prec_pos_punt_y = pos_punt_y ;
	ridisegna_tavola(tavola) ;
	cin>>tasto ;
	switch(tasto) {
	case 'j':
	    if (pos_punt_x == 0)
		break ;
	    pos_punt_x-- ;
	    break ;
	case 'l':
	    if (pos_punt_x == M-1)
		break ;
	    pos_punt_x++ ;
	    break ;
	case 'i':
	    if (pos_punt_y == 0)
		break ;
	    pos_punt_y-- ;
	    break ;
	case 'k':
	    if (pos_punt_y == M-1)
		break ;
	    pos_punt_y++ ;
	    break ;
	case 'u':
	    modo_puntatore = DISEGNA ;
	    break ;
	case 'o':
	    modo_puntatore = CANCELLA ;
	    break ;
	case 'n':
	    modo_puntatore = SOLO_SPOSTA ;
	    break ;
	}
	aggiorna_car_sotto_punt(tavola[prec_pos_punt_y][prec_pos_punt_x],
				    car_sotto_punt,
				    tavola[pos_punt_y][pos_punt_x],
				    simbolo_punt[modo_puntatore]) ;
	if (modo_puntatore == DISEGNA)
	    car_sotto_punt = '*' ;
	else if (modo_puntatore == CANCELLA)
	    car_sotto_punt = ' ' ;
    } while (tasto != 'q') ;

    // qui il terminale viene riportato nella modalita' precedente
    assegna_modo_terminale(vecchio_modo_terminale) ;

    return 0 ;
}
