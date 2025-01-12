#!/bin/sh

crea_tester()
{
    cat <<- EOF > singoli-test-prog-13Gen20.cc
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int main(int argc, char** argv)
{

	if (argc < 3) {
		cout<<"Argomenti mancanti"<<endl;
		return 1;
	}

	cout<<"Leggo l'output del programma, e come stampa finale dello stato "
		"mi aspetto:"<<endl;
	cout<<"Esecuzione: "<<argv[1]<<endl;
	cout<<"Accesi: "<<argv[2]<<endl;

	cout<<endl;
	cout<<"Se mi blocco, vuol dire che il programma si è bloccato o è "
		"terminato"<<endl
	    <<"inaspettatamente."<<endl;
	cout<<endl<<"Output completo del programma:"<<endl<<endl;

	stringstream primo_corretto(argv[1]), primo_da_controllare;
	stringstream secondo_corretto(argv[2]), secondo_da_controllare;

	string linea, prima_linea, seconda_linea;
	while (getline( cin, linea ))
	{
		cout<<linea<<endl;
		stringstream ss(linea);
		string primo_token;
		if (ss>>primo_token) {
			if (primo_token == "Esecuzione:") {
				prima_linea = linea;
				primo_da_controllare.str(std::string());
				primo_da_controllare << ss.rdbuf();
			} else if (primo_token == "Accesi:") {
				seconda_linea = linea;
				secondo_da_controllare.str(std::string());
				secondo_da_controllare << ss.rdbuf();
			}
		}
	}

	cout<<endl;
	if (prima_linea == "" || seconda_linea == "") {
		cout<<"Non ho trovato nessuna riga di stampa dello stato!"<<endl;
		cout<<"Verifica la presenza di tali righe nell'output"<<endl
		    <<"e la correttezza del formato di tali righe"<<endl;
		return 1;
	}

	int buf_corretto, buf_da_controllare;

	// controllo prima riga della stampa
	while (true) {
		primo_corretto>>buf_corretto;
		primo_da_controllare>>buf_da_controllare;

		if (!primo_corretto || !primo_da_controllare ||
		    buf_corretto != buf_da_controllare)
			break;
	}

	if (primo_corretto || primo_da_controllare) {
		cout<<"La seguente riga:"<<endl;
		cout<<prima_linea<<endl;
		cout<<"Non coincide con la riga attesa, ossia con:"<<endl;
		cout<<"Esecuzione: "<<argv[1]<<endl;
		return 1;
	}

	// controllo seconda riga della stampa
	while (true) {
		secondo_corretto>>buf_corretto;
		secondo_da_controllare>>buf_da_controllare;
		if (!secondo_corretto || !secondo_da_controllare ||
		    buf_corretto != buf_da_controllare)
			break;
	}

	if (secondo_corretto || secondo_da_controllare) {
		cout<<"La seguente riga:"<<endl;
		cout<<seconda_linea<<endl;
		cout<<"Non coincide con la riga attesa, ossia con:"<<endl;
		cout<<"Accesi: "<<argv[2]<<endl;

		return 1;
	}

	cout<<"Test superato!!!"<<endl;
	cout<<"-------------------------------------------------------------"
	    <<endl;

	return 0;
}
EOF
    g++ -Wall singoli-test-prog-13Gen20.cc -o singoli-test-prog-13Gen20

    if [ $? -ne 0 ]; then
	echo Compilazione del tester fallita
	exit 1
    fi
}

stampa_msg_punto_insufficiente()
{
    if [ "$1" != "" ]; then
	punto=$1
	echo Il tuo programma ha superato tutti i test relativi ai punti che
	echo precedono il punto $punto, ma non ha superato un test relativo al
	echo "punto $punto (ossia l'ultimo test effettuato finora)."
	echo
	echo "Il test del punto $punto potrebbe essere fallito semplicemente perche'"
	echo non hai ancora implementato il punto $punto.
	echo
	echo Per poter accedere alla correzione anche del $punto,
	echo "devi prima aver implementato il punto $punto ed aver corretto"
	echo " gli errori che fanno fallire l'ultimo test."
    else
	echo
	echo Per poter accedere alla correzione del compito,
	echo "devi prima correggere gli errori che fanno fallire l'ultimo test."
    fi

    echo
    echo "Scorri in alto fino all'inizio dell'ultimo test, se vuoi controllare "
    echo "di che test si tratta, e qual'e' stato l'input dato al tuo programma."
    echo
    echo Per correggere gli errori, puoi provare ad eseguire il tuo programma
    echo manualmente, dando lo stesso input provato da me.
    echo
    echo Quando il tuo programma superera\' questo test, eseguiro\' anche i successivi.
    echo

    rm singoli-test-prog-13Gen20*
    exit 1
}

esegui_test()
{
    echo
    echo ==== Inizio test $1 ====
    echo
    echo Eseguo il programma fornendo il seguente input: $2
    echo
    echo "$2" | ./$eseguibile | ./singoli-test-prog-13Gen20 "$3" "$4"

    if [ $? -ne 0 ]; then
	stampa_msg_punto_insufficiente $5
    fi
}

# MAIN

eseguibile=$1

if [ "$eseguibile" = "" ]; then
    echo
    echo Devi fornirmi il nome dell\'eseguibile da collaudare.
    echo
    echo Ossia devi invocarmi cosi\':
    echo $0 \<nome_eseguibile\>
    echo

    exit 1
fi

if [ ! -f $eseguibile ]; then
    echo Eseguibile $eseguibile non trovato
    exit 1
fi

crea_tester

esegui_test "con insieme vuoto" "3 8" "-1" ""

esegui_test "di accensione di compiti su insieme vuoto" "2 3 2 1 3 8" "-1" ""

esegui_test "con insieme di 10 compiti spenti" "1 10 3 8" "-1" ""

esegui_test "di accensione di un compito" "1 10 2 1 3 8" "-1" "1"

esegui_test "di accensione di due compiti" "1 10 2 3 2 1 3 8" "-1" "1 3"

esegui_test "di accensione di un compito con indice troppo alto" \
	    "1 1 2 1 3 8" "-1" ""

esegui_test "di accensione di un compito in insieme da un compito" \
	    "1 1 2 0 3 8" "-1" "0"

esegui_test "di reinizializzazione" "1 10 2 2 3 1 5 2 3 2 4 3 8" "-1" "3 4"

# Aggiungere test con reinizializzazione con stesso numero di elementi precedenti

# Dal precedente test superato in poi si è raggiunta la sufficienza

esegui_test "di esecuzione di un compito" "1 10 2 3 2 1 2 6 4 3 8" "1" "3 6" 4

esegui_test "di esecuzione di due compiti" "1 10 2 3 2 1 2 6 4 4 3 8" "3" "6" 4

esegui_test "salvataggio" "1 10 2 3 2 1 2 6 4 5 3 8" "1" "3 6" 5

esegui_test "caricamento" "6 3 8" "1" "3 6" 6

esegui_test "esecuzione compito 2" "1 10 2 7 2 6 2 5 2 3 2 1 7 7 7 7 3 8" \
	    "7" "6" 7

echo
echo Complimenti, il tuo programma ha superato tutti i test!
echo

rm singoli-test-prog-13Gen20*
