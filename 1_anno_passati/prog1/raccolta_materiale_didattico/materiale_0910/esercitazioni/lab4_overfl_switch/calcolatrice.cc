/* 
Facciamo una piccola calcolatrice
L'utente immette due operandi interi
Poi immette un numero per indicare che operazione vuole eseguire
1 --> + 
2 --> -
3 --> *
4 --> /
5 --> resto della divisione intera

In base alla scelta dell'utente viene eseguita se possibile
l'operazione richiesta, oppure viene segnalato che si è scelta una
opzione al di fuori dell'elenco (ossia un numero non compreso tra 1 e
5).
*/
   
#include <iostream>
using namespace std;

int main()
{
    int num1, num2, operazione, risultato ;
    bool ok_op, ok_ris;  
    /* num1 --> primo numero immesso dall'utente
       num2 --> secondo numero immesso dall'utente
       operazione --> numero che indica l'operazione da eseguire
       risultato --> risultato dell'operazione eseguita 
       ok_op --> mi serve per sapere se l'operatore immesso è corretto
       ok_ris --> mi serve per sapere se il risulttato è stato calcolato o se 
       c'è stato qualche problema
    */
    
    //chiediamo all'utente di immettere i due numeri
    cout<<"Immetti due numeri su cui eseguire un'operazione\n";
    //leggiamo i due numeri
    cin>>num1>>num2;
    /*chiediamo all'utente di immettere il numero corrispondente 
      all'operazione da eseguire*/
    cout<<"Immetti un numero fra 1 e 5 in base all'operazione che vuoi"
	" effettuare sui due operandi\n";
    cout<<"1 --> + \n2 --> -\n3 --> *\n4 --> /\n5 --> resto della divisione"
	" intera\nOperazione: ";
    //leggiamo l'operatore
    cin>>operazione;
    ok_op = true ; //supponiamo che l'operatore immesso sia corretto
    ok_ris = true ; //supponiamo che il risultato si possa calcolare
    //adesso in base all'operatore scelto eseguiamo l'operazione richiesta
    switch (operazione)
	{
	case 1:
	    risultato = num1 + num2;
	    break;
	case 2:
	    risultato = num1 - num2;
	    break;
	case 3:
	    risultato = num1 * num2;
	    break;
	case 4:
	    if (num2 == 0) //se il divisore è zero lo segnalo mettendo a
		           //falso ok_ris
		ok_ris = false ;
	    else  //altrimenti calcolo il risultato
		risultato = num1 / num2;
	    break;
	case 5:
	    if (num2 == 0) //se il divisore è zero lo segnalo mettendo a
		           //falso ok_ris
		ok_ris = false ;
	    else
		risultato = num1 % num2;
	    break;
	default:
	    ok_op = false ; // se l'operatore è sbagliato setto ok a falso
	}
    if (!ok_op)
	{
	    //dico all'utente che ha immesso un operatore sbagliato
	    cout<<"Hai immesso un operatore sbagliato\n";
	    return 1; // uso un valore di ritorno diverso da 0 per segnalare
	    // una situazione anomala di terminazione
	} 
    else //l'operatore è giusto
	if (ok_ris)
	    //l'operazione è stata eseguita 
	    cout<<"Il risultato vale "<<risultato<<endl ;
	else
	    {
		cout<<"Non puoi dividere per zero!\n";
		return 1; // uso un valore di ritorno diverso da 0 per
			  // segnalare una situazione anomala di terminazione
	    }
    return 0;// un valore di uscita 0 mi indica che tutto è andato bene
}

/*
 dopo aver compilato ed eseguito il programma digitare il comando
 $ echo $? [invio]
 per vedere il valore di uscita del nostro programma 
 
 NB: il fatto che un valore di uscita 0 indichi che tutto e' andato
 bene e' una convenzione universalmente riconosciuta nel caso di
 programmi eseguibili da una bash Questo mi permette anche di
 specificare un codice di errore per indicare quali sono le ragioni
 per cui l'esecuzione non e' terminata correttamente Nel nostro caso
 abbiamo scelto: un valore di uscita 1 mi indica che l'operatore e'
 sbagliato un valore di uscita 2 mi indica un tentativo di divisione
 per zero I valori 1 e 2 sono stati scelti arbitrariamente, nulla
 vieta di scegliere altri valori. In ogni caso devono essere ritornati
 valori interi positivi se si vuole essere in grado di interpretarli
 tramite la bash.
 
*/
  
