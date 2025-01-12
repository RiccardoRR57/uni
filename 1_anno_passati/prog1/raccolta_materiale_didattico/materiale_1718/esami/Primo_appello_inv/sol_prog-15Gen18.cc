#include <iostream>
#include <fstream>

using namespace std;

const char NOMEFILE[] = "stato_blocchi.txt";

/* Descrittore sequenza di stato dei blocchi */
struct stato_sequenza_t {
	bool *libero;	/* array di stato:
			   libero[i]==true => i-esimo blocco libero */
	unsigned int N;	/* numero totale di blocchi */
};

/* Inizializza la sequenza s a vuota */
void inizializza(stato_sequenza_t &s)
{
	s.N = 0;
}

/* Funzione di servizio per (ri)allocare la sequenza */
void rialloca_stato(stato_sequenza_t &s, unsigned int N)
{
	if (N == s.N)
		return;
	if (s.N != 0)
		delete s.libero;
	if (N > 0)
		s.libero = new bool[N];
	s.N = N;
}

/* Inizializza la sequenza s a contenere N elementi */
void inizializza(stato_sequenza_t &s, int N)
{
	rialloca_stato(s, N);
	for (int i = 0 ; i < N ; i++)
		s.libero[i] = true;
}

/*
 * Prova ad allocare n blocchi consecutivi a partire dal blocco di
 * indice idx nella sequenza s. Ritorna vero in caso di successo,
 * falso in caso do fallimento.
 */
bool alloca_blocchi(stato_sequenza_t &s, int idx, int n)
{
	if (idx < 0 || n < 0)
		return false;

	int ultimo = idx + n - 1;

	if (ultimo >= s.N)
		return false;

	for (int i = idx ; i <= ultimo ; i++)
		if (!s.libero[i])
			return false;

	for (int i = idx ; i <= ultimo ; i++)
		s.libero[i] = false;

	return true;
}

/*
 * Scrive lo stato della sequenza s sull'output stream os. Se su_file
 * e' vero, allora utilizza un formato adatto per il salvataggio dello
 * stato in un file. Ritorna vero in caso di successo, falso in caso
 * di fallimento.
 */
bool scrivi_stato(const stato_sequenza_t &s, ostream &os, bool su_file)
{
	if (su_file)
		os<<s.N<<endl;

	for (int i = 0 ; i < s.N ; i++)
		if (s.libero[i])
			os<<'-';
		else
			os<<'*';
	os<<endl;

	return os;
}

/*
 * Ricarica lo stato dal file, nella sequenza s. Ritorna vero in caso
 * di successo, falso altrimenti.
 */
bool carica_stato(stato_sequenza_t &s)
{
	ifstream f(NOMEFILE);

	if (!f)
		return false;

	unsigned int N;
	f>>N;
	rialloca_stato(s, N);

	for (int i = 0 ; i < N ; i++) {
		char carattere_stato;
		f>>carattere_stato;
		if (carattere_stato == '-')
			s.libero[i] = true;
		else
			s.libero[i] = false;
	}

	return f;
}

int blocchi_liberi(const stato_sequenza_t &s, int idx)
{
	if (idx < 0 || idx >= s.N)
		return -1;

	int ultimo;
	for (ultimo = idx ; ultimo < s.N && s.libero[ultimo] ; ultimo++)
		;

	return ultimo - idx;
}

bool cerca_alloca_blocchi(stato_sequenza_t &s, int n, bool massimizza)
{
	int num_max_liberi = 0, idx = 0;
	for (int num_liberi, i = 0; i < s.N ; i += num_liberi + 1) {
		num_liberi = blocchi_liberi(s, i);

		if (num_liberi > num_max_liberi) {
			num_max_liberi = num_liberi;
			idx = i;
		}

		if (num_liberi >= n && !massimizza)
			break;
	}

	if (num_max_liberi < n)
		return false;

	return alloca_blocchi(s, idx, n);
}

int main()
{
	stato_sequenza_t stato;
	inizializza(stato);

	const char menu[] =
		"1. Inizializza sequenza\n"
		"2. Alloca blocchi\n"
		"3. Stampa stato\n"
		"4. Salva stato\n"
		"5. Carica stato\n"
		"6. Stampa blocchi liberi da indice\n"
		"7. Cerca ed alloca blocchi\n"
		"8. Cerca ed alloca blocchi 2\n"
		"9. Esci\n";

	while (true) {
		cout<<menu<<endl;

		int scelta;
		cin>>scelta;

		switch (scelta) {
		case 1: {
			cout<<"Inserire numero totale di blocchi: ";
			unsigned int N;
			cin>>N;
			inizializza(stato, N);
			break;}
		case 2: {
			cout<<"Inserire indice iniziale e numero di blocchi: ";
			      int idx, n;
			      cin>>idx>>n;
			if (!alloca_blocchi(stato, idx, n))
				cout<<"Allocazione blocchi fallita"<<endl;
			break;}
		case 3:
			scrivi_stato(stato, cout, false);
			break;
		case 4: {
			ofstream f(NOMEFILE);
			if (!scrivi_stato(stato, f, true))
				cout<<"Salvataggio fallito"<<endl;
			break;}
		case 5:
			if (!carica_stato(stato))
				cout<<"Caricamento fallito"<<endl;
			break;
		case 6: {
			int idx;
			cout<<"Inserire indice: ";
			cin>>idx;
			cout<<blocchi_liberi(stato, idx)<<endl;
			break;}
		case 7: {
			cout<<"Inserire numero di blocchi: ";
			int n;
			cin>>n;
			if (!cerca_alloca_blocchi(stato, n, false))
				cout<<"Allocazione blocchi fallita"<<endl;
			break;}
		case 8: {
			cout<<"Inserire numero di blocchi: ";
			int n;
			cin>>n;
			if (!cerca_alloca_blocchi(stato, n, true))
				cout<<"Allocazione blocchi fallita"<<endl;
			break;}
		case 9:
			return 0;
		default:
			cout<<"Scelta errata"<<endl;
		}
	}


}
