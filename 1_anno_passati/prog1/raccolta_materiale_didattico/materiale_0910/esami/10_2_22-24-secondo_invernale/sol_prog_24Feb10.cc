#include <iostream>
#include <fstream>

using namespace std ;

// argomenti possibili per i libri
enum argomento_t {narrativa, scienza, storia} ;

// numero massimo di caratteri per le stringhe
const int MAX_CARATTERI = 10 ;

// dati di un libro
struct libro_t {
    char titolo[MAX_CARATTERI + 1] ; // titolo
    argomento_t arg ;                // argomento del libro
    bool ripetuto ;                  // booleano di supporto,
				     // utilizzato per implementare la funzione
                                     // stampa_ripetuti
} ;

// numero massimo di libri per scaffale
const int MAX_LIBRI = 10 ;

// dati di uno scaffale
struct scaffale_t {
    libro_t libri[MAX_LIBRI] ; // vettore di libri presenti sullo scaffale
    int num_libri ;            // numero di libri correntemente sullo scaffale
} ;

// dati di una biblioteca
struct biblioteca_t {
    scaffale_t *scaffali ; // vettore dinamico di scaffali
    int num_scaffali ;     // numero di scaffali presenti
} ;

// nome del file per salvataggio/caricamento
const char NOME_FILE[] = "biblio.txt" ;

// inizializza la biblioteca b a contenere un solo scaffale vuoto
void inizializza(biblioteca_t &b)
{
    b.scaffali = new scaffale_t[1] ;
    b.num_scaffali = 1 ;
    b.scaffali[0].num_libri = 0 ;
}

// riconfigura la biblioteca b a contenere n scaffali
void riconfigura_scaffali(biblioteca_t &b, int n)
{
    n = n > 0 ? n : 1 ;

    // se il nuovo numero di scaffali è diverso dal precedente
    if (n != b.num_scaffali) {
	delete [] b.scaffali ; // elimino il vecchio array
	b.scaffali = new scaffale_t[n] ; // creo il nuovo
	b.num_scaffali = n ;
    }

    // svuotamento scaffali
    for (int i = 0 ; i < n ; i++)
	b.scaffali[i].num_libri = 0 ;
}

// legge uno dei possibili argomenti da stdin e lo ritorna
argomento_t leggi_argomento()
{
    char arg ;
    while(true) {
	cout<<"Inserisci argomento"
	    <<"[n = narrativa, s = scienza, t=storia]: " ;
	cin>>arg ;
	switch(arg) {
	case 'n':
	    return narrativa ;
	    break ;
	case 's':
	    return scienza ;
	    break ;
	case 't':
	    return storia ;
	    break ;
	default:
	    cout<<"Argomento errato"<<endl ;
	}
    }
}

// converte la lettera nome_scaff nel corrispondente indice dello
// scaffale (da usare per accedere allo scaffale nell'array contenuto
// nella struct biblioteca_t)
int da_nome_a_indice(char nome_scaff)
{
    nome_scaff = toupper(nome_scaff) ;
    nome_scaff = nome_scaff < 'A' ? 'A' : nome_scaff ;
    nome_scaff = nome_scaff > 'Z' ? 'Z' : nome_scaff ;
    return nome_scaff - 'A' ; // da carattere ad indice
}

// Aggiunge il libro l sullo scaffale nome_scaff della biblioteca b,
// ritorna vero in caso di successo
bool inserisci_libro(biblioteca_t &b, char nome_scaff, const libro_t &l)
{
    int idx_scaff = da_nome_a_indice(nome_scaff) ;

    if (b.scaffali[idx_scaff].num_libri == MAX_LIBRI)
	return false ; // scaffale pieno

    // per semplificare la notazione
    scaffale_t &scaff = b.scaffali[idx_scaff] ;

    // controlla che il libro non sia già presente
    int idx ;
    for (idx = 0 ; idx <  scaff.num_libri &&
	     (strcmp(scaff.libri[idx].titolo, l.titolo) != 0
	      || scaff.libri[idx].arg != l.arg);
	 idx++)
	;
    if (idx < scaff.num_libri)
	return false ; // il libro c'è già

    // inserisce il libro
    scaff.libri[scaff.num_libri] = l ;
    scaff.num_libri++ ;

    return true ;
}

