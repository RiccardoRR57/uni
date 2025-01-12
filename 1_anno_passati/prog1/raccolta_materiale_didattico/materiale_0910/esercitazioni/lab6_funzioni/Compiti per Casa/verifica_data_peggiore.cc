/*
 * Scrivere un programma che verifica se la data immessa nel formato
 * GG MM AAAA e' una data corretta.  
 * Realizzare il programma definendo ed utlilizzando una funzione che
 * prende in ingresso tre numeri interi.
 *
 * Aiuto: un anno a è bisestile se e solo se l'espressione logica
 * !(a%400) || ( !(a%4) && (a%100) )
 * è vera
 *
 * Confrontarsi poi con la soluzione fornita in questo file e con
 * la soluzione, di migliore qualita', data nel file
 * verifica_data_migliore.cc
 */

#include <iostream>

using namespace std ;

const int ER_ANNO = 1 ;
const int ER_MESE = 2 ;
const int ER_GIORNO = 3 ;

int controlla(int, int, int);

int main()
{
  int giorno, mese, anno, data_ok;
  cout<<"Inserisci tre numeri che rappresentino una data nel formato "
      <<"GG MM AAAA\n" ;
  cin>>giorno>>mese>>anno ;
  data_ok = controlla(giorno, mese, anno);
  switch (data_ok)
  {
    case 1:
	    cout<<"La data "<<giorno<<"/"<<mese<<"/"<<anno
		<<" non e' corretta: ha un anno negativo o con piu' di "
		<<"4 cifre\n";
	    return 1;
    case 2:
	    cout<<"La data "<<giorno<<"/"<<mese<<"/"<<anno
		<<" non e' corretta: ha un mese inesistente\n" ;
	    return 2;
    case 3:
	    cout<<"La data "<<giorno<<"/"<<mese<<"/"<<anno
		<<" non e' corretta: ha un giorno inesistente\n" ;
	    return 3;  
    default:
	    cout<<"La data "<<giorno<<"/"<<mese<<"/"<<anno<<" e' corretta\n" ;
	    return 0;
  }
}


int controlla(int g, int m, int a)
{
  int bisestile=0, giorno_ok=0;

  if (a<=0 || a>9999)
      return ER_ANNO;

  bisestile = !(a%400) || ( !(a%4) && (a%100) ) ;

  switch (m){
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
      if (g>=1 && g <=31) giorno_ok=1;
      break;
    case 4:
    case 6:
    case 9:
    case 11:
      if (g>=1 && g <=30) giorno_ok=1;
      break;
    case 2:
      if ((g>=1 && g <=28) || (g==29 && bisestile)) giorno_ok=1;
      break;
    default: 
      return ER_MESE;
  }
  return (giorno_ok?0:ER_GIORNO); 
}  
