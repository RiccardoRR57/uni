/*
  Scrivere un programma contenente una funzione stampa_turno, che abbia 
  come parametro di ingresso un oggetto di tipo uguale al tipo di dato 
  rappresantante i giorni della settimana. Dato il giorno della settimana 
  passato in ingresso, la funzione stampa i turni di quel giorno. 
  Supporre che siano stati fissati i seguenti turni:
  Lunedi', Mercoledi' e Venerdi': mattina e pomeriggio
  Martedi' e Giovedi': solo mattina
  Sabato e Domenica: riposo.

  Nel main non si legge nulla da stdin, ma la funzione deve essere
  invocata per stampare i turni dei giorni di Lunedi', Giovedi',
  Domenica.

 */


#include <iostream>

using namespace std ;

enum giorno_t 
	{lunedi, martedi, mercoledi, giovedi, venerdi, sabato, domenica} ;

void stampa_turno(giorno_t g)
{
	switch(g) {
	case lunedi:
	case mercoledi:
	case venerdi:
		cout<<"Mattina e pomeriggio"<<endl ;
		break ;
	case martedi:
	case giovedi:
		cout<<"Solo mattina"<<endl ;
		break ;
	case sabato:
	case domenica:
		cout<<"Riposo"<<endl ;
	}
}

main()
{
	cout<<"Lunedi': " ;
	stampa_turno(lunedi) ;
	cout<<"Giovedi': " ;
	stampa_turno(giovedi) ;
	cout<<"Domenica: " ;
	stampa_turno(domenica) ;
}
