/*
  Definire una struttura figura contenente il tipo della figura
  geometrica, la sua base maggiore e minore e l'altezza.  Le figure
  possibili sono: quadrato, rettangolo, parallelogramma,
  trapezio. Scrivere un main() in cui l'utente inserisca il nome della
  figura interessata. Notare che facciamo scrivere all'utente il nome
  della figura e non gli facciamo semplicemente immettere un numero o
  un carattere; sarebbe stata più appropriata l'altra soluzione, ma
  scegliamo questa allo scopo di esercitarci con le stringhe.  Inoltre
  l'utente deve inserire i parametri geometrici necessari per
  calcolare l'area della figura.

  Ovviamente, nella struttura figura, il tipo della figura
  va memorizzato con il tipo di dato più appropriato.

  Attraverso la funzione area() calcolare l'area della figura
  indicata.  La funzione area ha come parametro d'ingresso la
  struttura e come valore di ritorno l'area.*/

#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std ;

enum tipo_t {QUADRATO, RETTANGOLO, PARALLELOGRAMMA, TRAPEZIO } ;

/* Definizione della struttura figura, composta da tre campi */
struct figura {
       tipo_t tipo ;
       int base_maggiore, base_minore, altezza;
};


/* Prototipo della funzione */
double area (const struct figura &);

int main()
{
    struct figura fig;
    double a;
    
    cout<<"Scrivi il nome della figura di cui vuoi calcolare l'area " ;
    cout<<"(quadrato, rettangolo, trapezio, parallelogramma): "<<endl;
    
    char nome[15] ; 
    cin>>nome;
    
    if (strcmp(nome, "trapezio")==0)
     {
	 fig.tipo = TRAPEZIO ;
	 cout<<"Immetti la base maggiore e la "
	     <<"base minore della figura "<<nome<<endl ;
	 cin>>fig.base_maggiore>>fig.base_minore ;
	 cout<<"Immetti l'altezza:"<<endl ;
         cin>>fig.altezza ;
     }
    else
	if (strcmp(nome,"quadrato")==0)
	    {
		fig.tipo = QUADRATO ;
		cout<<"Immetti il lato del quadrato:"<<endl ;
		cin>>fig.base_maggiore ;
	    }
	else
	 {
	     if (strcmp(nome, "rettangolo") == 0)
		 fig.tipo = RETTANGOLO ;
	     else if (strcmp(nome, "parallelogramma") == 0)
		 fig.tipo = RETTANGOLO ;
	     else
		 {
		     cout<<"Errore nell'immissione del nome della figura" ;
		     return 1;
		 }
	     
	     cout<<"Immetti la base del "<<nome<<endl ;
	     cin>>fig.base_maggiore ;
	     cout<<"Immetti l'altezza\n" ;
	     cin>>fig.altezza ;
	 }
    
    
    /*Invocazione della funzione area per calcolare l'area della
      figura immessa*/
    a = area(fig);
 
    cout<<"L'area della figura ("<<nome<<") è "<<a<<endl ;
    return 0 ;
}

double area (const struct figura &F)
{
    switch (F.tipo) {
    case TRAPEZIO:
	return ((F.base_minore+F.base_maggiore)*F.altezza)/2;
    case RETTANGOLO:
    case PARALLELOGRAMMA:
	return F.base_maggiore*F.altezza;
    case QUADRATO:
	return F.base_maggiore*F.base_maggiore;
    }
}
