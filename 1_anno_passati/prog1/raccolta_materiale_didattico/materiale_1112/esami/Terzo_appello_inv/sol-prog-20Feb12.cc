#include <iostream>
#include <fstream>

using namespace std ;

// nome del file di testo in cui si memorizza il vettore
const char NOME_FILE[] = "vettore.txt" ;

// struttura dati che descrive il vettore dinamico
struct vettore_t {
	int *contenitore ; // puntatore all'array dinamico che
			   // contiene il vettore
	int num_elem ;     // numero di elementi attualmente nel vettore
	int capacita ;     // capacita'à del vettore, ovvero dimensione
			   // dell'array dinamico
} ;

// inizializza il vettore v a capacita' e numero di elementi 0
void inizializza(vettore_t &v)
{
	v.num_elem = v.capacita = 0 ;
}

// aggiunge l'elemento di valore val in fondo al vettore v
bool aggiungi_elemento(vettore_t &v, int val)
{
	if (v.capacita == 0) {
		v.contenitore = new int[2] ;
		v.capacita = 2 ;
	}
	else if (v.num_elem == v.capacita)
		return false ;

	v.contenitore[v.num_elem] = val ;
	v.num_elem++ ;
	return true ;
}

// stampa capacita' ed elementi del vettore v
void stampa(const vettore_t &v)
{
	cout<<v.capacita<<" [ " ;
	for (int i = 0 ; i < v.num_elem ; i++) {
		cout<<v.contenitore[i] ;
		if (i < v.num_elem - 1)
			cout<<", " ;
	}
	cout<<" ]"<<endl ;
}

// salva il vettore v in un file di testo
bool salva(const vettore_t &v)
{
	ofstream f(NOME_FILE) ;
	f<<v.capacita<<endl ;
	f<<v.num_elem<<endl ;
	for (int i = 0 ; i < v.num_elem ; i++)
		f<<v.contenitore[i]<<endl ;
	return f ;
}

// carica il vettore v dal file di testo, il precedente contenuto e la
// precedente capacita' sono persi
bool carica(vettore_t &v)
{
	ifstream f(NOME_FILE) ;
	f>>v.capacita>>v.num_elem ;
	delete v.contenitore ;
	v.contenitore = new int [v.capacita] ;
	for (int i = 0 ; i < v.num_elem ; i++)
		f>>v.contenitore[i] ;
	return f ;
}

// funzione di supporto per riallocare l'array dinamico che contiene il vettore v
void rialloca_contenitore(vettore_t &v, int nuova_capacita)
{
	if (nuova_capacita < 0)
		return ;
	v.capacita = nuova_capacita ;
	int *tmp_vett = new int[v.capacita] ;
	for (int i = 0 ; i < v.num_elem ; i++)
		tmp_vett[i] = v.contenitore[i] ;
	delete v.contenitore ;
	v.contenitore = tmp_vett ;
}

// aggiunge un elemento in fondo al vettore v, raddoppiandone la
// capacita' se non c'e' abbastanza spazio
void aggiungi_elemento_rialloca(vettore_t &v, int val)
{
	if (v.num_elem == v.capacita) {
		if (v.capacita == 0)
			v.capacita = 1 ;
		rialloca_contenitore(v, v.capacita * 2) ;
	}
	v.contenitore[v.num_elem] = val ;
	v.num_elem++ ;
}

/*
 * elimina l'elemento in fondo al vettore v, dimmezzandone la
 * capacita' se il numero rimanente di elementi e' inferiore o uguale
 * ad un quarto della capacita' stessa
 */
bool elimina_elemento(vettore_t &v)
{
	if (v.num_elem == 0)
		return false ;
	v.num_elem-- ;
	if (v.num_elem <= v.capacita / 4)
		rialloca_contenitore(v, v.capacita / 2) ;
	return true ;
}

/*
 * funzione di support per la funzione partiziona: cerca il prossimo
 * elemento positivo nell'array contenitore a partire dalla posizione
 * cur_pos, e lo scambia con l'elemento nella posizione cur_pos
 */
bool scambia_con_pross_positivo(int *contenitore, int cur_pos, int num_elem)
{
	// cerca prossimo elemento positivo
	int pos_pross_positivo = cur_pos + 1 ;
	for ( ; pos_pross_positivo < num_elem &&
		      contenitore[pos_pross_positivo] <= 0 ;
	      pos_pross_positivo++) 
		;

	// nessun elemento positivo trovato
	if (pos_pross_positivo == num_elem)
		return false ;
	
	// scambia elementi
	int appoggio = contenitore[cur_pos] ;
	contenitore[cur_pos] = contenitore[pos_pross_positivo] ;
	contenitore[pos_pross_positivo] = appoggio ;

	return true ;
}

// moifica il vettore in modo tale che tutti gli elementi positivi stiano nella
// prima parte delle vettore, seguiti da tutti gli elementi negativi o nulli
void partiziona(vettore_t &v)
{

	for (int i = 0 ; i  < v.num_elem ; i++) {
		if (v.contenitore[i] > 0)
			continue ;
		if (! scambia_con_pross_positivo(v.contenitore, i,
						 v.num_elem))
			return ;
	}
}

int main()
{
	vettore_t vett ;
	inizializza(vett) ;

	const char menu[] =
		"1. Aggiungi elemento\n"
		"2. Stampa vettore\n"
		"3. Salva vettore\n"
		"4. Carica vettore\n"
		"5. Aggiungi elemento con riallocazione\n"
		"6. Elimina elemento\n"
		"7. Partiziona vettore\n"
		"8. Esci\n" ;

	while(true) {
		cout<<menu<<endl ;
		int scelta ;
		cin>>scelta ;
		switch(scelta) {
		case 1: {
			int val ;
			cout<<"Valore ? " ;
			cin>>val ;
			if (! aggiungi_elemento(vett, val))
				cout<<"Aggiunta nuovo elemento fallita"<<endl ;
			break ;
		}
		case 2:
			stampa(vett) ;
			break ;
		case 3:
			if (! salva(vett))
				cout<<"Salvataggio fallito"<<endl ;
			break ;
		case 4:
			if (! carica(vett))
				cout<<"Caricamento fallito"<<endl ;
			break ;
		case 5: {
			int val ;
			cout<<"Valore ? " ;
			cin>>val ;
			aggiungi_elemento_rialloca(vett, val) ;
			break ;
		}
		case 6:
			if (! elimina_elemento(vett))
				cout<<"Eliminazione fallita"<<endl ;
			break ;
		case 7:
			partiziona(vett) ;
			break ;
		case 8:
			return 0 ;
		default:
			cout<<"Scelta errata"<<endl ;
		}
	}
	return 1 ;
}
