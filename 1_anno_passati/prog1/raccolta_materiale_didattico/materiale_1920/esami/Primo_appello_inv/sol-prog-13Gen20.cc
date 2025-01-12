#include <iostream>
#include <fstream>

using namespace std;

// descrittore dello stato del sistema
struct stato_t {
	int *accesi; // array dinamico degli indici dei compiti
		     // accesi, in ordine di priorita' decrescente
	int *accesi_fifo; // secondo array dinamico degli indici dei
			  // compiti accesi, questa volta in ordine di
			  // accensione; di conseguenza il compito in
			  // testa all'array e' quello che aspetta da
			  // piu' tempo di essere eseguito
	int in_esecuzione; // indice del compito in esecuzione
	int num_compiti; // numero totale di compiti
	int num_accesi; // numero di compiti accesi
	int num_cambi; // numero di volte in cui il compito in
		       // esecuzione e' cambiato, a partire da quando
		       // il programma e' stato avviato
};

const char NOMEFILE[] = "stato.txt";

/*
 * inizializza lo stato s a vuoto, assumendo che lo stato non sia già
 * stato inizializzato precedentemente
 */
void inizializza_vuoto(stato_t &s)
{
	s.num_compiti = s.num_accesi = 0;
	s.num_cambi = 1;
	s.in_esecuzione = -1;
}

/*
 * (re)inizializza lo stato s ad un insieme di N compiti, assumendo
 * che lo stato sia gia' stato inizializzato precedentemente
 */
void inizializza(stato_t &s, unsigned int N)
{
	if (N != s.num_compiti && s.num_compiti != 0) {
		delete [] s.accesi;
		delete [] s.accesi_fifo;
		s.num_compiti = 0;
	}

	if (N > 0 && s.num_compiti == 0) {
		s.accesi = new int[N];
		s.accesi_fifo = new int[N];
		s.num_compiti = N;
	}

	s.num_accesi = 0;
	s.num_cambi = 1;
	s.in_esecuzione = -1;
}

/*
 * Accende il compito di indice i nello stato s. Ritorna falso in caso
 * di fallimento, vero altrimenti.
 */
bool accendi_compito(stato_t &s, unsigned int i)
{
	if (i >= s.num_compiti)
		return false;
	int j;
	for (j = 0 ; j < s.num_accesi ; j++)
		if (s.accesi[j] >= i)
			break;

	if (j < s.num_accesi && s.accesi[j] == i)
		return true;

	for (int k = s.num_accesi - 1 ; k >= j ; k--)
		s.accesi[k+1] = s.accesi[k];

	s.accesi[j] = i;
	s.accesi_fifo[s.num_accesi] = i;
	s.num_accesi++;

	return true;
}

/*
 * Scrive lo stato s sull'ostream os, usando un formato opportuno per
 * un file nel caso in cui su_file sia vero. Ritorna falso in caso di
 * fallimento, vero altrimenti.
 */
bool scrivi_stato(ostream &os, const stato_t &s, bool su_file)
{
	if (su_file)
		os<<s.num_compiti<<' '<<s.num_accesi<<endl;
	if (!su_file)
		os<<"Esecuzione: ";
	os<<s.in_esecuzione<<endl;

	if (!su_file)
		os<<"Accesi:";
	for (int i = 0 ; i < s.num_accesi; i++)
		os<<' '<<s.accesi[i];
	os<<endl;

	if (!su_file)
		os<<"Accesi FIFO:";
	for (int i = 0 ; i < s.num_accesi; i++)
		os<<' '<<s.accesi_fifo[i];
	os<<endl;

	return os;
}

int trova_idx_in_esecuzione(const stato_t &s, const int vett[])
{
	int i;
	for (i = 0 ; i < s.num_accesi &&
		     vett[i] != s.in_esecuzione ; i++)
		;
	return i;
}

void elimina_compito(stato_t &s, int vett[], int i)
{
	for (int k = i ; k < s.num_accesi - 1 ; k++)
		vett[k] = vett[k+1];
}

/*
 * Spegne il compito eventualmente in esecuzione e manda in esecuzione
 * il prossimo compito acceso a massima priorita'. Se fifo è vero,
 * allora, ogni quattro invocazioni manda in esecuzione invece il
 * compito acceso che aspetta da piu' tempo, indipendentemente dalla
 * sua priorita'.
 */
bool esegui_prossimo_compito(stato_t &s, bool fifo)
{
	if (s.num_accesi == 0)
		return false;

	if (!fifo || s.num_cambi % 4 != 0) {
		s.in_esecuzione = s.accesi[0];
		elimina_compito(s, s.accesi, 0);

		int i = trova_idx_in_esecuzione(s, s.accesi_fifo);
		elimina_compito(s, s.accesi_fifo, i);
	} else if (fifo) {
		s.in_esecuzione = s.accesi_fifo[0];
		elimina_compito(s, s.accesi_fifo, 0);

		int i = trova_idx_in_esecuzione(s, s.accesi);
		elimina_compito(s, s.accesi, i);
	}

	s.num_accesi--;
	s.num_cambi++;

	return true;
}

/*
 * Carica lo stato s da file. Ritorna falso in caso di fallimento,
 * vero altrimenti.
 */
bool carica_stato(stato_t &s)
{
	ifstream f(NOMEFILE);

	if (!f)
		return false;

	int N;
	f>>N;
	inizializza(s, N);

	f>>s.num_accesi;
	f>>s.in_esecuzione;
	for (int i = 0 ; i < s.num_accesi ; i++)
		f>>s.accesi[i];
	for (int i = 0 ; i < s.num_accesi ; i++)
		f>>s.accesi_fifo[i];

	return f;
}

int main()
{
	stato_t stato;
	inizializza_vuoto(stato);

	const char menu[] =
		"1. Inizializza insieme dei compiti\n"
		"2. Accendi compito\n"
		"3. Stampa stato\n"
		"4. Esegui prossimo compito\n"
		"5. Salva stato\n"
		"6. Carica stato\n"
		"7. Esegui prossimo compito 2\n"
		"8. Esci\n";

	while (true) {
		cout<<menu<<endl;

		int scelta;
		cout<<"Scelta: ";
		cin>>scelta;

		cout<<endl; // questo accapo è importante per il tester!

		switch (scelta) {
		case 1: {
			int N;
			cout<<"Quanti compiti? ";
			cin>>N;
			inizializza(stato, N); }
			break;
		case 2: {
			int i;
			cout<<"Indice compito? ";
			cin>>i;
			if (!accendi_compito(stato, i))
				cout<<"Accensione compito fallita"<<endl; }
			break;
		case 3:
			scrivi_stato(cout, stato, false);
			break;
		case 4:
			if (!esegui_prossimo_compito(stato, false))
				cout<<"Esecuzione prossimo compito fallita"
				    <<endl;
			break;
		case 5: {
			ofstream f(NOMEFILE);
			scrivi_stato(f, stato, true); }
			break;
		case 6:
			carica_stato(stato);
			break;
		case 7:
			if (!esegui_prossimo_compito(stato, true))
				cout<<"Esecuzione prossimo compito fallita"
				    <<endl;
			break;
		case 8:
			return 0;
		default:
			cout<<"Scelta non valida"<<endl;
		}
	}

	return 1;
}
