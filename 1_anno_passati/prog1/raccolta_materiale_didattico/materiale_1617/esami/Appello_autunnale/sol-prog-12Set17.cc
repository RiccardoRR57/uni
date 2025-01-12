#include <iostream>
#include <fstream>

using namespace std;

// numero massimo messaggi
const int M = 10;
// lunghezza buffer
const int N = 10;
const char NOMEFILE[] = "stato.txt";

// tipi possibili di comandi
enum tipo_comando {CONTROLLO, LETTURA};
// stringa per semplificare la scrittura dei nomei dei comandi
const char stringa_comando[][20] = {"controllo", "lettura"};

// descrittore di un comando
struct comando_t {
	tipo_comando tipo;
	int codice;
	char *buffer;
};

// insieme dei comandi
struct insieme_comandi_t {
	comando_t comandi[M];
	int num; // numero di comandi attualmente presenti
	int prossimo; // indice del prossimo comando da eseguire
};

// inizializza l'insieme ins a vuoto
void inizializza(insieme_comandi_t &ins)
{
	ins.num = ins.prossimo = 0;
}

/*
 * Inserisce un comndo di tipo t nell'insieme ins. Ritorna vero in
 * caso di successo, falso in caso di fallimento.
 */
bool inserisci_comando(insieme_comandi_t &ins, tipo_comando &t)
{
	if (ins.num == M)
		return false;

	if (t == CONTROLLO) {
		cout<<"Inserire codice controllo: ";
		cin>>ins.comandi[ins.num].codice;

		ins.comandi[ins.num].buffer = 0;
	} else
		ins.comandi[ins.num].buffer = new char[N];

	ins.comandi[ins.num].tipo = t;
	ins.num++;

	return true;
}

/*
 * Esegue il prossimo comando nell'insieme ins. Ritorna vero in caso
 * di successo, falso in caso di fallimento.
 */
bool esegui_prossimo_comando(insieme_comandi_t &ins)
{
	if (ins.num == 0 || ins.prossimo == ins.num)
		return false;

	if (ins.comandi[ins.prossimo].tipo == LETTURA) {
		cout<<"Inserire contenuto buffer: ";
		cin>>ins.comandi[ins.prossimo].buffer;
	}

	ins.prossimo++;

	return true;
}

/*
 * Scrive lo stato dell'insieme ins sull'ostream os, usando il formato
 * opportuno per il salvataggio in un file se su_file è vero. Ritorna
 * vero in caso di successo, falso in caso di fallimento.
 */
bool scrivi_stato(const insieme_comandi_t &ins, ostream &os, bool su_file)
{
	if (su_file)
		os<<ins.num<<endl;

	if (su_file)
		os<<ins.prossimo<<endl;
	else
		os<<"Eseguiti"<<endl;

	for (int i = 0 ; i < ins.prossimo ; i++) {
		os<<stringa_comando[ins.comandi[i].tipo]<<" ";

		if (ins.comandi[i].tipo == CONTROLLO)
			os<<ins.comandi[i].codice<<endl;
		else
			os<<ins.comandi[i].buffer<<endl;
	}

	if (!su_file)
		os<<"Da eseguire"<<endl;

	for (int i = ins.prossimo ; i < ins.num ; i++) {
		os<<stringa_comando[ins.comandi[i].tipo]<<" ";

		if (ins.comandi[i].tipo == CONTROLLO)
			os<<ins.comandi[i].codice<<endl;
		else
			os<<endl;
	}

	return os;
}

/*
 * Scrive lo stato dell'insieme ins da file. Ritorna
 * vero in caso di successo, falso in caso di fallimento.
 */
bool carica_stato(insieme_comandi_t &ins)
{
	for (int i = 0 ; i < ins.prossimo ; i++)
		if (ins.comandi[i].tipo == LETTURA)
			delete [] ins.comandi[i].buffer;

	ifstream f(NOMEFILE);

	f>>ins.num>>ins.prossimo;

	for (int i = 0 ; i < ins.num ; i++) {
		char com[20];

		f>>com;
		if (!strcmp(stringa_comando[CONTROLLO], com))
			ins.comandi[i].tipo = CONTROLLO;
		else
			ins.comandi[i].tipo = LETTURA;

		if (ins.comandi[i].tipo == CONTROLLO)
			f>>ins.comandi[i].codice;
		else if (i < ins.prossimo) { // lettura gia' eseguita
			ins.comandi[i].buffer = new char[N];
			f>>ins.comandi[i].buffer;
		}
	}

	return f;
}