// stampa su os il contenuto dello scaffale nome_scaff della
// biblioteca b; se il parametro to_file è vero, stampa nel formato da
// usare per scrivere il file nella funzione salva
void stampa(ostream &os, const biblioteca_t &b, char nome_scaff, bool to_file)
{
    int idx_scaff = da_nome_a_indice(nome_scaff) ;

    for (int i = 0 ; i < b.scaffali[idx_scaff].num_libri ; i++) {
	os<<b.scaffali[idx_scaff].libri[i].titolo<<" " ;
	switch(b.scaffali[idx_scaff].libri[i].arg) {
	case narrativa:
	    os<<"narrativa" ;
	    break ;
	case scienza:
	    os<<"scienza" ;
	    break ;
	case storia:
	    os<<"storia" ;
	    break ;
	}
	os<<endl ;
    }
}

// salva tutte le informazioni della biblioteca b in un file di testo,
// ritorna vero se tutto è andato bene
bool salva(const biblioteca_t &b)
{
    ofstream f(NOME_FILE);
    f<<b.num_scaffali<<endl ;
    for (int i = 0 ; i < b.num_scaffali ; i++) {
	// per ogni scaffale si salva prima il numero di libri su di
	// esso presenti, poi i libri stessi
	f<<b.scaffali[i].num_libri<<endl ;
	stampa(f, b, 'A' + i, true) ;
    }
    return f; // ritorna vero se tutto è andato bene
}

// configura la biblioteca b in base alle informazioni memorizzate in
// un file di testo, ritorna vero se tutto è andato bene
bool carica(biblioteca_t &b)
{
    ifstream f(NOME_FILE);
    if (! f)
	return false ;
    
    int nuovo_num_scaffali ;
    f>>nuovo_num_scaffali ;

    if (nuovo_num_scaffali != b.num_scaffali) {
	delete [] b.scaffali ;
	b.scaffali = new scaffale_t[nuovo_num_scaffali] ;
	b.num_scaffali = nuovo_num_scaffali ;
    }

    for (int i = 0 ; i < b.num_scaffali ; i++) {
	f>>b.scaffali[i].num_libri ;
	for (int j = 0 ; j < b.scaffali[i].num_libri ; j++) {
	    f>>b.scaffali[i].libri[j].titolo ;
	    char arg[MAX_CARATTERI + 1] ;
	    f>>arg ;
	    if (strcmp(arg, "narrativa"))
		b.scaffali[i].libri[j].arg = narrativa ;
	    else if (strcmp(arg, "scienza"))
		b.scaffali[i].libri[j].arg = scienza ;
	    else if (strcmp(arg, "storia"))
		b.scaffali[i].libri[j].arg = storia ;
	}
    }
    return f;
}

// ritorna la frazione di libri di argomento arg presenti sullo
// scaffale nome_scaff della biblioteca b
double frazione_arg(const biblioteca_t &b, char nome_scaff, argomento_t arg)
{
    int idx_scaff = da_nome_a_indice(nome_scaff) ;
    if (b.scaffali[idx_scaff].num_libri == 0)
	return 0 ;

    int num_arg = 0 ;

    for (int i = 0 ; i < b.scaffali[idx_scaff].num_libri ; i++)
	if (b.scaffali[idx_scaff].libri[i].arg == arg)
	    num_arg++ ;

    return (double) num_arg/b.scaffali[idx_scaff].num_libri ;
}

// stampa la frazione di libri di argomento arg presenti su ciascuno
// degli scaffali della biblioteca b
void stampa_distribuzione_arg(const biblioteca_t &b, argomento_t arg)
{
    for (int i = 0 ; i < b.num_scaffali ; i++)
	cout<<frazione_arg(b, 'A' + i, arg)<<endl ;
}

