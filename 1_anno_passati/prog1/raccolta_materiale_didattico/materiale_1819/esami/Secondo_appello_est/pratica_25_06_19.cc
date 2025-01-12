#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

// numero di righe nel display
const int NUM_RIGHE_DISPLAY = 5;

// numero di pixel per riga all'avvio del programma
const int NUM_PIXEL_INIZIO = 5;

const char NOME_FILE[] = "display.txt";

// stati possibili per un pixel
enum stato_pixel_t {OFF, ON};

// descrittore del display
struct display_t
{
	// array dinamico per lo stato dei pixel nel display
	stato_pixel_t *stato[NUM_RIGHE_DISPLAY];

	// numero di pixel presenti in una riga
	int num_pixel;		
};

/*
 * Alloca memoria per i pixel di ogni riga del display
 * e ne inizializza il valore allo stato ON.
 */
void inizializza(display_t &s)
{
	s.num_pixel = NUM_PIXEL_INIZIO;

	for (int i = 0 ; i < NUM_RIGHE_DISPLAY ; i++)
	{
		s.stato[i] = new stato_pixel_t[s.num_pixel];
		for (int j = 0 ; j < s.num_pixel ; j++)
				s.stato[i][j] = ON;
	}
}

/*
 * Scrive lo stato dei pixel di una singola riga del display su 
 * output stream os. Ritorna vero in caso di successo, falso
 * altrimenti.
 */
bool scrivi_riga(const display_t &s, int nriga, ostream &os, bool su_file)
{
	for (int i = 0 ; i < s.num_pixel ; i++)
		if (s.stato[nriga][i] == ON)
			os<<'*';
		else
			os<<'-';

	os<<endl;
	
	return os;
}

/*
 * Scrive lo stato dei pixel del display sull'output stream os; utilizza un    
 * formato adatto alla memorizzazione e successiva lettura da file se
 * su_file è vero, altrimenti utilizza un formato adatto alla lettura
 * da parte di un utente. Ritorna vero in caso di successo, falso
 * altrimenti.
 */
bool scrivi_stato(const display_t &s, ostream &os, bool su_file)
{
	bool toret = true;

	if (su_file)
		os<<s.num_pixel<<endl;

	for (int i = 0 ; (i < NUM_RIGHE_DISPLAY) && toret ; i++)
		toret = toret && scrivi_riga(s, i, os, su_file);

	return toret;
}



/*
 * Modifica in nuovo_stato lo stato del pixel di indice num_pixel
 * nella sequenza s. Ritorna vero in caso di successo,
 * falso altrimenti.
 */
bool modifica_stato_pixel(display_t &s, int nriga, int num_pixel,
													stato_pixel_t nuovo_stato)
{
	if (num_pixel < 0 || num_pixel >= s.num_pixel)
		return false;
	
	s.stato[nriga][num_pixel] = nuovo_stato;
	return true;
}


/*
 * Modifica in nuova_lun il numero di pixel di ogni riga del 
 * display. Ritorna vero in caso di successo, falso altrimenti.
 */
bool modifica_numero_pixel(display_t &s, int nuova_lun)
{
	int npixel = s.num_pixel;

	if (nuova_lun <= 0)
		return false;

	if (nuova_lun == npixel)
		return true;

	int num_da_copiare =
		npixel < nuova_lun ? npixel : nuova_lun;

	for (int i = 0 ; i < NUM_RIGHE_DISPLAY ; i++)
	{
		stato_pixel_t *nuova_seq = new stato_pixel_t[nuova_lun];

		for (int j = 0 ; j < num_da_copiare ; j++)
			nuova_seq[j] = s.stato[i][j];

		for (int j = num_da_copiare ; j < nuova_lun ; j++)
			nuova_seq[j] = ON;

		delete [] s.stato[i];

		s.stato[i] = nuova_seq;
		s.num_pixel = nuova_lun;
	
		return true;
	}
}


/*
 * Carica da file l'informazione relativa a una sola riga del display.
 */
void carica_riga(display_t &s, int nriga, ifstream &f, int nuova_lun)
{
	if (nuova_lun != s.num_pixel) {
		delete [] s.stato[nriga];
		s.stato[nriga] = new stato_pixel_t[nuova_lun];
	}

	for (int i = 0 ; i < nuova_lun ; i++) {
		char stato;
		f>>stato;
		if (stato == '*')
			s.stato[nriga][i] = ON;
		else
			s.stato[nriga][i] = OFF;
	}
}

