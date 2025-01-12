/*
Scrivere un programma che compie le seguenti azioni:
a) definisce ed inizializza due costanti N ed M;
b) definisce tre vettori di interi di dimensioni N, M ed N+M;
c) inizializza ciascuno dei due array con una sequenza di valori ordinata in 
   senso crescente di valori (la sequenza è definita a tempo di scrittura del
   programma);
c) copia il contenuto di entrambi i vettori nel terzo vettore;
   la copia deve essere effettuata visitando non più di una volta ciascun 
   elemento dei primi due vettori;
d) stampa i tre vettori.
*/

#include<iostream>

using namespace std ;

const int N=6 ;
const int M=4 ;

int main()
{
  int a[N]={2,6,7,10,12,15}, 
    b[M]={5,8,13,14}, 
      c[N+M];
  int i=0, j=0, k=0;

  do
    {
      if(a[i] <= b[j])
	c[k++] = a[i++];
      else 
	c[k++] = b[j++];
    }
  while((i<N) && (j<M));   //finche' non ho finito uno dei due array

  if(i<N) //se e' finito l'array b continuo con gli elementi di a
    for(; i<N; i++)
      c[k++] = a[i];
  else //se e' finito a continuo con gli elementi di b
    for(; j<M; j++)
      c[k++] = b[j];		

  /*Visualizzazione array a*/
  cout<<"Array a\n" ;
  for(k=0; k<N; k++)
    cout<<a[k]<<endl ;
  /*Visualizzazione array b*/	
  cout<<"Array b\n" ;
  for(k=0; k<M; k++)
    cout<<b[k]<<endl ;
  /*Visualizzazione fusione*/
  cout<<"Fusione di a e b\n" ;
  for(k=0; k<N+M; k++)
    cout<<c[k]<<endl ;
  return 0;
}
