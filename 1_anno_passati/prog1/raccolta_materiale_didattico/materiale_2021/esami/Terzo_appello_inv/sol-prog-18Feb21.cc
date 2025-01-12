#include <iostream>
#include <iomanip>
#include <cstring>
#include <fstream>

using namespace std;

const char NOMEFILE[] = "codice.dat";

// descrittore di un codice
struct codice_t {
	char *caratteri;	// array dinamico dei caratteri che
				// costituiscono il codice

	unsigned int N;		// numero di righe
	unsigned int M;		// numero di colonne (lunghezza di una riga)
};

/*
 * Inizializza il codice c a vuoto, assumendo nessuna inizializzazione
 * precedente.
 */
void inizializza(codice_t &c)
{
	c.N = 0;
}

/*
 * Reinizializza il codice c a contenere N righe da M caratteri
 * ciascuna. Legge il nuovo contenuto del codice dall'istream
 * is. Assume che il codice c sia già stato inizializzato almeno una
 * volta. L'eventuale precedente contenuto del codice è perso. Ritorna
 * vero in caso di successo, falso altrimenti.
 */
bool reinizializza(codice_t &c,
		   unsigned int N, unsigned int M,
		   istream &is)
{
	if (c.N != 0 && c.M != 0 && (c.N * c.M != N * M)) {
		delete [] c.caratteri;
		c.N = 0;
	}

	if (c.N == 0 && N > 0 && M > 0) {
		c.caratteri = new char[N * M];
	}

	c.N = N;
	c.M = M;

	for (unsigned int i = 0 ; i < N * M ; i++) {
		is>>c.caratteri[i];
		if (c.caratteri[i] < 'A' || c.caratteri[i] > 'Z') {
			cout<<"Inserisci di nuovo il carattere"<<endl;
			i--;
		}
	}

	return static_cast<bool>(is);
}

// Stampa il codice c su stdout.
void stampa_codice(const codice_t &c)
{
	for (unsigned int i = 0 ; i < c.N * c.M ; i++) {
		if (i>0) {
			if (i % c.M == 0)
				cout<<" | ";
			else
				cout<<' ';
		}
		cout<<c.caratteri[i];
	}
	cout<<endl;
}

/*
 * Salva il codice c su file binario. Ritorna vero in caso di
 * successo, falso altrimenti.
 */
bool salva_codice(codice_t &c)
{
	ofstream f(NOMEFILE);

	f.write(reinterpret_cast<const char *>(&(c.N)), sizeof(c.N));
	f.write(reinterpret_cast<const char *>(&(c.M)), sizeof(c.M));
	f.write(c.caratteri, sizeof(char) * c.N * c.M);

	return static_cast<bool>(f);
}

/*
 * Carica il codice c dal file. L'eventuale precedente codice è
 * perso. Ritorna vero in caso di successo, falso altrimenti.
 */
bool carica_codice(codice_t &c)
{
	ifstream f(NOMEFILE);

	unsigned int N, M;
	f.read(reinterpret_cast<char *>(&N), sizeof(N));
	f.read(reinterpret_cast<char *>(&M), sizeof(M));
	return (reinizializza(c, N, M, f));
}

// Ritorna l'indice, all'interno dell'array che rappresenta il codice
// c, del carattere in posizione (i, j).
unsigned int pos(const codice_t &c, unsigned int i, unsigned int j)
{
	return j*c.M + i;
}

/*
 * In caso di successo, memorizza nel carattere car il carattere
 * contenuto nella posizione (i, j) del codice c. Ritorna vero in caso
 * di successo, falso altrimenti.
 */
bool ritorna_carattere(const codice_t &c, unsigned int i, unsigned int j,
		       char &car)
{
	if (i >= c.N || j > c.M)
		return false;

	car = c.caratteri[pos(c, i, j)];

	return true;
}

// Ruota il codice c.
void ruota_codice(codice_t &c)
{
	if (c.N == 0 || c.M == 0)
		return;

	codice_t nuovo = {0, c.M, c.N} ;

	nuovo.caratteri = new char[c.N * c.M];

	for (unsigned int i = 0 ; i < c.N ; i++)
		for (unsigned int j = 0 ; j < c.M ; j++)
			nuovo.caratteri[pos(nuovo, i, j)] =
				c.caratteri[pos(c, j, i)];

	delete [] c.caratteri;
	c = nuovo;
}

int main()
{
	codice_t codice;
	inizializza(codice);

	const char menu[] =
		"1. Inizializza codice\n"
		"2. Stampa codice\n"
		"3. Salva codice\n"
		"4. Carica codice\n"
		"5. Stampa carattere\n"
		"6. Ruota codice\n"
		"7. Esci\n";

	while (true) {
		cout<<menu<<endl;
		int scelta;
		cin>>scelta;

		cout<<endl ; // per il corretto funzionamento del tester

		switch (scelta) {
		case 1: {
			unsigned int N, M;
			cout<<"Inserisci N, M ed i caratteri del codice: ";
			cin>>N>>M;
			reinizializza(codice, N, M, cin);
		}
			break;
		case 2:
			stampa_codice(codice);
			break;
		case 3:
			if (!salva_codice(codice))
				cout<<"Salvataggio fallito"<<endl;
			break;
		case 4:
			if (!carica_codice(codice))
				cout<<"Caricamento fallito"<<endl;
			break;
		case 5: {
			unsigned int i, j;
			char car;
			cout<<"Inserisci i e j:";
			cin>>i>>j;
			cout<<endl;
			if (ritorna_carattere(codice, i, j, car))
				cout<<car<<endl;
			else
				cout<<"FALLITO"<<endl;
		}
			break;
		case 6:
			ruota_codice(codice);
			break;
		case 7:
			return 0;
		default:
			cout<<"Scelta errata"<<endl;
		}
	}

	return 1;
}
