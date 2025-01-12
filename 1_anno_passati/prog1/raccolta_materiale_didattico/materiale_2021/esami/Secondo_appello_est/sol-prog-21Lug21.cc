#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>

using namespace std;

const char NOMEFILE[] = "puzzle.txt";
const unsigned int LUN_PAROLA = 10;

// descrittore di un puzzle
struct puzzle_t {
	char *caratteri;
	unsigned int N;
};

/*
 * Inizializza puzzle a dimensioni 0x0 assumendo che non sia mai stato
 * inizializzato prima.
 */
void inizializza(puzzle_t &puzzle)
{
	puzzle.N = 0;
}

/*
 * Reinizializza puzzle a dimensioni NxN, leggendo il contenuto del
 * puzzle dall'input stream is. Ritorna vero in caso di successo,
 * falso altrimenti.
 */
bool reinizializza(puzzle_t &puzzle, unsigned int N, istream &is)
{
	if (N != puzzle.N) {
		if (puzzle.N != 0)
			delete [] puzzle.caratteri;

		puzzle.caratteri = 0;
		puzzle.N = N;
	}

	if (puzzle.caratteri == 0 && N > 0)
		puzzle.caratteri = new char[N * N];

	for (unsigned int i = 0 ; i < N * N ; i++) {
		char c;

		is>>c;
		if (c < 'A' || c > 'Z')
			puzzle.caratteri[i] = 'A';
		else
			puzzle.caratteri[i] = c;
	}

	return static_cast<bool>(is);
}

/*
 * Scrive il contenuto di puzzle sull'ostream os. Utilizza un formato
 * adatto alla memorizzazione su file se su_file è vero.  Ritorna vero
 * in caso di successo, falso altrimenti.
 */
bool scrivi_puzzle(const puzzle_t &puzzle, ostream &os, bool su_file)
{
	if (su_file)
		os<<puzzle.N<<endl;

	for (unsigned int i = 0 ; i < puzzle.N * puzzle.N ; i++) {
		if (i%puzzle.N != 0)
			os<<' ';
		os<<puzzle.caratteri[i];

		if ((i+1)%puzzle.N == 0)
			os<<endl;

	}

	return static_cast<bool>(os);
}

/*
 * Carica il contenuto di puzzle da file. L'eventuale precedente
 * contenuto e' perso.  Ritorna vero in caso di successo, falso
 * altrimenti.
 */
bool carica_puzzle(puzzle_t &puzzle)
{
	ifstream f(NOMEFILE);

	if (!f)
		return false;

	unsigned int N;
	f>>N;

	return reinizializza(puzzle, N, f);
}

/*
 * Funzione di servizio che cerca la parola p, dentro puzzle, a
 * partire dalla posizione (i, j) e leggendo verso il basso o verso
 * l'alto nel caso in cui in_basso e', rispettivamente, vero oppure
 * falso. Ritorna vero se trova la parola, falso altrimenti.
 */
bool cerca_parola_da_posizione(const puzzle_t &puzzle, const char p[],
			       unsigned int lun_parola,
			       int i, int j, bool in_basso)
{
	if (in_basso)
		for (unsigned int k = 0 ; k < lun_parola ; k++)
			if (p[k] != puzzle.caratteri[(i+k)*puzzle.N + j])
				return false;

	if (!in_basso)
		for (unsigned int k = 0 ; k < lun_parola ; k++) {
			if (p[k] != puzzle.caratteri[(i-k)*puzzle.N + j])
				return false;
		}

	return true;
}

/*
 * Funzione di servizio che cerca la parola p, dentro puzzle, in
 * verticale, sia verso il basso che verso l'alto. Ritorna vero se
 * trova la parola, falso altrimenti.
 */
