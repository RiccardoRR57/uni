#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>

using namespace std ;

const int MAXLEN = 1024 ; // lunghezza array di caratteri
const int MAXCHAR = 255 ; // valore massimo per il tipo char
const char NOMEFILE[] = "tabella.txt" ;

// descrittore di una coppia
struct coppia_t {
	char nome[MAXLEN] ; // campo nome
	int valore ;        // campo valore
} ;

// descrittore di una tabella
struct tabella_t {
	coppia_t *coppie ; // array dinamico contenente le righe della
			   // tabella, le righe vuote hanno una
			   // stringa vuota come campo nome
	int N ;		   // numero di caratteri sommati per ottenre l'indice
	int num_righe ;    // numero corrente di righe della tabella
} ;

/*
 * Inizializza o reinizializza la tabella tab, assegnando il valore
 * nuovoN ad N e svuotando la tabella stessa, il parametro prima_volta
 * deve essere inizializzato a vero se la funzione e' invocata per una
 * tabella che viene inizializzata per la prima volta. Ritorna vero
 * inc aso di successo, falso altrimenti.
 */
bool inizializza(tabella_t &tab, int nuovoN, bool prima_volta)
{
	if (nuovoN <= 0 || nuovoN >= MAXLEN)
		return false ;

	tab.num_righe = MAXCHAR * nuovoN + 1 ;
	if (! prima_volta && nuovoN != tab.N) {
		delete[] tab.coppie ;
		tab.coppie = new coppia_t[tab.num_righe] ;
	} else if (prima_volta)
		tab.coppie = new coppia_t[tab.num_righe] ;

	tab.N = nuovoN ;
	for (int i = 0 ; i < tab.num_righe ; i++)
		tab.coppie[i].nome[0] = '\0' ;

	return true ;
}

/*
 * calcola l'indice per la coppia che ha il primo parametro formale
 * come primo campo, assumendo che N sia uguale al secondo parametro
 * formale. Ritorna -1 in caso di fallimento.
 */
int calcola_indice(const char nome[], int N)
{
	int lung = strlen(nome) ;
	if (lung == 0)
		return -1 ;

	int indice = 0 ;
	for (int i = 0 ; i < N && i < lung ; i++)
		indice += abs(nome[i]) ;

	return indice ;
}

// inserisce la coppia nella tabella tab; ritorna vero in caso di
// successo, falso altrimenti
bool inserisci_coppia(tabella_t &tab, const coppia_t &coppia)
{
	int indice = calcola_indice(coppia.nome, tab.N) ;
	if (indice == -1 || tab.coppie[indice].nome[0] != '\0')
		return false ;

	strcpy(tab.coppie[indice].nome, coppia.nome) ;
	tab.coppie[indice].valore = coppia.valore ;

	return true ;
}

/*
 * scrive la tabella tab sull'ostream os, utilizzando il formato
 * opportuno per la memorizzazione su file nel caso in cui su_file sia
 * vero; ritorna vero in caso di successo, falso altrimenti
 */
bool scrivi_tabella(const tabella_t &tab, ostream &os, bool su_file)
{
	if (! su_file)
		os<<"N = " ;
	os<<tab.N<<endl ;
	for (int i = 0 ; i < tab.num_righe ; i++)
		if (tab.coppie[i].nome[0] != '\0')
			os<<i<<'\t'<<tab.coppie[i].nome<<"\t\t"
			  <<tab.coppie[i].valore<<endl ;
	return os;
}

// carica la tabella da file, ritorna vero in caso di successo, falso
// altrimenti
bool carica_tabella(tabella_t &tab)
{
	ifstream f(NOMEFILE) ;
	if (! f)
		return false ;

	int nuovoN ;
	if (! (f>>nuovoN))
		return false ;
	inizializza(tab, nuovoN, false) ;

	while(true) {
		int indice ;
		if (!(f>>indice)) // non ci sono nuove righe, lettura finita
			return true ;
		if (!(f>>tab.coppie[indice].nome)) // riga incompleta
			break ;
		if (!(f>>tab.coppie[indice].valore)) // riga incompleta
			break ;
	}

	return f;
}

/*
 * Memorizza nel terzo parametro formale il valore memorizzato nella
 * coppia, all'interno della tabella tab, che ha nome uguale al
 * secondo parametro formale. Ritorna vero in caso di successo, falso
 * altrimenti (in caso di fallimento non modifica il terzo parametro
 * formale).
 */
bool ottieni_valore(const tabella_t &tab, const char nome[], int &val)
{
	int indice = calcola_indice(nome, tab.N) ;
	if (indice == -1 || tab.coppie[indice].nome[0] == '\0' ||
	    strcmp(tab.coppie[indice].nome, nome) != 0)
		return false ;

	val = tab.coppie[indice].valore ;
	return true ;
}

int main()
{
	tabella_t tabella ;

	inizializza(tabella, 3, true) ;

	const char menu[] =
		"1. Reinizializza tabella\n"
		"2. Inserisci coppia\n"
		"3. Stampa tabella\n"
		"4. Salva tabella\n"
		"5. Carica tabella\n"
		"6. Stampa valore\n"
		"7. Esci\n" ;

	while (true) {
		cout<<menu<<endl ;
		int scelta ;
		cin>>scelta ;
		switch(scelta) {
		case 1:{
			int nuovoN ;
			cin>>nuovoN ;
			if (!inizializza(tabella, nuovoN, false))
				cout<<"Reinizializzazione fallita"<<endl ;
			break ;}
		case 2:{
			coppia_t coppia ;
			cout<<"Inserire nome e valore"<<endl ;
			cin>>coppia.nome>>coppia.valore ;
			if (!inserisci_coppia(tabella, coppia))
				cout<<"Inserimento fallito"<<endl ;
			break ;}
		case 3:
			scrivi_tabella(tabella, cout, false) ;
			break ;
		case 4:{
			ofstream f(NOMEFILE) ;
			if (!f || !scrivi_tabella(tabella, f, true))
				cout<<"Salvataggio fallito"<<endl ;
			break ;}
		case 5:
			if (!carica_tabella(tabella))
				cout<<"Caricamento fallito"<<endl ;
			break ;
		case 6:{
			char nome[MAXLEN] ;
			int valore ;
			cout<<"Inserire nome "<<endl ;
			cin>>nome ;
			if (!ottieni_valore(tabella, nome, valore))
				cout<<"Coppia non trovata"<<endl ;
			else
				cout<<"Valore "<<valore<<endl ;
			break ;}
		case 7:
			return 0;
	
		default:
			cout<<"Scelta errata"<<endl ;
		}
	}

	return 1 ;
}
