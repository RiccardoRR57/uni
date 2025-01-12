/* Scrivere un programma che mostri la visibilità delle variabili.
 * In particolare, nel programma bisogna definire
 * 1) una funzione aggiuntiva oltre la funzione main. Tale funzione deve 
 *    prendere in ingresso un valore intero
 * 2) una variabile globale di nome x, inizializzata ad un qualche valore
 * 3) una variabile di nome x all'interno di un blocco all'interno della 
 *    funzione main
 * 4) una variabile di nome x all'interno di un blocco all'interno della 
 *    funzione aggiuntiva
 * La funzione main deve stampare il valore della variabile globale x, 
 * incrementarlo, e quindi stamparlo di nuovo. Quindi deve stampare il valore
 * della variabile x definita nel blocco interno, incrementarlo e stamparlo
 * di nuovo. Poi deve invocare due volte la funzione aggiuntiva passandogli 
 * prima la x definita nel blocco interno, quindi la x globale.
 * La funzione aggiuntiva deve stampare il valore della variabile globale x, 
 * incrementarlo, e quindi stamparlo di nuovo. Quindi deve stampare il valore
 * della variabile x definita nel proprio blocco interno, incrementarlo e 
 * stamparlo di nuovo. Assieme al valore della variabile x (globale o definita 
 * nel proprio blocco interno), la funzione aggiuntiva deve stampare ogni 
 * volta anche il valore del parametro attuale con cui è stata invocata.
 *
 * Esempio:
 * Sono il main e la variabile x vale 300
 * Sono il main e la variabile x vale 301 dopo l'incremento
 * Sono il main dentro il blocco e la variabile x vale 3
 * Sono il main dentro il blocco e la variabile x vale 4 dopo l'incremento
 * 
 * Sono il main dentro il blocco e adesso chiamo la funzione
 * Sono la funzione e la mia x vale 301 mentre la x di chi mi chiama vale 4
 * Sono la funzione e la mia x vale 302 dopo l'incremento,
 *         mentre la x di chi mi chiama vale 4
 * Sono la funzione dentro il blocco e la mia x vale 0,
 *         mentre la x di chi mi chiama vale 4
 * Sono la funzione dentro il blocco e la mia x vale 1 dopo l'incremento,
 *         mentre la x di chi mi chiama vale 4 
 * 
 * Sono il main e adesso chiamo la funzione
 * Sono la funzione e la mia x vale 302 mentre la x di chi mi chiama vale 302
 * Sono la funzione e la mia x vale 303 dopo l'incremento,
 *         mentre la x di chi mi chiama vale 302
 * Sono la funzione dentro il blocco e la mia x vale 0,
 *         mentre la x di chi mi chiama vale 302
 * Sono la funzione dentro il blocco e la mia x vale 1 dopo l'incremento,
 *         mentre la x di chi mi chiama vale 302 
 * 
 */

#include <iostream>

using namespace std ;

int x=300;
void funzione(int);

int main()
{
   cout<<"Sono il main e la variabile x vale "<<x<<endl ;
   x++;
   cout<<"Sono il main e la variabile x vale "<<x<<" dopo l'incremento\n" ;
   {
     int x=3;
     cout<<"Sono il main dentro il blocco e la variabile x vale "<<x<<endl ;
     x++;
     cout<<"Sono il main dentro il blocco e la variabile x vale "<<x<<
	     " dopo l'incremento\n";
     cout<<"\nSono il main dentro il blocco e adesso chiamo la funzione\n" ;
     funzione(x);
   }        
   cout<<"\nSono il main e adesso chiamo la funzione\n" ;
   funzione(x);
   return 0;
}

void funzione(int n)
{
  cout<<"Sono la funzione e la mia x vale "<<x
      <<" mentre la x di chi mi chiama vale "<<n<<endl ;
  x++;
  cout<<"Sono la funzione e la mia x vale "<<x<<" dopo l'incremento,\n"
      <<"\tmentre la x di chi mi chiama vale "<<n<<endl;
  {
    int x=0;
    cout<<"Sono la funzione dentro il blocco e la mia x vale "<<x<<",\n"
	<<"\tmentre la x di chi mi chiama vale "<<n<<endl ;
    x++;
    cout<<"Sono la funzione dentro il blocco e la mia x vale "<<x<<" dopo "
	<<"l'incremento,\n\tmentre la x di chi mi chiama vale "<<n<<endl ;
  }  
}