// funzione di servizio della stampa_ripetuti, che stampa gli
// eventuali libri identici, a partire da quello immediatamente
// successivo al libro attualmente sotto esame
void stampa_ripetuti_da(const biblioteca_t &b, int idx_scaff, int idx_libro)
{
    const libro_t &l = b.scaffali[idx_scaff].libri[idx_libro] ;
    bool nessuno = true ;
    int iniziale = idx_libro + 1 ; // indice iniziale del libro, da
				   // usare quando si parte con la
				   // ricerca

    for (int i = idx_scaff ; i < b.num_scaffali ; i++) {
	for (int j = iniziale ; j < b.scaffali[i].num_libri ; j++)
	    // si procede con la stampa solo se il libro non è già
	    // stato considerato ed è identico ad l
	    if (! b.scaffali[i].libri[j].ripetuto &&
		strcmp(b.scaffali[i].libri[j].titolo, l.titolo) == 0
		&& b.scaffali[i].libri[j].arg == l.arg) {
		if (nessuno) {
		    cout<<l.titolo<<" "<<static_cast<char>('A'+idx_scaff)<<" " ;
		    nessuno = false ;
		}
		cout<<static_cast<char>('A'+i)<<" " ;
		b.scaffali[i].libri[j].ripetuto = true ;
	    }
	iniziale = 0 ; // quando si è finito con lo scaffale in corso,
		       // bisogna ripartire dal primo libro (indice 0)
		       // dello scaffale successivo
    }
    if (! nessuno)
	cout<<endl ;
}


// stampa i titoli dei libri identici presenti su più di uno scaffale,
// nonché gli scaffali su cui tali libri sono presenti
void stampa_ripetuti(const biblioteca_t &b)
{
    for (int i = 0 ; i < b.num_scaffali ; i++)
	for (int j = 0 ; j < b.scaffali[i].num_libri ; j++)
	    b.scaffali[i].libri[j].ripetuto = false ;

    for (int i = 0 ; i < b.num_scaffali ; i++)
	for (int j = 0 ; j < b.scaffali[i].num_libri ; j++) {
	    if (! b.scaffali[i].libri[j].ripetuto)
		stampa_ripetuti_da(b, i, j) ;
	}
}

int main()
{
    biblioteca_t bib ;
    inizializza(bib) ;

    const char menu[] =
	"\t1. Riconfigura scaffali\n"
	"\t2. Inserisci libro\n"
	"\t3. Stampa contenuto scaffale\n"
	"\t4. Salva\n"
	"\t5. Carica\n"
	"\t6. Stampa frazione argomento\n"
	"\t7. Stampa distribuzione argomenti\n"
	"\t8. Stampa titoli ripetuti\n"
	"\t9. Esci\n" ;

    while(true) {
	cout<<endl<<menu<<endl ;
	int scelta ;
	cin>>scelta ;
	switch(scelta) {
	case 1:{
	    int n ;
	    cout<<"Numero scaffali? " ;
	    cin>>n ;
	    riconfigura_scaffali(bib, n) ;
	    break ;}
	case 2:{
	    cout<<"In quale scaffale? " ;
	    char scaff ;
	    cin>>scaff ;
	    libro_t libro ;
	    cout<<"Titolo libro? " ;
	    cin>>libro.titolo ;
	    libro.arg = leggi_argomento() ;
	    if (! inserisci_libro(bib, scaff, libro))
		cout<<"Inserimento fallito"<<endl ;
	    else
		cout<<"Inserimento riuscito"<<endl ;
	    break ;}
	case 3:{
	    cout<<"Quale scaffale? " ;
	    char scaff ;
	    cin>>scaff ;
	    stampa(cout, bib, scaff, false) ;
	    break ;}
	case 4:
	    if (! salva(bib))
		cout<<"Attenzione: salvataggio fallito"<<endl ;
	    break ;
	case 5:
	    if (! carica(bib))
		cout<<"Attenzione: caricamento fallito"<<endl ;
	    break ;
	case 6:{
	    cout<<"Quale scaffale? " ;
	    char scaff ;
	    cin>>scaff ;
	    argomento_t arg = leggi_argomento() ;
	    cout<<frazione_arg(bib, scaff, arg) ;
	    break ;}
	case 7:
	    stampa_distribuzione_arg(bib, leggi_argomento()) ;
	    break ;
	case 8:
	    stampa_ripetuti(bib) ;
	    break ;
	case 9:
	    return 0 ;
	default:
	    cout<<"Scelta non valida"<<endl ;
	}
    }

    // qui non si dovrebbe mai arrivare
    return 1 ;
}
