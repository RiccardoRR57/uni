#include <iostream>
#include <fstream>

using namespace std;
const char NOMEFILE[] = "stato.dat";

enum stato_auto {DISPONIBILE, NOLEGGIATA};

struct insieme_t {
	int N;
	unsigned int *auto_disp;
	int num_disp;
	stato_auto *stato;
};

void inizializza(insieme_t &ins)
{
	ins.num_disp = ins.N = 0;
}

void rialloca(insieme_t &ins, int N)
{
	if (ins.N == N)
		return;

	if (ins.N > 0) {
		delete [] ins.auto_disp;
		delete [] ins.stato;
	}

	if (N > 0) {
		ins.auto_disp = new unsigned int[N];
		ins.stato = new stato_auto[N];
	}
	ins.N = N;
}

bool inizializza(insieme_t &ins, int N)
{
	if (N < 0)
		return false;

	rialloca(ins, N);
	for (int i = 0 ; i < N ; i++) {
		ins.auto_disp[i] = i;
		ins.stato[i] = DISPONIBILE;
	}
	ins.num_disp = N;

	return true;
}

bool noleggia_auto(insieme_t &ins)
{
	if (ins.num_disp == 0)
		return false;

	ins.num_disp--;
	ins.stato[ins.auto_disp[ins.num_disp]] = NOLEGGIATA;
	return true;
}

void stampa_stato(const insieme_t &ins)
{
	for (int i = 0 ; i < ins.num_disp ; i++) {
		if (i > 0)
			cout<<" ";
		cout<<ins.auto_disp[i];
	}
	cout<<endl;
}

bool salva_stato(const insieme_t &ins)
{
	ofstream f(NOMEFILE);

	f.write(reinterpret_cast<const char *>(&ins.N), sizeof(int));

	f.write(reinterpret_cast<const char *>(&ins.num_disp), sizeof(int));
	f.write(reinterpret_cast<const char *>(ins.auto_disp),
		ins.num_disp * sizeof(unsigned int));

	f.write(reinterpret_cast<const char *>(ins.stato),
		ins.N * sizeof(stato_auto));

	return f;
}

bool carica_stato(insieme_t &ins)
{
	ifstream f(NOMEFILE);

	int N;
	f.read(reinterpret_cast<char *>(&N), sizeof(int));
	rialloca(ins, N);

	f.read(reinterpret_cast<char *>(&ins.num_disp), sizeof(int));
	f.read(reinterpret_cast<char *>(ins.auto_disp),
		ins.num_disp * sizeof(unsigned int));

	f.read(reinterpret_cast<char *>(ins.stato),
		ins.N * sizeof(stato_auto));

	return f;
}

bool auto_disponibile(const insieme_t &ins, int id)
{
	if (id < 0 || id >= ins.N)
		return false;

	return ins.stato[id] == DISPONIBILE;
}

bool restituisci_auto(insieme_t &ins, int id)
{
	if (id < 0 || id >= ins.N || ins.stato[id] == DISPONIBILE)
		return false;

	ins.stato[id] = NOLEGGIATA;

	ins.auto_disp[ins.num_disp] = id;
	ins.num_disp++;

	return true;
}

int main()
{
	insieme_t ins;
	inizializza(ins);

	const char menu[] =
		"1. Inizializza insieme\n"
		"2. Noleggia auto\n"
		"3. Stampa stato\n"
		"4. Salva stato\n"
		"5. Carica stato\n"
		"6. Controlla auto\n"
		"7. Restituisci auto\n"
		"8. Esci\n";

	while (true) {
		cout<<endl<<menu<<endl;

		int scelta;
		cin>>scelta;

		switch (scelta) {
		case 1: {
			int N;
			cout<<"Inserisci N: ";
			cin>>N;
			inizializza(ins, N);
			break;}
		case 2:
			if (!noleggia_auto(ins))
				cout<<"Noleggio fallito"<<endl;
			break;
		case 3:
			stampa_stato(ins);
			break;
		case 4:
			if (!salva_stato(ins))
				cout<<"Salvataggio fallito"<<endl;
			break;
		case 5:
			if (!carica_stato(ins))
				cout<<"Caricamento fallito"<<endl;
			break;
		case 6: {
			int id;
			cout<<"Inserisci id auto: ";
			cin>>id;
			if (auto_disponibile(ins, id))
				cout<<"Auto "<<id<<" disponibile"<<endl;
			else
				cout<<"Auto "<<id<<" non disponibile"<<endl;
			break;}
		case 7: {
			int id;
			cout<<"Inserisci id auto: ";
			cin>>id;
			if (restituisci_auto(ins, id))
				cout<<"Auto "<<id<<" restituita"<<endl;
			else
				cout<<"Auto "<<id<<" gia' disponibile"<<endl;
			break;}
			break;
		case 8:
			return 0;
			break;
		default:
			cout<<"Scelta errata"<<endl;
		}
	}
	return 1;
}
