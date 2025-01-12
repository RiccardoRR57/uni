/* Programma per la gestione di una Catena di Anelli tutti di FERRO.
   Gli anelli della catena sono numerati a partire da 1. All'inizio la catena 
   è vuota.
   Il programma deve fornire il seguente menu di operazioni:
   1) inserire un anello in posizione j (un anello alla volta)
      Le posizioni ammissibili vanno dalla prima a quella immediatamente 
      successiva all'ultima. Il programma da un messaggio di notifica nel caso
      in cui non sia possibile effettuare l'inserimento.
      Se l'inserimento ha successo il numero totale di anelli aumenta 
      ovviamente di una unità.
      Non esiste un limite al numero di anelli che si possono inserire 
      (ovviamente invocando piu' volte questa opzione).
   2) eliminare l'anello in posizione j (un anello alla volta)
      Il programma da un messaggio di notifica nel caso in cui non sia 
      possibile effettuare l'estrazione, altrimenti il numero di anelli
      diminuisce di una unità (non rimangono buchi nella catena).
   3) stampare la catena nel seguente formato:
       FFFF
      dove F indica un anello di FERRO. In questo esempio, la catena ha 4 
      anelli
   4) Terminare

  Dopo avere eseguito una delle operazioni possibili, il menu è riproposto.
  Realizzare prima il solo menu, sostituendo ciascuna funzionalità con una
  semplice stampa del numero dell'opzione scelta.
*/
 
#include <iostream>

using namespace std ;
     
int main(){
    int totale = 0; // numero totale di anelli della catena

    while (true) {
        int scelta, pos;

        cout<<"\n \n Gestione di una catena \n" 
                "Inserisci: \n"
                "1 - per inserire un anello \n"
                "2 - per estrarre un anello \n"
                "3 - per stampare la catena \n"
                "4 - per terminare\n\n"
                "Scelta\n? ";
        cin>>scelta ;
        switch (scelta){
            case 1 :
                cout<<"Posizione? " ;
                cin>>pos ;
                if (pos <= 0 || pos > totale + 1) {
                  cout<<"Non e' possibile effettuare l'inserimento\n" ;     
                  break;
		}
                totale++;
                break;
            case 2:
                cout<<"Posizione? " ;
                cin>>pos ;
                if (pos <= 0 || pos > totale)  {
                  cout<< "Non e' possibile effettuare l'estrazione\n" ;     
                  break;
                }   
               totale--;
               break;             
            case 3:
                cout<< "\n Catena: " ;
                for (int i = 1; i <= totale; i++)
			cout<<"F" ;
		cout<< endl ;   
		break ;
	case 4:
		return 0 ; /* termine programma */
	default:
	        cout<<"Scelta errata\n" ;
		  
	} /* Fine switch */  
       
    } /* Fine while */
   
    return 0; /* Questa istruzione non dovrebbe essere mai raggiunta */
 }    
