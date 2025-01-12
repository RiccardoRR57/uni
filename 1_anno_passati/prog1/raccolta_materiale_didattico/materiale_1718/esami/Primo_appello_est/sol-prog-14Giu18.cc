#include <iostream>
#include <fstream>

using namespace std;

const char NOMEFILE[] = "dipendenze.dat";

// descrittore dell'insieme delle dipendenze
struct insieme_dip_t {
	char *dip;	// puntatore all'array dinamico delle dipendenze
	int num_dip;	// numero di elementi dell'array dinamico
} ;

// inizializza ins ad un insieme vuoto
void inizializza(insieme_dip_t &ins)
{
	ins.dip = 0;
}

/*
 * (Re)inizializza ins ad un insieme di dipendenze da N elementi.
 */
void reinizializza(insieme_dip_t &ins, int N)
{
	if (ins.dip != 0 && ins.num_dip != N) {
		delete [] ins.dip;
		ins.dip = 0;
	}

	if (N > 0 && ins.dip == 0)
		ins.dip = new char[N];

	for (int i = 0 ; i < N ; i++)
		ins.dip[i] = '\0';

	ins.num_dip = N;
}

/*
 * Imposta p1 a dipendere da p2 all'interno dell'insieme delle
 * dipendenze ins. Ritorna vero in caso di successo, falso altrimenti.
 */
bool imposta_dipendenza(insieme_dip_t &ins, char p1, char p2)
{
	if (p1 - 'A' >= ins.num_dip ||
	    p2 - 'A' >= ins.num_dip ||
	    p1 < 'A' || p2 < 'A')
		return false;

	ins.dip[p1 - 'A'] = p2;

	return true;
}

// stampa l'insieme delle dipendenze ins
void stampa_dipendenze(const insieme_dip_t &ins)
{
	for (int i = 0 ; i < ins.num_dip ; i++) {
		cout<<static_cast<char>(i + 'A');
		if (ins.dip[i] != '\0')
			cout<<" -> "<<ins.dip[i];
		cout<<endl;
	}
}

/*
 * Salva l'insieme delle dipendenze ins su un file binario.  Ritorna
 * vero in caso di successo, falso altrimenti.
 */
bool salva_insieme(const insieme_dip_t &ins)
{
	ofstream f(NOMEFILE);

	f.write(reinterpret_cast<const char *>(&ins.num_dip),
		sizeof(ins.num_dip));

	f.write(reinterpret_cast<const char *>(ins.dip),
		ins.num_dip * sizeof(char));

	return f;
}

/*
 * Carica il contenuto dell'insieme delle dipendenze ins da un file
 * binario. Ritorna vero in caso di successo, falso altrimenti.
 */
bool carica_insieme(insieme_dip_t &ins)
{
	ifstream f(NOMEFILE);

	if (!f)
		return false;

	int N;
	f.read(reinterpret_cast<char *>(&N), sizeof(N));

	reinizializza(ins, N);

	f.read(reinterpret_cast<char *>(ins.dip), ins.num_dip * sizeof(char));

	return f;
}

/*
 * Stampa al più n dipendenze della catena di dipendenze che parte dal
 * pacchetto p, all'interno dell'insieme ins. Ritorna vero in caso di
 * successo, falso altrimenti.
 */
bool stampa_catena_dipendenze(const insieme_dip_t &ins, char p, int n)
{
	if (p - 'A' >= ins.num_dip || p < 'A')
		return false;

	for (int i = 0, idx = p - 'A' ; i < n ; i++) {
		if (i > 0)
			cout<<" -> ";
		cout<<static_cast<char>(idx + 'A');
		if (ins.dip[idx] == '\0')
			break;
		idx = ins.dip[idx] - 'A';
	}
	cout<<endl;

	return true;
}

int main()
{
	insieme_dip_t ins;
	inizializza(ins);

	const char menu[] =
		"1. Inizializza insieme\n"
		"2. Imposta dipendenza\n"
		"3. Stampa dipendenze\n"
		"4. Salva insieme\n"
		"5. Carica insieme\n"
		"6. Stampa catena delle dipendenze\n"
		"7. Esci\n";

	while (true) {
		cout<<menu<<endl;

		int scelta;
		cin>>scelta;

		switch (scelta) {
		case 1:{
			int N;
			cout<<"Numero elementi insieme: ";
			cin>>N;
			reinizializza(ins, N);
			break;}
		case 2:{
			char p1, p2;
			cout<<"Pacchetto da reimpostare: ";
			cin>>p1;
			cout<<"Pacchetto da cui dipende: ";
			cin>>p2;
			if (!imposta_dipendenza(ins, p1, p2))
				cout<<"Impostazione fallita"<<endl;
			break;}
		case 3:
			stampa_dipendenze(ins);
			break;
		case 4:
			if (!salva_insieme(ins))
				cout<<"Salvataggio fallito"<<endl;
			break;
		case 5:
			if (!carica_insieme(ins))
				cout<<"Caricamento fallito"<<endl;
			break;
		case 6: {
			cout<<"Pacchetto di partenza: ";
			char p;
			cin>>p;
			cout<<"Numero massimo dipendenze: ";
			int n;
			cin>>n;
			if (!stampa_catena_dipendenze(ins, p, n))
				cout<<"Stampa catena dipendenze fallita"<<endl;
			break;}
		case 7:
			return 0;
		default:
			cout<<"Scelta errata"<<endl;
		}
	}
}
