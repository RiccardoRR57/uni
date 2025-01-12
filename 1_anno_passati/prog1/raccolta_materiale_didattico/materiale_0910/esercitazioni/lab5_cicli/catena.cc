/* Programma per la gestione di una Catena di Anelli.
   Gli anelli della catena possono essere di RAME o di FERRO.
   Possono essere presenti al piu' due anelli di RAME, mentre non esiste un 
   limite al numero di anelli di FERRO. All'inizio la catena è vuota.
   Gli anelli della catena sono numerati a partire da 1.
   Il programma deve fornire un menu con le seguenti operazioni:
   1) inserire un anello di RAME o di FERRO in posizione j (uno alla volta)
      Le posizioni ammissibili vanno dalla prima a quella immediatamente 
      successiva all'ultima. Il programma da un messaggio di notifica nel caso
      in cui non sia possibile effettuare l'inserimento.
      Quando un anello è inserito nella posizione j, tutti quelli che si 
      trovano nelle posizioni da j in poi si spostano in avanti di una 
      posizione. Il numero totale di anelli aumenta ovviamente di una unità.
   2) eliminare l'anello in posizione j (uno alla volta)
      Il programma da un messaggio di notifica nel caso in cui non sia
      possibile effettuare l'estrazione.
      Cosa succede agli anelli dalla posizione j+1 in poi?
   3) stampare la catena nel seguente formato:
       FFRFR
       dove F indica un anello di FERRO; R indica un anello di RAME.
       La catena precedente ha 5 anelli; gli in posizione 1, 2 e 4 sono di 
       ferro, mentre gli anelli in posizione 3 e 5 sono di RAME.
   4) Terminare
*/
      
 
#include <iostream>

using namespace std ;
     
int main(){
    int totale = 0; // numero totale di anelli della catena
    int quantiRame = 0; // numero totale di anelli di rame della catena
    // posR1 e posR2 mantengono le posizioni degli anelli di rame nella catena
    // posR1 = j se anello j della catena e' di rame.
    // posR1 e posR2 mantengono 0 se non indicano nessun anello della catena
    int posR1 = 0; 
    int posR2 = 0;

    while (1) {
        int scelta, m, pos;

        cout<<"\n \n Gestione di una catena \n" 
                "Inserisci: \n"
                "1 - per inserire un anello \n"
                "2 - per estrarre un anello \n"
                "3 - per stampare la catena \n"
                "4 - per terminare \n \n"
                "Scelta \n? ";
        cin>>scelta ;
        switch (scelta){
            case 1 :
                cout<< "Materiale (1 == Rame, 2 == Ferro)? " ;
                cin>>m ;
                cout<<"Posizione? " ;
                cin>>pos ;
                if ((m == 1 && quantiRame == 2) || 
		    pos <= 0 || pos > totale + 1) {
                  cout<<"Non e' possibile effettuare l'inserimento\n" ;     
                  break;
		}
                if (posR1 >= pos) posR1++;
                if (posR2 >= pos) posR2++;
                totale++;
                if (m == 1){
                  quantiRame++;
                  if (posR1 == 0) posR1 = pos;
                   else posR2 = pos;
		}   
                break;
            case 2:
                cout<<"Posizione? " ;
                cin>>pos ;
                if (pos <= 0 || pos > totale)  {
                  cout<< "Non e' possibile effettuare l'estrazione\n" ;     
                  break;
                }   
                if (posR1 == pos) {
                    posR1 = 0;
                    quantiRame--;
                }   
                if (posR2 == pos) {
                    posR2 = 0;
                    quantiRame--;
                }   
                if (posR1 > pos) posR1--;
                if (posR2 > pos) posR2--;
               totale--;
               break;             
            case 3:
                cout<< "\n Catena: " ;
                for (int i = 1; i <= totale; i++)
                  if (i == posR1 || i == posR2)
		    cout<<"R" ;
                  else
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
