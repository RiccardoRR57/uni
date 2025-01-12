#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

const int MAX_PAROLE = 10;
const char NOMEFILE[] = "parole.txt";

// descrittore insieme di parole
struct insieme_parole_t {
	char *prefissi[MAX_PAROLE]; // array statico di prefissi
	int quanti;		    // numero di prefissi attuali
	int maxlun;		    // lun massima parole memorizzate
};

// inizializza l'insieme ins a vuoto
void inizializza(insieme_parole_t &ins)
{
	ins.quanti = 0;
}

// aggiungi una parola, di suffisso suff, all'insieme ins; ritorna
// vero in caso di successo, falso altrimenti
bool aggiungi_parola(insieme_parole_t &ins, const char suff[])
{
	if (ins.quanti == MAX_PAROLE)
		return false;

	int lun = strlen(suff);

	ins.prefissi[ins.quanti] = new char[lun + 1];
	strcpy(ins.prefissi[ins.quanti], suff);
	ins.quanti++;

	ins.maxlun += lun;

	return true;
}

// scrivi il contenuto dell'insime ins sull'ostream os, utilizzando il
// formato adatto al file nel caso in cui su_file sia vero; ritorna
// vero in caso di successo, falso altrimenti
bool scrivi_parole(ostream &os, const insieme_parole_t &ins, bool su_file)
{
	char *buf;

	if (su_file) {
		os<<ins.quanti<<" "<<ins.maxlun<<endl;
		for (int i = 0;  i < ins.quanti; i++)
			os<<strlen(ins.prefissi[i])<<" "<<ins.prefissi[i]<<endl;
		return os;
	}

	buf = new char[ins.maxlun + 1];
	for (int i = 0, pos = 0 ; i < ins.quanti; i++) {
		int lun = strlen(ins.prefissi[i]);

		for (int j = 0 ; j < lun ;  j++)
			buf[pos + j] = ins.prefissi[i][j];
		buf[pos + lun] = '\0';
		os<<buf<<endl;
		pos += lun;
	}

	return true;
}

// carica le parole nell'insieme ins, leggendole dal file predefinito;
// ritorna vero in caso di successo, falso altrimenti
bool carica_parole(insieme_parole_t &ins)
{
	ifstream f(NOMEFILE);

	if (!f)
		return false;

	int quanti;
	f>>quanti;

	f>>ins.maxlun;

	int sovrascrivibili = quanti < ins.quanti ? quanti : ins.quanti;

	for (int i = 0 ; i < quanti; i++) {
		int lun;
		f>>lun;

		if (i < sovrascrivibili &&
		    strlen(ins.prefissi[i]) != lun) {
			delete ins.prefissi[i];
			ins.prefissi[i] = 0;
		}

		if (i >= sovrascrivibili || ins.prefissi[i] == 0)
			ins.prefissi[i] = new char[lun + 1];

		f>>ins.prefissi[i];
	}
	ins.quanti = quanti;

	return f;
}

// controlla se la parola memorizzata nella stringa s risulta essere
// un prefisso per almeno una delle parole memorizzare nell'insieme
// ins; in caso di successo ritorna l'indice della piu' piccola parola
// in ins per cui s è un prefisso, altrimenti ritorna -1
int controlla_se_prefisso(const insieme_parole_t &ins, const char s[])
{
	if (s[0] == '\0' || strlen(s) >= ins.maxlun)
		return -1;

	for (int i = 0, pos = 0 ; i < ins.quanti ; i++) {
		int lun = strlen(ins.prefissi[i]);
		for (int j = 0 ; j < lun; j++) {
			if (ins.prefissi[i][j] != s[pos])
				return -1;
			pos++;
			if (s[pos] == '\0')
				return i;
		}
	}

	// non dovremmo MAI arrivare qui, perché strlen[s] <= ins.maxlun
	return -1;
}

int main()
{
	insieme_parole_t ins;

	inizializza(ins);

	const char menu[] =
		"1. Aggiungi parola\n"
		"2. Stampa parole\n"
		"3. Salva stato\n"
		"4. Carica stato\n"
		"5. Controlla se prefisso\n"
		"6. Esci\n";

	while (true) {
		cout<<menu<<endl;
		int scelta;
		cin>>scelta;

		switch(scelta) {
		case 1: {
			cout<<"Suffisso? ";
			char suff[128];
			cin>>suff;

			if (!aggiungi_parola(ins, suff))
				cout<<"Inserimento fallito"<<endl;
			break;}
		case 2:
			scrivi_parole(cout, ins, false);
			break;
		case 3: {
			ofstream f(NOMEFILE);
			if (!scrivi_parole(f, ins, true))
				cout<<"Salvataggio fallito"<<endl;
			break;}
		case 4:
			if (!carica_parole(ins))
				cout<<"Caricamento fallito"<<endl;
			break;
		case 5: {
			cout<<"Parola? ";
			char p[128];
			cin>>p;

			int idx = controlla_se_prefisso(ins, p);
			cout<<"Indice: "<<idx<<endl;
			break;}
		case 6:
			return 0;
		default:
			cout<<"Scelta errata"<<endl;

		}


	}

	return 1;
}
