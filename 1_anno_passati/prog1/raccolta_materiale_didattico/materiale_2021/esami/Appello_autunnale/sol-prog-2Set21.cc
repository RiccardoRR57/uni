#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>

using namespace std;

const char NOMEFILE[] = "memoria.txt";

// descrittore di un oggetto allocato
struct oggetto_t {
	unsigned int pos, dim; // posizione e numero di celle occupate
};

// descrittore della memoria
struct memoria_t {
	unsigned int N;			// numero di celle della memoria
	oggetto_t *oggetti;		// array dinamico oggetti allocati
	unsigned int num_oggetti;	// numero oggetti allocati
};

/*
 * Inizializza la memoria m a 0 celle, assumendo che non sia mai stata
 * inizializzata prima.
 */
void inizializza(memoria_t &m)
{
	m.N = 0;
}

/*
 * Reinizializza la memoria m ad N celle, assumendo che sia già stata
 * inizializzata precedentemente. L'eventuale precedente contenuto
 * della memoria e' perso.
 */
void reinizializza(memoria_t &m, unsigned int N)
{
	if (N != m.N && m.N > 0) {
		delete [] m.oggetti;
		m.N = 0;
	}

	if (N > 0 && m.N == 0) {
		m.oggetti = new oggetto_t[N];
		m.N = N;
	}
	m.num_oggetti = 0 ;
}

/*
 * Funzione di supporto che prova a spostare l'oggetto di indice
 * 'successivo' all'interno della memoria m, per fare posto ad un
 * oggetto da mettere in posizione pos e che occupa dim celle. Ritorna
 * vero in caso di successo, e falso altrimenti.
 */
bool prova_spostamento(memoria_t &m, unsigned int pos, unsigned int dim,
		       unsigned int successivo)
{
	unsigned int nuova_pos = pos + dim;

	unsigned int limite;
	if (successivo + 1 < m.num_oggetti)
		limite = m.oggetti[successivo + 1].pos;
	else
		limite = m.N;

	if (nuova_pos >= limite)
		return false;

	m.oggetti[successivo].pos = nuova_pos;

	return true;
}

/*
 * Alloca un oggetto di dimensione dim, in posizione pos, nella
 * memoria m. Se sposta e' vero, allora, nel caso in cui non vi sia
 * spazio sufficiente, prova a sostare l'oggetto successivo per
 * ottenere lo spazio necessario. Se lo spazio per il nuovo oggetto
 * c'è o è stato ricavato, allora effettua l'allocazione e ritorna
 * vero. Altrimenti non effettua alcuna allocazione e ritorna falso.
 */
bool alloca_oggetto(memoria_t &m, unsigned int pos, unsigned int dim, bool sposta)
{
	if (dim == 0 || pos >= N)
		return false;

	unsigned int successivo = 0 ;
	for (; successivo < m.num_oggetti ; successivo++)
		if (pos <= m.oggetti[successivo].pos +
		    m.oggetti[successivo].dim - 1)
			break;

	unsigned int limite;
	if (successivo < m.num_oggetti)
		limite = m.oggetti[successivo].pos;
	else
		limite = m.N;

	if (pos + dim - 1 >= limite)
		if (!sposta || successivo == m.num_oggetti ||
		    !prova_spostamento(m, pos, dim, successivo))
			return false;

	for (unsigned int i = m.num_oggetti ; i > successivo ; i--)
		m.oggetti[i] = m.oggetti[i-1];

	m.oggetti[successivo].pos = pos;
	m.oggetti[successivo].dim = dim;

	m.num_oggetti++;

	return true;
}

// stampa il contenuto della memoria m su stdout
void stampa_memoria(const memoria_t &m)
{

	for (unsigned int i = 0 ; i < m.N ; i++)
		cout<<i%10;
	cout<<endl;

	unsigned int ultima = 0 ;
	for (unsigned int i = 0 ; i < m.num_oggetti ; i++) {
		for (unsigned j = ultima ; j < m.oggetti[i].pos ; j++)
			cout<<'-';
		ultima = m.oggetti[i].pos + m.oggetti[i].dim;
		for (unsigned j = m.oggetti[i].pos ;
		     j < ultima; j++)
			cout<<'*';
	}
	for (unsigned j = ultima ; j < m.N ; j++)
		cout<<'-';

	cout<<endl;
}

// salva dimensioni e contenuto della memoria m
bool salva_memoria(const memoria_t &m)
{
	ofstream f(NOMEFILE);

	if (!f)
		return false;

	f<<m.N<<' '<<m.num_oggetti<<endl;

	for (unsigned int i = 0 ; i < m.num_oggetti ; i++)
		f<<m.oggetti[i].pos<<' '<<m.oggetti[i].dim<<endl;

	return static_cast<bool>(f);
}

/*
 * Carica dimensioni e contenuto della memoria m da file. L'eventuale
 * precedente contenuto della memoria e' perso.
 */
bool carica_memoria(memoria_t &m)
{
	ifstream f(NOMEFILE);

	if (!f)
		return false;

	unsigned int N;
	f>>N;
	reinizializza(m, N);

	f>>m.num_oggetti;
	for (unsigned int i = 0 ; i < m.num_oggetti ; i++)
		f>>m.oggetti[i].pos>>m.oggetti[i].dim;

	return static_cast<bool>(f);
}

int main()
{
	memoria_t memoria;
	inizializza(memoria);

	const char menu[] =
		"1. Reinizializza memoria\n"
		"2. Stampa memoria\n"
		"3. Alloca oggetto\n"
		"4. Salva memoria\n"
		"5. Carica memoria\n"
		"6. Alloca oggetto 2\n"
		"7. Esci\n";

	while (true) {
		cout<<menu<<endl;
		int scelta;
		cin>>scelta;

		cout<<endl ; // per il corretto funzionamento del tester

		switch (scelta) {
		case 1: {
			unsigned int N;

			cout<<"Inserisci dimensioni: ";
			cin>>N;
			reinizializza(memoria, N);
		}
			break;
		case 2:
			stampa_memoria(memoria);
			break;
		case 3: {
			unsigned int pos, dim;

			cout<<"Inserisci posizione e dimensioni: ";
			cin>>pos>>dim;

			if (!alloca_oggetto(memoria, pos, dim, false))
				cout<<"Allocazione fallita"<<endl;
		}
			break;
		case 4:
			if (!salva_memoria(memoria))
				cout<<"Scrittura su file fallita"<<endl;
			break;
		case 5:
			if (!carica_memoria(memoria))
				cout<<"Caricamento da file fallito"<<endl;
			break;
		case 6: {
			unsigned int pos, dim;

			cout<<"Inserisci posizione e dimensioni: ";
			cin>>pos>>dim;

			if (!alloca_oggetto(memoria, pos, dim, true))
				cout<<"Allocazione fallita"<<endl;
		}
			break;
		case 7:
			return 0;
		default:
			cout<<"Scelta errata"<<endl;
		}
	}

	return 1;
}
