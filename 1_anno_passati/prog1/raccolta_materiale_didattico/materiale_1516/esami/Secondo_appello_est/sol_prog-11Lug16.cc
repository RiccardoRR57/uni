#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

const int NUM_BLOCCHI = 10 ;
const int MAX_LUN_NOME = 10 ;
const int DIM_BLOCCO = 128 ;
const char NOME_FILE[] = "stato.txt" ;

// descrittore di un blocco
struct blocco_t {
	char nome[MAX_LUN_NOME] ;
	char *sequenza ; // sequenza di byte del blocco
	int num_utenti ; // numero di utenti che stanno utilizzando il blocco
} ;

// descrittore dell'insieme di blocchi
struct insieme_blocchi_t {
	blocco_t blocchi[NUM_BLOCCHI] ; // contenitore dei blocchi
	int num_occupati ;
} ;

// inizializza l'insieme dei blocchi
void inizializza(insieme_blocchi_t &ins_blocchi)
{
	for (int i = 0 ; i < NUM_BLOCCHI ; i++)
		ins_blocchi.blocchi[i].sequenza = 0 ;
	ins_blocchi.num_occupati = 0 ;
}

/*
 * Prende un blocco. Ritorna l'indirizzo della sequenza di byte in
 * caso di successo, 0 in caso di fallimento.
 */
char *ottieni_blocco(insieme_blocchi_t &ins_blocchi, const char *nome)
{
	int i ;
	for (i = 0 ; i < ins_blocchi.num_occupati ; i++)
		if (!strcmp(ins_blocchi.blocchi[i].nome, nome))
			break ;

	if (i == NUM_BLOCCHI)
		return 0 ;

	if (i == ins_blocchi.num_occupati) {
		strcpy(ins_blocchi.blocchi[i].nome, nome) ;
		ins_blocchi.blocchi[i].sequenza = new char[DIM_BLOCCO] ;
		ins_blocchi.blocchi[i].num_utenti = 1 ;
		ins_blocchi.num_occupati++ ;

		return ins_blocchi.blocchi[i].sequenza ;
	}

	ins_blocchi.blocchi[i].num_utenti++ ;
    
	return ins_blocchi.blocchi[i].sequenza ;
}

/*
 * Scrive lo stato sull'output stream os; utilizza un formato adatto
 * alla memorizzazione e successiva lettura da file se su_file è vero,
 * altrimenti utilizza un formato adatto alla lettura da parte di un
 * utente.
 */
bool scrivi_stato(const insieme_blocchi_t &ins_blocchi, ostream &os,
		  bool su_file)
{
	if (su_file)
		os<<ins_blocchi.num_occupati<<endl ;

	for (int i = 0 ; i < ins_blocchi.num_occupati ; i++) {
		os<<ins_blocchi.blocchi[i].nome<<' '
		  <<ins_blocchi.blocchi[i].num_utenti ;

		if (!su_file)
			cout<<' '
			    <<reinterpret_cast<void *>
				(ins_blocchi.blocchi[i].sequenza) ;

		cout<<endl ;
	}

	return os ;
}

/*
 * Rilascia il blocco di nome 'nome'. Ritorna vero in caso di
 * successo, falso in caso di fallimento.
 */
bool rilascia_blocco(insieme_blocchi_t &ins_blocchi, const char *nome)
{
	int i ;
	for (i = 0 ; i < ins_blocchi.num_occupati ; i++)
		if (!strcmp(ins_blocchi.blocchi[i].nome, nome))
			break ;

	if (i == ins_blocchi.num_occupati)
		return false ;

	ins_blocchi.blocchi[i].num_utenti-- ;

	if (ins_blocchi.blocchi[i].num_utenti > 0)
		return true ;

	delete [] ins_blocchi.blocchi[i].sequenza ;

	if (i + 1 < ins_blocchi.num_occupati)
		ins_blocchi.blocchi[i] =
			ins_blocchi.blocchi[ins_blocchi.num_occupati - 1] ;
	else
		ins_blocchi.blocchi[i].sequenza = 0;

	ins_blocchi.num_occupati--;

	return true ;
}

/*
 * Ricarica lo stato da file, lo stato precedente è perso.  Ritorna
 * vero in caso di successo, falso in caso di fallimento.
 */
bool carica_stato(insieme_blocchi_t &ins_blocchi)
{
	ifstream f(NOME_FILE) ;

	int nuovo_num_occupati ;
	f>>nuovo_num_occupati ;

	if (!f)
		return false ;

	for (int i = nuovo_num_occupati ; i < ins_blocchi.num_occupati ; i++)
		delete [] ins_blocchi.blocchi[i].sequenza ;

	for (int i = 0 ; i < nuovo_num_occupati ; i++) {
		if (i >= ins_blocchi.num_occupati)
			ins_blocchi.blocchi[i].sequenza = new char[DIM_BLOCCO] ;
		f>>ins_blocchi.blocchi[i].nome
		 >>ins_blocchi.blocchi[i].num_utenti ;
	}

	ins_blocchi.num_occupati = nuovo_num_occupati ;

	return f ;
}

int main()
{
	const char menu[] =
		"1. Ottieni blocco\n"
		"2. Stampa stato\n"
		"3. Rilascia blocco\n"
		"4. Salva stato\n"
		"5. Carica stato\n"
		"6. Rilascia blocco 2\n"
		"7. Esci\n" ;

	insieme_blocchi_t ins_blocchi ;
	inizializza(ins_blocchi) ;

	while (true) {
		cout<<menu<<endl ;

		int scelta ;
		cin>>scelta ;

		switch (scelta) {
		case 1: {
			char nome[MAX_LUN_NOME] ;
			cout<<"Nome del blocco?"<<endl ;
			cin>>nome ;
			char *ind_sequenza = ottieni_blocco(ins_blocchi, nome) ;
			if ( ind_sequenza == 0)
				cout<<"Operazione fallita"<<endl ;
			else
				cout<<"Indirizzo sequenza: "
				    <<reinterpret_cast<void *>(ind_sequenza)
				    <<endl ;
			break ;}
		case 2:
			scrivi_stato(ins_blocchi, cout, false) ;
			break ;
		case 3:
		case 6: {
			char nome[MAX_LUN_NOME] ;
			cout<<"Nome del blocco?"<<endl ;
			cin>>nome ;
			;
			if (!rilascia_blocco(ins_blocchi, nome))
				cout<<"Operazione fallita"<<endl ;
			break ;}
		case 4: {
			ofstream f(NOME_FILE) ;
			if (!scrivi_stato(ins_blocchi, f, true))
				cout<<"Salvataggio fallito"<<endl ;
			break ;}
		case 5:
			if (!carica_stato(ins_blocchi))
				cout<<"Caricamento fallito"<<endl ;
			break ;
		case 7:
			return 0;
		default:
			cout<<"Scelta errata"<<endl ;
		}
	}

	return 1;
}
