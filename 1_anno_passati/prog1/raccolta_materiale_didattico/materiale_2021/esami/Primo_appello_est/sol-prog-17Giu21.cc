#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>

using namespace std;

const unsigned int M = 20; // lunghezza massima nomi
const char NOMEFILE[] = "biglietti.txt";

// Descrittore di un biglietto
struct biglietto_t {
	char nome[M+1];		// nome del proprietario
	unsigned int numero;	// numero del biglietto
};

// Descrittore dell'insieme dei biglietti
struct ins_biglietti_t {
	biglietto_t *biglietti; // array dinamico dei biglietti
	unsigned int num;	// numero attuale di biglietti
	unsigned int max;	// numero massimo di biglietti
};

/*
 * Inizializza l'insieme dei biglietti b a vuoto, assumendo che non
 * sia mai stato inizializzato prima.
 */
void inizializza(ins_biglietti_t &b)
{
	b.num = b.max = 0;
}

/*
 * Rialloca l'array dinamico di biglietti contenuto nell'insieme b. In
 * particolare, ne raddoppia le dimensioni.
 */
void rialloca(ins_biglietti_t &b)
{
	unsigned int nuovo_max = b.max > 0 ? b.max * 2 : 1;

	biglietto_t *nuovo_biglietti = new biglietto_t[nuovo_max];

	for (unsigned int i = 0 ; i < b.num ; i++)
		nuovo_biglietti[i] = b.biglietti[i];

	if (b.max != 0)
		delete [] b.biglietti;

	b.biglietti = nuovo_biglietti;
	b.max = nuovo_max;
}

/*
 * Aggiunge all'insieme b un biglietto per il proprietario di nome
 * 'nome', con numero uguale a 'numero'. Ritorna vero in caso di
 * successo, falso altrimenti.
 */
bool vendi_biglietto(ins_biglietti_t &b, const char nome[],
		     unsigned int numero)
{
	if (nome[0] == '\0' || numero == 0)
		return false;

	for (unsigned int i = 0 ; i < b.num; i++)
		if (b.biglietti[i].numero == numero)
			return false;

	if (b.num == b.max)
		rialloca(b);

	strcpy(b.biglietti[b.num].nome, nome);


	b.biglietti[b.num].numero = numero;
	b.num++;

	return true;
}

/*
 * Scrive l'insieme di biglietti b sull'ostream os. Se su_file è vero,
 * allora utilizza un formato adatto ad un file di stato. Ritorna
 * vero in caso di successo, falso altrimenti.
 */
bool scrivi_ins_biglietti(const ins_biglietti_t &b, ostream &os, bool su_file)
{
	if (su_file)
		os<<b.max<<' '<<b.num<<endl;

	for (unsigned int i = 0 ; i < b.num ; i++)
		os<<b.biglietti[i].nome<<'\t'
		  <<b.biglietti[i].numero
		  <<endl;

	return static_cast<bool>(os);
}

/*
 * Carica il contenuto dell'insieme dei biglietti b da
 * file. L'eventuale precedente contenuto è perso. Ritorna vero in
 * caso di successo, falso altrimenti.
 */
bool carica_ins_biglietti(ins_biglietti_t &b)
{
	ifstream f(NOMEFILE);

	if (!f)
		return false;

	unsigned int max;
	f>>max;

	if (max != b.max) {
		if (b.max != 0)
			delete [] b.biglietti;

		if (max > 0)
			b.biglietti = new biglietto_t[max];
		b.max = max;
	}

	f>>b.num;

	for (unsigned int i = 0 ; i < b.num ; i++)
		f>>b.biglietti[i].nome>>b.biglietti[i].numero;

	return static_cast<bool>(f);
}

/*
 * Funzione di servizio che stampa un biglietto a caso tra quelli
 * nel vettore biglietti (vettore di num elementi).
 */
unsigned int __estrai_biglietto(biglietto_t biglietti[], unsigned int num)
{
	unsigned int idx = rand() % num;

	cout<<biglietti[idx].nome<<'\t'
	    <<biglietti[idx].numero
	    <<endl;

	return idx;
}

/*
 * Funzione di servizio che elimina il biglietto di indice idx dal
 * vettore temp. Il vettore ha num elementi, e tale numero viene
 * decrementato da questa funzione (e' un parametro di ingresso e
 * uscita).
 */
void elimina_biglietto(biglietto_t temp[], unsigned int idx, unsigned int &num)
{
	for (unsigned int i = idx + 1 ; i < num ; i++)
		temp[i-1] = temp[i];
	num--;
}

/*
 * Stampa n a caso nell'insieme b.
 */
void estrai_primi_n_biglietti(const ins_biglietti_t &b, unsigned int n)
{
	if (b.num == 0) {
		cout<<"NESSUNO 0"<<endl;
		return;
	}

	biglietto_t *temp = new biglietto_t[b.num];
	unsigned int num = b.num;

	for (unsigned int i = 0 ; i < b.num ; i++)
		temp[i] = b.biglietti[i];

	if (n > b.num)
		n = b.num;

	for (unsigned int i = 0 ; i < n ; i++) {
		unsigned int idx = __estrai_biglietto(temp, num);

		if (num > 1)
			elimina_biglietto(temp, idx, num);
	}

	delete [] temp;
}

int main()
{
	srand(1);

	ins_biglietti_t b;
	inizializza(b);

	const char menu[] =
		"1. Vendi biglietto\n"
		"2. Stampa biglietti venduti\n"
		"3. Salva biglietti venduti\n"
		"4. Carica biglietti venduti\n"
		"5. Stampa vincitore\n"
		"6. Stampa primi n vincitori\n"
		"7. Esci\n";

	while (true) {
		cout<<menu<<endl;
		int scelta;
		cin>>scelta;

		cout<<endl ; // per il corretto funzionamento del tester

		switch (scelta) {
		case 1: {
			char nome[M+1];
			unsigned int numero;

			cout<<"Inserisci nome: ";
			cin>>nome;
			cout<<"Inserisci numero: ";
			cin>>numero;
			if (!vendi_biglietto(b, nome, numero))
				cout<<"Vendita fallita"<<endl;;
		}
			break;
		case 2:
			scrivi_ins_biglietti(b, cout, false);
			break;
		case 3: {
			ofstream f(NOMEFILE);

			if (!scrivi_ins_biglietti(b, f, true))
				cout<<"Salvataggio fallito"<<endl;
		}
			break;
		case 4:
			carica_ins_biglietti(b);
			break;
		case 5:
			estrai_primi_n_biglietti(b, 1);
			break;
		case 6: {
			unsigned int n;
			cout<<"Numero biglietti da estrarre: ";
			cin>>n;
			cout<<endl;
			estrai_primi_n_biglietti(b, n);
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
