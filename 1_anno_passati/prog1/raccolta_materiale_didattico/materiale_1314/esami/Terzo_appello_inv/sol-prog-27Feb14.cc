#include <iostream>
#include <fstream>

using namespace std ;

const char NOME_FILE[] = "vettore.bin" ;

// descrittore di un consumo per tratta
struct cons_tratta_t {
	double lunghezza ; // in chilometri
	double consumo ; // in litri
} ;

// descrittore del vettore di consumi
struct vettore_consumi_t {
	cons_tratta_t *cons_tratta ; // puntatore all'array dinamico
	int max_num_tratte ;         // dimensioni array dinamico
	int num_tratte ;             // dimensione del vettore dinamico
} ;

// inizializza il vettore v a vuoto
void inizializza(vettore_consumi_t &v) {
	v.cons_tratta = 0 ;
	v.num_tratte = 0 ; // per evitare controlli aggiuntivi, per il
			   // caso di array non ancora allocato, nell
			   // funzioni di stampa e di calcolo del
			   // consumo medio
}

/*
 * Alloca spazio in memoria per un vettore v di al più N elementi, e
 * con numero di tratte correnti uguale a num_tratte (utilizzato per
 * realizzare la carica_vettore). Se necessario dealloca il precedente
 * vettore.
 */
bool crea_vettore(vettore_consumi_t &v, int N, int num_tratte)
{
	if (N <= 0 || num_tratte > N)
		return false ;
	
	if (v.cons_tratta != 0 && v.max_num_tratte != N) {
		delete v.cons_tratta ;
		v.cons_tratta = 0 ;
	}

	if (v.cons_tratta == 0)
		v.cons_tratta = new cons_tratta_t[N] ;

	v.max_num_tratte = N ;
	v.num_tratte = num_tratte ;
	return true ;
}

/*
 * Inserisce il consumo per tratta cons, in fondo al vettore v;
 * ritorna falso in caso di fallimento, vero altrimenti.
 */
bool inserisci_consumo(vettore_consumi_t &v, const cons_tratta_t &cons)
{
	if ( v.cons_tratta == 0 || v.num_tratte == v.max_num_tratte)
		return false ;

	v.cons_tratta[v.num_tratte] = cons ;
	v.num_tratte++ ;

	return true ;
}

// stampa il contenuto del vettore v
void stampa_vettore(const vettore_consumi_t &v)
{
	for (int i = 0 ; i < v.num_tratte ; i++) {
		cout<<"Tratta "<<i<<": "
		    <<v.cons_tratta[i].lunghezza<<"\t"
		    <<v.cons_tratta[i].consumo
		    <<endl ;
	}
}

/*
 * Salva il contenuto del vettore v in un file binario; ritorna
 * falso in caso di fallimento, vero altrimenti.
 */
bool salva_vettore(const vettore_consumi_t &v)
{
	if (v.cons_tratta == 0)
		return false ;

	ofstream f(NOME_FILE) ;
	
	f.write(reinterpret_cast<const char *>(&v.max_num_tratte),
		sizeof(v.max_num_tratte)) ;
	f.write(reinterpret_cast<const char *>(&v.num_tratte),
		sizeof(v.num_tratte)) ;
	f.write(reinterpret_cast<const char *>(v.cons_tratta),
		sizeof(cons_tratta_t) * v.max_num_tratte) ;

	return f ;
}

/*
 * Carica il contenuto del vettore v dal file binario; ritorna falso
 * in caso di fallimento, vero altrimenti. Il precedente contenuto del
 * vettore è perso.
 */
bool carica_vettore(vettore_consumi_t &v)
{
	ifstream f(NOME_FILE) ;
	
	int nuovo_max, nuovo_num_tratte ;
	f.read(reinterpret_cast<char *>(&nuovo_max), sizeof(nuovo_max)) ;
	f.read(reinterpret_cast<char *>(&nuovo_num_tratte),
	       sizeof(nuovo_num_tratte)) ;

	crea_vettore(v, nuovo_max, nuovo_num_tratte) ;

	f.read(reinterpret_cast<char *>(v.cons_tratta),
		sizeof(cons_tratta_t) * v.max_num_tratte) ;

	return f ;
}

// Calcola il consumo medio per il vettore v.
double calcola_cons_medio(const vettore_consumi_t &v)
{
	if (v.num_tratte == 0)
		return 0 ;

	double consumo_tot = 0, lunghezza_tot = 0  ;

	for (int i = 0 ; i < v.num_tratte ; i++) {
		consumo_tot += v.cons_tratta[i].consumo ;
		lunghezza_tot += v.cons_tratta[i].lunghezza ;
	}

	return 100 * (consumo_tot / lunghezza_tot) ;
}

/*
 * Ritorna vero se la modifica spiegata nella traccia comporta un
 * risparmio in termini di consumo medio, dato il contenuto corrente
 * del vettore v.
 */
bool valuta_risparmio(const vettore_consumi_t &v)
{
	if (v.num_tratte == 0)
		return false ;

	double consumo_tot = 0, lunghezza_tot = 0  ;
	for (int i = 0 ; i < v.num_tratte ; i++) {
		if (v.cons_tratta[i].consumo/v.cons_tratta[i].lunghezza > .07)
			consumo_tot += v.cons_tratta[i].consumo * .7 ;
		else
			consumo_tot += v.cons_tratta[i].consumo * 1.2 ;

		lunghezza_tot += v.cons_tratta[i].lunghezza ;
	}

	return 100 * (consumo_tot / lunghezza_tot) < calcola_cons_medio(v) ;
}

int main()
{
	vettore_consumi_t vett ;

	inizializza(vett) ;

	const char menu[] =
		"1. Crea vettore\n"
		"2. Inserisci consumo\n"
		"3. Stampa vettore\n"
		"4. Salva vettore consumi\n"
		"5. Carica vettore consumi\n"
		"6. Calcola consumo medio\n"
		"7. Valuta risparmio\n"
		"8. Esci\n" ;

	while (true) {
		cout<<menu<<endl ;
		int scelta ;
		cin>>scelta ;
		switch(scelta) {
		case 1: {
			int N ;
			cout<<"Inserisci dimensione massima vettore: " ;
			cin>>N ;
			if (!crea_vettore(vett, N, 0))
				cout<<"Creazione vettore fallita"<<endl ;
			break ;}
		case 2:{
			cons_tratta_t cons ;
			cout<<"Inserisci lunghezza e consumo: " ;
			cin>>cons.lunghezza ;
			cin>>cons.consumo ;
			if (!inserisci_consumo(vett, cons))
				cout<<"Inserimento fallito"<<endl ;
			break ;}
		case 3:
			stampa_vettore(vett) ;
			break ;
		case 4:
			if (!salva_vettore(vett))
				cout<<"Salvataggio fallito"<<endl ;
			break ;
		case 5:
			carica_vettore(vett) ;
			break ;
		case 6:
			cout<<"Consumo medio: "<<calcola_cons_medio(vett)<<endl ;
			break ;
		case 7:
			if (valuta_risparmio(vett))
				cout<<"Ci sarebbe risparmio"<<endl ;
			break ;
		case 8:
			return 0 ;
		default:
			cout<<"Scelta errata"<<endl ;
		}
	}
	return 1 ;
}
