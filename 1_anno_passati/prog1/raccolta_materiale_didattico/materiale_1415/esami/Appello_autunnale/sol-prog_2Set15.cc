#include <iostream>
#include <fstream>

using namespace std ;

const int M = 5 ; // lunghezza massima delle stringhe nei contenitori
const int N = 5 ; // numero di contenitori, ossia lunghezza della sequenza

// stati possibili di un contenitore
enum stato_t {LIBERO, ATTESA, OCCUPATO} ;

// testo relativo a ciascuno stato, per semplificare il codice della stampa
const char testo[][15] = {"LIBERO", "ATTESA_LETTURA", "OCCUPATO"} ;

// descrittore di un contenitore
struct contenitore_t {
	stato_t stato ;
	char dati[M+1] ; // stringa di al piu' M caratteri
} ;

// alias utile per definire la sequenza dei contenitori nel main
typedef contenitore_t seq_contenitori_t[N] ;

// nome del file in cui viene salvato lo stato dei contenitori
const char NOMEFILE[] = "stato.dat" ;

// inizializza lo stato di tutti i contenitori a libero
void inizializza(seq_contenitori_t &s)
{
	for (int i = 0 ; i < N ; i++)
		s[i].stato = LIBERO ;
}

/*
 * Prova a richiedere una lettura (simulata) dal dispositivo.  Se non
 * trova alcun contenitore libero fallisce e ritorna -1, altrimenti
 * mette in stato di attesa_lettura il primo contenitore libero, e ne
 * ritorna l'indice.
 */
int richiedi_lettura(seq_contenitori_t &s)
{
	int idx ;
	for (idx = 0 ; idx < N ; idx++)
		if (s[idx].stato == LIBERO)
			break ;

	if (idx >= N)
		return -1 ;

	s[idx].stato = ATTESA ;

	return idx ;
}

/*
 * Simula la lettura dal dispositivo, mettendo la stringa nel
 * contenitore di indice idx. Fallisce se tale contenitore non e' in
 * stato di attesa_lettura. Ritorna vero in caso di successo, falso
 * altrimenti.
 */
bool effettua_lettura(seq_contenitori_t &s, int idx)
{
	if (idx < 0 || idx >= N || s[idx].stato != ATTESA)
		return false ;

	cout<<"Inserire la stringa di al pi' M caratteri: " ;
	
	cin>>s[idx].dati ;

	s[idx].stato = OCCUPATO ;
	
	return true ;
}

/*
 * Fa passare il contenitore di indice idx in stato libero, solo se e'
 * attualmente in stato occupato. Ritorna vero in caso di successo,
 * falso altrimenti.
 */
bool libera_contenitore(seq_contenitori_t &s, int idx)
{
	if (idx < 0 || idx >= N || s[idx].stato != OCCUPATO)
		return false ;

	s[idx].stato = LIBERO ;
	
	return true ;
}

// stampa lo stato dei contenitori su stdout
void stampa_stato(const seq_contenitori_t &s)
{
	for (int i = 0 ; i < N ; i++) {
		cout<<i<<" "<<testo[s[i].stato] ;
		if (s[i].stato == OCCUPATO)
			cout<<" "<<s[i].dati ;
		cout<<endl ;
	}
}

/*
 * Salva lo stato dei contenitori. Ritorna vero in caso di successo, falso
 * altrimenti.
 */
bool salva_stato(const seq_contenitori_t &s)
{
	ofstream f(NOMEFILE) ;
	f.write(reinterpret_cast<const char *>(&s), sizeof(s));
	return f ;
}

/*
 * Carica lo stato dei contenitori. Ritorna vero in caso di successo, falso
 * altrimenti. Il precedente stato e' perso.
 */
bool carica_stato(seq_contenitori_t &s)
{
	ifstream f(NOMEFILE) ;
	f.read(reinterpret_cast<char *>(&s), sizeof(s));
	return f ;
}

/*
 * Sposta tutti i contenitori liberi in testa alla sequenza.
 */
void deframmenta(seq_contenitori_t &s)
{
	int prox_non_libero = 0, prox_libero = 1 ;
	while (true) {
		// cerca il prossimo contenitore non libero
		while (prox_non_libero < N &&
		       s[prox_non_libero].stato == LIBERO)
			prox_non_libero++;

		if (prox_non_libero >= N - 1) // se il prossimo non
					      // libero ha un indice
					      // così alto, allora ci
					      // puo' essere rimasto
					      // al piu' un
					      // contenitore libero in
					      // fondo, quindi non
					      // c'e' niente da
					      // spostare
			break ;
		
		// cerca il prossimo contenitore libero
		while (prox_libero < N &&
		       s[prox_libero].stato != LIBERO)
			prox_libero++ ;

		if (prox_libero == N) // non c'e' piu' alcun contenitore libero
			break ;

		/*
		 * sposta il contenitore non libero nella posizione di
		 * quello libero, e lo fa passare nello stato libero
		 */
		s[prox_libero] = s[prox_non_libero] ;
		s[prox_non_libero].stato = LIBERO ;

		/*
		 * Siccome abbiamo gia' lavorato sulla coppia di
		 * contenitori non-libero e libero puntati dagli
		 * indici prox_non_libero e prox_libero, alla prossima
		 * iterazione non dovremo più considerare tale
		 * coppia. Quindi spostiamo entrambi gli indici in
		 * avanti di una posizione.
		 */
		prox_non_libero++ ;
		prox_libero++ ;
	}
}

int main()
{
	seq_contenitori_t seq ;
	inizializza(seq) ;
	
	const char menu[] =
		"1. Richiedi lettura\n"
		"2. Effettua lettura\n"
		"3. Libera contenitore\n"
		"4. Stampa stato\n"
		"5. Salva stato\n"
		"6. Carica stato\n"
		"7. Deframmenta\n"
		"8. Esci\n" ;
	
	while (true) {
		cout<<menu<<endl ;
		
		int scelta ;
		cin>>scelta ;
		switch(scelta) {
		case 1:{
			int idx = richiedi_lettura(seq) ;
			if (idx == -1)
				cout<<"Richiesta di lettura fallita"<<endl ;
			else
				cout<<"Indice contenitore: "<<idx<<endl ;
			break ;}
		case 2:{
			int idx ;
			cout<<"Indice contenitore: " ;
			cin>>idx ;
			if (! effettua_lettura(seq, idx))
				cout<<"Lettura fallita"<<endl;
			
			break ;}
		case 3: {
			int idx ;
			cout<<"Indice contenitore: " ;
			cin>>idx ;
			if (! libera_contenitore(seq, idx))
				cout<<"Operazione fallita"<<endl ;
			break ;
		}
		case 4:
			stampa_stato(seq) ;
			break ;
		case 5:
			if (! salva_stato(seq))
				cout<<"Operazione fallita"<<endl ;
			break ;
		case 6:
			if (! carica_stato(seq))
				cout<<"Operazione fallita"<<endl ;
			break ;
		case 7:
			deframmenta(seq) ;
			break;
		case 8:
			return 0 ;
		default:
			cout<<"Scelta errata"<<endl ;
		}
	}
	return 1 ;
}
