#include <cstdlib>
#include <iostream>
#include <cmath>

using namespace std ;

/*
   La traccia e' nel file traccia_test_rand.pdf 
*/

// Se non conoscete la ricorsione, trascurate pure la seguente
// funzione
long double v_medio_ric(const long double valori[], int n) 
{
  if (n == 1)
    return valori[0] ;
  return ( v_medio_ric(valori, n/2) + v_medio_ric(valori + n/2, n/2) ) / 2 ;
}

int main()
{
  const int S = 15 ; 
  const unsigned int NUM_PROVE = pow(2., S) ; // NUM_PROVE = 2^S
  long double min, max ;
  long double valori[NUM_PROVE] ;
  // il valor medio atteso (ossia quello che ci aspettiamo) e' 
  // circa uguale a RAND_MAX/2
  int medio_atteso = RAND_MAX/2 ;
  long double val_medio, errore, diff ;

  // errore massimo ammesso tra il risultato della procedura iterativa e
  // quello della procedura ricorsiva; l'errore e' espresso in 
  // percentuale rispetto al valore medio atteso
  const double err_max = 0.01 ;
  
  srand(1) ;
  
  cout<<"Testo il generatore di numeri casuali su "<<NUM_PROVE<<" eventi\n" ;

  // caricamento dei valori nel vettore
  min = max = valori[0] = rand() ;
  for (int i = 1 ; i < NUM_PROVE ; i++) {
    valori[i] = rand() ;
    min = valori[i] < min ? valori[i] : min ;
    max = valori[i] > max ? valori[i] : max ;
  }
	
  // calcoliamo il valor medio mediante una procedura ricorsiva
  // (che non distrugge il contenuto del vettore iniziale)
  // Se non conoscete la ricorsione, trascurate pure l'invocazione di
  // questa funzione
  val_medio = v_medio_ric(valori, NUM_PROVE) ;
  
  // segue il calcolo del valor medio per via iterativa
  // la seguente procedura lavora sul vettore stesso, per
  // cui ne altera il contenuto.
  // In uscita dal ciclo (for) piu' esterno, il primo elemento del 
  // vettore contiene il valor medio che stiamo cercando
  for (int j = 1 ; j <= S ; j++) {
    for (int i = 0 ; i < NUM_PROVE ; i += (1<<j)) 
      valori[i] = (valori[i] + valori[i + (1<<(j-1))]) / 2 ;
  } 
	
  cout<<"\nValore minimo: "<<min<<endl ;
  cout<<"Valore massimo: "<<max<<endl ;
  cout<<"\nValor medio (proc. iterativa): "<<valori[0]<<endl ;
  cout<<"Valor medio (proc. ricorsiva): "<<val_medio<<endl ;
  
  // calcolo dell'errore
  errore = valori[0] - val_medio ;
  errore = errore > 0.0 ? errore : -errore ;
  
  // esprimiamo l'errore in percentuale rispetto al valore medio atteso
  errore = 100 * errore / medio_atteso ;
  if (errore > err_max) {
	  cout<<"Errore: lo scostamento tra i valori medi calcolati e' "
	      <<"eccessivo\n" ; 
	  return 0 ;
  }
  cout<<"Scostamento tra il valor medio ritornato dalla proc. iterativa "
      <<"e quello\nritornato dalla proc. ricorsiva: "<<errore<<endl ;
	    
  // calcolo della diferenza tra il valore calcolato con la procedura
  // ricorsiva e quello atteso
  diff = medio_atteso - val_medio ;
  diff = diff > 0 ? diff : -diff ;
	
  // esprimiamo diff in percentuale rispetto al valore medio medio atteso
  diff = 100*diff/medio_atteso ;
  cout<<"\nValor medio atteso: "<<medio_atteso<<endl ;
  cout<<"Scostamento tra il valor medio calcolato "
      <<"e quello atteso: "<<diff<<"%"<<endl ;
}    

