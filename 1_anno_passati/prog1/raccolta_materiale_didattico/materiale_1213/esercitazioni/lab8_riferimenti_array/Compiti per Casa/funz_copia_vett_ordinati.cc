/* Esercizio:
Scrivere una funzione:

void copiaord (int v1[], int n1, int v2[], int n2, int v3[]);

che riceve per parametri tre vettori di interi;
i primi due vettori sono ORDINATI ed hanno dimensioni rispettivamente n1 e n2,
la funzione assume che il terzo vettore abbia dimensioni n1+n2 e vi copia, in
modo ordinato, gli elementi dei due vettori

Si scriva poi un main() che compie le seguenti azioni:
a) definisce ed inizializza due costanti n1 ed n2;
b) definisce tre vettori di interi di dimensioni n1, n2 ed n1+n2;
c) per entrambi i primi due vettori, chiede all'utente di inserire i valori in
   esso contenuti in ordine crescente
c) copia il contenuto di entrambi i vettori nel terzo vettore, utilizzando la 
   funzione copiaord();
d) stampa il terzo vettore.
*/

#include <iostream>

using namespace std ;

void copiaord (int v1[], int n1, int v2[], int n2, int v3[])
{
  int i1=0, i2=0, i3=0;

  while (i1 < n1 && i2 < n2)
  {
    if (v1[i1]<v2[i2]) v3[i3++]=v1[i1++];
    else v3[i3++]=v2[i2++];
  }

  if (i1==n1) 
    while (i2<n2) v3[i3++]=v2[i2++];
  else 
    while (i1<n1) v3[i3++]=v1[i1++];
}

void inizializzavettore (int v[], int n)
{
  int i ; // Indice nei cicli
  cout<<"\nInserisci i "<<n<<" elementi del vettore in ordine crescente\n" ;
  for (i=0; i<n; i++) cin>>v[i] ;
  
}

int main() 
{
  int i ; // Indice nei cicli
  const int n1=3, n2=4;
  int v1[n1], v2[n2], v3[n1+n2];

  // vettore 1
  inizializzavettore (v1, n1);
  inizializzavettore (v2, n2);

  copiaord (v1,n1,v2,n2, v3);
  
  // Stampa nuovo vettore:
  cout<<"\nIl vettore risultante e' : \n" ;
  for (i=0; i<n1+n2; i++) cout<<v3[i]<<" " ;
  cout<<endl ;

  return 0 ;
}