/*
 * Ricarica lo stato da file, lo stato precedente è perso.
 * Ritorna vero in caso di successo, falso in caso di fallimento.
 */
bool carica_stato(display_t &s)
{
	ifstream f(NOME_FILE);

	int nuova_lun;
	f>>nuova_lun;

	if (!f)
		return false;

	s.num_pixel = nuova_lun;

	for (int i = 0 ; i < NUM_RIGHE_DISPLAY ; i++)
		carica_riga(s, i, f, nuova_lun);

	return true;
}


/*
 * Modifica lo stato dei pixel nella riga nriga in accordo al
 * contenuto della stringa nuovo_stato. Ritorna vero in caso di
 * successo, falso altrimenti.
 */
bool modifica_stato_riga(display_t &s, int nriga, const char *nuovo_stato)
{
	if (nuovo_stato == 0)
		return false;

	int lun = strlen(nuovo_stato);
	
	if (lun == 0 || lun > s.num_pixel)
		return false;

	for (int i = 0 ; i < lun ; i++)
		if (nuovo_stato[i] != '*' && nuovo_stato[i] != '-')
			return false;
	
	for (int i = 0 ; i < lun ; i++)
		if (nuovo_stato[i] == '*')
			s.stato[nriga][i] = ON;
		else
			s.stato[nriga][i] = OFF;

	return true;
}


/*
 * Modifica lo stato di tutti i pixel del display
 * chiedendo riga per riga il nuovo stato da stdin.
 */
bool modifica_stato_display(display_t &s)
{
	bool toret = true;

	for (int i = 0 ; (i < NUM_RIGHE_DISPLAY) && toret ; i++)
	{
		char *nuovo_stato = new char[s.num_pixel + 1];
		cout<<"Nuovo stato riga "<<i<<"? ";
		cin>>nuovo_stato;
		toret = toret && modifica_stato_riga(s, i, nuovo_stato);
		if (!toret)
			cout<<"Modifica stato riga "<<i<<" fallita."<<endl;
	}

	return toret;
}

int main()
{
	display_t seq;

	inizializza(seq);
	
	const char menu[] =
		"1. Modifica stato pixel\n"
		"2. Stampa display\n"
		"3. Modifica numero pixel per riga\n"
		"4. Salva stato display\n"
		"5. Carica stato display\n"
		"6. Modifica stato singola riga\n"
		"7. Modifica stato display\n"
		"8. Esci\n";
	
	while (true) {
		cout<<endl<<menu<<endl;

		int scelta;
		cin>>scelta;
		
		switch (scelta) {

		case 1: {
			int r, c;
			cout<<"Indice riga? ";
			cin>>r;
			cout<<"Indice colonna? ";
			cin>>c;
			char s;
			cout<<"Nuovo stato [*|-] ? ";
			cin>>s;
			stato_pixel_t nuovo_stato = OFF;
			if (s == '*')
				nuovo_stato = ON;
			if (!modifica_stato_pixel(seq, r, c, nuovo_stato))
				cout<<"Modifica stato pixel fallita"<<endl;
			break;
		}

		case 2:
			scrivi_stato(seq, cout, false);
			break;

		case 3: 
		{
			int n;
			cout<<"Nuovo numero pixel per riga? ";
			cin>>n;
			if (!modifica_numero_pixel(seq, n))
				cout<<"Modifica numero pixel fallita"<<endl;
			break;
		}

		case 4: 
		{
			ofstream f(NOME_FILE);
			if (!scrivi_stato(seq, f, true))
				cout<<"Salvataggio fallito"<<endl;
			break;
		}

		case 5:
			if (!carica_stato(seq))
				cout<<"Caricamento fallito"<<endl;
			break;

		case 6: 
		{
			int n;
			cout<<"Che riga si vuole modificare? ";
			cin>>n;
			char *nuovo_stato = new char[seq.num_pixel + 1];
			cout<<"Nuovo stato riga "<<n<<"? ";
			cin>>nuovo_stato;
			if (!modifica_stato_riga(seq, n, nuovo_stato))
				cout<<"Modifica stato riga "<<n<<" fallita"<<endl;
			break;
		}

		case 7: {
				if (!modifica_stato_display(seq))
					cout<<"Modifica stato display fallita"<<endl;
				break;
			}

		case 8:
			return 0;

		default:
			cout<<"Scelta errata"<<endl;
		}
	}
	return 1;
}
