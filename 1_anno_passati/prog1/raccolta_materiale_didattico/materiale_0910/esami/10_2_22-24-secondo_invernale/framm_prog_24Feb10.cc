#include <iostream>
#include <fstream>

using namespace std ;

int main()
{

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
	    break ;}
	case 2:
	    break ;
	case 3:
	    break ;
	case 4:
	    break ;
	case 5:
	    break ;
	case 6:
	    break ;
	case 7:
	    break ;
	case 8:
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
