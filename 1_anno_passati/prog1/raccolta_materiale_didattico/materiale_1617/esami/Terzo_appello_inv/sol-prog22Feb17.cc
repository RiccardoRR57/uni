#include <iostream>
#include <fstream>

using namespace std ;

const char NOMEFILE[] = "sequenza.txt" ;

// tipi possibilit di quadrilatero
enum tipo_quad { QUADRATO, RETTANGOLO, TRAPEZIO } ;

// descrittore di un quadrilatero
struct quadrilatero_t {
	tipo_quad tipo ;
	int lati[4] ; // misure dei lati
} ;

// descrittore sequenza di quadrilateri
struct sequenza_quad_t {
	quadrilatero_t *quadrilateri; // array dinamico di quadrilateri
	int num ; // numero corrente di elementi nella sequenza
	int max_num ; // massimo numero possibile di elementi
} ;

// inizializza la sequenza s a vuota
void inizializza(sequenza_quad_t &s)
{
	s.num = 0 ;
	s.max_num = 0 ;
}

/*
 * Imposta ad N la lunghezza massima per la sequenza s, eliminando
 * l'eventuale precedente contenuto della sequenza. Ritorna vero in
 * caso di successo, falso altrimenti.
 */
bool modifica_lun_max(sequenza_quad_t &s, int N)
{
	if (N <= 0)
		return false ;

	if (s.max_num != N) {
		if (s.max_num != 0)
			delete [] s.quadrilateri ;
		s.quadrilateri = new quadrilatero_t[N] ;
	}
	s.num = 0 ;
	s.max_num = N ;

	return true ;
}

/*
 * Inserisce un quadrilatero nella sequenza s, leggendo i dati del
 * quadrilatoero dall'input stream is. Se da_file e' vero, allora
 * assume di stare leggendo da file. Ritorna vero in caso di successo,
 * falso altrimenti.
 */
bool inserisci_quadrilatero(sequenza_quad_t &s, istream &is,
			    bool da_file)
{
	if (s.num == s.max_num)
		return false ;

	char tipo ;
	do {
		if (!da_file)
			cout<<"Inserisci tipo quadrilatero [Q|R|T]: " ;
		is>>tipo ;
	} while (tipo != 'Q' && tipo != 'R' && tipo != 'T') ;

	if (tipo == 'Q')
		s.quadrilateri[s.num].tipo = QUADRATO ;
	else if (tipo == 'R')
		s.quadrilateri[s.num].tipo = RETTANGOLO ;
	else
		s.quadrilateri[s.num].tipo = TRAPEZIO ;

	for (int i = 0 ; i < 4 ; i++) {
		do {
			if (!da_file)
				cout<<"Inserisci lunghezza lato "<<i<<": " ;
			is>>s.quadrilateri[s.num].lati[i] ;
		} while (s.quadrilateri[s.num].lati[i] <= 0) ;
	}

	s.num++ ;

	return true ;
}

/*
 * Scrive il contenuto della sequenza s sull'ooutput stream os. Se
 * su_file e' vero, allora assume di stare scrivendo su file. Ritorna
 * vero in caso di successo, falso altrimenti.
 */
bool scrivi_sequenza(const sequenza_quad_t &s, ostream &os, bool su_file)
{
	char tipo[3][20] = {"QUADRATO", "RETTANGOLO", "TRAPEZIO"} ;

	if (!os)
		return false ;

	if (su_file) {
		for (int i = 0 ; i < 3 ; i++)
			tipo[i][1] = '\0' ;
		os<<s.num<<" "<<s.max_num<<endl ;
	}

	for (int i = 0 ; i < s.num ; i++) {
		os<<tipo[s.quadrilateri[i].tipo] ;
		for (int j = 0 ; j < 4 ; j++)
			os<<" "<<s.quadrilateri[i].lati[j] ;
		os<<endl ;
	}

	return os ;
}

/*
 * Ritorna vero se le misure dei lati del quadrilatero di indice idx,
 * nella sequenza s, sono compatibili col tipo del quadrilatero.
 */
bool controlla_quadrilatero(sequenza_quad_t &s, int idx)
{
	if (idx < 0 || idx >= s.num)
		return false ;

	switch(s.quadrilateri[idx].tipo) {
	case QUADRATO:
		if (s.quadrilateri[idx].lati[0] !=
		    s.quadrilateri[idx].lati[1] ||
		    s.quadrilateri[idx].lati[1] !=
		    s.quadrilateri[idx].lati[2] ||
		    s.quadrilateri[idx].lati[2] !=
		    s.quadrilateri[idx].lati[3])
			return false ;
		break ;
	case RETTANGOLO: {
		int i ;
		for (i = 1 ; i < 4 ; i++)
			if (s.quadrilateri[idx].lati[i] ==
			    s.quadrilateri[idx].lati[0])
				break ;
		if (i == 4)
			return false ;

		if ((i == 1 &&
		     s.quadrilateri[idx].lati[2] !=
		     s.quadrilateri[idx].lati[3]) ||
		    (i == 2 &&
		     s.quadrilateri[idx].lati[1] !=
		     s.quadrilateri[idx].lati[3]) ||
		    (i == 3 &&
		     s.quadrilateri[idx].lati[1] !=
		     s.quadrilateri[idx].lati[2]))
			return false ;

		break ;}
	case TRAPEZIO:
		break ;
	}

	return true ;
}

/*
 * Carica il contenuto della sequenza s da file. Ritorna vero in caso
 * di successo, falso altrimenti.
 */
bool carica_sequenza(sequenza_quad_t &s)
{
	ifstream f(NOMEFILE) ;

	if (!f)
		return false ;

	int num, max_num ;
	f>>num>>max_num ;

	modifica_lun_max(s, max_num) ;

	for (int i = 0 ; i < num ; i++)
		inserisci_quadrilatero(s, f, true) ;

	return f ;
}

int main()
{
	sequenza_quad_t s ;
	inizializza(s) ;

	const char menu[] =
		"1. Modifica lunghezza massima\n"
		"2. Inserisci quadrilatero\n"
		"3. Stampa sequenza\n"
		"4. Salva stato\n"
		"5. Carica stato\n"
		"6. Controlla quadrilatero\n"
		"7. Esci\n";

	while (true) {
		cout<<menu<<endl ;

		int scelta ;
		cin>>scelta ;

		switch (scelta) {
		case 1: {
			int N ;
			cout<<"Nuova lunghezza massima? " ;
			cin>>N ;
			modifica_lun_max(s, N) ;
			break ;}
		case 2:
			if (!inserisci_quadrilatero(s, cin, false))
				cout<<"Inserimento fallito"<<endl ;
			break ;
		case 3:
			scrivi_sequenza(s, cout, false) ;
			break ;
		case 4: {
			ofstream f(NOMEFILE);

			if (!scrivi_sequenza(s, f, true))
				cout<<"Salvataggio fallito"<<endl ;
			break ;}
		case 5:
			carica_sequenza(s) ;
			break ;
		case 6: {
			cout<<"Indice quadrilatero da controllare? " ;
			int idx ;
			cin>>idx ;

			if (controlla_quadrilatero(s, idx))
				cout<<"Tipo consistente"<<endl ;
			else
				cout<<"Tipo inconsistente"<<endl ;
			break ;}
		case 7:
			return 0 ;
		default:
			cout<<"Scelta sbagliata"<<endl ;

		}
	}

	return 1 ;
}
