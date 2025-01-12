#include <iostream>
#include <fstream>

using namespace std;

const char NOMEFILE[] = "lista_operazioni.txt";

/* descrittore di una singola operazione di stoccaggio */
struct operazione_t {
	unsigned int posizione;		/* posizione contenitore interessato */
	unsigned int num_scatole;	/* numero di scatole da stoccare */
};

/* lista delle operazioni da eseguire */
struct lista_operazioni_t {
	operazione_t *operazioni;	/* array dinamico contenente la lista */
	unsigned int num_op;		/* numero di operazioni nella lista */
	unsigned max_op;		/* lunghezza massima della lista */
};

/* inizializza la lista l a vuota */
void inizializza(struct lista_operazioni_t &l)
{
	l.num_op = l.max_op = 0;
}

/*
 * Fissa ad N la lunghezza massima per la lista l. L'eventuale
 * precedente contenuto e' perso.
*/
void cambia_max_operazioni(struct lista_operazioni_t &l, unsigned int N)
{

	if (l.max_op > 0 && l.max_op != N) {
		delete [] l.operazioni;
		l.max_op = 0;
	}

	if (l.max_op == 0)
		l.operazioni = new operazione_t[N];

	l.max_op = N;
	l.num_op = 0;
}

/* enumerato per scegliere la versione della inserisci da eseguire */
enum versione_t {uno, due};

/*
 * Inserisce nella lista l una operazione di stoccaggio di n scatole
 * nel contenitore in posizione p. Esegue la versione base o la
 * versione due della funzione in base al valore del parametro
 * ver. Ritorna verso in caso di successo, falso altrimenti.
 */
bool inserisci_operazione(struct lista_operazioni_t &l, unsigned int p,
			  unsigned int n, versione_t ver)
{
	if (l.num_op >= l.max_op)	/* posizioni partono da 0 */
		return false;

	int i, idx_fusione = -1;
	for (i = 0 ; i < l.num_op && p > l.operazioni[i].posizione ; i++)
		;

	if (i < l.num_op && p == l.operazioni[i].posizione)
		idx_fusione = i;
	else if (ver == due) {
		int dist_prec = 30, dist_succ = 30;

		if (i > 0)
			dist_prec = p - l.operazioni[i-1].posizione;

		if (i < l.num_op)
			dist_succ = l.operazioni[i].posizione - p;

		cout<<"i "<<i<<"l.num_op "<<l.num_op
		    <<"dist_prec "<<dist_prec
		    <<"dist_succ "<<dist_succ<<endl;

		if (dist_prec < dist_succ && dist_prec <= 20)
			idx_fusione = i - 1;
		else if (dist_prec >= dist_succ && dist_succ <= 20)
			idx_fusione = i;
	}

	if (idx_fusione != -1)
		l.operazioni[idx_fusione].num_scatole += n;
	else {
		for (int j = l.num_op - 1 ; j >= i ; j--)
			l.operazioni[j + 1] = l.operazioni[j];

		l.operazioni[i].posizione = p;
		l.operazioni[i].num_scatole = n;

		l.num_op++;
	}
	return true;
}

/*
 * Scrive il contenuto della lista l sull'ostream os. Scrive tutti i
 * dati della lista se su_file è vero. Ritorna verso in caso di
 * successo, falso altrimenti.
 */
bool scrivi_lista(const struct lista_operazioni_t &l, ostream &os, bool su_file)
{
	if (su_file)
		os<<l.max_op<<" "<<l.num_op<<endl;

	for (int i = 0 ; i < l.num_op ; i++)
		os<<l.operazioni[i].posizione<<" "
		  <<l.operazioni[i].num_scatole<<endl;
	return os;
}

/*
 * Carica il contenuto della lista l da file. L'eventuale contenuto
 * precedente e' perso. Ritorna verso in caso di successo, falso
 * altrimenti.
 */
bool carica_lista(struct lista_operazioni_t &l)
{
	ifstream f(NOMEFILE);

	if (!f)
		return false;

	unsigned int N;
	f>>N;
	cambia_max_operazioni(l, N);

	f>>l.num_op;
	for (int i = 0 ; i < l.num_op ; i++)
		f>>l.operazioni[i].posizione>>l.operazioni[i].num_scatole;

	return f;
}

int main()
{
	lista_operazioni_t l;
	inizializza(l);

	const char menu[] =
		"1. Inizializza contenitori\n"
		"2. Inserisci operazione\n"
		"3. Stampa lista operazioni\n"
		"4. Salva lista operazioni\n"
		"5. Carica lista operazioni\n"
		"6. Inserisci operazione 2\n"
		"7. Esci\n";

	while (true) {
		cout<<menu<<endl;

		int scelta;
		cin>>scelta;

		switch (scelta) {
		case 1: {
			unsigned int N;
			cout<<"Nuova lunghezza massima lista: ";
			cin>>N;
			cambia_max_operazioni(l, N);
			break;}
		case 2: {
			unsigned int p, n;

			cout<<"Posizione e numero scatole: ";
			cin>>p>>n;
			if (!inserisci_operazione(l, p, n, uno))
				cout<<"Inserimento fallito"<<endl;
			break;}
		case 3:
			scrivi_lista(l, cout, false);
			break;
		case 4:{
			ofstream f(NOMEFILE);

			if (!scrivi_lista(l, f, true))
				cout<<"Salvataggio fallito"<<endl;
			break;}
		case 5:
			if (!carica_lista(l))
				cout<<"Caricamento fallito"<<endl;
			break;
		case 6: {
			unsigned int p, n;

			cout<<"Posizione e numero scatole: ";
			cin>>p>>n;
			if (!inserisci_operazione(l, p, n, due))
				cout<<"Inserimento fallito"<<endl;
			break;}
		case 7:
			return 0;
		}
	}

	return 1;
}
