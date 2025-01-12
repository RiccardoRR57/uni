#include <iostream>
#include <fstream>

using namespace std;

const int MAXLUN = 50;
const char NOMEFILE[] = "docenti.txt";

// descrittore di un docente
struct docente_t {
	char cognome[MAXLUN]; // cognome del docente (una parola)
	unsigned int preferenze[3]; // preferenza per ciascun corso:
				    // tre numeri interi compresi tra
				    // 0 e 10
	bool assegnato; // variabile su supporto per i punti 5 e 6
};

// descrittore dell'insieme dei docenti e delle loro preferenze
struct ins_docenti_t {
	docente_t *docenti;
	unsigned int num_docenti;
};

/*
 * Inizializza l'insieme d a vuoto, assumendo che non sia mai stato
 * inizializzato prima.
 */
void inizializza(ins_docenti_t &d)
{
	d.num_docenti = 0;
}

/*
 * Reinizializza l'insieme dei docenti d a contenere N
 * docenti. L'eventuale precedente contenuto dell'insieme è
 * perso. Legge il contenuto dell'insieme dall'inout stream is. Se
 * da_file è vero, allora assume che is sia collegato ad un file in
 * cui è stato salvato il contenuto dell'insieme. Ritorna vero in caso
 * di successo, falso altrimenti.
 */
bool reinizializza(ins_docenti_t &d, unsigned int N, istream &is, bool da_file)
{
	if (d.num_docenti > 0 && d.num_docenti != N) {
		delete [] d.docenti;
		d.num_docenti = 0;
	}

	if (d.num_docenti == 0 && N > 0)
		d.docenti = new docente_t[N];

	d.num_docenti = N;

	if (N > 0 && !da_file)
		cout<<"Inserire i nomi dei docenti e le preferenze:"<<endl;

	for (unsigned int i = 0 ; i < N ; i++) {
		is>>d.docenti[i].cognome;
		for (int j = 0 ; j < 3 ; j++) {
			is>>d.docenti[i].preferenze[j];
			if (d.docenti[i].preferenze[j] > 10)
				return false;
		}
		d.docenti[i].assegnato = false;
	}

	return true;
}

/*
 * Scrive il contenuto dell'insieme d sull'ostream os. Se su_file è
 * vero, assume che os sia associato al file in cui va salvato
 * l'insieme, e scrive quindi l'insieme in un formato adatto allo
 * scopo. Ritorna vero in caso di successo, falso altrimenti.
 */
bool scrivi_insieme(const ins_docenti_t &d, ostream &os, bool su_file)
{
	if (!su_file)
		os<<"Corsi: Programmazione I, Algoritmi, Architettura"<<endl
		  <<"Docenti e preferenze:"<<endl;
	else
		os<<d.num_docenti<<endl;

	for (unsigned int i = 0 ; i < d.num_docenti ; i++) {
		os<<d.docenti[i].cognome;

		for (int j = 0 ; j < 3 ; j++)
			os<<' '<<d.docenti[i].preferenze[j];
		os<<endl;
	}

	return static_cast<bool>(os);
}

/*
 * Carica il contenuto dell'insieme dal file. L'eventuale precedente
 * contenuto è perso. Ritorna vero in caso di successo, falso
 * altrimenti.
 */
bool carica_insieme(ins_docenti_t &d)
{
	ifstream f(NOMEFILE);

	if (!f)
		return false;

	int N;
	f>>N;

	if (!reinizializza(d, N, f, true))
		return false;

	return static_cast<bool>(f);
}

/*
 * Stampa su stdout un assegnamento ottimale di docenti ai corsi. Se
 * versione2 è vero, allora controlla anche che nessuno dei docenti
 * assegnati abbia, per qualche altro corso, una preferenza maggiore
 * rispetto a tutti gli altri docenti ancora da assegnare.
 *
 * Per realizzare la seconda modalità di funzionamento, si utilizza il
 * seguente stratagemma: 1) si permette ai docenti di essere assegnati
 * a più di un corso, 2) si controlla se effettivamente un docente era
 * da assegnare a più di un corso, ed in tal caso si dichiara il
 * fallimento.
 */
void assegna_docenti(ins_docenti_t &d, bool versione2)
{
	if (d.num_docenti == 0)
		return;

	int *assegnamenti = new int[d.num_docenti];

	for (unsigned int i = 0 ; i < d.num_docenti ; i++)
		assegnamenti[i] = -1;

	for (unsigned int i = 0 ; i < 3 ; i++) {
		int max_pref_idx = -1; // nessun docente per il momento
		for (unsigned int j = 0 ; j < d.num_docenti ; j++)
			if ((versione2 || !d.docenti[j].assegnato) &&
			    (max_pref_idx == -1 || d.docenti[j].preferenze[i] >
			     d.docenti[max_pref_idx].preferenze[i]))
				max_pref_idx = j;
		assegnamenti[i] = max_pref_idx;
		d.docenti[max_pref_idx].assegnato = true;
	}

	if (versione2 &&
	    (assegnamenti[0] == assegnamenti[1] ||
	     assegnamenti[0] == assegnamenti[2] ||
	     assegnamenti[1] == assegnamenti[2])
		) {
		cout<<"Assegnamento fallito"<<endl;
		return;
	}

	for (unsigned int i = 0 ; i < 3 && assegnamenti[i] != -1 ; i++) {
		if (i > 0)
			cout<<' ';
		cout<<d.docenti[assegnamenti[i]].cognome;
	}
	cout<<endl;

	delete [] assegnamenti;

	for (unsigned int i = 0 ; i < d.num_docenti ; i++)
		d.docenti[i].assegnato = false;
}

int main()
{
	ins_docenti_t ins;
	inizializza(ins);

	const char menu[] =
		"1. Inizializza insieme docenti e preferenze\n"
		"2. Stampa insieme\n"
		"3. Salva insieme\n"
		"4. Carica insieme\n"
		"5. Assegna docenti\n"
		"6. Assegna docenti 2\n"
		"7. Esci\n";

	while (true) {
		cout<<menu<<endl;
		int scelta;
		cin>>scelta;

		cout<<endl ; // per il corretto funzionamento del tester

		switch (scelta) {
		case 1: {
			cout<<"Numero di docenti: ";
			int N;
			cin>>N;
			if (!reinizializza(ins, N, cin, false))
				cout<<"Inizializzazione fallita"<<endl;
		}
			break;
		case 2:
			scrivi_insieme(ins, cout, false);
			break;
		case 3: {
			ofstream f(NOMEFILE);
			if (!scrivi_insieme(ins, f, true))
				cout<<"Salvataggio fallito"<<endl;
		}
			break;
		case 4:
			if (!carica_insieme(ins))
				cout<<"Caricamento fallito"<<endl;
			break;
		case 5:
			assegna_docenti(ins, false);
			break;
		case 6:
			assegna_docenti(ins, true);
			break;
		case 7:
			return 0;
		default:
			cout<<"Scelta errata"<<endl;
		}
	}

	return 1;
}
