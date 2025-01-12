/*
Contenitore

Un Contenitore e' in grado di contenere elementi in numero limitato (la
capienza del contenitore). Ciascun elemento ha un nome che consiste in
una lettera (minuscola) dell'alfabeto. Piu' elementi di un contenitore
possono avere lo stesso nome. Le operazioni che possono essere effettuate
sul contenitore sono le seguenti:

.	Inizializza(N);
Inizializza il contenitore con capienza pari ad N elementi. Il
contenitore e' vuoto. L'eventuale contenuto precedente viene perso.

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
utilizzare per testare le funzioni nella vostra soluzione. Svolgere
l'esercizio senza utilizzare il costrutto struct (non ancora visto a
lezione).
*/

#include <iostream>

using namespace std ;

/*
 * Per non inserire nel main nessun pezzo della soluzione, si sono
 * utilizzate qui tre variabili globali, ma la soluzione migliore
 * sarebbe stata quella di definire queste variabili nel main e
 * passare ogni volta alle funzioni tutti i parametri necessari.
 */
int numElem, cap;
int ee[26];

int capienza() {return cap;}
int quanti() {return numElem;}

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
	ee[i] = 0;
    numElem = 0;
    cap = N;
}

void Inserisci(char p)
{
	if (numElem >= cap)
		errore("Capienza insufficiente");
	if (p < 'a' || p > 'z')
		errore("Nome di elemento errato");
	ee[p - 'a']++;
	numElem++;
}

void Estrai (char p)
{
	if (p < 'a' || p > 'z')
		errore("Nome di elemento errato");
	int i = p - 'a';
	if (ee[i]) {
		numElem = numElem - ee[i];
		ee[i] = 0;
	}
}

void Modifica(int N)
{
	if (numElem > N)
		errore ("Capienza insufficiente");
	cap = N;
}

void stampa()
{
	int i = 0;
	cout<<"<" ;
	while (i < 25 && ee[i] == 0)
	    i++;
	if (ee[i] > 0) {
		cout<<ee[i] 
		    <<": "<<static_cast<char>(i + 'a') ;
	    while (++i <= 25)
		if (ee[i])
		    cout<<", "<<ee[i] 
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
	while(true) {
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

