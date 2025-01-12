#include <iostream>
#include <fstream>

using namespace std;

const int N = 3 ;	// numero di furgoni
const int MAXLUN = 10 ; // lunghezza massima codici (piu' uno per via del terminatore)
const char NOMEFILE[] = "stato.txt" ;

// descrittore di un furgone
struct furgone_t {
	char (*pacchi)[MAXLUN] ; // codici dei pacchi caricati sul furgone
	int num_pacchi ;	 // numero di pacchi caricati sul furgone
	int capienza ;		 // dimensione array dinamico dei codici 
} ;
	
// descrittore dell'insieme dei furgoni
struct furgoni_t {
	furgone_t furgoni[N] ;
} ;

// inizializza l'insieme dei furgoni
void inizializza(furgoni_t &f)
{

	for (int i = 0 ; i < N ; i++)
		f.furgoni[i].num_pacchi = f.furgoni[i].capienza = 0 ;
}

// aggiunge il pacco p al furgone fur, ritorna falso in caso di errore
bool aggiungi_pacco(furgoni_t &f, int fur, const char *p)
{
	if (fur < 0 || fur >= N || p == NULL || p[0] == '\0')
		return false ;

	if (f.furgoni[fur].num_pacchi == f.furgoni[fur].capienza) {
		if (f.furgoni[fur].pacchi != 0)
			delete [] f.furgoni[fur].pacchi ;

		f.furgoni[fur].capienza = f.furgoni[fur].capienza == 0 ?
			1 : f.furgoni[fur].capienza * 2 ;
		
		f.furgoni[fur].pacchi = new char[f.furgoni[fur].capienza][MAXLUN] ;
	}

	strcpy(f.furgoni[fur].pacchi[f.furgoni[fur].num_pacchi], p) ;
	f.furgoni[fur].num_pacchi++ ;
	
	return true ;
}

// scrive lo stato sull'ostream os, ritorna falso in caso di errore
bool scrivi_stato(ostream &os, const furgoni_t &f, bool su_file)
{
	if (su_file)
		os<<N<<endl ;
	for (int i = 0 ; i < N ; i++) {
		if (su_file)
			os<<f.furgoni[i].num_pacchi ;
		else
			os<<i ;

		for (int j = 0 ; j < f.furgoni[i].num_pacchi ; j++)
			os<<' '<<f.furgoni[i].pacchi[j] ;

		os<<endl ;
	}
	return os ;
}

// carica lo stato, ritorna falso in caso di errore
bool carica_stato(furgoni_t &f)
{
	ifstream in_f(NOMEFILE) ;
	int n ;
	in_f>>n ;
	if (n != N)
		return false ;

	for (int i = 0 ; i < N ; i++) {
		int nuovo_num_pacchi ;
		in_f>>nuovo_num_pacchi ;
		if (f.furgoni[i].num_pacchi != 0 && f.furgoni[i].num_pacchi != nuovo_num_pacchi) {
			delete [] f.furgoni[i].pacchi ;
			f.furgoni[i].pacchi = 0 ;
		}

		if (f.furgoni[i].pacchi == 0)
			f.furgoni[i].pacchi = new char[nuovo_num_pacchi][MAXLUN] ; 

		f.furgoni[i].capienza = f.furgoni[i].num_pacchi = nuovo_num_pacchi ;
		
		for (int j = 0 ; j < f.furgoni[i].num_pacchi ; j++)
			in_f>>f.furgoni[i].pacchi[j] ;
	}
	return in_f ;
}

// copia il carico del furgone f1 nel furgone f2, ritorna falso in
// caso di errore
bool copia_carico(furgoni_t &f, int f1, int f2)
{
	if (f1 == f2 || f1 < 0 || f1 >= N || f2 < 0 || f2 >=N)
		return false ;

	if (f.furgoni[f2].capienza != f.furgoni[f1].capienza) {
		if (f.furgoni[f2].capienza != 0) {
			delete [] f.furgoni[f2].pacchi ;
			f.furgoni[f2].capienza = 0 ;
		}

		if (f.furgoni[f2].capienza == 0 && f.furgoni[f1].capienza != 0)
			f.furgoni[f2].pacchi =
				new char[f.furgoni[f1].capienza][MAXLUN] ;
		
		f.furgoni[f2].capienza =
			f.furgoni[f1].capienza ;
	}

	f.furgoni[f2].num_pacchi = f.furgoni[f1].num_pacchi ;

	for (int i = 0 ; i < f.furgoni[f1].num_pacchi ; i++)
		strcpy(f.furgoni[f1].pacchi[i], f.furgoni[f2].pacchi[i]) ;

	return true ;
}

// sposta il carico del furgone f1 nel furgone f2, ritorna falso in
// caso di errore
bool sposta_carico(furgoni_t &f, int f1, int f2)
{
	if (f1 == f2 || f1 < 0 || f1 >= N || f2 < 0 || f2 >=N)
		return false ;

	/*
	 * Versione piu' semplice ma non ottimizzata, perche' non
	 * evita le delete nel caso in cui le capienze siano identiche
	 * tra i due furgoni.
	 */
	if (f.furgoni[f2].capienza != 0)
		delete [] f.furgoni[f2].pacchi ;
		
	f.furgoni[f2] = f.furgoni[f1] ;
	f.furgoni[f1].capienza = f.furgoni[f1].num_pacchi = 0 ;

	return true ;
}

int main()
{
	furgoni_t furgoni ;

	inizializza(furgoni) ;
	
	const char menu[] =
		"1. Aggiungi pacco\n"
		"2. Stampa carico\n"
		"3. Salva stato\n"
		"4. Carica stato\n"
		"5. Copia carico\n"
		"6. Sposta carico\n"
		"7. Esci\n" ;
	
	while(true) {
		cout<<menu<<endl ;
		int scelta ;
		cin>>scelta ;
		switch(scelta) {
		case 1: {
			int fur ;
			cout<<"Indice furgone? " ;
			cin>>fur ;
			char buf[MAXLUN] ;
			cout<<"Codice pacco? " ;
			cin>>buf ;
			
			aggiungi_pacco(furgoni, fur, buf) ;
			break ;}
		case 2:
			scrivi_stato(cout, furgoni, false) ;
			break ;
		case 3: {
			ofstream f(NOMEFILE) ;
			if (!scrivi_stato(f, furgoni, true))
				cout<<"Errore nel salvataggio"<<endl ;
			break ;}
		case 4:
			if (!carica_stato(furgoni))
				cout<<"Errore nel caricamento"<<endl ;
			break ;
		case 7:
			return 0;
		default:
			cout<<"Scelta sbagliata"<<endl ;
		}
	}


}
