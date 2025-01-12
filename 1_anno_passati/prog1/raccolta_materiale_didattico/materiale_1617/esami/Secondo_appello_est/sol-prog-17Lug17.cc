#include <iostream>
#include <fstream>

using namespace std;

/* lunghezza massima descrizione di un compito e di un luogo */
const int MAXLUN = 30;
/* nome del file in cui memorizzare lo stato dell'agenda */
const char NOME_FILE[] = "agenda.txt";

// descrittore di un compito
struct compito_t {
	char descr[MAXLUN]; // stringa nulla -> compito vuoto
	char luogo[MAXLUN];
};

// descrittore di una agenda
struct agenda_t {
	compito_t *compiti; // array dinamico dei compiti
	int ora_min; // tempo minimo per i compiti
	int ora_max; // tempo massimo per i compiti: se uguale ad
		     // (ora_min -1 ), allora l'agenda non puo'
		     // contenere nessun compito
};

/*
 * Scrive il contenuto dell'agenda a sull'ostream os, usando un
 * formato opportuno per il file di stato se su_file e' vero. Ritorna
 * vero in caso di successo, falso altrimenti.
 */
bool scrivi_agenda(const agenda_t &a, ostream &os, bool su_file)
{
	int num_ore = a.ora_max - a.ora_min + 1;

	if (su_file)
		os<<a.ora_min<<" "<<a.ora_max<<endl;

	for (int i = 0 ; i < num_ore ; i++)
		if (a.compiti[i].descr[0] != '\0')
			os<<i+a.ora_min<<" "
			  <<a.compiti[i].descr<<" "
			  <<a.compiti[i].luogo
			  <<endl;

	if (su_file)
		os<<-1<<endl; // per segnalare la fine dei compiti

	return os;
}

/*
 * Aggiunge all'agenda a un compito da svolgere al tempo tempo, con
 * descrizione descr, e luogo luogo Ritorna vero in caso di successo,
 * falso altrimenti.
 */
bool aggiungi_compito(agenda_t &a, int tempo, const char descr[],
		      const char luogo[])
{
	if (tempo < a.ora_min || tempo > a.ora_max)
		return false;

	int idx = tempo - a.ora_min;

	if(a.compiti[idx].descr[0] != '\0')
		return false;

	strcpy(a.compiti[idx].descr, descr);
	strcpy(a.compiti[idx].luogo, luogo);

	return true;
}

/*
 * Inizializza l'agenda a per contenere compiti con tempo che va da
 * ora_min ad ora_max. L'eventuale precedente contenuto dell'agenda e'
 * perso.
 */
bool reinizializza(agenda_t &a, int ora_min, int ora_max)
{
	if (ora_min < 8 || ora_min > 23 ||
	    ora_max < 8 || ora_max > 23 ||
	    ora_max < ora_min - 1)
		return false;

	int num_ore = ora_max - ora_min + 1;
	bool array_da_deallocare =
		num_ore != a.ora_max - a.ora_min + 1 &&
		a.ora_max - a.ora_min + 1 != 0;

	if (array_da_deallocare) {
		delete a.compiti;
		a.compiti = 0;
	}

	if (a.compiti == 0)
		a.compiti = new compito_t[num_ore];

	a.ora_min = ora_min;
	a.ora_max = ora_max;
	for (int i = 0 ; i < num_ore ; i++)
		a.compiti[i].descr[0] = '\0';

	return true;

}

/*
 * Carica il contenuto dell'agenda a dal file di stato. Ritorna vero
 * in caso di successo, falso altrimenti.
 */
bool carica_agenda(agenda_t &a)
{
	ifstream f(NOME_FILE);

	int ora_min, ora_max;
	f>>ora_min>>ora_max;

	if (!f)
		return false;

	if (!reinizializza(a, ora_min, ora_max))
		return false;

	int tempo;
	while (f>>tempo) {
		if (tempo == -1)
			break;
		int idx = tempo - a.ora_min;
		char descr[MAXLUN], luogo[MAXLUN];
		f>>a.compiti[idx].descr>>a.compiti[idx].luogo;
	}

	return f;
}

void inizializza_nulla(agenda_t &a)
{
	a.compiti = 0;
	a.ora_min = 8;
	a.ora_max = a.ora_min - 1;
}

/*
 * Seconda versione della aggiungi compito. Come la prima versione,
 * aggiunge all'agenda a un compito da svolgere al tempo tempo, con
 * descrizione descr, e luogo luogo Ritorna vero in caso di successo,
 * falso altrimenti. A differenza della prima versione, prova a fare
 * spazio se necessario.
 */
bool aggiungi_compito_2(agenda_t &a, int tempo, const char descr[],
			 const char luogo[])
{
	if (tempo < a.ora_min || tempo > a.ora_max)
		return false;

	int idx = tempo - a.ora_min;

	int num_ore = a.ora_max - a.ora_min + 1;

	// trova prima ora libera a partire da idx
	int prima_libera;
	for (prima_libera = idx ; prima_libera < num_ore &&
		     a.compiti[prima_libera].descr[0] != '\0' ;
	     prima_libera++)
		;
	if (prima_libera == num_ore)
		return false;

	// sposta in avanti di una posizione i compiti
	for (int i = prima_libera ; i > idx ; i--)
		     a.compiti[i] = a.compiti[i-1] ;

	strcpy(a.compiti[idx].descr, descr);
	strcpy(a.compiti[idx].luogo, luogo);

	return true;
}

int main()
{
	agenda_t agenda;
	inizializza_nulla(agenda);

	const char menu[] =
		"1. Reinizializza agenda\n"
		"2. Aggiungi compito\n"
		"3. Stampa compiti\n"
		"4. Salva stato\n"
		"5. Carica stato\n"
		"6. Aggiungi compito 2\n"
		"7. Esci\n";

	while (true) {
		cout<<menu<<endl;
		int scelta;

		cin>>scelta;
		switch (scelta) {
		case 1:{
			int ora_min, ora_max;
			cout<<"Inserire ora minima ed ora massima: ";
			cin>>ora_min>>ora_max;
			if (!reinizializza(agenda, ora_min, ora_max))
				cout<<"Reinizializzazione fallita"<<endl;
			break;}
		case 2:{
			int tempo;
			char descr[MAXLUN], luogo[MAXLUN];

			cout<<"Inserire tempo, descrizione e luogo: ";
			cin>>tempo>>descr>>luogo;
			if (!aggiungi_compito(agenda, tempo, descr, luogo))
				cout<<"Inserimento fallito"<<endl;
			break;}
		case 3:
			scrivi_agenda(agenda, cout, false);
			break;
		case 4:{
			ofstream f(NOME_FILE);
			if (!scrivi_agenda(agenda, f, true))
				cout<<"Salvataggio fallito"<<endl;
			break;}
		case 5:
			if (!carica_agenda(agenda))
				cout<<"Caricamento fallito"<<endl;
			break;
		case 6:{
			int tempo;
			char descr[MAXLUN], luogo[MAXLUN];

			cout<<"Inserire tempo, descrizione e luogo: ";
			cin>>tempo>>descr>>luogo;
			if (!aggiungi_compito_2(agenda, tempo, descr, luogo))
				cout<<"Inserimento fallito"<<endl;
			break;}

		case 7:
			return 0;
		default:
			cout<<"Scelta errata"<<endl;
		}
	}

	return 1;
}
