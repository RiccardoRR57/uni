/* Esercizio:
Scrivere una funzione:

int init (int vett[], int vett2[], int n);

che riceve in ingresso due vettori di interi di uguale dimensione e un intero
n pari alla dimensione dei due vettori, inizializza il secondo vettore con i 
soli interi PARI (contenuti nel vettore di partenza) 
e ritorna il numero di elementi significativi contenuti nel nuovo vettore.
Se il numero di interi PARI contenuti nel primo vettore e' minore di
n, la funzione assegna agli elementi nelle posizioni 'vuote' del secondo 
vettore il valore -1.
Ad esempio, se il primo vettore in ingresso ha dimensione 5 e contiene i valori
[3, 2, 7, 8, 10], la funzione assegna agli elementi del secondo vettore i 
valori:
[2, 8, 10, -1, -1].

Si scriva poi un main() che compie le seguenti azioni:
a) definisce ed inizializza una costante n;
b) definisce due vettori di interi di dimensione n;
c) chiede all'utente di inserire i valori da inserire nel primo vettore
c) richiama la funzione init() passandole i due vettori;
d) stampa solo i numeri validi contenuti nel secondo vettore (quello contenente
   i numeri pari).
*/

#include <iostream>

using namespace std ;

int init (int vett[], int vett2[], int n)
{
  // calcolo quanti sono gli elementi pari del vettore di partenza:
  int n2=0, i, j;
  for (i=0; i<n; i++) if (vett[i]%2==0) n2++;

  // copio gli elementi pari del vecchio vettore nel nuovo;
  i=0, j=0;
  for (; j<n2; j++)
  {
    while (vett[i]%2) i++;
    vett2[j]=vett[i++];
  }
  for (; j<n ; j++)
    vett2[j] = -1 ;
    
  return n2 ;
}

int main() 
{
  int i ;
  const int n = 5 ;
  int v1[n], v2[n];

  // Inizializzazione vettore:
  cout<<"\n Inserisci i "<<n<<" elementi del vettore :\n" ;
  for (i=0; i<n; i++) cin>>v1[i] ;

  // Inizializzazione nuovo vettore:
  int n2 = init(v1, v2, n);

  /* Stampa solo i numeri validi del nuovo vettore.
     Nota: nel seguente ciclo si sfrutta la conoscenza del valore n2
     per sapere quali dove finisce la sequenza di elementi validi contenuti nel
     vettore v2. Quindi l'inizializzazione degli
     elementi non validi di v2 ad un qualsiasi valore speciale (in questo
     esercizio sono stati inizializzati a -1) e' stata una
     operazione superflua. Un approccio complementare era
     il seguente: senza memorizzare in una variabile
     (in questo caso n2) il numero di elementi validi, si
     poteva sfruttare invece il fatto che il primo elemento di v2 contenente
     il valore -1 delimitava la fine della sequenza dei valori validi
   */
  cout<<"\nIl vettore dei numeri pari e' :\n" ;
  for (i=0; i<n2; i++) cout<<v2[i]<<" " ;
  cout<<endl ;
   
  return 0 ;
}

