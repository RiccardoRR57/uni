#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

const int MAXLUN = 50;
const char NOMEFILE[] = "testo.txt";

// legge una riga da istream is e la copia nel buffer riga
void leggi_riga(istream &is, char *riga)
{
 // consuma eventuali sequenze di newline,
 // per evitare errori nella lettura di
 // una riga che si sta per effettuare
	while (is.peek() == '\n')
			is.get() ;

	is.get(riga, MAXLUN) ; // legge una riga
	is.get() ; // consuma il newline che
		   // segue la riga appena letta
}

/*
 * Descrittore di un testo.
 */
struct testo_t {
	char (*righe)[MAXLUN];	// contenuto righe del testo
	int num_righe;		// numero di righe
};

/*
 * Inizializza il testo t a vuoto, assumendo che t non sia ancora mai
 * stato inizializzato.
 */
void inizializza(testo_t &t)
{
	t.num_righe = 0;
}

/*
 * Reinizializza il test t a contenere N righe, lette dall'input
 * stream is. Se da_file e' vero, allora assuem che is sia associato
 * ad un file. Assume che il testo sia già stato inizializzato almeno
 * una volta. Ritorna vero in caso di successo, falso altrimenti.
 */
bool reinizializza(testo_t &t, int N, istream &is, bool da_file)
{
	if (N < 0)
		return false;

	if (t.num_righe != N && t.num_righe > 0) {
		delete [] t.righe;
		t.num_righe = 0;
	}

	if (t.num_righe == 0 && N > 0)
		t.righe = new char[N][MAXLUN];

	t.num_righe = N;

	if (! da_file)
		cout<<"Inserisci righe:"<<endl;

	for (int i = 0 ; i < N ; i++)
		leggi_riga(is, t.righe[i]);

	return is;
}

/*
 * Scrive il contenuto del teto t sull'output stream os, utilizzando
 * un formato opportuno per il salvataggio su file nel caso in cui
 * su_file sia vero. Ritorna vero in caso di successo, falso
 * altrimenti.
 */
bool scrivi_testo(const testo_t &t, ostream &os, bool su_file)
{
	if (su_file)
		os<<t.num_righe<<endl;

	for (int i = 0 ; i < t.num_righe ; i++)
		os<<t.righe[i]<<endl;

	return os;
}

/*
 * Carica il contenuto del testo t da file. L'eventuale precedente
 * contenuto è perso. Ritorna vero in caso di successo, falso
 * altrimenti.
 */
bool carica_testo(testo_t &t)
{
	ifstream f(NOMEFILE);

	if (!f)
		return false;

	int N;
	f>>N;

	if (!reinizializza(t, N, f, true))
		return false;

	return f;
}

bool salta_spazio(const char riga[], int &idx)
{
	if (riga[idx] == ' ' || riga[idx] == '\t') {
		idx++;
		return true;
	}

	return false;
}

/*
 * Ritorna vero se le righe prima e seconda sono uguali, trascurando
 * eventuali differenze nel numero di spazi nel caso in cui
 * salta_spazi sia vero.
 */
bool righe_uguali(const char prima[], const char seconda[], bool salta_spazi)
{
	if (!salta_spazi)
		return !strcmp(prima, seconda);

	int lun1 = strlen(prima);
	int lun2 = strlen(seconda);
	int idx1 = 0, idx2 = 0;

	while (idx1 < lun1 && idx2 < lun2) {
		bool saltato1 = salta_spazio(prima, idx1);
		bool saltato2 = salta_spazio(seconda, idx2);

		if (saltato1 || saltato2)
			continue;

		if (prima[idx1] != seconda[idx2])
			return false;

		idx1++;
		idx2++;
	}

	if (idx1 == lun1 && idx2 == lun2)
		return true;

	return false;
}

/*
 * Legge M righe da standard input, e ritorna vero se tali righe sono
 * presenti, l'una dopo l'altra, nel testo t. Se salta_spazi è vero,
 * allora trascura eventuali differenze nel numero di spazi tra le
 * righe da cercare e quelle contenute nel testo.
 */
bool cerca_righe(const testo_t &t, int M, bool salta_spazi)
{
	testo_t da_cercare;
	inizializza(da_cercare);
	if (!reinizializza(da_cercare, M, cin, false))
		return false;

	if ((M == 0 && t.num_righe > 0) ||
	    M > t.num_righe) {
		delete [] da_cercare.righe;
		return false;
	}

	if (M == 0 && t.num_righe == 0) {
		delete [] da_cercare.righe;
		return true;
	}

	int inizio;
	for (inizio = 0 ; inizio < t.num_righe ; inizio++)
		if (righe_uguali(t.righe[inizio], da_cercare.righe[0],
				 salta_spazi))
			break;

	if (inizio + M > t.num_righe) {
		delete [] da_cercare.righe;
		return false;
	}

	for (int i = 1 ; i < M ; i++) {
		if (!righe_uguali(t.righe[i + inizio], da_cercare.righe[i],
				  salta_spazi)) {
			delete [] da_cercare.righe;
			return false;
		}
	}

	delete [] da_cercare.righe;
	return true;
}

int main()
{
	testo_t t;
	inizializza(t);

	const char menu[] =
		"1. Inizializza testo\n"
		"2. Stampa testo\n"
		"3. Salva testo\n"
		"4. Carica testo\n"
		"5. Cerca righe\n"
		"6. Cerca righe 2\n"
		"7. Esci\n";

	while (true) {
		cout<<menu<<endl;
		int scelta;
		cin>>scelta;

		cout<<endl ; // per il corretto funzionamento del tester

		switch (scelta) {
		case 1: {
			cout<<"Numero righe: ";
			int N;
			cin>>N;

			if (!reinizializza(t, N, cin, false))
				cout<<"Reinizializzazione fallita"<<endl;
		}
			break;
		case 2:
			scrivi_testo(t, cout, false);
			break;
		case 3: {
			ofstream f(NOMEFILE);
			if (!scrivi_testo(t, f, true))
				cout<<"Salvataggio fallito"<<endl;
		}
			break;
		case 4:
			if (!carica_testo(t))
				cout<<"Caricamento fallito"<<endl;
			break;
		case 5: {
			cout<<"Numero righe: ";
			int M;
			cin>>M;

			if (cerca_righe(t, M, false))
				cout<<"Trovate"<<endl;
			else
				cout<<"Non trovate"<<endl;
		}
			break;
		case 6: {
			cout<<"Numero righe: ";
			int M;
			cin>>M;

			if (cerca_righe(t, M, true))
				cout<<"Trovate"<<endl;
			else
				cout<<"Non trovate"<<endl;
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
