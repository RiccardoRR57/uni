/*
Contenitore

Un Contenitore e' in grado di contenere elementi in numero limitato (la
capienza del contenitore). Ciascun elemento ha un nome che consiste in
una lettera (minuscola) dell.FŽ¢alfabeto. Piu' elementi di un contenitore
possono avere lo stesso nome. Implementare il contenitore mediante il
tipo di dato struct. Le operazioni che possono essere effettuate sul
contenitore sono le seguenti:

.	Inizializza(N);
Inizializza il contenitore con capienza pari ad N elementi. Il
contenitore e' vuoto. LŽ¢eventuale contenuto precedente viene perso.

.	Inserisci(p)
Inserisce un elemento avente nome p.

.	Estrai(p)
Estrae dal contenitore tutti gli elementi aventi nome p.

.	Modifica(N)
Modifica la capienza del contenitore. Dopo la modifica il contenitore
ha capienza N e contenuto identico a quello originario. Affinche'
l'operazione abbia successo, il numero di elementi contenuti nel
contenitore deve essere minore od uguale ad N.

.	capienza()
Ritorna la capienza del contenitore.

.	quanti()
Ritorna il numero degli elementi presenti nel contenitore.

.	stampa()  

Stampa il contenuto del Contenitore. LŽ¢uscita ha la forma seguente:
		<a:3, d:1, s:5>
In questo esempio, nel contenitore sono presenti tre elementi di nome
'a', uno di nome 'd' e cinque di nome 's'.

Nella soluzione e' contenuto anche un main, che potete eventualmente
utilizzare per testare le funzioni nella vostra soluzione.
*/

#include <iostream>

using namespace std ;

/*
 * Per non inserire nel main nessun pezzo della soluzione, si e'
 * utilizzato un oggetto global, ma la soluzione migliore sarebbe
 * stata quella di definire questo oggetto nel main e passare ogni
 * volta alle funzioni tutti i parametri necessari.
 */
struct {
	int numElem, cap;
	int ee[26];
} Contenitore ;

int capienza() {return Contenitore.cap;}
int quanti() {return Contenitore.numElem;}

void errore(const char s[])
{
	cout<<"Contenitore: "<<s<<endl ;
    	exit(1);
}

void Inizializza(int N)
{
    int i ; 
    if (N <= 0)
	errore("Capienza errata");
    for (i = 0; i <= 25; i++)
	Contenitore.ee[i] = 0;
    Contenitore.numElem = 0;
    Contenitore.cap = N;
}

void Inserisci(char p)
{
	if (Contenitore.numElem >= Contenitore.cap)
		errore("Capienza insufficiente");
	if (p < 'a' || p > 'z')
		errore("Nome di elemento errato");
	Contenitore.ee[p - 'a']++;
	Contenitore.numElem++;
}

void Estrai (char p)
{
	if (p < 'a' || p > 'z')
		errore("Nome di elemento errato");
	int i = p - 'a';
	if (Contenitore.ee[i]) {
		Contenitore.numElem = Contenitore.numElem - Contenitore.ee[i];
		Contenitore.ee[i] = 0;
	}
}

void Modifica(int N)
{
	if (Contenitore.numElem > N)
		errore ("Capienza insufficiente");
	Contenitore.cap = N;
}

void stampa()
{
	int i = 0;
	cout<<"<" ;
	while (i < 25 && Contenitore.ee[i] == 0)
	    i++;
	if (Contenitore.ee[i] > 0) {
		cout<<Contenitore.ee[i] 
		    <<": "<<static_cast<char>(i + 'a') ;
	    while (++i <= 25)
		if (Contenitore.ee[i])
		    cout<<", "<<Contenitore.ee[i] 
			<<": "<<static_cast<char>(i + 'a') ;
	}
	cout<<">" ;
}


int main()
{
	const char Menu[] = 
	    "\nComandi disponibili:\n"
	    "\ti - per inserire un elemento nel contenitore\n"
	    "\te - per estrarre elementi dal contenitore\n"
	    "\tc - per modificare la capienza del contenitore\n"
	    "\tf - per informazioni sul contenitore\n"
	    "\tt - per terminare\n" ;
	
	cout<< "Inizializzazione contenitore.\n" ;
	cout<< "Immetterne la capienza (e premere Invio): " ;
	int n;
	cin>>n ;
	Inizializza(n) ;
	cout<<endl ;
	while(1) {
	    char comando;

	    stampa() ;
	    cout<<Menu<<"\n\nImmettere comando e premere Invio: " ;
	    cin>>comando ; // 'consumiamo' il precedente newline
	    switch (comando) {
	    case 'i': {
		char p;
		cout<<"Inserisci nome elemento " ;
		cin>>p ;
		Inserisci(p);
		break;
	    }
	    case 'e': {
		char p;
		cout<<"Inserisci nome elemento " ;
		cin>>p ;
		Estrai(p);
		break;
	    }
	    case 'c': {
		int i;
		cout<<"Inserisci nuova capienza (e premi Invio): " ;
		cin>>i ;
		Modifica(i);
		break;
	    }
	    case 'f': 
		cout<<"Capienza: "<<capienza()<<"\tElementi: "
		    <<quanti()<<endl ;
		break;
	    case 't': 
		return 0 ;
	    default: 
		cout<< "Comando non valido\n" ;
	    }
	}
	return 0 ;
}

