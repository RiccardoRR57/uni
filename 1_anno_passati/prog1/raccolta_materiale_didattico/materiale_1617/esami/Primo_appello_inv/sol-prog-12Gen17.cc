#include <iostream>
#include <fstream>

using namespace std ;

const int N = 3 ;
const char NOMEFILE[] = "stato.txt" ;

// descrittore di una coda
struct coda_t {
	int num_accodati ; // numero attuale di utenti in coda
	int ultimo_accodato, prossimo_da_servire ; // numeri di
						   // servizio de,
						   // rispettivamente,
						   // l'ultimo utente
						   // accodato ed il
						   // prossimo utente
						   // da servire
} ;

// descrittore dell'insieme di code
struct code_t {
	coda_t *code ;		// array dinamico di code
	int M ;			// numero di code
	bool numeri_limitati ;	// vero se il sistema e' in modalita'
				// numeri limitati
} ;

// inizializza il sistema con zero code
void inizializza(code_t &c)
{
	c.M = 0 ;
	c.numeri_limitati = false ;
}

// funzione di servizio per allocare M code in c se necessario
void alloca_code(code_t &c, int M)
{
	if (c.M != M) {
		if (c.M)
			delete [] c.code ;
		c.code = new coda_t[M] ;
		c.M = M ;
	}
}

// inizializza le code in c a vuote
void inizializza_code(code_t &c)
{
	for (int i = 0 ; i < c.M ; i++) {
		c.code[i].prossimo_da_servire = 1 ;
		c.code[i].ultimo_accodato = 0 ;
		c.code[i].num_accodati = 0 ;
	}
}

// (ri)configura il sistema per contenere M code; ritorna vero in caso
// di successo, falso altrimenti
bool configura_code(code_t &c, int M)
{
	if (M < 1)
		return false ;

	alloca_code(c, M) ;
	inizializza_code(c) ;

	return true ;
}

// accoda un nuovo utente in fondo alla coda i-esima; ritorna il
// numero di servizio del nuovo utente in caso di successo, -1
// altrimenti
int accoda_utente(code_t &c, int i)
{
	if (i < 0 || i > c.M)
		return -1 ;

	coda_t &coda = c.code[i] ;

	if (coda.num_accodati == N)
		return -1 ;

	coda.ultimo_accodato++ ;

	if (c.numeri_limitati && coda.ultimo_accodato == N + 1)
		coda.ultimo_accodato = 1 ;

	coda.num_accodati++ ;

	return coda.ultimo_accodato ;
}

// in caso di successo, ritorna il numero di servizio del prossimo
// utente da servire nella coda i-esima, ed estrae tale utente dalla
// coda; in caso di fallimento, ritorna -1
int servi_prossimo(code_t &c, int i)
{
	if (i < 0 || i > c.M)
		return -1 ;

	coda_t &coda = c.code[i] ;
	if (coda.num_accodati == 0)
		return -1 ;

	int prossimo = coda.prossimo_da_servire ;
	if (!c.numeri_limitati || prossimo < N)
		coda.prossimo_da_servire++ ;
	else
		coda.prossimo_da_servire = 1 ;

	coda.num_accodati-- ;

	return prossimo ;
}

// scrive lo stato del sistema sull'ostream os
bool scrivi_stato(const code_t &c, ostream &os, bool su_file)
{
	if (su_file)
		os<<c.M<<endl ;

	for (int i = 0 ; i < c.M ; i++)
		os<<i<<" "
		  <<c.code[i].num_accodati<<" "
		  <<c.code[i].ultimo_accodato<<" "
		  <<c.code[i].prossimo_da_servire
		  <<endl ;

	return os ;
}

// carica lo stato da file
bool carica_stato(code_t &c)
{
	ifstream f(NOMEFILE) ;
	if (!f)
		return false ;

	int M ;
	f>>M ;

	alloca_code(c, M) ;

	for (int i = 0 ; i < M ; i++) {
		int buf ;
		f>>buf ;
		f>>c.code[i].num_accodati ;
		f>>c.code[i].prossimo_da_servire ;
		f>>c.code[i].ultimo_accodato ;
	}

	return f ;
}

// reinizializza le code ed attiva la modalita' numeri limitati
void attiva_modo_numeri_limitati(code_t &c)
{
	inizializza_code(c) ;
	c.numeri_limitati = true ;
}

int main()
{
	const char menu[] =
		"1. Inizializza code\n"
		"2. Accoda utente\n"
		"3. Servi prossimo utente\n"
		"4. Stampa stato code\n"
		"5. Salva stato code\n"
		"6. Carica stato code\n"
		"7. Attiva modalita' numeri limitati\n"
		"8. Esci\n" ;

	code_t code ;
	inizializza(code) ;

	while (true) {
		cout<<menu<<endl ;

		int scelta ;
		cout<<"Scelta: " ;
		cin>>scelta ;

		switch (scelta) {
		case 1: {
			int M ;
			cout<<"Nuovo numero code: " ;
			cin>>M ;
			configura_code(code, M) ;
			break ;}
		case 2: {
			cout<<"Indice coda: " ;
			int i ;
			cin>>i ;
			int numero = accoda_utente(code, i) ;
			if (numero == -1)
				cout<<"Accodamento fallito"<<endl ;
			else
				cout<<"Accodato con numero di servizio "
				    <<numero<<endl ;
			break ;}
		case 3: {
			cout<<"Indice coda: " ;
			int i ;
			cin>>i ;
			int numero = servi_prossimo(code, i) ;
			if (numero == -1)
				cout<<"Servizio fallito"<<endl ;
			else
				cout<<"Servito utente con numero di servizio "
				    <<numero<<endl ;
			break ;}
		case 4:
			scrivi_stato(code, cout, false) ;
			break ;
		case 5:{
			ofstream f(NOMEFILE);
			if (!scrivi_stato(code, f, true))
				cout<<"Salvataggio stato fallito"<<endl ;
			break ;}
		case 6:
			if (!carica_stato(code))
				cout<<"Caricamento stato fallito"<<endl ;
			break ;
		case 7:
			attiva_modo_numeri_limitati(code) ;
			break ;
		case 8:
			return 0 ;
		default:
			cout<<"Scelta sbagliata"<<endl ;
		}
	}

	return 1 ;
}
