/*
Ricevimento studenti

Supponiamo di andare a ricevimento da un professore. Con le domande che 
dobbiamo fare ci basterebbero 10 minuti, solo che, appena ci sediamo il 
professore riceve una telefonata e chiacchiera per 2 minuti. Dopo 5 minuti
ne riceve un'altra, e parla per altri 2 minuti. E così via: ogni 5 minuti 
riceve una telefonata e chiacchiera per 2 minuti. Quanto tempo impiegheremo 
prima di avere risposta a tutte le nostre domande?
Ovviamente tale tempo non è 14 minuti, come si potrebbe erroneamente pensare ...

Realizzare un programma che calcoli, in generale, la durata di un ricevimento,
data una durata qualsiasi delle domande, dell'intervallo di tempo tra una 
telefonata e l'altra, e di ciascuna telefonata (la durata è uguale per tutte 
le telefonate). 

Aiuto:
Nel caso dei dieci minuti di domande, bisogna considerare che, appena ci 
sediamo, arriva una telefonata e aspettiamo subito 2 minuti. Quindi noi 
prevederemmo di finire in 12 minuti. Solo che, dopo che abbiamo iniziato a 
parlare, arriva una nuova telefonata (siamo al quinto minuto) e dobbiamo 
aspettare altri 2 minuti. Quindi, finita anche questa telefonata, abbiamo 
aspettato 4 minuti di telefonate ed abbiamo parlato per tre minuti.
Ci rimarrebbero altri 7 minuti, ma, mentre continuiamo a parlare arrivano 
sempre nuove telefonate. Una prima soluzione potrebbe essere quella di contare
quante telefonate cascano nei dieci minuti (cioe' 2) e sommare il tempo di 
tali telefonate (cioe' 4 minuti) ai nostri dieci minuti iniziali. Arriveremmo
a 14 minuti, solo che, in 14 minuti il professore riesce a ricevere anche 
un'altra telefonata, quindi il nostro tempo si sposta ancora piu' in la'...
Se riusciremo a fare i conti bene, scopriremo che il tempo necessario sara' di
18 minuti.

Attenzione: per contare il numero di telefonate che possono arrivare, si puo' 
utilizzare la divisione intera. Pero', se il resto della divisione e' diverso 
da zero, vuol dire che, rispetto al risultato della divisione intera, una 
ulteriore telefonata fa in tempo ad arrivare...

Attenzione: se immettiamo, come tempo di una telefonata, un valore maggiore o 
uguale al tempo che trascorre tra una telefonata e l'altra, e' come se le 
telefonate continuassero ad arrivare e si accodassero mentre il professore 
parla al telefono. Pertanto, se ci pensate bene, in tal caso il professore 
rimarrebbe "per sempre" al telefono e noi dovremmo aspettare un tempo infinito.

*/

#include <iostream>

using namespace std ;

int calcola_durata(int tempo_domande, int intervallo, int durata_tel)
{
    int durata = tempo_domande; // durata iniziale presunta
    int durata_precedente ;     // variabile ausiliaria

    do {
       int numero_interruzioni ; // numero di interruzioni durante il ricev.
       durata_precedente = durata ; // aggiorno la variabile ausiliaria

       // calcoliamo il numero di interruzioni che cascano durante la durata
       // presunta:
       numero_interruzioni = durata / intervallo ;
       if (durata % intervallo != 0) // resto maggiore di zero, quindi
          numero_interruzioni++ ; // un'altra telefonata fa in tempo ad arrivare
       durata = tempo_domande + numero_interruzioni * durata_tel ;
    } while (durata != durata_precedente) ; // la durata continua ad aumentare
    return durata ;
}

int main()
{
      int tempo_domande ;
      int intervallo ;
      int durata_tel ;

      cout<<"In quanti minuti speri di cavartela? " ;
      cin>>tempo_domande ;
      cout<<"Ogni quanto tempo arriva una telefonata? " ;
      cin>>intervallo ;
      cout<<"Quanto dura ogni telefonata? " ;
      cin>>durata_tel ;
      if (durata_tel >= intervallo) 
            cout<<"Non te la caverai mai :-(\n" ;
      else {
            cout<<"Te la caverai in " ;
            cout<<calcola_durata(tempo_domande, intervallo, durata_tel) ;
            cout<<" minuti\n" ;
      }
      return 0;
}
