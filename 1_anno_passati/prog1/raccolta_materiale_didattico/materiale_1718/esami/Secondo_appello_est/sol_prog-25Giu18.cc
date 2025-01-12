#include <iostream>
#include <fstream>

using namespace std;

const char NOMEFILE[] = "insieme.txt";

// descrittore di un elemento
struct elemento_t {
	int codice;
	int num; // numero di occorrenze dell'elemento
};

// insieme di elementi
struct insieme_t {
	elemento_t *elementi;
	int num_elem;
	int max_num_elem;
};

void inizializza(insieme_t &ins)
{
	ins.max_num_elem = 0;
}

/*
 * Ritorna un insieme non allocato (con max_numm_elem == 0) in caso di
 * errore.
 */
insieme_t crea_insieme(int N)
{
	insieme_t ins = { 0, 0, 0 };

	if (N <= 0)
		return ins;

	ins.elementi = new elemento_t[N];
	ins.max_num_elem = N;

	return ins;
}

/*
 * Aggiunge il codice cod all'insieme ins. Ritorna vero in caso di
 * successo, falso altrimenti.
 */
bool aggiungi_codice(insieme_t &ins, int cod)
{

	if (cod <= 0)
		return false;
	int idx ;
	bool trovato = false;

	for (idx = 0 ; idx < ins.num_elem &&
		     ins.elementi[idx].codice <= cod ; idx++) {
		if (ins.elementi[idx].codice == cod) {
			trovato = true;
			break;
		}
	}

	if (!trovato && ins.num_elem == ins.max_num_elem)
		return false;

	if (trovato)
		ins.elementi[idx].num++;
	else {
		for (int i = ins.num_elem ; i > idx ; i--)
			ins.elementi[i] = ins.elementi[i-1];
		ins.elementi[idx].codice = cod;
		ins.elementi[idx].num = 1;
		ins.num_elem++;
	}

	return true;
}

/*
 * Scrive il contenuto dell'insieme ins sull'ostream os. Usa un
 * formato adeguato per un file, se su_file è vero. Ritorna vero in
 * caso di successo, falso altrimenti.
 */
bool scrivi_insieme(const insieme_t &ins, ostream &os, bool su_file)
{
	if (su_file) {
		os<<ins.max_num_elem<<" "<<ins.num_elem<<endl;
	}
	for (int i = 0 ; i < ins.num_elem ; i++) {
		cout<<ins.elementi[i].codice;
		if (!su_file)
			os<<": ";
		os<<ins.elementi[i].num<<endl;
	}

	return os;
}

/*
 * Carica il contenuto dell'insieme ins dal file. Ritorna vero in caso
 * di successo, falso altrimenti.
 */
bool carica_insieme(insieme_t &ins)
{
	ifstream f(NOMEFILE);

	if (!f)
		return false;

	int max_num_elem;
	f>>max_num_elem;

	if (max_num_elem != ins.max_num_elem &&
	    ins.max_num_elem != 0) {
		delete [] ins.elementi;
		ins.max_num_elem = 0;
	}

	if (ins.max_num_elem == 0) {
		if (max_num_elem > 0)
			ins.elementi = new elemento_t[max_num_elem];
		ins.max_num_elem = max_num_elem;
	}

	f>>ins.num_elem;

	for (int i = 0 ; i < ins.num_elem ; i++)
		f>>ins.elementi[i].codice>>ins.elementi[i].num;

	return f;
}

// stampa l'intersezione tra gli insiemi ins1 ed ins2
void stampa_intersezione(const insieme_t &ins1, const insieme_t &ins2)
{
	int j = 0;
	for (int i = 0 ; i < ins1.num_elem ; i++) {
		for ( ; j < ins2.num_elem &&
			    ins2.elementi[j].codice <=
			     ins1.elementi[i].codice ; j++) {
			if (ins2.elementi[j].codice ==
			    ins1.elementi[i].codice) {
				cout<<ins1.elementi[i].codice<<": ";
				if (ins1.elementi[i].num <
				    ins2.elementi[j].num)
					cout<<ins1.elementi[i].num<<endl;
				else
					cout<<ins2.elementi[j].num<<endl;
				j++;
				break;
			}
		}
		if (j == ins2.num_elem)
			break;
	}
}


int main()
{
	const char menu[] =
		"1. Crea insieme\n"
		"2. Aggiungi codice\n"
		"3. Stampa insieme\n"
		"4. Salva insieme\n"
		"5. Carica insieme\n"
		"6. Stampa intersezione\n"
		"7. Esci\n";

	insieme_t ins;
	inizializza(ins);

	while (true) {
		cout<<menu<<endl;

		int scelta;
		cin>>scelta;

		switch (scelta) {
		case 1: {
			if (ins.max_num_elem > 0)
				delete [] ins.elementi;
			cout<<"Numero massimo di codici distinti: ";
			int N;
			cin>>N;
			ins = crea_insieme(N);
			break;}
		case 2: {
			cout<<"Codice: ";
			int cod;
			cin>>cod;
			if (!aggiungi_codice(ins, cod))
				cout<<"Aggiunta codice fallita"<<endl;
			break;}
		case 3:
			scrivi_insieme(ins, cout, false);
			break;
		case 4: {
			ofstream f(NOMEFILE);

			if (!scrivi_insieme(ins, f, true))
				cout<<"Salvataggio fallito"<<endl;
			break;}
		case 5:
			carica_insieme(ins);
			break;
		case 6: {
			insieme_t ins2 = crea_insieme(4);
			aggiungi_codice(ins2, 10);
			for (int i = 0 ; i < 3; i++) {
				aggiungi_codice(ins2, 95);
				aggiungi_codice(ins2, 3214);
			}
			aggiungi_codice(ins2, 87483);
			cout<<"Insieme 2:"<<endl;
			scrivi_insieme(ins2, cout, false);
			cout<<endl
			    <<"Intersezione: "<<endl;
			stampa_intersezione(ins, ins2);
			break;}
		case 7:
			return 0;
		default:
			cout<<"Scelta sbagliata"<<endl;
		}
	}

	return 1;

}
