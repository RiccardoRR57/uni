/*
  Scrivere un programma per la gestione di un "ascensore impazzito"
  per un parco giochi.

  L'ascensore si trova inizialmente in una posizione "0", a 20 metri
  dal suolo. Se ci si sposta verso l'altro la posizione aumenta di
  valore, mentre se ci si sposta verso il basso la posizione
  diminuisce di valore. Quindi, per esempio, la posizione 1 è a 21
  metri d'altezza, mentre la posizione -2 è a 18 metri
  d'altezza. Nell'attrazione l'ascensore sale o cade velocemente verso
  una nuova posizione, quindi frena bruscamente. L'ascensore è appeso
  a funi spostate da un motore comandato mediante impulsi elettrici:
  un impulso di voltaggio positivo o negativo fa ruotare il motore di
  un angolo di base in una direzione o nell'altra. A ciascuna
  rotazione di base, corrisponde uno spostamento di base
  dell'ascensore di 0.1 m verso l'alto o verso il basso.

  Supporre per dare un impulso al motore e quindi far spostare
  l'ascensore occorra invocare una funzione singolo_impulso, alla
  quale si passa la posizione attuale e la direzione (su o giu) verso
  cui effettuare uno spostamento di base. Nel nostro programma
  supponiamo che la funzione si limiti a ritornare il valore della
  posizione passata come parametro, più o meno 0.1 a seconda della
  direzione passata anch'essa come parametro. NON UTILIZZARE UN INTERO
  PER LA DIREZIONE. E neanche un booleano.

  Il main gestisce l'ascensore leggendo da stdin un numero intero
  rappresentante il numero di spostamenti di base da effettuare, ed
  invocando per un numero di volte oppportuno e per la direzione opportuna
  la funzione singolo_impulso.  Numeri in ingresso negativi implicano
  spostamenti verso il basso, mentre numeri in ingresso positivi
  implicano spostamenti verso l'alto.

  Nel nostro sistema di riferimento, le posizioni possibili vanno da
  -20.0 a +20.0 (ossia da 0 a 40 metri di altezza nel mondo reale). Se
  si richiedono un numero di spostamenti eccessivi il programma li limita
  comunque per restare nell'intervallo di posizioni [-20.0, +20.0] ed
  evitare che l'ascensore si schianti al suolo o sul motore stesso.
  
  Scrivere il programma ed assicurarsi che funzioni.  
*/


#include <iostream>

using namespace std ;
enum direzione {su, giu} ;

double singolo_impulso(double pos, direzione d)
{
	if (d == su)
		return pos + 0.1 ;
	else
		return pos - 0.1 ;
}

int main() {
	double pos = 0.0 ;
	
	while(true) {
		int n;
		cin>>n ; // lettura numero di spostamenti da effettuare
		n = n < -200 - static_cast<int>(pos*10) ?  
			-200 - static_cast<int>(pos*10) : n ;
		n = n > 200 - static_cast<int>(pos*10) ? 
			200 - static_cast<int>(pos*10) : n ;
		int num = abs(n) ;
		direzione dir = n > 0 ? su : giu ;
		for (int i = 0 ; i < num ; i++)
			pos = singolo_impulso(pos, dir) ;
		cout<<"Nuova posizione: "<<pos ;		
	}
	return 0 ;
}
