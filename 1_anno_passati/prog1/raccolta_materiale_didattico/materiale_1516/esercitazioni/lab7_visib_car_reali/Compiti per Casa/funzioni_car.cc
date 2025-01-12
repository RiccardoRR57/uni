/*
 Includendo il file di intestazione <ctype>, si posso utilizzare una
 serie di funzioni che operano sui caratteri. Tali funzioni prendono
 in ingresso un valore intero, e ritornano un valore intero.
 Il valore preso in ingresso è interpretato come il codice ASCII di un
 carattere (in ogni caso si puo passare a tali funzioni anche un valore di tipo
 char in ingresso, perchè, come vedremo in seguito, tale valore viene 
 convertito implicitamente nel tipo int). A seconda della specifica funzione,
 il valore di ritorno può rappresentare il codice ASCII di un carattere,
 oppure un valore logico (0 per falso, 1 per vero).  Alcune di queste
 funzioni sono:

 // Ritorna un valore diverso da 0 se c e' alfanumerico, 0 altrimenti
 int isalnum(int c) ;

 // Ritorna un valore diverso da 0 se c e' alfabetico, 0 altrimenti
 int isalpha(int c) ;

 // Ritorna un valore diverso da 0 se c e' una cifra decimale, 0 altrimenti
 int isdigit(int c) ;

 // Ritorna un valore diverso da 0 se c e' una cifra esadecimale, 0 altrimenti
 int isxdigit(int c) ;

 // Ritorna un valore diverso da 0 se c e' una lettera minuscola, 0 altrimenti
 int islower(int c) ;

 // Ritorna un valore diverso da 0 se c e' una lettera maiuscola, 0 altrimenti
 int isupper(int c) ;

 // Se c è la codifica di una lettera maiuscola, restituisce la codifica della 
 // corrispondente lettera minuscola, altrimenti ritorna c
 int tolower(int c) ;

 // Se c è la codifica di una lettera minuscola, restituisce la codifica della 
 // corrispondente lettera maiuscola, altrimenti ritorna c
 int toupper(int c) ;

 Per esercizio, realizzare una propria versione di ciascuna di queste
 funzioni, con nome e tipo dei parametri modificati come segue:

 bool alfanum(char c) ;
 bool alfabetico(char c) ;
 bool cifra_dec(char c) ;
 bool cifra_esadec(char c) ;
 bool minuscolo(char c) ;
 bool maiuscolo(char c) ;

 Scrivere il programma supponendo di non conoscere il codice ASCII dei 
 caratteri, ma solo l'ordinamento tra i caratteri, come visto a lezione.
*/

 
