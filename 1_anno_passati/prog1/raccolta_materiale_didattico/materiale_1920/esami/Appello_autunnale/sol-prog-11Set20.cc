#include <iostream>
#include <fstream>

using namespace std;

const char NOMEFILE[] = "sequenza.txt";

/*
 * tipo dell'operazione sugli oggetti, il tipo Ignota viene utilizzato
 * per gestire situazione di errore
 */
enum tipo_operazione {Allocazione, Accesso, Deallocazione, Ignota};

// descrittore di una operazione
struct operazione_t {
	tipo_operazione tipo; // tipo dell'operazione
	unsigned int indice; // indice dell'oggetto su cui eseguire l'operazione
};

// descrittore di una sequenza di operazioni
struct sequenza_t {
	operazione_t *operazioni; // sequenza di operazioni
	unsigned int N; // lunghezza della sequenza
};

/*
 * inizializza la sequenza a vuota, assumendo che non sia mai stata
 * inizializzata prima
 */
void inizializza(sequenza_t &s)
{
	s.N = 0;
}

/*
 * Ritorna il tipo di operazione corrispondete al carattere car_op,
 * oppure Ignota se nessuna operazione corrisponde a tale carattere.
 */
tipo_operazione converti_car_in_tipo(char car_op)
{
	switch (car_op) {
	case 'A':
		return Allocazione;
	case 'X':
		return Accesso;
	case 'D':
		return Deallocazione;
	default:
		return Ignota;
	}
}

/*
 * Ritorna il carattere che rappresenta il tipo di operazione tipo.
 */
char converti_tipo_in_car(tipo_operazione tipo)
{
	switch (tipo) {
	case Allocazione:
		return 'A';
	case Accesso:
		return 'X';
	case Deallocazione:
		return 'D';
	default:
		return 'I';
	}
}


/*
 * Legge N operazioni dall'istream is, e le memorizza nella sequenza
 * s. Ritorna vero in caso di successo, falso altrimenti.
 */
bool leggi_sequenza(istream &is, sequenza_t &s, unsigned int N)
{
	for (unsigned int i = 0 ; i < N ; i++) {
		char car_op;
		is>>car_op;
		if (!is)
			return false;

		s.operazioni[i].tipo = converti_car_in_tipo(car_op);
		if (s.operazioni[i].tipo == Ignota)
			return false;

		is>>s.operazioni[i].indice;
		if (!is || s.operazioni[i].indice > N ||
		    s.operazioni[i].indice == 0)
			return false;
	}

	return true;
}

/*
 * Reinizializza la sequenza s a contenere N operazioni, e legge tali
 * operazioni dall'istream is.
 */
bool reinizializza(sequenza_t &s, unsigned int N, istream &is)
{
	if (N != s.N && s.N != 0) {
		delete [] s.operazioni;
		s.N = 0;
	}

	if (s.N == 0 && N > 0)
		s.operazioni = new operazione_t[N];

	s.N = N;

	if (N == 0)
		return true;

	if (!leggi_sequenza(is, s, N)) {
		delete [] s.operazioni;
		s.N = 0;
		return false;
	}

	return true;
}

/*
 * Scrive la sequenza s sull'ostream os, utilizzando un formato adatto
 * per il file di stato se su_file e' vero. Ritorna vero in caso di
 * successo, falso altrimenti.
 */
bool scrivi_sequenza(const sequenza_t &s, ostream &os, bool su_file)
{
	if (su_file)
		os<<s.N<<endl;

	for (unsigned int i = 0 ; i < s.N ; i++)
		os<<converti_tipo_in_car(s.operazioni[i].tipo)<<' '
		  <<s.operazioni[i].indice<<endl;

	return static_cast<bool>(os);
}

/*
 * Carica la sequenza s da file. L'eventuale precedente contenuto
 * della sequenza e' perso. Ritorna verso in caso di successo, falso
 * altrimenti.
 */
bool carica_sequenza(sequenza_t &s)
{
	ifstream f(NOMEFILE);

	if (!f)
		return false;

	unsigned int N;
	f>>N;

	if (!reinizializza(s, N, f))
		return false;

	return static_cast<bool>(f);
}

/*
 * Stampa il numero massimo di oggetti che possono essere presenti
 * contemporaneamente in memoria, in base alla sequenza di operazioni s.
 */
void stampa_occupazione(const sequenza_t &s)
{
	int allocati = 0, max_allocati = 0 ;
	for (unsigned int i = 0 ; i < s.N ; i++) {

		if (s.operazioni[i].tipo == Allocazione) {
			allocati++;
			if (allocati > max_allocati)
				max_allocati = allocati;
		} else if (s.operazioni[i].tipo == Deallocazione)
			allocati--;
	}

	cout<<max_allocati<<endl;
}

/*
 * Controlla la correttezza della sequenza di operazioni s, e stampa
 * corretta o non corretta in base al risultato.
 */
void controlla_sequenza(const sequenza_t &s)
{
	if (s.N == 0) {
		cout<<"Sequenza corretta"<<endl;
		return;
	}

	enum stato_t {Allocato, Deallocato};

	stato_t *stati = new stato_t[s.N];

	for (unsigned int i = 0 ; i < s.N ; i++)
		stati[i] = Deallocato;

	for (unsigned int i = 0 ; i < s.N ; i++) {
		bool corretta = true;

		int indice = s.operazioni[i].indice - 1;

		switch (s.operazioni[i].tipo) {
		case Allocazione:
			if (stati[indice] != Allocato)
				stati[indice] = Allocato;
			else
				corretta = false;
			break;
		case Accesso:
			if (stati[indice] != Allocato)
				corretta = false;
			break;
		case Deallocazione:
			if (stati[indice] != Deallocato)
				stati[indice] = Deallocato;
			else
				corretta = false;
			break;
		default:
			corretta = false;
		}

		if (!corretta) {
			cout<<"Sequenza non corretta"<<endl;
			delete [] stati;
			return;
		}
	}

	cout<<"Sequenza corretta"<<endl;
	delete [] stati;
}

int main()
{
	sequenza_t seq;
	inizializza(seq);

	const char menu[] =
		"1. Reinizializza sequenza\n"
		"2. Stampa sequenza\n"
		"3. Salva sequenza\n"
		"4. Carica sequenza\n"
		"5. Stampa occupazione memoria\n"
		"6. Controlla sequenza\n"
		"7. Esci\n";

	while (true) {
		cout<<menu<<endl;
		int scelta;
		cin>>scelta;

		cout<<endl ; // per il corretto funzionamento del tester

		switch (scelta) {
		case 1: {
			cout<<"Lunghezza della sequenza: ";
			int N;
			cin>>N;

			cout<<"Sequenza: ";

			if (!reinizializza(seq, N, cin))
				cout<<"Inizializzazione fallita"<<endl;
		}
			break;
		case 2:
			scrivi_sequenza(seq, cout, false);
			break;
		case 3: {
			ofstream f(NOMEFILE);
			if (!scrivi_sequenza(seq, f, true))
				cout<<"Salvataggio fallito"<<endl;
		}
			break;
		case 4:
			if (!carica_sequenza(seq))
				cout<<"Caricamento fallito"<<endl;
			break;
		case 5:
			stampa_occupazione(seq);
			break;
		case 6:
			controlla_sequenza(seq);
			break;
		case 7:
			return 0;
		default:
			cout<<"Scelta errata"<<endl;
		}
	}

	return 1;
}
