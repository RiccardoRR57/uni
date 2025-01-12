#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

const int MAXLUNTITOLO = 31;
const char NOMEFILE_BRANI[] = "brani.txt";
const char NOMEFILE_SERVER[] = "server.txt";

/* descrittore generi musicali */
enum genere_t {	pop, classica, rock };

/* descrittore brano */
struct brano_t {
	char titolo[MAXLUNTITOLO];
	genere_t genere;
	unsigned int num_downl;
};

/* descrittore catalogo */
struct catalogo_t {
	brano_t *brani;			/* array dinamico di brani */
	unsigned int num_brani;		/* numero attuale di brani nel catal. */
	unsigned int max_num_brani;	/* lunghezza massima catalogo */
};

/* inizializza il catalogo cat a vuoto */
void inizializza(catalogo_t &cat)
{
	cat.brani = 0;
}

/*
 * Reinizializza il catalogo cat a contenere al piu' N
 * brani. L'eventuale precedente contenuto è perso.
 */
void reinizializza(catalogo_t &cat, unsigned int N)
{

	if (cat.brani != 0 && cat.max_num_brani != N) {
		delete [] cat.brani;
		cat.brani = 0;
	}

	if (cat.brani == 0 && N > 0)
		cat.brani = new brano_t[N];

	cat.num_brani = 0;
	cat.max_num_brani = N;
}

/*
 * Legge un genere dall'istream is, sotto forma di carattere, e lo
 * inserisce nella variabile genere. Ritorna vero in caso di successo,
 * falso altrimenti.
 */
bool leggi_genere(istream &is, genere_t &genere)
{
	char c;
	is>>c;

	switch (c) {
	case 'p':
		genere = pop;
		break;
	case 'c':
		genere = classica;
		break;
	case 'r':
		genere = rock;
		break;
	default:
		return false;
	}

	return true;
}

/*
 * Scrive il genere g sull'ostream os, sotto forma di carattere.
 */
void scrivi_genere(ostream &os, genere_t g)
{
	switch (g) {
	case pop:
		os<<'p';
		break;
	case classica:
		os<<'c';
		break;
	case rock:
		os<<'r';
		break;
	}
}

/*
 * Inserisce un brano, dal titolo e genere passati in ingresso, nel
 * catalogo cat. Inizializza il numero di download per tale brano a
 * num_downl. Ritorna vero in caso di successo, falso altrimenti.
 */
bool inserisci_brano(catalogo_t &cat, const char *titolo, genere_t genere,
		     unsigned int num_downl)
{
	if (cat.brani == 0 || cat.num_brani == cat.max_num_brani)
		return false;

	int ins_idx;
	for (ins_idx = 0 ; ins_idx < cat.num_brani ; ins_idx++)
		if (strcmp(cat.brani[ins_idx].titolo, titolo) >= 0)
			break;
	if (strcmp(cat.brani[ins_idx].titolo, titolo) == 0)
		return false;

	for (int i = cat.num_brani ; i > ins_idx ; i--)
		cat.brani[i] = cat.brani[i-1];

	strcpy(cat.brani[ins_idx].titolo, titolo);
	cat.brani[ins_idx].genere = genere;
	cat.brani[ins_idx].num_downl = num_downl;

	cat.num_brani++;

	return true;
}

/*
 * Incrementa di 1 il numero di download del brano dal titolo passato
 * in ingresso, all'interno del catalogo cat.
 */
bool scarica_brano(catalogo_t &cat, const char *titolo)
{
	if (cat.brani == 0)
		return false;

	for (int i = 0 ; i < cat.num_brani ; i++)
		if (strcmp(cat.brani[i].titolo, titolo) == 0) {
			cat.brani[i].num_downl++;
			break;
		}

	return true;
}

/*
 * Scrive il contenuto del catalogo cat sull'ostream os, utilizzando
 * un formato opportuno per il salvataggio nel caso in cui su_file sia
 * vero. Ritorna vero in caso di successo, falso altrimenti.
 */
bool scrivi_catalogo(const catalogo_t &cat, ostream &os, bool su_file)
{
	if (su_file)
		os<<cat.max_num_brani<<" "<<cat.num_brani<<endl;

	if (cat.brani == 0)
		return os;

	for (int i = 0 ; i < cat.num_brani ; i++) {
		os<<cat.brani[i].titolo<<'\t';
		scrivi_genere(os, cat.brani[i].genere);
		os<<'\t'<<cat.brani[i].num_downl
		    <<endl;
	}

	return os;
}

