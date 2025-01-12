#include <iostream>
#include <fstream>

using namespace std;

const int MAXLUN = 20;
const char NOMEFILE[] = "consuntivo.txt";

/* descrittore di un dipendente all'interno di un consuntivo */
struct dati_dipendente_t {
	char nome[MAXLUN]; /* stringa contenente il nome */
	unsigned int ore;  /* numero di ore lavorate dal dipendente */
};

/* descrittore di un consuntivo */
struct consuntivo_t {
	char nome_azienda[MAXLUN]; /* stringa contenente il nome dell'azienda */
	unsigned int anno;	   /* anno a cui è relativo il consuntivo */
	dati_dipendente_t *elenco; /* elenco dati dei dipendenti */
	unsigned int num_dip;	   /* lunghezza dell'elenco */
};

/*
 * Inizializza il consuntivo c a vuoto, assumendo che non sia mai stato
 * inizializzato prima
*/
void inizializza_consuntivo(consuntivo_t &c)
{
	c.nome_azienda[0] = '\0';
	c.anno = 0;
	c.num_dip = 0;
}

/*
 * Funzione di servizio per inserire i dati d all'interno del
 * consuntivo c, mantenendo l'elenco ordinato alfabeticamente per nome
 * dei dipendenti. Assume la lunghezza corrente dell'elenco sia
 * cur_num.
 */
void inserisci_in_ordine(consuntivo_t &c, const dati_dipendente_t &d,
			 unsigned int cur_num)
{
	int i;
	for (i = 0 ; i < cur_num &&
		     strcmp(c.elenco[i].nome, d.nome) < 0 ; i++)
		;

	for (int j = cur_num ; j > i ; j--) {
		cout<<"Copying "<<j-1<<"into "<<j<<endl;
		strcpy(c.elenco[j].nome, c.elenco[j-1].nome);
		c.elenco[j].ore = c.elenco[j-1].ore;
	}

	strcpy(c.elenco[i].nome, d.nome);
	c.elenco[i].ore = d.ore;
}

/*
 * Reinizializza il consuntivo c a contenere i dati di N dipendenti,
 * con tutte le informazioni lette dall'input stream is.
 */
void reinizializza_consuntivo(istream &is, consuntivo_t &c, unsigned int N)
{

	if (N != c.num_dip && c.num_dip > 0) {
		delete [] c.elenco;
		c.num_dip = 0;
	}

	if (c.num_dip == 0 && N > 0)
		c.elenco = new dati_dipendente_t[N];

	is>>c.nome_azienda;
	is>>c.anno;
	c.num_dip = N;
	for (unsigned int i = 0 ; i < N ; i++) {
		dati_dipendente_t d;

		is>>d.nome>>d.ore;
		inserisci_in_ordine(c, d, i);
	}
}

/*
 * Scrive il consuntivo c sull'ostream os. Se sufile è vero, allora
 * utilizza un formato adatto al salvataggio del consuntivo su
 * file. Ritorna vero in caso di successo, falso altrimenti.
 */
bool scrivi_consuntivo(ostream &os, const consuntivo_t &c, bool sufile)
{
	if (sufile)
		os<<c.num_dip<<endl;

	if (!sufile && c.nome_azienda[0] == '\0')
		return os;

	os<<c.nome_azienda<<'\t'<<c.anno<<endl;

	for (int i = 0 ; i < c.num_dip ; i++)
		os<<c.elenco[i].nome<<"\t\t"<<c.elenco[i].ore<<endl;

	return os;
}

/*
 * Carica il contenuto del file NOMEFILE all'interno del consuntivo c
 * L'eventuale precedente contenuto del consuntivo è perso. Ritorna
 * vero in caso di successo, falso altrimenti.
 */
bool carica_consuntivo(consuntivo_t &c)
{
	ifstream f(NOMEFILE);

	unsigned int N;
	f>>N;

	reinizializza_consuntivo(f, c, N);

	return f;
}

/*
 * Stampa la fusione tra i consuntivi c1 e c2.
 */
void stampa_consuntivi(const consuntivo_t &c1, const consuntivo_t &c2)
{
	int ultima = 0;
	for (int i = 0 ; i < c1.num_dip ; i++) {
		bool uguale = false;

		int j;
		for (j = ultima ; j < c2.num_dip &&
			     strcmp(c2.elenco[j].nome, c1.elenco[i].nome) <= 0;
		     j++) {
			if (strcmp(c2.elenco[j].nome, c1.elenco[i].nome) != 0)
				cout<<c2.elenco[j].nome<<"\t\t"
				    <<c2.elenco[j].ore<<endl;
			else {
				cout<<c2.elenco[j].nome<<"\t\t"
				    <<c1.elenco[i].ore + c2.elenco[j].ore
				    <<endl;
				uguale = true;
			}
		}
		ultima = j;

		if (!uguale)
				cout<<c1.elenco[i].nome<<"\t\t"
				    <<c1.elenco[i].ore<<endl;
	}
}

int main()
{
	consuntivo_t c1, c2;
	inizializza_consuntivo(c1);
	inizializza_consuntivo(c2);

	const char menu[] =
		"1. Reinizializza consuntivo\n"
		"2. Stampa consuntivo\n"
		"3. Salva catalogo\n"
		"4. Carica consuntivo\n"
		"5. Stampa consuntivi\n"
		"6. Esci\n";

	while (true) {
		cout<<menu<<endl;

		int scelta;
		cin>>scelta;

		switch (scelta) {
		case 1: {
			unsigned int N;
			cout<<"Nuovo numero dipendenti: ";
			cin>>N;
			cout<<"Inserire nome azienda, anno e dati dipendenti: ";
			reinizializza_consuntivo(cin, c1, N);
			break;}
		case 2:
			scrivi_consuntivo(cout, c1, false);
			break;
		case 3: {
			ofstream f(NOMEFILE);
			if (!scrivi_consuntivo(f, c1, true))
				cout<<"Salvataggio fallito"<<endl;
			break;}
		case 4:
			if (!carica_consuntivo(c1))
				cout<<"Caricamento fallito"<<endl;
			break;
		case 5: {
			unsigned int N;
			cout<<"Nuovo numero dipendenti: ";
			cin>>N;
			cout<<"Inserire nome azienda, anno e dati dipendenti: ";
			reinizializza_consuntivo(cin, c2, N);

			stampa_consuntivi(c1, c2);
			break;}
		case 6:
			return 0;
		default:
			cout<<"Scelta non valida"<<endl;
		}
	}
}
