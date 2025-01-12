/*

Scrivere un programma che, preso in ingresso un numero reale non negativo, 
lo ristampi come frazione in forma minima. Trascurare tutti i problemi di 
overflow.

Possibili output:

Inserisci un numero: 0.5
1/2

Inserisci un numero: 13
13

Inserisci un numero: 1.8
9/5

Ulteriori esercizi: 
1) generalizzare al caso di numero reale qualsiasi
2) gestire problemi di overflow
*/

#include <iostream>

using namespace std ;

int main()
{
    int i;
    double d;
    int numeratore, denominatore = 1;

    cout<<"Inserisci un numero reale non negativo: " ;
    cin>>d ;
    /*
     * Moltiplichiamo iterativamente il numero per dieci,
     * fino a far sparire la parte decimale.
     * In uscita dal ciclo, la variabile i conterra' il numero
     * di cifre dopo la virgola
     * Attenzione: nel seguente codice trascuriamo problemi di overflow
     */
    for (i = 0 ; d != static_cast<int>(d) ; i++) {
        d *= 10 ; 
        denominatore *= 10 ;
    }

    // Troviamo il mcd tra numeratore e denominatore
    int a = numeratore = static_cast<int>(d) ;
    /* 
     * lo static_cast nella precedente istruzione serve a dire al compilatore
     * che sappiamo quello che stiamo facendo, inoltre aiuta il lettore
     * a notare che in quel punto potrebbe esserci una perdita di informazione
     */
    int b = denominatore ;

    while (b != 0) {
    	int resto = a%b ;
    	a = b ;
    	b = resto ;
    }

    // Riduciamo la frazione ai minimi termini
    numeratore /= a ;
    denominatore /= a ;

    // Stampiamo la frazione ridotta ai minimi termini
    cout<<numeratore ;
    if (denominatore > 1)
       cout<<"/"<<denominatore ;

    cout<<endl ;

    return 0;
}
