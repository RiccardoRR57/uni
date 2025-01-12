#include <iostream>
#include <fstream>

using namespace std;

const char NOMEFILE[] = "coda.txt";

// descrittore della coda di utenti
struct coda_t {
	char *utenti; // puntatore all'array dinamico di codici in coda
	int inizio, fine, quanti, N; // parametri implementazione coda
};

/*
 * Inizializza coda a vuota, assumendo che non sia mai stata
 * inizializzata prima
 */
void inizializza(coda_t &coda)
{
	coda.quanti = coda.N = 0;
}

/*
 * Reinizializza coda a contenere al massimo N elementi, assumendo che
 * sia gia' stata inizializzata almeno una volta prima. Ritorna vero
 * inc aso di successo, falso altrimenti.
 */
bool reinizializza (coda_t &coda, int N)
{
	if (N < 0)
		return false;

	if (N != coda.N && coda.N > 0) {
		delete [] coda.utenti;
		coda.N = 0;
	}

	if (coda.N == 0 && N > 0)
		coda.utenti = new char[N];

	coda.inizio = coda.fine = coda.quanti = 0;
	coda.N = N;

	return true;
}

/*
 * Inserisce un utente in testa a coda, per il servizio di codice
 * 'codice'. Ritorna vero in caso di successo, falso altrimenti.
 */
bool accoda_utente(coda_t &coda, char codice)
{
	if (coda.quanti == coda.N ||
	    codice < 'A' || codice > 'Z')
		return false;

	coda.utenti[coda.fine] = codice;
	coda.fine = (coda.fine+1) % coda.N;
	coda.quanti++;

	return true;
}

/*
 * Scrive il contenuto di coda sull'ostream os, utilizzando un formato
 * adatto ad un file di stato se su_file e' vero. Ritorna vero inc
 * aso di successo, falso altrimenti.
 */
bool scrivi_coda(const coda_t &coda, ostream &os, bool su_file)
{
	if (su_file)
		os<<coda.N<<' '<<coda.quanti<<endl;

	for (int i = 0 ; i < coda.quanti ; i++) {
		if (i > 0)
			os<<' ';
		os<<coda.utenti[(coda.inizio + i)%coda.N];
	}

	os<<endl;

	return static_cast<bool>(os);
}

/*
 * Carica il contenuto di coda da file. L'eventuale precedente
 * contenuto e' perso. Ritorna vero in caso di successo, falso
 * altrimenti.
 */
bool carica_coda(coda_t &coda)
{
	ifstream f(NOMEFILE);

	if (!f)
		return false;

	int N;
	f>>N;

	if (!reinizializza(coda, N))
		cout<<"Reinizializzazione fallita"<<endl;

	int quanti;
	f>>quanti;

	for (int i = 0 ; i < quanti ; i++) {
		char c;
		f>>c;
		accoda_utente(coda, c);
	}

	return static_cast<bool>(f);
}

/*
 * Estrae l'utente in testa da coda.  Ritorna vero in caso di
 * successo, falso altrimenti.
 */
bool servi_prossimo_utente(coda_t &coda)
{
	if (coda.quanti == 0)
		return false;

	coda.inizio = (coda.inizio + 1) % coda.N;
	coda.quanti--;

	return true;
}

/*
 * Sposta nella posizione i l'utente che si trova nella posizione j,
 * traslando di una posizione verso destra tutti gli utenti presenti
 * nelle posizioni da i a j-1.
 */
void sposta(coda_t &coda, int i, int j)
{
	char originale = coda.utenti[j];

	for (int k = j ; k > i ; k--)
		coda.utenti[k] = coda.utenti[k-1];

	coda.utenti[i] = originale;
}

/*
 * Sposta in testa alla coda tutti gli utenti che attendono per il
 * servizio di codice c.
 */
void anticipa_servizio(coda_t &coda, char c)
{
	int inizio_ricerca = coda.inizio;

	for (int i = 1 ; i < coda.quanti ; i++) {
		int pos = (coda.inizio + i) % coda.N;

		if (coda.utenti[i] != c)
			continue;

		for ( ; inizio_ricerca < i ; inizio_ricerca++)
			if (coda.utenti[inizio_ricerca] != c) {
				sposta(coda, inizio_ricerca, pos);
				inizio_ricerca =
					(inizio_ricerca + 1) % coda.N;
				break;
			}
	}
}

int main()
{
	coda_t coda;
	inizializza(coda);

	const char menu[] =
		"1. Reinizializza coda\n"
		"2. Accoda utente\n"
		"3. Stampa coda\n"
		"4. Salva coda\n"
		"5. Carica coda\n"
		"6. Servi prossimo utente\n"
		"7. Anticipa servizio\n"
		"8. Esci\n";

	while (true) {
		cout<<menu<<endl;
		int scelta;
		cin>>scelta;

		cout<<endl ; // per il corretto funzionamento del tester

		switch (scelta) {
		case 1: {
			cout<<"Lunghezza massima della coda: ";
			int N;
			cin>>N;

			if (!reinizializza(coda, N))
				cout<<"Inizializzazione fallita"<<endl;
		}
			break;
		case 2: {
			cout<<"Codice del servizio: ";
			char c;
			cin>>c;

			if (!accoda_utente(coda, c))
				cout<<"Accodamento fallito"<<endl;
		}
			break;
		case 3:
			scrivi_coda(coda, cout, false);
			break;
		case 4: {
			ofstream f(NOMEFILE);
			if (!scrivi_coda(coda, f, true))
				cout<<"Salvataggio fallito"<<endl;
		}
			break;
		case 5:
			if (!carica_coda(coda))
				cout<<"Caricamento fallito"<<endl;
			break;
		case 6:
			if (!servi_prossimo_utente(coda))
				cout<<"Servizio fallito"<<endl;
			break;
		case 7: {
			cout<<"Inserisci codice di servizio: "<<endl;
			char c;
			cin>>c;

			anticipa_servizio(coda, c);
		}
			break;
		case 8:
			return 0;
		default:
			cout<<"Scelta errata"<<endl;
		}
	}

	return 1;
}
