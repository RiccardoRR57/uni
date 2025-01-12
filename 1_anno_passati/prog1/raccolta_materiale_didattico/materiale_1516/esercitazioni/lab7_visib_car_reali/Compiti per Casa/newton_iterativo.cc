/* Esercizio 
   
   Metodo di Newton per la risoluzione di equazioni trascendenti.
   Data una funzione continua f, che ha UNA ED UNA SOLA radice
   nell'intervallo [a,b], il metodo di Newton trova la radice per
   approssimazioni successive.

   Osservato che, se f ha una ed una sola radice in [a,b], f(a) e f(b)
   sono discordi in segno, il metodo di Newton può essere enunciato come segue:

   Calcolo c=(a+b)/2, ed f(c).
   Se:
   - f(c) == 0, ho trovato la radice.
   - se f(c) è concorde in segno con f(a), posso applicare di nuovo il metodo 
     all'intervallo [c,b]
   - se f(c) è concorde in segno con f(b), posso applicare di nuovo il metodo 
     all'intervallo [a,c]

     L'algoritmo può terminare se:
     - ho trovato una radice.
     - l'intervallo al passo j-esimo ha una estensione minore di un valore di 
       precisione p dato, ossia b - a < p (ad esempio p=10^-6).

     Scrivere un programma che, data una funzione matematica f(x) qualsiasi, 
     rappresentata mediante una funzione C++
     double f(double x) ;
     definita a tempo di scrittura del programma, e letti da stdin due estremi 
     a e b, ed il valore di precisione desiderato, calcoli, mediante il metodo 
     di Newton, una delle radici della funzione contenute nell'intervallo 
     [a, b]. Basandosi sulle precedenti proprietà, il programma deve
     continuare a chiedere di reinserire i due estremi, finché non è certo 
     che in tali estremi sia presente una radice.

     Il metodo di Newton deve essere implementato mediante una funzione:

     double newton(double inf, double sup, double precision);       

     Includendo <cmath> è possibile utilizzare la funzione exp(x) = e^x.
     Data la funzione f(x)=exp(x) - x^2 -2, utilizzare il
     programma per calcolare la sua radice nell'intervallo [0,3] con
     una precisione di 10^-6.  Come controprova della correttezza
     della soluzione, fare stampare il valore assunto dalla funzione
     per x uguale alla radice calcolata.
*/

#include <iostream>
#include <cmath>

using namespace std ;

double f (double x)  {  return exp(x) - x*x -2.0; }

double newton (double inf, double sup, double precision)
{
 double med;
 while (sup-inf>precision)
 {
    med=(inf+sup)/2.0;
    if (f(med)==0.0) return med;
    if (f(med) * f(inf) <0.0) sup=med;
    else inf=med;
 }
 return (inf+sup)/2.0;
}

main ()
{
  double a,b,prec, radice;

  do 
  {
    cout<<"\nInserire i due estremi dell'intervallo : " ;
    cin>>a>>b ;
  } while (b<=a || f(a)*f(b)>0.0);

  do
  {
    cout<<"\nInserire la precisione voluta : " ;
    cin>>prec ;
  } while (prec<=0.0);

  radice = newton (a,b,prec);  
  cout<<"\nUna stima della radice e' "<<radice<<endl ;

}
