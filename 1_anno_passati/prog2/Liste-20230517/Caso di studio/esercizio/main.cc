#include <iostream>
#include <fstream>
using namespace std;
#include "tipo.h"
#include "liste.h"
#include "parola.h"
#include <cstring>

/* PUNTO 1 */
parola *load(int &n)
{
  ifstream in("inverted");

  int temp = 0;

  in >> n;

  parola *arr = new parola[n];

  for (int i = 0; i < n; i++)
  {
    in >> arr[i].p;

    in >> arr[i].n_doc;

    for (int j = 0; j < arr[i].n_doc; j++)
    {
      in >> temp;
      arr[i].l = insert_elem(arr[i].l, new_elem(temp));
    }
  }
  in.close();
  return arr;
}

void stampa(parola *p, int n)
{
  for (int i = 0; i < n; i++)
  {
    cout << p[i].p << "\t" << p[i].n_doc << "\t";
    elem * e;
    e = p[i].l;

    while(p[i].l != NULL) {
      cout << p[i].l->inf << ", ";
      p[i].l = tail(p[i].l);
    }
    
    p[i].l = e;
    cout << endl;
  }
  
}

/* PUNTO 2 */
void update(parola *&II, char *fileName, int &n)
{
}

/* PUNTO 3*/

void AND(parola *II, char *W1, char *W2, int n)
{
}

/* MAIN */
int main()
{
  /* INIZIO PUNTO 1 */
  
  ifstream file("inverted");
  int n = 0;
  parola *p = load(n);
  file >> n;
  file.close();
  stampa(p, n);
  /* FINE PUNTO 1 */

  /* INIZIO PUNTO 2 */
  char fileName[256];
  cout << "Inserisci il nome del file:";
  cin >> fileName;
  update(p, fileName, n);
  cout << "Post Update:" << endl;
  stampa(p, n);
  /* FINE PUNTO 2 */

  /* INIZIO PUNTO 3 */
  cout << "Inserisci il primo elemento:" << endl;
  char W1[80];
  cin >> W1;
  cout << "Inserisci il secondo elemento:" << endl;
  char W2[80];
  cin >> W2;
  AND(p, W1, W2, n);
  /* FINE PUNTO 3* */

  return 0;
}
