#include <iostream>
#include <fstream>

using namespace std ;

// Lunghezza massima coda entita' in attesa
const int MAXLUN_CODA = 10 ;

// Descrittore di una entita' accodata
struct entita_accodata {
	int id ;	// id dell'entita'
	int tempo ;	// istante in cui si e' accodata
} ;

// descrittore di una risorsa
struct risorsa_t {
	bool libera ;	// stato della risorsa (libera, occupata)
	int entita ;	// id dell'entita' occupante, valido se la
			// risorsa e' effettivamente occupata
	entita_accodata coda[MAXLUN_CODA] ; // coda delle entita' accodate
	int num_in_coda ;	// numero di entita' attualmente in coda
	int tempo ;		// tempo corrente (misurato in numero
				// di volte in cui la risorsa e' stata
				// liberata)
} ;

const char NOMEFILE[] = "stato.dat" ;

// attesa massima oltre la quale non e' più possibile l'accodamento
// prioritario di una entita'
const int MAX_ATTESA = 2 ;

// inizializza la risorsa r a libera e con nessuna entita' accodata
void inizializza(risorsa_t &r)
{
	r.libera = true ;
	r.num_in_coda = 0 ;
	r.tempo = 0 ;
}

// tipo di richiesta di accesso alla risorsa: prioritaria o non prioritaria
enum tipo_t {PRIO, NON_PRIO} ;

/*
 * Se la risorsa r è libera, assegna la risorsa alla entita' id,
 * altrimenti accoda l'entita'. L'accodamento e' prioritario o non
 * prioritario, in base al valore del parametro di ingresso tipo (nel
 * caso di accodamento non prioritario, l'entita' e' sempre inserita
 * in fondo alla coda se la risorsa non e' libera).
 */
bool prendi_risorsa(risorsa_t &r, int id, tipo_t tipo)
{
	if (r.libera) {
		r.libera = false ;
		r.entita = id ;
		return true ;
	}

	if (r.num_in_coda == MAXLUN_CODA)
		return false ;

	int pos_inserimento = r.num_in_coda ;
	
	if (tipo == PRIO && r.num_in_coda > 0) {
		int in_attesa ;
		for (in_attesa = 0 ; in_attesa < r.num_in_coda;
		     in_attesa++)
			if (r.coda[in_attesa].tempo >=
			    r.tempo - MAX_ATTESA)
				break ;
		
		if (in_attesa == r.num_in_coda) { // nessuna entita'
						  // aspetta da troppo
						  // tempo
			// preparazione dell'inserimento in testa
			pos_inserimento = 0 ;
			for (int i = r.num_in_coda ; i > 0 ; i--)
				r.coda[i] = r.coda[i-1] ;
		}
	}

	r.coda[pos_inserimento].id = id ;
	r.coda[pos_inserimento].tempo = r.tempo ;
	r.num_in_coda++ ;
	
	return true ;
}

// stampa lo stato della risorsa r, e le entita' accodate
void stampa_stato(const risorsa_t &r)
{
	if (r.libera) {
		cout<<"Libera"<<endl ;
		return ;
	}

	cout<<"Occupata da "<<r.entita<<endl ;
	if (r.num_in_coda == 0)
		cout<<"Nessun entita' in coda"<<endl ;
	else {
		cout<<"In coda: "<<r.coda[0].id ;
		for (int i = 1 ; i < r.num_in_coda ; i++)
			cout<<" "<<r.coda[i].id ;
		cout<<endl ;
	}
}


// salva lo stato della risorsa r, e le entita' accodate
bool salva_stato(const risorsa_t &r)
{
	ofstream f(NOMEFILE) ;

	f.write(reinterpret_cast<const char *>(&r), sizeof(r)) ;
	
	return f ;
}

// carica lo stato della risorsa r, e le entita' accodate
bool carica_stato(risorsa_t &r)
{
	ifstream f(NOMEFILE) ;

	f.read(reinterpret_cast<char *>(&r), sizeof(r)) ;
	
	return f ;
}

// libera la risorsa r
bool libera_risorsa(risorsa_t &r)
{
	if (r.libera)
		return false ;

	if (r.num_in_coda == 0) {
		r.libera = true ;
		return true ;
	}

	r.entita = r.coda[0].id ;
	
	for (int i = 0 ; i < r.num_in_coda - 1 ; i++)
		r.coda[i] = r.coda[i+1] ;

	r.num_in_coda-- ;

	r.tempo++ ;
	
	return true ;
	
}
	
int main()
{
	risorsa_t risorsa ;
	inizializza(risorsa) ;
	
	const char menu[] =
		"1. Prendi risorsa\n"
		"2. Stampa stato\n"
		"3. Salva stato\n"
		"4. Carica stato\n"
		"5. Libera risorsa\n"
		"6. Prendi risorsa 2\n"
		"7. Esci\n" ;
	
	while (true) {
		cout<<menu<<endl ;
		int scelta ;
		cin>>scelta ;

		switch(scelta) {
		case 1:{
			int id ;
			cin>>id ;
			if (!prendi_risorsa(risorsa, id, NON_PRIO))
				cout<<"Operazione fallita"<<endl ;
			break ;}
		case 2:
			stampa_stato(risorsa) ;
			break ;
		case 3:
			salva_stato(risorsa) ;
			break ;
		case 4:
			carica_stato(risorsa) ;
			break ;
		case 5:
			if (!libera_risorsa(risorsa))
				cout<<"Risorsa gia' libera"<<endl ;
			break ;
		case 6:{
			int id ;
			cin>>id ;
			if (!prendi_risorsa(risorsa, id, PRIO))
				cout<<"Operazione fallita"<<endl ;
			break ;}
		case 7:
			return 0 ;
		default:
			cout<<"Scelta errata"<<endl ;
		}
	}
	return 1 ;
}