/*
 * Carica il contenuto del catalogo cat da file. Il precedente
 * contenuto è perso. Ritorna vero in caso di successo, falso
 * altrimenti.
 */
bool carica_catalogo(catalogo_t &cat)
{

	ifstream f(NOMEFILE_BRANI);

	if (!f)
		return false;

	unsigned int N;
	f>>N;

	reinizializza(cat, N);

	unsigned int num_brani;
	f>>num_brani;

	for (int i = 0 ; i < num_brani ; i++) {
		char titolo[MAXLUNTITOLO];
		f>>titolo;
		genere_t genere;
		if (!leggi_genere(f, genere))
			return false;
		unsigned int num_downl;
		f>>num_downl;
		inserisci_brano(cat, titolo, genere, num_downl);
	}

	return f;
}

/*
 * Stampa il numero totale di download eseguiti da ciascun server.
 */
void stampa_download_per_server(const catalogo_t &cat)
{
	ifstream f(NOMEFILE_SERVER);

	if (cat.brani == 0) {
		cout<<"Catalogo vuoto"<<endl;
		return;
	}

	if (!f) {
		cout<<"Errore in apertura file"<<endl;
		return;
	}

	const unsigned int MAXLUN_NOME_SERVER = 30;
	struct server_t {
		char nome[MAXLUN_NOME_SERVER];
		genere_t genere;
		unsigned int tot_downl;
	} ;
	server_t server[3];

	for (int i = 0 ; i < 3 ; i++) {
		char nome[MAXLUN_NOME_SERVER];
		genere_t genere;
		f>>nome;
		leggi_genere(f, genere);
		strcpy(server[genere].nome, nome);
		server[genere].genere = genere;
		server[genere].tot_downl = 0;
	}

	for (int j = 0 ; j < cat.num_brani ; j++)
		server[cat.brani[j].genere].tot_downl +=
			cat.brani[j].num_downl;

	for (int i = 0 ; i < 3 ; i++) {
		cout<<server[i].nome<<'\t';
		scrivi_genere(cout, server[i].genere);
		cout<<'\t'<<server[i].tot_downl<<endl;
	}
}

int main()
{
	catalogo_t cat;

	inizializza(cat);

	const char menu[] =
		"1. Reinizializza catalogo\n"
		"2. Inserisci brano\n"
		"3. Scarica brano\n"
		"4. Stampa catalogo\n"
		"5. Salva catalogo\n"
		"6. Carica catalogo\n"
		"7. Stampa download per server\n"
		"8. Esci\n";

	while (true) {
		cout<<menu<<endl;
		int scelta;
		cin>>scelta;

		switch (scelta) {
		case 1: {
			unsigned int N;
			cout<<"Lunghezza massima catalogo: ";
			cin>>N;
			reinizializza(cat, N);
			break;}
		case 2: {
			char titolo[MAXLUNTITOLO];
			cout<<"Titolo: ";
			cin>>titolo;
			genere_t genere;
			cout<<"Inserisci genere [p|c|r]: ";
			if (!leggi_genere(cin, genere)) {
				cout<<"Genere errato, operazione annullata"
				    <<endl;
				break;
			}
			if (!inserisci_brano(cat, titolo, genere, 0))
				cout<<"Inserimento fallito"<<endl;
			break;}
		case 3: {
			char titolo[MAXLUNTITOLO];
			cout<<"Titolo: ";
			cin>>titolo;
			if (!scarica_brano(cat, titolo))
				cout<<"Aggiornamento fallito"<<endl;
			break;}
		case 4:
			scrivi_catalogo(cat, cout, false);
			break;
		case 5: {
			ofstream f(NOMEFILE_BRANI);
			if (!scrivi_catalogo(cat, f, true))
				cout<<"Salvataggio fallito"<<endl;
			break;}
		case 6:
			if (!carica_catalogo(cat))
				cout<<"Caricamento fallito"<<endl;
			break;
		case 7:
			stampa_download_per_server(cat);
			break;
		default:
			return 0;
		}
	}

	return 1;
}
