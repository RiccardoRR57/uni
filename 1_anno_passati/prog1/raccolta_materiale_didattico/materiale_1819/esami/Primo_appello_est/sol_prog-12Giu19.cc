#include <iostream>
#include <fstream>

using namespace std;

const char NOMEFILE[] = "insieme_proc.txt";

enum stato_proc { FUNZIONANTE, FALLITO };

const char stringa_stato[][12] = {"funzionante", "fallito"};

struct processo_t {
	stato_proc stato; /* stato del processo */
	int sync_pid; /* pid del processo rispetto a cui questo
		       * processo e' sincronizzato; -1 vuol dire
		       * nessuna sincronizzazione
		       */
	unsigned int *processi_sync;
	unsigned int num_proc_sync;
};

struct insieme_processi_t {
	processo_t *processi;
	unsigned int num_proc;
};

void inizializza_insieme(insieme_processi_t &ins)
{
	ins.num_proc = 0;
}

void rialloca_insieme(insieme_processi_t &ins, unsigned int N)
{
	if (N != ins.num_proc && ins.num_proc > 0) {
		for (int i = 0 ; i < ins.num_proc ; i++)
			delete [] ins.processi[i].processi_sync;

		delete [] ins.processi;
		ins.num_proc = 0;
	}

	if (N > 0 && ins.num_proc == 0) {
		ins.processi = new processo_t[N];

		for (int i = 0 ; i < N ; i++) {
			ins.processi[i].processi_sync = new unsigned
			int[N];
		}
	}

	ins.num_proc = N;
}

void reinizializza_insieme(insieme_processi_t &ins, unsigned int N)
{
	rialloca_insieme(ins, N);

	for (int i = 0 ; i < N ; i++) {
		ins.processi[i].stato = FUNZIONANTE;
		ins.processi[i].sync_pid = -1;

		ins.processi[i].num_proc_sync = 0;
	}
}


bool scrivi_insieme(ostream &os, const insieme_processi_t &ins,
		    bool su_file) {

	if (su_file)
		os<<ins.num_proc<<endl;

	for (int i = 0 ; i < ins.num_proc ; i++) {
		if (su_file)
			os<<ins.processi[i].stato<<'\t'
			  <<ins.processi[i].sync_pid<<'\t'
			  <<ins.processi[i].num_proc_sync;
		else {
			os<<i<<' '
			  <<stringa_stato[ins.processi[i].stato]<<'\t';

			if (ins.processi[i].sync_pid != -1)
				os<<ins.processi[i].sync_pid;
			else
				os<<"no-sinc";

		}

		os<<'\t';
		for (int j = 0 ;
		     j < ins.processi[i].num_proc_sync;
		     j++)
			os<<' '<<ins.processi[i].processi_sync[j];

		os<<endl;
	}

	return os;
}

bool carica_insieme(insieme_processi_t &ins) {
	ifstream f(NOMEFILE);

	unsigned int N;
	f>>N;
	rialloca_insieme(ins, N);

	for (int i = 0 ; i < ins.num_proc ; i++) {
		int buf_stato;
		f>>buf_stato;

		if (buf_stato == 0)
			ins.processi[i].stato = FUNZIONANTE;
		else
			ins.processi[i].stato = FALLITO;

		f>>ins.processi[i].sync_pid;

		f>>ins.processi[i].num_proc_sync;

		for (int j = 0 ;
		     j < ins.processi[i].num_proc_sync;
		     j++)
			f>>ins.processi[i].processi_sync[j];
	}
	return true;
}

bool crea_sincronizzazione(insieme_processi_t &ins, unsigned int p1,
			   unsigned int p2)
{
	if (p1 == p2 || p1 >= ins.num_proc || p2 >= ins.num_proc ||
	    ins.processi[p2].stato == FALLITO)
		return false;

	ins.processi[p1].sync_pid = p2;

	unsigned int &num_proc_sync = ins.processi[p2].num_proc_sync;

	ins.processi[p2].processi_sync[num_proc_sync] = p1;
	num_proc_sync++;

	return true;
}

bool imposta_fallito(insieme_processi_t &ins, unsigned int p)
{

	if (p >= ins.num_proc)
		return false;

	for (int i = 0 ; i < ins.processi[p].num_proc_sync ; i++)
		ins.processi[ins.processi[p].processi_sync[i]].sync_pid = -1;
	ins.processi[p].num_proc_sync = 0;

	ins.processi[p].stato = FALLITO;

	return true;
}

int main()
{
	insieme_processi_t ins;
	inizializza_insieme(ins);

	const char menu[] =
		"1. Reinizializza insieme\n"
		"2. Stampa insieme\n"
		"3. Salva insieme\n"
		"4. Carica insieme\n"
		"5. Crea sincronizzazione\n"
		"6. Imposta fallito\n"
		"7. Esci\n";

	while (true) {
		cout<<menu<<endl;

		int scelta;
		cin>>scelta;

		switch (scelta) {
		case 1: {
			unsigned int N;
			cout<<"Nuovo numero processi: ";
			cin>>N;
			reinizializza_insieme(ins, N);
			break;}
		case 2:
			scrivi_insieme(cout, ins, false);
			break;
		case 3: {
			ofstream f(NOMEFILE);
			if (!scrivi_insieme(f, ins, true))
				cout<<"Salvataggio fallito"<<endl;
			break;}
		case 4:
			if (!carica_insieme(ins))
				cout<<"Caricamento fallito"<<endl;
			break;
		case 5: {
			unsigned int p1, p2;

			cout<<"Inserire pid dei due processi: ";
			cin>>p1>>p2;

			crea_sincronizzazione(ins, p1, p2);
			break;}
		case 6:{
			unsigned int p;

			cout<<"Inserire pid del processo: ";
			cin>>p;

			imposta_fallito(ins, p);
			break;}
		case 7:
			return 0;
		default:
			cout<<"Scelta non valida"<<endl;
		}
	}
}
