#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

const int NUM_LAMPIONI_INIZIO = 5; // numero di lampioni all'avvio del prog
const char NOME_FILE[] = "stato_lampioni.txt";

// stati possibili per ciascun lampione
enum stato_lampione_t {FUNZIONANTE, GUASTO};

// descrittore di una sequenza di lampioni
struct sequenza_lampioni_t {
	stato_lampione_t *stato; // array dinamico per lo stato dei lampioni
	int num_lampioni;	 // numero di lampioni presenti
};

/*
 * Inizializza la sequenza s a contentere NUM_LAMPIONI_INIZIO
 * lampioni, tutti funionanti.
 */
void inizializza(sequenza_lampioni_t &s)
{
	s.stato = new stato_lampione_t[NUM_LAMPIONI_INIZIO];
	s.num_lampioni = NUM_LAMPIONI_INIZIO;

	for (int i = 0 ; i < s.num_lampioni ; i++)
		s.stato[i] = FUNZIONANTE;
}

/*
 * Scrive lo stato dei lampioni sull'output stream os; utilizza un
 * formato adatto alla memorizzazione e successiva lettura da file se
 * su_file è vero, altrimenti utilizza un formato adatto alla lettura
 * da parte di un utente. Ritorna vero in caso di successo, falso
 * altrimenti.
 */
bool scrivi_stato(const sequenza_lampioni_t &s, ostream &os, bool su_file)
{
	if (su_file)
		os<<s.num_lampioni<<endl;

	for (int i = 0 ; i < s.num_lampioni ; i++)
		if (s.stato[i] == FUNZIONANTE)
			os<<'*';
		else
			os<<'-';

	os<<endl;
	
	return os;
}

/*
 * Modifica in nuovo_stato lo stato del lampione di indice
 * num_lampione nella sequenza s. Ritorna vero in caso di successo,
 * falso altrimenti.
 */
bool modifica_stato_lampione(sequenza_lampioni_t &s, int num_lampione,
			     stato_lampione_t nuovo_stato)
{
	if (num_lampione < 0 || num_lampione >= s.num_lampioni)
		return false;
	
	s.stato[num_lampione] = nuovo_stato;
	return true;
}

/*
 * Modifica in nuova_lun il numero di lampioni della sequenza
 * s. Ritorna vero in caso di successo, falso altrimenti.
 */
bool modifica_numero_lampioni(sequenza_lampioni_t &s, int nuova_lun)
{
	if (nuova_lun <= 0)
		return false;

	if (nuova_lun == s.num_lampioni)
		return true;

	stato_lampione_t *nuova_seq = new stato_lampione_t[nuova_lun];

	int num_da_copiare =
		s.num_lampioni < nuova_lun ? s.num_lampioni : nuova_lun;

	for (int i = 0 ; i < num_da_copiare ; i++)
		nuova_seq[i] = s.stato[i];

	for (int i = num_da_copiare ; i < nuova_lun ; i++)
		nuova_seq[i] = FUNZIONANTE;

	delete [] s.stato;

	s.stato = nuova_seq;
	s.num_lampioni = nuova_lun;
	
	return true;
}

/*
 * Ricarica lo stato da file, lo stato precedente è perso.  Ritorna
 * vero in caso di successo, falso in caso di fallimento.
 */
bool carica_stato(sequenza_lampioni_t &s)
{
	ifstream f(NOME_FILE);

	int nuova_lun;
	f>>nuova_lun;

	if (!f)
		return false;

	if (nuova_lun != s.num_lampioni) {
		delete [] s.stato;
		s.stato = new stato_lampione_t[nuova_lun];
		s.num_lampioni = nuova_lun;
	}

	for (int i = 0 ; i < nuova_lun ; i++) {
		char stato;
		f>>stato;
		if (stato == '*')
			s.stato[i] = FUNZIONANTE;
		else
			s.stato[i] = GUASTO;
	}
	
	return true;
}

/*
 * Modifica lo stato dei lampioni nella sequenza s in accordo al
 * contenuto della stringa nuovo_stato. Ritorna vero in caso di
 * successo, falso altrimenti.
 */
bool modifica_stato(sequenza_lampioni_t &s, const char *nuovo_stato)
{
	if (nuovo_stato == 0)
		return false;

	int lun = strlen(nuovo_stato);
	
	if (lun == 0 || lun > s.num_lampioni)
		return false;

	for (int i = 0 ; i < lun ; i++)
		if (nuovo_stato[i] != '*' && nuovo_stato[i] != '-')
			return false;
	
	for (int i = 0 ; i < lun ; i++)
		if (nuovo_stato[i] == '*')
			s.stato[i] = FUNZIONANTE;
		else
			s.stato[i] = GUASTO;

	return true;
}

int main()
{
	sequenza_lampioni_t seq;

	inizializza(seq);
	
	const char menu[] =
		"1. Modifica stato lampione\n"
		"2. Stampa stato\n"
		"3. Modifica numero lampioni\n"
		"4. Salva stato\n"
		"5. Carica stato\n"
		"6. Modifica stato sequenza\n"
		"7. Esci\n";
	
	while (true) {
		cout<<endl<<menu<<endl;

		int scelta;
		cin>>scelta;
		
		switch (scelta) {
		case 1: {
			int n;
			cout<<"Indice lampione? ";
			cin>>n;
			char s;
			cout<<"Nuovo stato [*|-] ? ";
			cin>>s;
			stato_lampione_t nuovo_stato = GUASTO;
			if (s == '*')
				nuovo_stato = FUNZIONANTE;
			if (!modifica_stato_lampione(seq, n, nuovo_stato))
				cout<<"Modifica stato lampione fallita"<<endl;
			break;}
		case 2:
			scrivi_stato(seq, cout, false);
			break;
		case 3: {
			int n;
			cout<<"Nuovo numero lampioni? ";
			cin>>n;
			if (!modifica_numero_lampioni(seq, n))
				cout<<"Modifica numero lampioni fallita"<<endl;
			break;}
		case 4: {
			ofstream f(NOME_FILE);
			if (!scrivi_stato(seq, f, true))
				cout<<"Salvataggio fallito"<<endl;
			break;}
		case 5:
			if (!carica_stato(seq))
				cout<<"Caricamento fallito"<<endl;
			break;
		case 6: {
			char *nuovo_stato = new char[seq.num_lampioni + 1];
			cout<<"Nuovo stato lampioni? ";
			cin>>nuovo_stato;
			if (!modifica_stato(seq, nuovo_stato))
				cout<<"Modifica stato fallita"<<endl;
			break;}
		case 7:
			return 0;
		default:
			cout<<"Scelta errata"<<endl;
		}
	}
	return 1;
}
