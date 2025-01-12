/* 
   Scrivere un programma che apra in lettura un file (il cui nome e'
   stabilito a tempo di scrittura del programma) e stampi la lunghezza
   del file in byte.
*/
#include <iostream>
#include <fstream>

using namespace std ;

int main()
{
  ifstream f("prova"); // apro il file in lettura
 
  if (!f) 
  {
  	cerr<<"Errore di apertura\n" ;
  	exit(1);
  }
  f.seekg(0, ios::end);    //sposto il contatore a 0 bytes dalla
    		           //fine del file

  int n = f.tellg();       //leggo la posizione corrente del contatore

  cout<<"Il file contiene "<<n<<" byte\n" ;

  return 0;
}
