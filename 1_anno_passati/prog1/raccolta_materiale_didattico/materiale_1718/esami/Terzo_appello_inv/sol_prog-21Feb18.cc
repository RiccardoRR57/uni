#include <iostream>
#include <fstream>

using namespace std;

// nome del file in cui viene memorizzata la sequenza
const char NOMEFILE[] = "sequenza.txt";

const int N = 10; // numero massimo di parole
const int L = 50; // lunghezza massima delle parole

// descrittore della sequenza di parole
struct sequenza_t {
	char *parole; // contenutitore dell'intera sequenza di parole,
		      // una dietro l'altra
	int lun_totale; // lunghezza totale del contenitore
	int *indici;    // indici, all'interno del contenutore, degli
			// ulitmi caratteri delle parole
	int num_parole; // numero di parole nella sequenza
};

// inizializza la sequenza s a vuota
void inizializza(sequenza_t &s)
{
	s.num_parole = s.lun_totale = 0;
}

/*
 * Inserisce la parola p nella sequenza s. Ritorna vero in caso di
 * successo, falso altrimenti.
 */
bool inserisci_parola(sequenza_t &s, const char *p)
{
	int lun_parola = strlen(p);

	if (s.num_parole == N ||
	    s.lun_totale + lun_parola > N * L)
		return false;

	int vecchio_num_parole = s.num_parole;

	char *nuovo_parole = new char [s.lun_totale + lun_parola];

	for (int i = 0 ; i < s.lun_totale ; i++)
		nuovo_parole[i] = s.parole[i];
	for (int i = 0 ; i < lun_parola ; i++)
		nuovo_parole[s.lun_totale + i] = p[i];
	s.lun_totale += lun_parola;

	int *nuovo_indici = new int [s.num_parole + 1];

	for (int i = 0 ; i < s.num_parole ; i++)
		nuovo_indici[i] = s.indici[i];
	nuovo_indici[s.num_parole] = s.lun_totale - 1;

	s.num_parole += 1;

	if (vecchio_num_parole > 0) {
		delete [] s.parole;
		delete [] s.indici;
	}
	s.indici = nuovo_indici;
	s.parole = nuovo_parole;

	return true;
}

/*
 * Scrive la sequenza s sull'output stream os, usando un formato
 * adatto alla memorizzazione in un file se su_file e' vero. Ritorna
 * vero in caso di successo, falso altrimenti.
 */
bool scrivi_sequenza(const sequenza_t &s, ostream &os, bool su_file)
{
	if (su_file)
		os<<s.lun_totale<<" "<<s.num_parole<<endl;

	for (int i = 0 ; i < s.lun_totale  ; i++) {
		os<<s.parole[i];
		if (!su_file && i == s.indici[j])
			os<<endl;
	}

	if (!su_file)
		return os;

	os<<endl;
	for (int i = 0 ; i < s.num_parole ; i++)
		os<<s.indici[i]<<endl;

	return os;
}

// funzione di servizio per carica_sequenza, per deallocare e
// riallocare le parole
void rialloca_parole(sequenza_t &s, int lun_totale)
{
	if (s.lun_totale == lun_totale)
		return;

	if (s.lun_totale > 0)
		delete [] s.parole;

	if (lun_totale > 0)
		s.parole = new char[lun_totale];

	s.lun_totale = lun_totale;
}

// funzione di servizio per carica_sequenza, per deallocare e
// riallocare gli indici
void rialloca_indici(sequenza_t &s, int num_parole)
{
	if (s.num_parole == num_parole)
		return;

	if (s.num_parole > 0)
		delete [] s.parole;

	if (num_parole > 0)
		s.indici = new int[num_parole];

	s.num_parole = num_parole;
}

/*
 * Carica la sequenza s da file. Ritorna vero in caso di successo,
 * falso altrimenti.
 */
bool carica_sequenza(sequenza_t &s)
{
	ifstream f(NOMEFILE);

	if (!f)
		return false;

	int lun_totale, num_parole;

	f>>lun_totale>>num_parole;

	rialloca_parole(s, lun_totale);
	rialloca_indici(s, num_parole);

	f>>s.parole;
	for (int i = 0 ; i < s.num_parole ; i++)
		f>>s.indici[i];

	return f;
}

/*
 * Sposta gli ultimi n caratteri della parola di indice idx in testa
 * alla prossima parola, poi fa lo stesso con la parola successiva, e
 * così via. Ritorna vero in caso di successo, falso altrimenti.
 */
bool sposta_in_prossima(sequenza_t &s, int idx, int n)
{
	if (idx < 0 || idx >= s.num_parole)
		return false;

	for (int i = idx ; i < s.num_parole ; i++) {
		int j = i > 0 ? s.indici[i-1] : -1;

		if (s.indici[i] - j <= n)
			return false;
	}

	for (int i = idx ; i < s.num_parole ; i++)
		s.indici[i] -= n;

	s.lun_totale -= n;

	char *nuovo_parole = new char [s.lun_totale];

	for (int i = 0 ; i < s.lun_totale ; i++)
		nuovo_parole[i] = s.parole[i];
	delete [] s.parole;
	s.parole = nuovo_parole;

	return true;
}

int main()
{
	sequenza_t seq;
	inizializza(seq);

	const char menu[] =
		"1. Inserisci parola\n"
		"2. Stampa sequenza\n"
		"3. Salva sequenza\n"
		"4. Carica sequenza\n"
		"5. Sposta caratteri nella prossima parola\n"
		"6. Esci\n";


	while (true) {
		cout<<menu<<endl;

		int scelta;
		cin>>scelta;
		switch (scelta) {
		case 1: {
			char parola[L];
			cout<<"Parola: ";
			cin>>parola;
			if (!inserisci_parola(seq, parola))
				cout<<"Inserimento fallito"<<endl;
			break;}
		case 2:
			scrivi_sequenza(seq, cout, false);
			break;
		case 3: {
			ofstream f(NOMEFILE);
			scrivi_sequenza(seq, f, true);
			break;}
		case 4:
			carica_sequenza(seq);
			break;
		case 5:{
			int idx, n;
			cout<<"idx: ";
			cin>>idx;
			cout<<"n: ";
			cin>>n;
			if (!sposta_in_prossima(seq, idx, n))
				cout<<"Sostituzione fallita"<<endl;
			break;}
		case 6:
			return 0;
		default:
			cout<<"Scelta errata"<<endl;

		}
	}


	return 1;
}