bool cerca_parola_verticale(const puzzle_t &puzzle, const char p[],
			    const int lun_parola)
{
	const int max_idx = puzzle.N - lun_parola;
	for (int i = 0 ; i <= max_idx ; i++)
		for (unsigned int j = 0 ; j < puzzle.N ; j++)
			if (cerca_parola_da_posizione(puzzle, p, lun_parola,
						      i, j, true))
				return true;

	const unsigned int min_idx = lun_parola - 1;
	for (unsigned int i = min_idx ; i < puzzle.N ; i++)
		for (unsigned int j = 0 ; j < puzzle.N ; j++)
			if (cerca_parola_da_posizione(puzzle, p, lun_parola,
						      i, j, false))
				return true;

	return false;
}

/*
 * Funzione di servizio che cerca la parola p, globalmente dentro
 * puzzle. Ritorna vero se trova la parola, falso altrimenti.
 */
bool cerca_parola_globale(const puzzle_t &puzzle, const char p[],
			  const int lun_parola)
{
	unsigned int num_rimasti = lun_parola;
	unsigned int num_caratteri['Z' - 'A' + 1];

	for (int i = 0 ; i < 'Z' - 'A' + 1 ; i++)
		num_caratteri[i] = 0;

	for (int i = 0 ; i < lun_parola ; i++)
		num_caratteri[p[i] - 'A']++;

	for (unsigned int i = 0 ; i < puzzle.N * puzzle.N ; i++)
		if (num_caratteri[puzzle.caratteri[i]-'A'] > 0) {
			num_caratteri[puzzle.caratteri[i]-'A']--;
			num_rimasti--;

			if (num_rimasti == 0)
				return true;
		}

	return false;
}

/*
 * Funzione di interfaccia che cerca la parola p dentro puzzle. Se
 * globale e' vero, allora la parola e' cercata globalmente,
 * altrimenti e' cercata in verticale. Stampa PRESENTE se la parola
 * viene trovata, ASSENTE altrimenti.
 */
void cerca_parola(const puzzle_t &puzzle, const char p[], bool globale)
{
	const int lun_parola = strlen(p);

	if (lun_parola == 0) {
		cout<<"ASSENTE"<<endl;
		return;
	}

	bool trovata = false;
	if (globale)
		trovata = cerca_parola_globale(puzzle, p, lun_parola);
	else
		trovata = cerca_parola_verticale(puzzle, p, lun_parola);

	if (trovata)
		cout<<endl<<"PRESENTE"<<endl;
	else
		cout<<endl<<"ASSENTE"<<endl;
}

int main()
{
	puzzle_t puzzle;
	inizializza(puzzle);

	const char menu[] =
		"1. Reinizializza puzzle\n"
		"2. Stampa puzzle\n"
		"3. Salva puzzle\n"
		"4. Carica puzzle\n"
		"5. Trova parola in verticale\n"
		"6. Trova parola globalmente\n"
		"7. Esci\n";

	while (true) {
		cout<<menu<<endl;
		int scelta;
		cin>>scelta;

		cout<<endl ; // per il corretto funzionamento del tester

		switch (scelta) {
		case 1: {
			unsigned int N;

			cout<<"Inserisci dimensioni: ";
			cin>>N;
			reinizializza(puzzle, N, cin);
		}
			break;
		case 2:
			scrivi_puzzle(puzzle, cout, false);
			break;
		case 3: {
			ofstream f(NOMEFILE);

			if (!scrivi_puzzle(puzzle, f, true))
				cout<<"Scrittura su file fallita"<<endl;
		}
			break;
		case 4:
			if (!carica_puzzle(puzzle))
				cout<<"Lettura da file fallita"<<endl;
			break;
		case 5: {
			char p[LUN_PAROLA];

			cout<<"Inserisci parola da cercare: ";
			cin>>p;
			cerca_parola(puzzle, p, false);
		}
			break;
		case 6: {
			char p[LUN_PAROLA];

			cout<<"Inserisci parola da cercare: ";
			cin>>p;
			cerca_parola(puzzle, p, true);
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
