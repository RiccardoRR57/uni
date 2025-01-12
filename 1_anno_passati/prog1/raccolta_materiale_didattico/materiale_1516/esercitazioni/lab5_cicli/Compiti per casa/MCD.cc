/* MCD
 * 
 * Scrivere un programma che legge in ingresso due numeri e ne stampa il
 * massimo comun divisore. Utilizzare il seguente algoritmo:
 * Siano a e b i due numeri in questione. Finche' b e' diverso da zero, si 
 * calcola il resto della divisione intera tra a e b, si assegna ad a il 
 * valore di b e si assegna a b il valore del resto appena calcolato.
 * Quando b diventa pari a zero si termina ed il valore di a e' proprio il 
 * massimo comun divisore tra i due valori iniziali.
 *
 * Esempio dell'algoritmo. Nell'esempio e' riportato il valore assunto da a, b
 * e dal resto in ciascuno dei 4 passi necessari per arrivare alla soluzione:
 *
 *	a	b	resto
 * 1:	35	21	14		
 * 2:	21	14	7
 * 3:	14	7	0
 * 4:	7	0
 */

#include <iostream>

using namespace std ;

int main()
{
    int a, b ;

    cout<<"Inserisci i due numeri : " ;
    cin>>a>>b;
    while (b != 0) {
    	int resto = a%b ;
	a = b ;
	b = resto ;
    }
    cout<<"Il massimo comun divisore e' "<<a<<endl ;

    return 0 ;
}
