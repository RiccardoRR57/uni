#include <iostream>
#include <fstream>

using namespace std;

const int MAX_ELEM = 10; // numero massimo di elementi in una sequenza
const int MAX_SEQ = 5;   // numero massimo di sequenze
const char NOME_FILE[] = "insieme.dat";

// descrittore di una sequenza
struct sequenza_t {
    int vettore[MAX_ELEM];	// array contenente gli elementi
    int num_elem;		// numero attuale di elementi
};

// descrittore dell'insieme di sequenze
struct insieme_t {
    sequenza_t sequenze[MAX_SEQ];	// array contenente le sequenze
    int num_seq;			// numero attuale di sequenze
};

void inizializza(insieme_t &i)
{
    i.num_seq = 0 ;
}

// legge da stdin una sequena di interi e li inserisce in s
void leggi_sequenza(sequenza_t &s)
{
    cout<<"Inserisci gli elementi della sequenza seguiti da Ctrl-D: ";

    int i = 0 ;
    while(i < MAX_ELEM && cin>>s.vettore[i])
	i++;
    cin.clear();

    s.num_elem = i;
}

// aggiunge la sequenza s all'insieme ins, ritorna vero in caso di
// successo, falso altrimenti
bool aggiungi_sequenza(insieme_t &ins, sequenza_t &s)
{
    if (ins.num_seq == MAX_SEQ)
	return false;
    for (int i = 0 ; i < s.num_elem ; i++)
	ins.sequenze[ins.num_seq].vettore[i] = s.vettore[i];
    ins.sequenze[ins.num_seq].num_elem = s.num_elem;
    ins.num_seq++;
    return true;
}

void stampa_insieme(const insieme_t &ins)
{
    for (int i = 0 ; i < ins.num_seq ; i++) {
	for (int j = 0 ; j < ins.sequenze[i].num_elem ; j++) {
	    if (j > 0)
		cout<<" ";
	    cout<<ins.sequenze[i].vettore[j];
	}
	cout<<endl;
    }
    cout<<endl;
}

// salva l'insieme ins su un file binario, ritorna vero in caso di
// successo, falso altrimenti
bool salva_insieme(const insieme_t &ins)
{
    ofstream f(NOME_FILE);
    f.write(reinterpret_cast<const char *>(&ins), sizeof(ins));
    
    return f;
}

// carica l'insieme ins da un file binario, ritorna vero in caso di
// successo, falso altrimenti
bool carica_insieme(insieme_t &ins)
{
    ifstream f(NOME_FILE);
    insieme_t buffer;

    f.read(reinterpret_cast<char *>(&buffer), sizeof(ins));
    if (f)
	ins = buffer;

    return f;
}

// elimina l'ultima sequenza dall'insieme ins, solo se tale sequenza
// e' piu' lunga di almeno un'altra sequenza, ritorna vero in caso di
// successo, falso altrimenti
bool elimina_ultima_sequenza(insieme_t &ins)
{
	if (ins.num_seq == 0)
		return false;

	int num_elem_ult_seq = ins.sequenze[ins.num_seq].num_elem;
	int i;
	for (i = 0 ; i < ins.num_seq - 1 ; i++)
		if (ins.sequenze[i].num_elem < num_elem_ult_seq)
			break;
	if (i < ins.num_seq - 1)
		ins.num_seq--;

	return true;
}

// ritorna vero se l'elemento elem e' presente in tutte le sequenze
// dell'insieme a partire dalla seconda
bool presente(const insieme_t &ins, int elem)
{
    if (ins.num_seq == 1)
	return true;

    for (int i = 1 ; i < ins.num_seq ; i++) {
	int j;
	for (j = 0 ; j < ins.sequenze[i].num_elem ; j++)
	    if (ins.sequenze[i].vettore[j] == elem)
		break;
	if (j == ins.sequenze[i].num_elem)
	    return false;
    }
    return true;
}

// aggiunge una sequenza contenten l'intersezione di tutte le altre
// sequenze, ritorna vero in caso di successo, falso altrimenti
bool aggiungi_sequenza_intersezione(insieme_t &ins)
{
    if (ins.num_seq == 0 || ins.num_seq == MAX_SEQ)
	return false;
    int num_elem_inters = 0;
    for (int i = 0 ; i < ins.sequenze[0].num_elem ; i++)
	if (presente(ins, ins.sequenze[0].vettore[i])) {
	    ins.sequenze[ins.num_seq].vettore[num_elem_inters] =
		ins.sequenze[0].vettore[i];
	    num_elem_inters++;
	}
    if (num_elem_inters > 0) {
	ins.sequenze[ins.num_seq].num_elem = num_elem_inters;
	ins.num_seq++;
    } else
	return false;

    return true;
}

int main()
{
    insieme_t insieme;
    inizializza(insieme);

    char menu[] =
	"1. Aggiungi sequenza all'insieme\n"
	"2. Stampa insieme delle sequenze\n"
	"3. Salva insieme delle sequenze\n"
	"4. Carica insieme delle sequenze\n"
	"5. Aggiungi sequenza intersezione all'insieme\n"
	"6. Esci\n";

    while(true) {
	cout<<menu<<endl;

	int scelta;
	cin>>scelta ;
	switch(scelta) {
	case 1:{
	    sequenza_t seq;
	    leggi_sequenza(seq);
	    if (! aggiungi_sequenza(insieme, seq))
		cout<<"Inserimento fallito"<<endl;
	    break;}
	case 2:
	    stampa_insieme(insieme);
	    break;
	case 3:
	    if (! salva_insieme(insieme))
		cout<<"Salvataggio fallito"<<endl;
	    break;
	case 4:
	    if (! carica_insieme(insieme))
		cout<<"Caricamento fallito"<<endl;
	    break;
	case 5:
	    if (! aggiungi_sequenza_intersezione(insieme))
		cout<<"Nessuna sequenza aggiunta"<<endl;
	    break;
	case 6:
	    return 0;
	    break;
	default:
	    cout<<"Scelta errata"<<endl;
	}
    }
}
