#include <iostream>
#include <fstream>

using namespace std ;

const int LUN_NOME = 20 ;
const int M = 10 ;
const char NOME_FILE[] = "reperibilita.txt" ;

struct giorno_t {
	char operatori[M][LUN_NOME] ;
	int num_operatori ;
} ;

struct sequenza_giorni_t {
	giorno_t *giorni ;
	int num_giorni ;
} ;

void inizializza(sequenza_giorni_t &s)
{
	s.num_giorni = 0 ;
}

/*
 * Modifica la sequenza s affinche' contenga N giorni. Se il parametro
 * inizializza e' vero, inizializza anche le reperibilita' per ciascun
 * giorno. Ritorna falso in caso di errore.
 */
bool modifica(sequenza_giorni_t &s, int N, bool inizializza)
{
	if (N < 0)
		return false ;
	// se necessario, dealloca la vecchia sequenza ed alloca la nuova
	if (N != s.num_giorni) {
		if (s.num_giorni != 0)
			delete s.giorni ;
		if (N > 0)
			s.giorni = new giorno_t[N] ;
	}

	// inizializza reperibilita'
	if (inizializza)
		for (int i = 0 ; i < N ; i++)
			s.giorni[i].num_operatori = 0 ;

	s.num_giorni = N ;

	return true ;
}

/*
 * Aggiunge l'operatore dal nome passato in ingresso, nel giorno di
 * indice idx_giorno, nella sequenza s. Ritorna falso in caso di
 * fallimento.
 */
bool aggiungi_reperibilita(sequenza_giorni_t &s, int idx_giorno,
			   const char *nome)
{
	if (idx_giorno < 0 || idx_giorno >= s.num_giorni ||
	    s.giorni[idx_giorno].num_operatori >= M)
		return false ;
	
	giorno_t &giorno = s.giorni[idx_giorno] ;

	// controlla se l'operatore e' gia' presente
	for (int i = 0 ; i < giorno.num_operatori ; i++)
		if (!strcmp(giorno.operatori[i], nome))
			return false ;

	// aggiungi operatore
	strcpy(giorno.operatori[giorno.num_operatori], nome) ;
	giorno.num_operatori++ ;

	return true ;
}

/*
 * Scrive sull'ostream os il contenuto della sequenza s. Ritorna falso
 * in caso di fallimento.
 */
bool scrivi(const sequenza_giorni_t &s, ostream &os, bool su_file)
{
	if (su_file)
		os<<s.num_giorni<<endl ;

	for (int i = 0 ; i < s.num_giorni ; i++) {
		const giorno_t &giorno = s.giorni[i] ;

		if (su_file)
			os<<giorno.num_operatori ;
		else
			os<<i+1<<'\t' ;

		for (int j = 0 ; j < giorno.num_operatori ; j++)
			os<<" "<<giorno.operatori[j] ;
		os<<endl ;
	}

	return os ;
}

/*
 * Carica da file il contenuto della sequenza s. L'eventuale
 * precedente contenuto della sequenza e' perso. Ritorna falso in caso
 * di fallimento.
 */
bool carica(sequenza_giorni_t &s)
{
	ifstream f(NOME_FILE) ;

	int N ;
	f>>N ;
	modifica(s, N, false) ;
	
	for (int i = 0 ; i < N ; i++) {
		giorno_t &giorno = s.giorni[i] ;

		f>>giorno.num_operatori ;

		for (int j = 0 ; j < giorno.num_operatori ; j++)
			f>>giorno.operatori[j] ;
	}

	return f ;
}

/*
 * Equalizza le reperibilita' nella sequenza s.
 */
void equalizza(sequenza_giorni_t &s)
{
	if (s.num_giorni < 2)
		return ;

	while(true) {
		/*
		 * Trova il giorno col numero massimo di operatori
		 * reperibili, ed il giorno col numero minimo di
		 * operatori reperibili.
		 */
		int idx_max = 0, idx_min = 0 ;
		for (int i = 1 ; i < s.num_giorni ; i++) {
			if (s.giorni[i].num_operatori >
			    s.giorni[idx_max].num_operatori)
				idx_max = i ;
			else if  (s.giorni[i].num_operatori <
			    s.giorni[idx_min].num_operatori)
				idx_min = i ;
		}

		// Se la differenza massima tra il numero di operatori
		// reperibili, per qualsiasi coppia di giorni, e' al
		// piu' uguale ad 1, non c'e' niente altro da fare.

		if (s.giorni[idx_max].num_operatori <=
		    s.giorni[idx_min].num_operatori + 1)
			return ;
		cout<<"idx_min "<<idx_min
		    <<", idx_max "<<idx_max
		    <<endl ;

		/*
		 * Sposta un operatore dal giorno col numero massimo
		 * di operatori al giorno col numero minimo di
		 * operatori.
		 */
		giorno_t &giorno_max = s.giorni[idx_max] ;
		int &num_operatori_max = giorno_max.num_operatori ;
		num_operatori_max-- ;
		
		aggiungi_reperibilita(s, idx_min,
				      giorno_max.operatori[num_operatori_max]);
	}
}

int main()
{
	sequenza_giorni_t sequenza ;

	inizializza(sequenza) ;

	const char menu[] =
		"1. Modifica sequenza giorni\n"
		"2. Aggiungi reperiblita'\n"
		"3. Stampa reperibilita'\n"
		"4. Salva reperibilita'\n"
		"5. Carica reperibilita'\n"
		"6. Equalizza reperibilita'\n"
		"7. Esci\n" ;

	while(true) {
		cout<<menu<<endl ;

		int scelta ;
		cin>>scelta ;

		switch(scelta) {
		case 1: {
			cout<<"Nuovo numero di giorni? " ;
			int N ;
			cin>>N ;
			if (!modifica(sequenza, N, true))
				cout<<"Modifica fallita"<<endl ;
			break ;}
		case 2: {
			int idx_giorno ;
			char nome[LUN_NOME] ;
			cout<<"Indice giorno [1-"<<sequenza.num_giorni<<"]? " ;
			cin>>idx_giorno ;
			cout<<"Nome operatore? " ;
			cin>>nome ;
			if (!aggiungi_reperibilita(sequenza, idx_giorno - 1,
						   nome))
				cout<<"Aggiunta reperibilita fallita"<<endl ;
			break ;}
		case 3:
			cout<<endl ;
			scrivi(sequenza, cout, false) ;
			break ;
		case 4: {
			ofstream f(NOME_FILE) ;
			if (!scrivi(sequenza, f, true))
				cout<<"Salvataggio non riuscito"<<endl ;
			break ;
		}
		case 5:
			if (!carica(sequenza))
				cout<<"Caricamento non riuscito"<<endl ;
			break ;
		case 6:
			equalizza(sequenza) ;
			break ;
		case 7:
			return 0 ;
		default:
			cout<<"Scelta sbagliata"<<endl ;
		}
	}
	return 1 ;
}
