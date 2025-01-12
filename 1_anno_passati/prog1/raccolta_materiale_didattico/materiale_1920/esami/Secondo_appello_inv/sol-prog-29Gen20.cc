#include <iostream>
#include <fstream>

using namespace std;

const int MAXLUN = 20;
const int NUMGIORNI = 5;
const char NOMEFILE[] = "sondaggio.dat";

// stato di un partecipante per un dato giorno
enum stato_t { DISPONIBILE, NON_DISPONIBILE} ;

// descrittore di un partecipante
struct partecipante_t {
	char nome[MAXLUN+1];	   // nome del partecipante
	stato_t giorni[NUMGIORNI]; // stato del partecipante per i vari giorni
};

// descrittore del sondaggio per i giorni lavorativi di una settimana
struct sondaggio_t {
	partecipante_t *partecipanti;	// array dinamico dei partecipanti
	int num_partecipanti;		// numero attuale dei partecipanti
	int dim_array;			// lunghezza attuale array dinamico
	int num_disponibili[NUMGIORNI]; // vettore contenente il
					// numero di partecipanti
					// disponibili per ciascun giorno
};

/*
 * Inizializza il sondaggio s a vuoto, assumendo che non sia stato mai
 * inizializzato prima.
 */
void inizializza(sondaggio_t &s)
{
	s.num_partecipanti = s.dim_array = 0;
	for (int i = 0 ; i < NUMGIORNI ; i++)
		s.num_disponibili[i] = 0 ;
}

/*
 * Aggiunge il partecipante p al sondaggio s.
 */
void aggiungi_partecipante(sondaggio_t &s, const partecipante_t &p)
{
	if (s.num_partecipanti == s.dim_array) {

		int nuova_dim = s.dim_array == 0 ? 1 : s.dim_array*2;
		partecipante_t *nuovo = new partecipante_t[nuova_dim];

		for (int i = 0 ; i < s.dim_array ; i++)
			nuovo[i] = s.partecipanti[i];

		delete [] s.partecipanti;
		s.partecipanti = nuovo;

		s.dim_array = nuova_dim;
	}

	s.partecipanti[s.num_partecipanti] = p;
	s.num_partecipanti++;

	for (int i = 0 ; i < NUMGIORNI ; i++)
		if (p.giorni[i] == DISPONIBILE)
			s.num_disponibili[i]++;
}

/*
 * Salva il sondaggio s su un file binario dal nome
 * predefinito. Ritorna vero in caso di successo, falso altrimenti.
 */
bool salva_sondaggio(const sondaggio_t &s)
{
	ofstream f(NOMEFILE);

	f.write(reinterpret_cast<const char *>(&s.dim_array),
		sizeof(int));
	f.write(reinterpret_cast<const char *>(s.partecipanti),
		s.dim_array * sizeof(partecipante_t));
	f.write(reinterpret_cast<const char *>(&s.num_partecipanti),
		sizeof(int));
	f.write(reinterpret_cast<const char *>(s.num_disponibili),
		NUMGIORNI * sizeof(int));

	return f;
}

/*
 * Carica il sondaggio s dal file. Il precedente contenuto del
 * sondaggio e' perso. Ritorna vero in caso di successo, falso
 * altrimenti.
 */
bool carica_sondaggio(sondaggio_t &s)
{
	ifstream f(NOMEFILE);

	if (!f)
		return false;

	int nuova_dim;
	f.read(reinterpret_cast<char *>(&nuova_dim),
		sizeof(int));

	if (nuova_dim != s.dim_array && s.dim_array > 0) {
		delete [] s.partecipanti;
		s.partecipanti = 0;
	}

	if (s.partecipanti == 0 && nuova_dim > 0) {
		s.partecipanti = new partecipante_t[nuova_dim];
		s.dim_array = nuova_dim;
	}

	f.read(reinterpret_cast<char *>(s.partecipanti),
		s.dim_array * sizeof(partecipante_t));

	f.read(reinterpret_cast<char *>(&s.num_partecipanti),
		sizeof(int));

	f.read(reinterpret_cast<char *>(s.num_disponibili),
		NUMGIORNI * sizeof(int));

	return f;
}

/*
 * Funzione di supporto per leggere la stringa delle
 * disponibilita'. Trasforma tale stringa nel vettore giorni.
 */
bool leggi_giorni_disponibili(stato_t giorni[])
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

/*
 * Stampa il sondaggio s.
 */
void stampa_sondaggio(const sondaggio_t &s)
{
	cout<<"L M M G V Nome"<<endl;
	for (int i = 0 ; i < s.num_partecipanti ; i++) {
		for (int j = 0 ; j < NUMGIORNI ; j++)
			if (s.partecipanti[i].giorni[j] == DISPONIBILE)
				cout<<"* ";
			else
				cout<<"- ";
		cout<<s.partecipanti[i].nome<<endl;
	}

}

/*
 * Ritorna l'indice del giorno migliore nel sondaggio s, iniziando a
 * contare da 1. Se nessun partecipante è mai disponibile, allora
 * ritorna 0.
 */
int trova_giorno_migliore(const sondaggio_t &s)
{
	int disponibili = 0, migliore = -1;

	for (int i = 0 ; i < NUMGIORNI ; i++)
		if (s.num_disponibili[i] > disponibili) {
			migliore = i;
			disponibili = s.num_disponibili[i];
		}

	return migliore + 1;
}

int main()
{
	sondaggio_t sondaggio;
	inizializza(sondaggio);

	const char menu[] =
		"1. Aggiungi partecipante\n"
		"2. Stampa sondaggio\n"
		"3. Salva sondaggio\n"
		"4. Carica sondaggio\n"
		"5. Trova giorno migliore\n"
		"6. Esci\n";

	const char nomi_giorni[][10] =
		{"Nessuno", "Lunedi", "Martedi", "Mercoledi", "Giovedi",
		 "Venerdi"};

	while (true) {
		cout<<menu<<endl;
		int scelta;
		cin>>scelta;

		cout<<endl ; // per il corretto funzionamento del tester

		switch (scelta) {
		case 1: {
			partecipante_t p;

			cout<<"Inserisci nome partecipante: ";
			cin>>p.nome;
			if (!leggi_giorni_disponibili(p.giorni)) {
				cout<<"Formato giorni errato"<<endl;
				break;
			}
			aggiungi_partecipante(sondaggio, p);
		}
			break;
		case 2:
			stampa_sondaggio(sondaggio);
			break;
		case 3:
			salva_sondaggio(sondaggio);
			break;
		case 4:
			carica_sondaggio(sondaggio);
			break;
		case 5:
			cout<<"Il giorno migliore è il "
			    <<endl
			    <<nomi_giorni[trova_giorno_migliore(sondaggio)]
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
