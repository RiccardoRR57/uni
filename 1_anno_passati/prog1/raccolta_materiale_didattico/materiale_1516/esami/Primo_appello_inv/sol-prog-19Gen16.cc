#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std ;

// descrittore di una partita
struct partita_t {
	unsigned int *caselle ; // sequenza di caselle
	int num_caselle ;	// numero di caselle della sequenza
	int posizione ;		// posizione corrente della pedina
	int punteggio ;		// punteggio corrente
} ;

const char NOME_FILE[] = "stato.txt" ;

// Inizializza allo stato sequenza vuota e quindi nessuna partita in corso.
void inizializza(partita_t &p)
{
	p.num_caselle = 0 ;
}

/*
 * Funzione di servizio per generare una sequenza dinamica di caselle
 * per la partita p.
 */
void genera_sequenza(partita_t &p, int num_caselle)
{
	if (num_caselle != p.num_caselle) {
		if (p.num_caselle > 0)
			delete p.caselle ;

		if (num_caselle > 0)
			p.caselle = new unsigned int[num_caselle] ;
		
		p.num_caselle = num_caselle ;
	}
}

/*
 * Fa iniziare una nuova partita p, generando una nuova sequenza ed
 * azzerando posizione e punteggio.
 */
void inizia_partita(partita_t &p)
{
	int num_caselle = 5 + rand() % (46) ;
	genera_sequenza(p, num_caselle) ;
	
	p.caselle[0] = 0 ;
	for (int i = 1 ; i < p.num_caselle ; i++)
		p.caselle[i] = 1 + rand() % 5 ;
	p.posizione = 0 ;
	p.punteggio = 0 ;
}

// Stampa lo stato della partita p.
void stampa_stato(const partita_t &p)
{
	if (p.num_caselle == 0) {
		cout<<"Nessuna partita in corso"<<endl ;
		return ;
	}
	
	cout<<0 ;
	for (int i = 1 ; i < p.num_caselle ; i++)
		cout<<' '<<p.caselle[i] ;
	cout<<endl ;

	for (int i = 0 ; i < p.posizione ; i++)
		cout<<"  " ;
	cout<<'^'<<endl ;

	cout<<"Punteggio: "<<p.punteggio<<endl<<endl ;
}

// Fa saltare la pedina in avanti di almeno n posizioni nella partita p.
void sposta_pedina(partita_t &p, unsigned int n)
{
	n = n > p.caselle[p.posizione] ? n :  p.caselle[p.posizione] ;
	p.posizione = p.posizione + n ;
	if (p.posizione < p.num_caselle) {
		p.punteggio += p.caselle[p.posizione] ;
		stampa_stato(p) ;
	}

	if (p.posizione < p.num_caselle - 1)
		return ;
	
	cout<<"Partita terminata!"<<endl ;
	p.posizione = 0 ;
	p.punteggio = 0 ;
}

// Salva lo stato della partita p, ritorando falso in caso di errore.
bool salva_stato(const partita_t &p)
{
	ofstream f(NOME_FILE) ;

	f<<p.num_caselle ;

	if (p.num_caselle == 0)
		return f ;
	
	f<<endl<<0 ;
	for (int i = 1 ; i < p.num_caselle ; i++)
		f<<' '<<p.caselle[i] ;
	f<<endl<<p.posizione<<endl ;
	f<<p.punteggio<<endl ;

	return f ;
}

// Carica lo stato della partita p, ritorando falso in caso di errore.
bool carica_stato(partita_t &p)
{
	ifstream f(NOME_FILE) ;

	int num_caselle ;
	f>>num_caselle ;
	genera_sequenza(p, num_caselle) ;
	if (num_caselle == 0)
		return f;
	for (int i = 0 ; i < p.num_caselle ; i ++)
		f>>p.caselle[i] ;
	f>>p.posizione ;
	f>>p.punteggio ;
	
	return f ;
}

/*
 * Ritorna il punteggio massimo per la partita p, nel caso in cui per
 * ogni casella visitata, tranne la prima, il numero di caselle da
 * saltare fosse esattamente uguale al valore della casella visitata
 */
unsigned int punteggio_massimo(partita_t &p)
{
	unsigned int punteggio_max = 0 ;
	for (int i = 1 ; i < p.num_caselle ; i++) {
		unsigned int pos = i , punteggio = 0;
		do {
			punteggio += p.caselle[pos] ;
			pos = pos + p.caselle[pos] ;
		} while (pos < p.num_caselle) ;

		if (punteggio > punteggio_max)
			punteggio_max = punteggio ;
	}

	return punteggio_max ;
}

int main()
{
	partita_t p ;
	srand(time(0)) ;
	inizializza(p) ;
	
	const char menu[] =
		"1. Genera sequenza\n"
		"2. Stampa stato\n"
		"3. Salva stato\n"
		"4. Carica stato\n"
		"5. Sposta pedina\n"
		"6. Punteggio massimo\n"
		"7. Esci\n" ;
	
	while (true) {
		cout<<menu<<endl ;
		
		int scelta ;
		cin>>scelta ;
		switch (scelta) {
		case 1:
			inizia_partita(p) ;
			break ;
		case 2:
			stampa_stato(p) ;
			break ;
		case 3:
			if (!salva_stato(p))
				cout<<"Salvataggio fallito"<<endl ;
			break ;
		case 4:
			if (!carica_stato(p))
				cout<<"Caricamento fallito"<<endl ;
			break ;
		case 5: {
			cout<<"Di quante caselle vuoi spostare la pedina? "
			    <<endl ;
			unsigned int n ;
			cin>>n ;
			sposta_pedina(p, n) ;
			break ;
		}
		case 6:
			cout<<"Punteggio massimo: "<<punteggio_massimo(p)
			    <<endl ;
			break ;
		case 7:
			return 0 ;
		default:
			cout<<"Scelta errata"<<endl ;
		}
	}
	return 1 ;
}
