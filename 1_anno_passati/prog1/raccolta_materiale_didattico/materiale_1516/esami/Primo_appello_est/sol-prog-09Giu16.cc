#include <iostream>
#include <fstream>

using namespace std ;

const char NOME_FILE[] = "magazzino.txt" ;

/* Descrittore magazzino */
struct magazzino_t {
	int *lunghezze ;
	int N ;
} ;

/* Inizializza il magazzino m a vuoto */
void inizializza(magazzino_t &m)
{
	m.N = 0 ;
}

/*
 * Funzione di servizio che rialloca il magazzino m affinché possa
 * contenere cavi di lunghezza a l più N
 */
void rialloca(magazzino_t &m, int N)
{
	if (m.N != N) {
		if (m.N != 0)
			delete [] m.lunghezze ;
		m.N = 0;
	}
	if (m.N == 0)
		m.lunghezze = new int[N] ;
	m.N = N ;

	for (int i = 0 ; i < N ; i++)
		m.lunghezze[i] = 0 ;

}

/*
 * Crea/Ricrea il magazzino m per contenere cavi di lunghezza al più
 * N. Ritorna vero in caso di successo, falso altrimenti.
 */
bool crea(magazzino_t &m, int N) {
    if (N < 0)
	return false ;

    rialloca(m, N);

    return true ;
}

/*
 * Aggiunge un cavo di lunghezza n al magazzino m. Ritorna vero in
 * caso di successo, falso altrimenti.
 */
bool aggiungi_cavo(magazzino_t &m, int n)
{
	if (n < 0 || n > m.N)
		return false ;

	m.lunghezze[n]++ ;

	return true ;
}

/*
 * Scrive il contenuto del magazzino m sull'stream os. Se su_file è
 * vero, allora utilizza un formato appropriato per il salvataggio su
 * file. Ritorna vero in caso di successo, falso altrimenti.
 */
bool scrivi_magazzino(const magazzino_t &m, ostream &os, bool su_file)
{
	if (su_file)
		os<<m.N<<endl ;
	for (int i = 0 ; i < m.N ; i++)
		if (m.lunghezze[i] > 0)
			os<<i+1<<" "<<m.lunghezze[i]<<endl ;
	return os ;
}

/*
 * Estrae un cavo di lunghezza n dal magazzino m. Ritorna vero in caso
 * di successo, falso altrimenti.
 */
bool estrai_cavo(magazzino_t &m, int n)
{
	if (n < 0 || n > m.N)
		return false ;
	
	if (m.lunghezze[n] > 0)
		m.lunghezze[n]-- ;
	else
		return false ;
	
	return true ;
}

/*
 * Carica il contenuto del magazzino m da file.Ritorna vero in caso di
 * successo, falso altrimenti.
 */
bool carica_magazzino(magazzino_t &m)
{
	ifstream f(NOME_FILE);
	if (!f)
		return false ;
	int N ;
	f>>N ;
	rialloca(m, N) ;
	int n, quanti ;

	while (true) {
		if (!(f>>n)) // per semplicita' assumo che il file sia
			     // semplicemente finito
			return true ;

		if (!(f>>quanti))
			return false ; // file certamente corrotto
		m.lunghezze[n - 1] = quanti ;
	}
	return true ;
}

/*
 * Estrae dal magazzino m il numero minimo possibile di cavi, tali
 * che, se si estraesse un solo altro cavo, allora la somma delle
 * lunghezze dei cavi estratti supererebbe M.
 */
void estrai_cavi(magazzino_t &m, int M)
{
	int residuo = M ;
	
	while (true) {
		bool trovato = false ;
		for (int i = residuo - 1 ; i >= 0 ; i--)
			if (m.lunghezze[i] > 0) {
				residuo -= i + 1 ;
				m.lunghezze[i]-- ;
				trovato = true ;
				break ;
			}
		if (! trovato)
			break ;
	}

}

int main()
{
	const char menu[] =
		"1. Crea magazzino\n"
		"2. Aggiungi cavo\n"
		"3. Stampa magazzino\n"
		"4. Salva magazzino\n"
		"5. Carica magazzino\n"
		"6. Estrai cavo\n"
		"7. Estrai cavi\n"
		"8. Esci\n" ;
	
	magazzino_t m;
	inizializza(m);


	while (true) {
		cout<<endl<<menu<<endl ;
		
		int scelta ;
		cin>>scelta ;
		switch (scelta) {
		case 1: {
			int N ;
			cout<<"Dimensioni magazzino: " ;
			cin>>N ;
			if (!crea(m, N))
				cout<<"Creazione fallita"<<endl ;
			break ;}
		case 2: {
			int n ;
			cout<<"Lunghezza cavo: " ;
			cin>>n ;
			if (!aggiungi_cavo(m, n-1))
				cout<<"Aggiunta cavo fallita"<<endl ;
			break ;}
		case 3:
			scrivi_magazzino(m, cout, false) ;
			break ;
		case 4: {
			ofstream f(NOME_FILE);
			if (!scrivi_magazzino(m, f, true))
				cout<<"Salvataggio fallito"<<endl ;
			break ;}
		case 5:
			if (!carica_magazzino(m))
				cout<<"Caricamento fallito"<<endl ;
			break ;
		case 6: {
			int n ;
			cout<<"Lunghezza cavo: " ;
			cin>>n ;
			if (!estrai_cavo(m, n-1))
				cout<<"Estrazione cavo fallita"<<endl ;
			break ;}
		case 7: {
			int M ;
			cout<<"M: " ;
			cin>>M ;
			estrai_cavi(m, M) ;
			break ;}
		case 8:
			return 0;
		default:
			cout<<"Scelta errata"<<endl ;
		}
	}
	return 1 ;
}
