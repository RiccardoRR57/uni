#include <iostream>
#include <fstream>

using namespace std;

const int MAXLUN = 21;
const int NUMGIORNI = 5;
const char NOMEFILE[] = "Doodle.dat";

enum stato_t { DISPONIBILE, NON_DISPONIBILE} ;

struct giocatore_t {
	char nome[MAXLUN];
	stato_t giorni[NUMGIORNI];
};

struct doodle_t {
	giocatore_t *giocatori;
	int num_giocatori;
	int dim_array;
	int num_disponibili[NUMGIORNI];
};

void inizializza(doodle_t &d)
{
	d.num_giocatori = d.dim_array = 0;
	for (int i = 0 ; i < NUMGIORNI ; i++)
		d.num_disponibili[i] = 0 ;
}

void ingrandisci_doodle(doodle_t &d)
{
	if (d.num_giocatori == d.dim_array) {

		int nuova_dim = d.dim_array == 0 ? 1 : d.dim_array*2;
		giocatore_t *nuovo = new giocatore_t[nuova_dim];

		for (int i = 0 ; i < d.dim_array ; i++)
			nuovo[i] = d.giocatori[i];

		delete [] d.giocatori;
		d.giocatori = nuovo;

		d.dim_array = nuova_dim;
	}
}

void aggiungi_giocatore(doodle_t &d, const giocatore_t &g)
{
	ingrandisci_doodle(d);

	d.giocatori[d.num_giocatori] = g;
	d.num_giocatori++;

	for (int i = 0 ; i < NUMGIORNI ; i++)
		if (g.giorni[i] == DISPONIBILE)
			d.num_disponibili[i]++;
}

bool salva_doodle(const doodle_t &d)
{
	ofstream f(NOMEFILE);

	f.write(reinterpret_cast<const char *>(&d.dim_array),
		sizeof(int));
	f.write(reinterpret_cast<const char *>(d.giocatori),
		d.dim_array * sizeof(giocatore_t));
	f.write(reinterpret_cast<const char *>(&d.num_giocatori),
		sizeof(int));
	f.write(reinterpret_cast<const char *>(d.num_disponibili),
		NUMGIORNI * sizeof(int));

	return f;
}

bool carica_doodle(doodle_t &d)
{
	ifstream f(NOMEFILE);

	if (!f)
		return false;

	int nuova_dim;
	f.read(reinterpret_cast<char *>(&nuova_dim),
		sizeof(int));

	if (nuova_dim != d.dim_array && d.dim_array > 0) {
		delete [] d.giocatori;
		d.giocatori = 0;
	}

	if (d.giocatori == 0 && nuova_dim > 0) {
		d.giocatori = new giocatore_t[nuova_dim];
		d.dim_array = nuova_dim;
	}

	f.read(reinterpret_cast<char *>(d.giocatori),
		d.dim_array * sizeof(giocatore_t));

	f.read(reinterpret_cast<char *>(&d.num_giocatori),
		sizeof(int));

	f.read(reinterpret_cast<char *>(d.num_disponibili),
		NUMGIORNI * sizeof(int));

	return f;
}

bool leggi_giorni(stato_t giorni[])
{
	cout<<"Inserisci stringa disponibilita': ";

	for (int i = 0 ; i < NUMGIORNI ; i++) {
		char c;
		cin>>c;
		if (c != '*' && c!= '-')
			return false;

		if (c == '*')
			giorni[i] = DISPONIBILE;
		else
			giorni[i] = NON_DISPONIBILE;
	}

	return true;
}

void stampa_doodle(const doodle_t &d)
{
	cout<<"L M M G V Nome"<<endl;
	for (int i = 0 ; i < d.num_giocatori ; i++) {
		for (int j = 0 ; j < NUMGIORNI ; j++)
			if (d.giocatori[i].giorni[j] == DISPONIBILE)
				cout<<"* ";
			else
				cout<<"- ";
		cout<<d.giocatori[i].nome<<endl;
	}

}

/*
 * Ritorna l'indice del giorno migliore nel doodle s, iniziando a
 * contare da 1. Se nessun giocatore è mai disponibile, allora
 * ritorna 0.
 */
int scegli_serata(const doodle_t &d)
{
	int disponibili = 0, migliore = -1;

	for (int i = 0 ; i < NUMGIORNI ; i++)
		if (d.num_disponibili[i] > disponibili) {
			migliore = i;
			disponibili = d.num_disponibili[i];
		}

	return migliore + 1;
}

int main()
{
	doodle_t doodle;
	inizializza(doodle);

	const char menu[] =
		"1. Inserisci giocatore\n"
		"2. Stampa Doodle\n"
		"3. Salva Doodle\n"
		"4. Carica Doodle\n"
		"5. Scegli serata\n"
		"6. Esci\n";

	const char nomi_giorni[][10] =
		{"Nessuno", "Lunedi", "Martedi", "Mercoledi", "Giovedi", "Venerdi"};

	while (true) {
		cout<<menu<<endl;
		int scelta;
		cin>>scelta;

		cout<<endl ; // per il corretto funzionamento del tester

		switch (scelta) {
		case 1: {
			giocatore_t g;

			cout<<"Inserisci nome giocatore: ";
			cin>>g.nome;
			if (!leggi_giorni(g.giorni)) {
				cout<<"Formato giorni errato"<<endl;
				break;
			}
			aggiungi_giocatore(doodle, g);
		}
			break;
		case 2:
			stampa_doodle(doodle);
			break;
		case 3:
			salva_doodle(doodle);
			break;
		case 4:
			carica_doodle(doodle);
			break;
		case 5:
			cout<<"La sera migliore è il "
			    <<endl
			    <<nomi_giorni[scegli_serata(doodle)]
			    <<endl;
			break;
		case 6:
			return 0;
		default:
			cout<<"Scelta errata"<<endl;
		}
	}

	return 1;
}
