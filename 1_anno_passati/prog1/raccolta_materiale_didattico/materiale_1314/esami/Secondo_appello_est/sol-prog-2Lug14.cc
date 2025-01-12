#include <iostream>
#include <fstream>

using namespace std ;

const char NOME_FILE[] = "azienda.txt" ;

// descrittore azienda
struct azienda_t {
	float *stipendi ;	// vettore dipendenti
	int num_dipendenti ;	// numero dipendenti
} ;

// inizializza azienda
void inizializza(azienda_t &a)
{
	a.num_dipendenti = 0 ;
}

// funzione ausiliaria di ordinamento di un vettore
void ordina(float vett[], int num)
{
	for (int i = 0 ; i < num ; i++) {
		for (int j = i + 1 ; j < num ; j++) {
			if (vett[i] > vett[j]) {
				float tmp = vett[i] ;
				vett[i] = vett[j] ;
				vett[j] = tmp ;
			}
		}
	}
}

/*
 * Modifica l'azienda a, per contenere il vettore di stipendi vett.
 * L'eventuale contenuto precedente e' perso. Ritorna falso in caso di
 * fallimento.
 */
bool modifica_azienda(azienda_t &a, const float vett[], int num)
{
	if (num <= 0)
		return false ;
	
	if (a.num_dipendenti != 0 && a.num_dipendenti != num) {
		a.num_dipendenti = 0 ;
		delete [] a.stipendi ;
	}
	if (a.num_dipendenti == 0)
		a.stipendi = new float[num] ;
	
	for (int i = 0 ; i < num ; i++)
		a.stipendi[i] = vett[i] ;

	ordina(a.stipendi, num) ;
	a.num_dipendenti = num ;

	return true ;
}

// Scrive il contenuto dell'azienda sullo'ostream os. Ritorna falso in
// caso di fallimento.
bool scrivi(const azienda_t &a, ostream &os, bool su_file)
{
	if (su_file || a.num_dipendenti != 0)
		os<<a.num_dipendenti ;

	if (a.num_dipendenti == 0)
		return os ;

	for (int i = 0 ; i < a.num_dipendenti ; i++)
		os<<" "<<a.stipendi[i] ;
	os<<endl ;

	return os ;
}

// Carica il contenuto dell'azienda a da file. Ritorna falso in caso
// di fallimento. Il precedente vettore degli stipendi e' perso.
bool carica(azienda_t &a)
{
	ifstream f(NOME_FILE) ;

	if (!f)
		return false ;
	
	int num ;
	f>>num ;
	float *vett = new float[num] ;
	
	for (int i = 0 ; i < num ; i++)
		f>>vett[i] ;
	if (! modifica_azienda(a, vett, num))
		return false ;

	delete [] vett ;

	return f ;
}

// Copia il contenuto dell'azienda a nell'azienda b. Ritorna falso in
// caso di fallimento.
bool copia(azienda_t &a, azienda_t &b)
{
	return modifica_azienda(a, b.stipendi, b.num_dipendenti) ;
}

// Fonde l'azienda a con l'azienda b. Ritorna falso in caso di fallimento.
bool fondi(azienda_t &a, azienda_t &b)
{
	int tot_dipendenti = a.num_dipendenti + b.num_dipendenti ;
	if (tot_dipendenti == 0)
		return true ;

	float *vett = new float[tot_dipendenti] ;

	int min_dip = a.num_dipendenti < b.num_dipendenti ?
					 a.num_dipendenti : b.num_dipendenti ;

	for (int i = 0 ; i < num_dip ; i++)
		if (a.stipendi[i] < b.stipendi[i] + 200) {
			delete [] vett ;

			return false ;
		}

	for (int i = 0 ; i < a.num_dipendenti ; i++)
		vett[i] = a.stipendi[i] ;

	for (int i = 0  ; i < b.num_dipendenti ; i++)
		vett[i + a.num_dipendenti] = b.stipendi[i] ;

	bool risultato = modifica_azienda(a, vett, tot_dipendenti) ;

	if (b.num_dipendenti != 0) {
		delete [] b.stipendi ;
		b.num_dipendenti = 0 ;
	}

	delete [] vett ;

	return risultato ;
}

int main()
{

	azienda_t a, b ;
	inizializza(a) ;
	inizializza(b) ;

	const char menu[] =
		"1. Modifica azienda\n"
		"2. Stampa azienda\n"
		"3. Salva azienda\n"
		"4. Carica azienda\n"
		"5. Copia azienda\n"
		"6. Fondi aziende\n"
		"7. Esci\n";
		
	while (true) {
		cout<<menu<<endl ;

		int scelta ;
		cin>>scelta ;

		switch(scelta) {
		case 1: {
			int num ;
			do {
				cout<<"Numero dipendenti? " ;
				cin>>num ;
			} while (num <= 0) ;

			float *vett = new float[num] ;
			
			cout<<"Inserire stipendi in qualsiasi ordine: " ;
			for (int i = 0 ; i < num ; i++)
				cin>>vett[i] ;
			modifica_azienda(a, vett, num) ;
			break ;}
		case 2:
			scrivi(a, cout, false) ;
			break ;
		case 3: {
			ofstream f(NOME_FILE) ;
			scrivi(a, f, true) ;
			break ;}
		case 4:
			carica(a) ;
			break ;
		case 5: {
			b.stipendi = new float[2] ;
			b.num_dipendenti = 2 ;
			b.stipendi[0] = 7000 ;
			b.stipendi[1] = 3000 ;
			if (! copia(a, b))
				cout<<"Copia fallita"<<endl ;
			delete [] b.stipendi ;
			b.num_dipendenti = 0 ;
			break ;}
		case 6:{
			b.stipendi = new float[2] ;
			b.num_dipendenti = 2 ;
			b.stipendi[0] = 7000 ;
			b.stipendi[1] = 3000 ;
			if (! fondi(a, b))
				cout<<"Fusione fallita"<<endl ;
			if (b.num_dipendenti != 0) {
				delete [] b.stipendi ;
				b.num_dipendenti = 0 ;
			}
			break ;}
		case 7:
			return 0 ;
		default:
			cout<<"Scelta errata"<<endl ;
		}
	}
	return 1 ;
}
