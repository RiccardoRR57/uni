#include <iostream>
#include <fstream>

using namespace std ;

const int N = 10 ; // numero massimo di intervalli
const char NOME_FILE[] = "info.dat" ; // file in cui salvare lo stato

// descrittore di un singolo spostamento
struct spostamento_t {
    int distanza ;  // distanza percorsa in metri
    int durata ;    // durata dell'intervallo in secondi
} ;

// vettore dinamico contenente le informazioni sugli intervalli memorizzati
struct info_t {
    spostamento_t spostamenti[N] ;
    int num_memorizzati ;  // numero di intervalli correntemente memorizzati
} ;

// (re)inizializza il sistema cancellando tutte le informazioni
void inizializza(info_t &info)
{
    info.num_memorizzati = 0 ;
}

/*
 * Aggiunge informazioni su un nuovo spostamento al vettore info, in
 * particolare memorizza la distanza dist e la durata dell'intervallo.
 * ritorna falso in caso di fallimento, vero altrimenti
 */
bool aggiungi_spostamento(info_t &info, int dist, int durata)
{
    if (info.num_memorizzati == N || dist < 1 || durata < 1)
	return false ;

    info.spostamenti[info.num_memorizzati].distanza = dist ;
    info.spostamenti[info.num_memorizzati].durata = durata ;
    info.num_memorizzati++ ;
    
    return true ;
}

// stampa le statistiche
void stampa(const info_t &info)
{
    if (info.num_memorizzati == 0)
	return ;

    cout<<"Inizio\tDurata\tDist\tVelocita"<<endl ;
    for(int i = 0, inizio = 0 ; i < info.num_memorizzati ; i++)  {
	double velocita = static_cast<double>(info.spostamenti[i].distanza)/
	    info.spostamenti[i].durata ;
	cout<<inizio<<'\t'
	    <<info.spostamenti[i].durata<<'\t'
	    <<info.spostamenti[i].distanza<<'\t'
	    <<velocita<<endl ;
	inizio += info.spostamenti[i].durata ;
    }
}

// salva le informazioni contenute in info in un file binario
bool salva(const info_t &info)
{
    ofstream f(NOME_FILE) ;
    f.write(reinterpret_cast<const char *>(&info), sizeof(info)) ;
    return f ;
}

// carica dal file le informazioni e le memorizza dentro info 
bool carica(info_t &info)
{
    ifstream f(NOME_FILE) ;
    if (!f)
	return false ;
    f.read(reinterpret_cast<char *>(&info), sizeof(info)) ;
    return f ;
}

/*
 * Ritorna la velocita media dall'inizio dell'intervallo memorizzato
 * che contiene t1 alla fine dell'intervallo che contiene t2, ove tali
 * intervalli sono memorizzati in info.
 * Se non trova un intervallo o una coppia di intervalli appropriati ritorna 0.
 */
double calcola_velocita_media(const info_t &info, int t1, int t2)
{
    if (t1 < 0 || t2 <= t1 || info.num_memorizzati == 0)
	return 0 ;
    
    // ricerca del primo intervallo
    int interv1, inizio_interv1 ;
    for (interv1 = 0, inizio_interv1 = 0 ; interv1 < info.num_memorizzati ;
	 interv1++) {
	if (t1 >= inizio_interv1 &&
	    t1 < inizio_interv1 + info.spostamenti[interv1].durata)
	    break ;
	inizio_interv1 += info.spostamenti[interv1].durata ;
    }

    if (interv1 == info.num_memorizzati) // nessun intervallo trovato
	return 0 ;

    // ricerca del secondo intervallo e calcolo della distanza totale percorsa
    int dist_totale = 0 ;
    int interv2, inizio_interv2, fine_interv2 ;
    for (interv2 = interv1, inizio_interv2 = inizio_interv1 ;
	 interv2 < info.num_memorizzati ;
	 interv2++) {
	dist_totale += info.spostamenti[interv2].distanza ;
	fine_interv2 = inizio_interv2 + info.spostamenti[interv2].durata ;
	if (t2 >= inizio_interv2 &&
	    t2 < inizio_interv2 + info.spostamenti[interv2].durata)
	    break ;
	inizio_interv2 += info.spostamenti[interv2].durata ;
    }

    if (interv2 == info.num_memorizzati) // nessun intervallo trovato
	return 0 ;

    return static_cast<double>(dist_totale)/(fine_interv2 - inizio_interv1) ;
}

int main()
{
    info_t info ;
    inizializza(info) ;

    char menu[] =
	"1. Inizializza\n"
	"2. Aggiungi spostamento\n"
	"3. Stampa statistiche\n"
	"4. Salva stato\n"
	"5. Carica stato\n"
	"6. Stampa velocita' media\n"
	"7. Esci\n" ;

    while(true) {
	cout<<menu<<endl ;
	
	int scelta ;
	cin>>scelta ;
	switch(scelta) {
	case 1:
	    inizializza(info) ;
	    break ;
	case 2:{
	    cout<<"Inserisci distanza e duarata dell'intervallo: " ;
	    int dist, durata ;
	    cin>>dist>>durata ;
	    if(! aggiungi_spostamento(info, dist, durata))
		cout<<"Inserimento fallito"<<endl ;
	    break ;}
	case 3:
	    stampa(info) ;
	    break ;
	case 4:
	    if (! salva(info))
		cout<<"Salvataggio fallito"<<endl ;
	    break ;
	case 5:
	    if (! carica(info))
		cout<<"Caricamento fallito"<<endl ;
	    break ;
	case 6:{
	    cout<<"Inserisci t1 e t2: " ;
	    int t1, t2 ;
	    cin>>t1>>t2 ;
	    cout<<calcola_velocita_media(info, t1, t2)<<endl ;
	    break ;}
	case 7:
	    return 0 ;
	default:
	    cout<<"Scelta errata"<<endl ;
	}
    }
    return 1 ;
}