void vai_su_prossimo_buffer(const insieme_comandi_t &ins, int &idx_com)
{
	if (idx_com == ins.prossimo)
		return;

	while (idx_com < ins.prossimo &&
	       ins.comandi[idx_com].tipo != LETTURA)
		idx_com++;
}

// assume che ci si trovi su un comando di lettura eseguito
void vai_su_prossima_posizione(const insieme_comandi_t &ins, int &idx_com,
			       int &idx_car)
{
	if (ins.comandi[idx_com].buffer[idx_car+1] != '\0') {
		idx_car++;
		return;
	}
	idx_com++;
	vai_su_prossimo_buffer(ins, idx_com);
	idx_car = 0;
}

/*
 * Ritorna vero se la parola p è contenuta nella concatenazione
 * dei contenuti dei buffer dei comandi di lettura gia' eseguiti
 * all'interno dell'insieme ins.
 */
bool cerca_parola(const insieme_comandi_t &ins, const char p[])
{
	int idx_com = 0, idx_car = 0;
	vai_su_prossimo_buffer(ins, idx_com);

	cout<<"Paro andando su "<<idx_com<<endl<<endl;
	while (idx_com < ins.prossimo) {
		if (ins.comandi[idx_com].buffer[idx_car] == p[0]) {
			int i = 0;
			int idx_com2 = idx_com, idx_car2 = idx_car;
			do {
				i++;
				vai_su_prossima_posizione(ins, idx_com2,
							  idx_car2);
			} while(p[i] != '\0' &&
				idx_com2 < ins.prossimo &&
				ins.comandi[idx_com2].buffer[idx_car2] ==
				p[i]) ;

			if (p[i] == '\0')
				return true;
		}
		vai_su_prossima_posizione(ins, idx_com, idx_car);
	}
	return false;
}

int main()
{
	insieme_comandi_t ins;

	inizializza(ins);

	const char menu[] =
		"1. Inserisci comando\n"
		"2. Esegui prossimo comando\n"
		"3. Stampa comandi\n"
		"4. Salva stato\n"
		"5. Carica stato\n"
		"6. Cerca parola\n"
		"7. Esci\n";

	while (true) {
		cout<<menu<<endl;
		int scelta;
		cin>>scelta;

		switch (scelta) {
		case 1: {
			char tipo_comando_car;
			tipo_comando tipo;

			cout<<"Inserire tipo comando ([C]ontrollo [L]ettura): "
			    <<endl;
			cin>>tipo_comando_car;
			if (tipo_comando_car == 'C' || tipo_comando_car == 'c')
				tipo = CONTROLLO;
			else
				tipo = LETTURA;
			if (!inserisci_comando(ins, tipo))
				cout<<"Inserimento fallito"<<endl;
			break;}
		case 2:
			if (!esegui_prossimo_comando(ins))
				cout<<"Esecuzione fallita"<<endl;
			break;
		case 3:
			scrivi_stato(ins, cout, false);
			break;
		case 4: {
			ofstream f(NOMEFILE);

			if (!scrivi_stato(ins, f, true))
				cout<<"Salvataggio fallito"<<endl;
			break;}
		case 5:
			if (!carica_stato(ins))
				cout<<"Caricamento fallito"<<endl;
			break;
		case 6:{
			char parola[N];

			cout<<"Parola da cercare: ";
			cin>>parola;
			if (cerca_parola(ins, parola))
				cout<<"Parola trovata"<<endl;
			else
				cout<<"Parola non trovata"<<endl;
			break;}
		case 7:
			return 0;
		default:
			cout<<"Scelta errata"<<endl;
		}
	}
	return 1;
}
