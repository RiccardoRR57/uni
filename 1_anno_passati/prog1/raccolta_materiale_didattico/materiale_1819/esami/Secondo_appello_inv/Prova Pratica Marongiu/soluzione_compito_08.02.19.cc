#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

const char FILE_BRANI[] = "brani.txt";
const char FILE_SERVER[] = "servers.txt";
const int MAX_LEN = 21;

struct Brano
{
  char artista[MAX_LEN];
  char titolo[MAX_LEN];
  int anno;
  char genere;
  int downloads;
};

struct Server
{
  char nomeServer[MAX_LEN];
  char tipoServer;
  int totDownloads;
};

Brano * leggiBrani (const char filename[], int &dim)
{
  Brano *b = 0;
  int count, i;
  ifstream f(FILE_BRANI);

  if (f)
  {
    f >> count;

    b = new Brano[count];

    for (i = 0; i < count; i++)
    {
      f >> b[i].artista >> b[i].titolo >> b[i].anno;
      f >> b[i].genere >> b[i].downloads;
    }

    dim = count;
  }

  return b;
}

Server * leggiServer (const char filename[], int &dim)
{
  Server *s = 0;
  int count, i;
  ifstream f(FILE_SERVER);

  if (f)
  {
    f >> count;

    s = new Server[count];

    for (i = 0; i < count; i++)
      f >> s[i].nomeServer >> s[i].tipoServer;

    dim = count;
  }

  return s;
}

void stampaBrani (Brano b[], int dim, char filtro)
{
  int i;

  for (i = 0; i < dim; i++)
  {
    if (b[i].genere == filtro || filtro == '_')
    {
      cout << "BRANO (" << i << ")";
      cout << "\t" << b[i].artista << "\t" << b[i].titolo << "\t(";
      cout << b[i].anno << " - " << b[i].genere << ").\tDownloads = ";
      cout << b[i].downloads << "." << endl;
    }
  }
}



Brano * cercaNelleDate (Brano b[], const int dim, int y1, int y2, int &dimR)
{
  int i, count = 0;
  int *indexes = new int[dim];
  Brano *result;
  
  for (i = 0; i < dim; i++)
    if ((b[i].anno >= y1) && (b[i].anno <= y2))
      indexes[count++] = i;

  result = new Brano[count];

  for (i = 0; i < count; i++)
    result[i] = b[indexes[i]];

  dimR = count;

  delete [] indexes;

  return result;
}


// Implements selection sort on totDownloads
void ssort (Server s[], int dimS)
{
  for(int j = 0; j < dimS - 1 ; j++)
    for(int i = j + 1 ; i < dimS ; i++) 
      if(s[i].totDownloads > s[j].totDownloads)
	{
	  // swap
	  Server aux = s[i]; 
	  s[i] = s[j]; 
	  s[j] = aux;
	}
}


void classifica (Server s[], int dimS, Brano b[], int dimB)
{
  int i;

  // First initialize totDownloads for all servers to 0...
  for (i = 0; i < dimS; i++)
    s[i].totDownloads = 0;

  // ...then calculate the actual cumulated downloads.
  for (i = 0; i < dimB; i++)
  {
    int j = 0;
    char genere = b[i].genere;

    // Search for the server that hosts movies of the same category
    // of the current one
    while (s[j].tipoServer != genere && j < dimS)
      j++;

    if (j < dimS)
      s[j].totDownloads += b[i].downloads;
  }

  // Now reorder server list by decreasing total number of downloads
  ssort (s, dimS);

  // Print for each server
  // (a) its name;
  // (b) the total number of downloads;
  // (c) the list of movies it hosts.
  for (i = 0; i < dimS; i++)
  {
    cout << endl << endl;
    cout << "---------------- " << endl;
    cout << "    SERVER " << i  << endl;
    cout << "---------------- " << endl;

    cout << "Name: " << s[i].nomeServer << ".\nDownloads totali: ";
    cout << s[i].totDownloads << "." << endl;
    stampaBrani (b, dimB, s[i].tipoServer);
  }
}


int main ()
{
  int dimB;
  int dimS;
  Brano *brani = leggiBrani (FILE_BRANI, dimB); 
  if (!brani)
  {
    cout << "\n\n*** ERROR! Could not open " << FILE_BRANI;
    exit (1);
  }
  Server *server = leggiServer (FILE_SERVER, dimS);
  if (!server)
  {
    cout << "\n\n*** ERROR! Could not open " << FILE_SERVER;
    exit (1);
  }

  cout << endl;
  cout << "-----------------------------" << endl;
  cout << "Lista dei brani in catalogo.." << endl;
  cout << "-----------------------------" << endl;
  stampaBrani (brani, dimB, '_');

  int dimF;
  Brano *filtro = cercaNelleDate (brani, dimB, 2000, 2018, dimF);

  cout << endl;
  cout << "--------------------------------------------" << endl;
  cout << "Lista dei brani usciti tra il 2000 e il 2018" << endl;
  cout << "--------------------------------------------" << endl;
  stampaBrani (filtro, dimF, '_');

  classifica (server, dimS, brani, dimB);

  delete [] brani;
  delete [] server;
  delete [] filtro;
 
  return 0;
}
