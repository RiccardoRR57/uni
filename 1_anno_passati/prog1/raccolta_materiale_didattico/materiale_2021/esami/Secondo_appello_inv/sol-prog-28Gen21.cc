#include <iostream>
#include <iomanip>
#include <cstring>
#include <fstream>

using namespace std;

const char NOMEFILE[] = "matrice.dat";
const int MAXLUNBUFFER = 100; // lunghezza massima buffer per leggere da stdin
const unsigned int M = 3; // numero di righe della matrice
const unsigned int N = 2; // numero di colonne della matrice

// descrittore della matrice
struct matrice_t {
	char *parole[M][N];	// matrice di puntatori ad array di caratteri
	unsigned int maxlun;	// lunghezza parola più lunga nella matrice
};

/*
 * Inizializza la matrice assumendo che non sia stata gia'
 * inizializzata. Tutte le parole saranno vuote (ma allocate).
 */
void inizializza(matrice_t &m)
{
	for (unsigned int i = 0 ; i < M ; i++)
		for (unsigned int j = 0 ; j < N ; j++) {
			m.parole[i][j] = new char[1];
			m.parole[i][j][0] = '\0';
		}
	m.maxlun = 0;
}

/*
 * Funzione di servizio per leggere da stdin la parola p da
 * sostituire, e le coordinate i e j della posizione in cui
 * sostituirla.
 */
void leggi_parola_coord(char *p, unsigned int &i, unsigned int &j)
{
	cout<<"Parola: ";
	cin>>p;

	cout<<"Coordinate: ";
	cin>>i>>j;
}

/*
 * Sostituisce, con la parola p, la parola presente nella posizione
 * (i, j) all'interno della matrice m. Se accetta_lun_zero e' vero,
 * allora accetta la parola p anche se ha lunghezza 0. Ritorna verso
 * in caso di successo, falso altrimenti.
 */
bool sostituisci_parola(matrice_t &m, const char *p,
			unsigned int i, unsigned int j,
			bool accetta_lun_zero)
{
	if ((!accetta_lun_zero && strlen(p) == 0) ||
	    i >= M || j >= N)
		return false;

	unsigned int nuovalun = strlen(p),
		vecchialun = strlen(m.parole[i][j]);

	if (nuovalun != vecchialun) {
		delete [] m.parole[i][j];
		m.parole[i][j] = new char [nuovalun + 1];
	}

	strcpy(m.parole[i][j], p);

	if (vecchialun == m.maxlun) {
		m.maxlun = 0 ;
		for (unsigned int i = 0 ; i < M ; i++)
			for (unsigned int j = 0 ; j < N ; j++)
				if (strlen(m.parole[i][j]) > m.maxlun)
					m.maxlun = strlen(m.parole[i][j]);
	} else if (nuovalun > m.maxlun)
		m.maxlun = nuovalun;

	return true;
}

/*
 * Stampa la matrice m su stdout.
 */
void stampa_matrice(const matrice_t &m)
{
	for (unsigned int i = 0 ; i < M ; i++) {
		for (unsigned int j = 0 ; j < N ; j++) {
			if (j > 0)
				cout<<' ';
			cout<<setw(m.maxlun + 1)<<setfill(' ')
			    <<m.parole[i][j];
		}
		cout<<endl;
	}
}

/*
 * Salva la matrice m in un file binario. Ritorna verso in caso di
 * successo, falso altrimenti.
 */
bool salva_matrice(const matrice_t &m)
{
	ofstream f(NOMEFILE);

	for (unsigned int i = 0 ; i < M ; i++)
		for (unsigned int j = 0 ; j < N ; j++) {
			unsigned int lun = strlen(m.parole[i][j]);
			f.write(reinterpret_cast<const char *>(&lun),
				sizeof(lun));
			f.write(m.parole[i][j], lun);
		}

	return static_cast<bool>(f);
}

/*
 * Carica il contenuto della matrice m dal file binario. L'eventuale
 * precedente contenuto della matrice e' perso. Ritorna verso in caso
 * di successo, falso altrimenti.
 */
bool carica_matrice(matrice_t &m)
{
	ifstream f(NOMEFILE);

	if (!f)
		return false;

	for (unsigned int i = 0 ; i < M ; i++)
		for (unsigned int j = 0 ; j < N ; j++) {
			unsigned int lun;
			f.read(reinterpret_cast<char *>(&lun),
			       sizeof(lun));
			char *buffer = new char [lun + 1];

			f.read(buffer, lun);
			buffer[lun] = '\0';
			sostituisci_parola(m, buffer, i, j, true);
			delete [] buffer;
		}

	return static_cast<bool>(f);
}

