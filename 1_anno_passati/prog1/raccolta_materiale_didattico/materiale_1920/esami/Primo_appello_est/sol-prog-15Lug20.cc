#include <iostream>
#include <cstring>
#include <fstream>
#include <time.h>

using namespace std;

const int MAXLUN = 50; // lunghezza massima righe
const int M = 3; // numero di risposte per ogni domanda
const char NOMEFILE[] = "traccia.txt"; // nome del file in cui si salva lo stato

// descrittore di una domanda
struct domanda_t {
	char testo_domanda[MAXLUN];
	char testo_risposte[M][MAXLUN]; // vettore di M risposte
	int idx_corretta; // indice della risposta corretta nel vettore
};

// descrittore di una traccia
struct traccia_t {
	domanda_t *domande; // vettore dinamico di domande
	int N; // numero di domande
};

// inizializza la traccia t a non contenere alcuna domada, assumendo
// che non sia stata già inizializzata
void inizializza(traccia_t &t)
{
	t.N = 0;
}

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
 * Reinizializza la traccia t a contenere N domande, leggendo le
 * domande da is. Se da_file e' vero, allora assume di stare leggendo
 * dal file in cui e' stato salvato lo stato. Lo stato precedente e'
 * perso. Assume che t sia gia' stata inizializzata. Ritorna verso in
 * caso di successo, falso altrimenti.
 */
bool reinizializza(traccia_t &t, int N, istream &is, bool da_file)
{
	if (N < 0)
		return false;

	if (t.N != N && t.N > 0) {
		delete [] t.domande;
		t.N = 0;
	}

	if (t.N == 0)
		t.domande = new domanda_t[N];

	t.N = N;

	for (int i = 0 ; i < N ; i++) {
		if (!da_file)
			cout<<"Testo domanda: ";
		leggi_riga(is, t.domande[i].testo_domanda);

		for (int j = 0 ; j < M ; j++) {
			if (!da_file)
				cout<<"Testo risposta "
				<<static_cast<char>('a'+j)<<": ";
			leggi_riga(is, t.domande[i].testo_risposte[j]);
		}
		if (!da_file)
			cout<<"Indice risposta corretta: ";
		is>>t.domande[i].idx_corretta;

		if (t.domande[i].idx_corretta < 0 ||
		    t.domande[i].idx_corretta >= M)
			return false;
	}

	return static_cast<bool>(is);
}

/*
 * Scrive il contenuto della traccia sull'ostream os, in formato
 * testuale. Se su_file e' vero, allora assume che os sia associato al
 * file in cui salvare lo stato. Ritorna verso in caso di successo,
 * falso altrimenti.
 */
bool scrivi_traccia(const traccia_t &t, ostream &os, bool su_file)
{
	if (su_file)
		os<<t.N<<endl;

	for (int i = 0 ; i < t.N ; i++) {
		if (!su_file)
			os<<i+1<<". ";

		os<<t.domande[i].testo_domanda<<endl;

		for (int j = 0 ; j < M ; j++) {
			if (!su_file) {
				if (j == t.domande[i].idx_corretta)
					os<<"* ";
				os<<static_cast<char>('a'+j)<<") ";
			}
			os<<t.domande[i].testo_risposte[j]<<endl;
		}

		if (su_file)
			os<<t.domande[i].idx_corretta<<endl;
	}
	return true;
}

/*
 * Carica il contenuto della traccia t dal file. L'eventuale
 * precedente contenuto e' perso. Ritorna vero in caso di successo,
 * falso altrimenti.
 */
bool carica_traccia(traccia_t &t)
{
	ifstream f(NOMEFILE);

	if (!f)
		return false;

	int N;
	f>>N;

	if (!reinizializza(t, N, f, true))
		return false;

	return static_cast<bool>(f);
}

/*
 * Stampa il testo della domanda i-esima, e chiede di inserirne la
 * risposta da stdin. Stampa Esatto in caso di risposta corretta,
 * Sbagliato altrimenti.
 */
void fai_domanda(const traccia_t &t, int i)
{
	if (i <= 0 || i > t.N) {
		cout<<"Indice errato"<<endl;
		return;
	}

	cout<<i<<endl;

	cout<<i<<". "<<t.domande[i-1].testo_domanda<<endl;

	for (int j = 0 ; j < M ; j++) {
		cout<<static_cast<char>('a'+j)<<") ";
		cout<<t.domande[i-1].testo_risposte[j]<<endl;
	}

	char tentativo;
	cin>>tentativo;
	int idx = tentativo - 'a';

	if (idx < 0 || idx >= M)
		cout<<"Indice risposta errato"<<endl;

	if (idx == t.domande[i-1].idx_corretta)
		cout<<"Esatto"<<endl;
	else
		cout<<"Sbagliato"<<endl;
}

/*
 * Uguale a fai_domanda, ma con la domanda scelta casualmente.
 */
void fai_domanda2(const traccia_t &t)
{
	if (t.N == 0) {
		cout<<"Traccia vuota"<<endl;
		return;
	}
	fai_domanda(t, (rand() % t.N) + 1);
}

int main()
{

	traccia_t t;
	inizializza(t);

	srand(time(0));

	const char menu[] =
		"1. Inizializza traccia\n"
		"2. Stampa traccia\n"
		"3. Salva traccia\n"
		"4. Carica traccia\n"
		"5. Fai domanda\n"
		"6. Fai domanda 2\n"
		"7. Esci\n";

	while (true) {
		cout<<menu<<endl;
		int scelta;
		cin>>scelta;

		cout<<endl ; // per il corretto funzionamento del tester

		switch (scelta) {
		case 1: {
			cout<<"Numero domande: ";
			int N;
			cin>>N;

			if (!reinizializza(t, N, cin, false))
				cout<<"Reinizializzazione fallita"<<endl;
		}
			break;
		case 2:
			scrivi_traccia(t, cout, false);
			break;
		case 3: {
			ofstream f(NOMEFILE);
			if (!scrivi_traccia(t, f, true))
				cout<<"Salvataggio fallito"<<endl;
		}
			break;
		case 4:
			if (!carica_traccia(t))
				cout<<"Caricamento fallito"<<endl;
			break;
		case 5: {
			cout<<"Indice domanda: ";
			int i;
			cin>>i;

			fai_domanda(t, i);
		}
			break;
		case 6:
			fai_domanda2(t);
			break;
		case 7:
			return 0;
		default:
			cout<<"Scelta errata"<<endl;
		}
	}

	return 1;
}
