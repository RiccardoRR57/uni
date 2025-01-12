#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

const int RIPIANI = 5 ;	// numero di ripiani
const int MAXLUN = 5 ; // lunghezza massima codici (piu' uno per via del terminatore)
const char NOMEFILE[] = "stato.txt" ;

// descrittore di uno scaffale
struct scaffale_t {
	char pacchi[RIPIANI][MAXLUN] ; // codici dei pacchi nello scaffale
	int num_pacchi ;	 // numero di pacchi sullo scaffale
} ;
	
// descrittore dell'insieme degli scaffali
struct magazzino_t {
	scaffale_t *scaffali;
	int num_scaffali; 
} ;

// inizializza l'insieme degli scaffali
void inizializza_vuoto(magazzino_t &m)
{
	m.num_scaffali = 0;
}

// reinizializza l'insieme degli scaffali
void reinizializza(magazzino_t &m, int n)
{
	if (m.num_scaffali != n && m.num_scaffali != 0)
	{
			delete [] m.scaffali;
			m.num_scaffali = 0;
	}
	if (n>0 && m.num_scaffali==0)
	{
		m.scaffali = new scaffale_t[n];
		m.num_scaffali = n;
	}
	for (int i = 0 ; i < n ; i++)
		m.scaffali[i].num_pacchi = 0;
}

// aggiunge il pacco p allo scaffale scaf, ritorna falso in caso di errore
bool aggiungi_pacco(magazzino_t &m, int scaf, const char *p)
{
	if (scaf < 0 || scaf >= m.num_scaffali || p == NULL || p[0] == '\0')
		return false ;
	if (m.scaffali[scaf].num_pacchi==RIPIANI)
		return false;

	strcpy(m.scaffali[scaf].pacchi[m.scaffali[scaf].num_pacchi], p) ;
	m.scaffali[scaf].num_pacchi++;
	
	return true ;
}

// scrive lo stato sull'ostream os, ritorna falso in caso di errore
bool scrivi_stato(ostream &os, const magazzino_t &m, bool su_file)
{
	if (su_file)
		os<<m.num_scaffali<<endl ;
	else
		os<<"Magazzino:"<<endl;
	for (int i = 0 ; i < m.num_scaffali ; i++) {
		if (su_file)
			os<<m.scaffali[i].num_pacchi ;
		else
			os<<i;

		for (int j = 0 ; j < m.scaffali[i].num_pacchi ; j++)
			os<<' '<<m.scaffali[i].pacchi[j] ;

		os<<endl ;
	}
	return os ;
}

// carica lo stato, ritorna falso in caso di errore
bool carica_stato(magazzino_t &m)
{
	ifstream in_f(NOMEFILE) ;
	int n ;
	in_f>>n ;
	reinizializza(m, n);

	for (int i = 0 ; i < n ; i++) {
		int nuovo_num_pacchi ;
		in_f>>nuovo_num_pacchi ;
		m.scaffali[i].num_pacchi = nuovo_num_pacchi;	
		for (int j = 0 ; j < m.scaffali[i].num_pacchi ; j++)
			in_f>>m.scaffali[i].pacchi[j] ;
	}
	return in_f ;
}

// copia il carico dello scaffale s1 nello scaffale s2, ritorna falso in
// caso di errore
bool copia_carico(magazzino_t &m, int s1, int s2)
{
	if (s1 == s2 || s1 < 0 || s1 >= m.num_scaffali || s2 < 0 || s2 >=m.num_scaffali)
		return false ;

	m.scaffali[s2] = m.scaffali[s1];

	//o più dettagliatamente
	
	//m.scaffali[s2].num_pacchi = m.scaffali[s1].num_pacchi;

	//for (int i = 0 ; i < m.scaffali[s1].num_pacchi ; i++)
	//	strcpy(m.scaffali[s1].pacchi[i], m.scaffali[s2].pacchi[i]) ;

	return true ;
}

// funzione di appoggio per fondere scaffali: rimuove un pacco dallo scaffale e shifta i consecutivi
bool estrai_pacco(magazzino_t &m, int s1)
{
	if (s1 < 0 || s1 >= m.num_scaffali)
		return false;
	
	for (int i=0; i<m.scaffali[s1].num_pacchi-1; i++)
		strcpy(m.scaffali[s1].pacchi[i], m.scaffali[s1].pacchi[i+1]);
	
	m.scaffali[s1].num_pacchi--;
	
	return true;
}

// fonde due scaffali s1 e s2
bool fondi_scaffali(magazzino_t &m, int s1, int s2)
{
	if (s1 == s2 || s1 < 0 || s1 >= m.num_scaffali || s2 < 0 || s2 >=m.num_scaffali)
		return false ;

	while (m.scaffali[s2].num_pacchi>0 && aggiungi_pacco(m,s1,m.scaffali[s2].pacchi[0]))
		estrai_pacco(m, s2);

	return true ;
}


int main()
{
	magazzino_t magazzino ;

	inizializza_vuoto(magazzino) ;
	
	const char menu[] =
		"Menu:\n"
		"1. Inizializza-reinizializza magazzino\n"
		"2. Aggiungi pacco\n"
		"3. Stampa carico\n"
		"4. Salva stato\n"
		"5. Carica stato\n"
		"6. Copia carico\n"
		"7. Fondi scaffali\n"
		"8. Esci\n" ;
	
	while(true) {
		cout<<menu<<endl ;
		int scelta ;
		cin>>scelta ;

		cout<<endl; // questo accapo è importante per il tester!

		switch(scelta) {
		case 1: {
			int dimensione ;
			cout<<"Dimensione magazzino? " ;
			cin>>dimensione ;
			
			reinizializza(magazzino, dimensione) ;
			break ;
		}
		case 2: {
			int scaf ;
			cout<<"Indice scaffale? " ;
			cin>>scaf ;
			char buf[MAXLUN] ;
			cout<<"Codice pacco? " ;
			cin>>buf ;
			
			aggiungi_pacco(magazzino, scaf, buf) ;
			break ;}
		case 3:
			scrivi_stato(cout, magazzino, false) ;
			break ;
		case 4: {
			ofstream f(NOMEFILE) ;
			if (!scrivi_stato(f, magazzino, true))
				cout<<"Errore nel salvataggio"<<endl ;
			break ;}
		case 5:
			if (!carica_stato(magazzino))
				cout<<"Errore nel caricamento"<<endl ;
			break ;
		case 6: {
			int s1, s2 ;
			cout<<"Indice scaffale partenza? " ;
			cin>>s1 ;
			cout<<"Indice scaffale arrivo? " ;
			cin>>s2 ;
			
			copia_carico(magazzino, s1, s2) ;
			break ;}
		case 7: {
			int s1, s2 ;
			cout<<"Indice scaffale 1? " ;
			cin>>s1 ;
			cout<<"Indice scaffale 2? " ;
			cin>>s2 ;
			
			fondi_scaffali(magazzino, s1, s2) ;
			break ;}
		case 8:
			return 0;
		default:
			cout<<"Scelta sbagliata"<<endl ;
		}
	}


}