/*
 * All'interno della matrice m, scambia la parola nella posizione (i,
 * j) con la parola nella posizione (i2, j2). Ritorna verso in caso di
 * successo, falso altrimenti.
 */
bool scambia(matrice_t &m, unsigned int i1, unsigned int j1,
	     unsigned int i2, unsigned int j2)
{
	if (i1 >= M || j1 >= N || i2 >= M || j2 >= N)
		return false;

	char *p1 = m.parole[i1][j1];
	char *tmp = new char[strlen(p1) + 1];
	strcpy(tmp, p1);
	sostituisci_parola(m, m.parole[i2][j2], i1, j1, true);
	sostituisci_parola(m, tmp, i2, j2, true);

	return true;
}

/*
 * Trova la posizione della parola di lunghezza minima, presente nella
 * matrice m a partire dalla posizione (i_min, j_min). Memorizza la
 * posizione di tale parola di lunghezza minima all'interno degli
 * stessi indici i_min e j_min. Infine ritorna la lunghezza di tale
 * parola.
 */
unsigned int trova_indici_minimo(const matrice_t &m,
				 unsigned int &i_min,
				 unsigned int &j_min)
{
	unsigned int i2 = i_min, j2_iniziale = j_min;
	unsigned int minlun = strlen(m.parole[i2][j2_iniziale]);

	for (; i2 < M ; i2++) {
		for (unsigned int j2 = j2_iniziale; j2 < N ; j2++) {
			unsigned int lun = strlen(m.parole[i2][j2]);

			if (lun > 0 && (minlun == 0 || lun < minlun)) {
				i_min = i2;
				j_min = j2;
				minlun = strlen(m.parole[i2][j2]);
			}
		}
		j2_iniziale = 0;
	}

	return minlun;
}

/*
 * Scambia la parola presente nella posizione (i,j) nella matrice m,
 * con la parola di lunghezza minima presente nella matrice a partire
 * da tale posizione. Ritorna verso in caso di successo, falso
 * altrimenti.
 */
bool scambia_con_minimo(matrice_t &m, unsigned int i, unsigned int j)
{
	if (i >= M || j >=N || (i == M - 1 && j == N - 1))
		return false;

	unsigned int i_min = i, j_min = j + 1;
	if (j_min == N) {
		i_min++;
		j_min = 0;
	}
	trova_indici_minimo(m, i_min, j_min);
	scambia(m, i, j, i_min, j_min);

	return true;
}

int main()
{
	matrice_t matrice;
	inizializza(matrice);

	const char menu[] =
		"1. Sostituisci parola\n"
		"2. Stampa matrice\n"
		"3. Salva matrice\n"
		"4. Carica matrice\n"
		"5. Scambia parole\n"
		"6. Scambia con parola di lunghezza minima\n"
		"7. Esci\n";

	while (true) {
		cout<<menu<<endl;
		int scelta;
		cin>>scelta;

		cout<<endl ; // per il corretto funzionamento del tester

		switch (scelta) {
		case 1: {
			unsigned int i, j;
			char p[MAXLUNBUFFER];

			leggi_parola_coord(p, i, j);

			if (!sostituisci_parola(matrice, p, i, j, false))
				cout<<"Inizializzazione fallita"<<endl;
		}
			break;
		case 2:
			stampa_matrice(matrice);
			break;
		case 3: {
			if (!salva_matrice(matrice))
				cout<<"Salvataggio fallito"<<endl;
		}
			break;
		case 4:
			if (!carica_matrice(matrice))
				cout<<"Caricamento fallito"<<endl;
			break;
		case 5: {
			unsigned int i, j, i2, j2;
			cout<<"Coordinate prima posizione: ";
			cin>>i>>j;
			cout<<"Coordinate seconda posizione: ";
			cin>>i2>>j2;

			if (!scambia(matrice, i, j, i2, j2))
				cout<<"Scambio fallito"<<endl;
		}
			break;
		case 6: {
			unsigned int i, j;
			cout<<"Coordinate posizione: ";
			cin>>i>>j;

			if (!scambia_con_minimo(matrice, i, j))
				cout<<"Scambio fallito"<<endl;
		}
			break;
		case 7:
			return 0;
		default:
			cout<<"Scelta errata"<<endl;
		}
	}

	return 1;
}
