/*
  Scrivere un programma in cui si dichiari un tipo enumerato giorno,
  rappresentante i giorni della settimana, e si stampino i valori
  delle 7 costanti (senza usare cicli). Quindi si definisca una
  variabile di tipo giorno, le si assegni una delle costanti a
  piacere, e la si stampi.
 */


#include <iostream>

using namespace std ;

enum giorno_t 
	{lunedi, martedi, mercoledi, giovedi, venerdi, sabato, domenica} ;

main()
{
	cout<<lunedi<<endl ;
	cout<<mercoledi<<endl ;
	cout<<domenica<<endl ;

	giorno_t giorno ;
	giorno = giovedi ;
	cout<<"giorno: "<<giorno<<endl ;
}
