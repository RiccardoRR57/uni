#!/bin/sh

crea_tester ()
{
    cat <<- EOF > singoli-test-prog-15Gen20.cc
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int main(int argc, char** argv)
{

	if (argc < 2) {
		cout<<"Argomenti mancanti"<<endl;
		return 1;
	}

	cout<<"Leggo l'output del programma, e come stampa finale dello stato "
		"mi aspetto:"<<endl;
	cout<<argv[1]<<endl;

	cout<<endl;
	cout<<"Se mi blocco, vuol dire che il programma si è bloccato o è "
		"terminato"<<endl
	    <<"inaspettatamente."<<endl;
	cout<<endl<<"Output completo del programma:"<<endl<<endl;

	stringstream primo_corretto(argv[1]), primo_da_controllare;

	string linea;
	bool prima_linea = false;
	bool to_save = false;
	while (getline( cin, linea ))
	{
		cout<<linea<<endl;
		stringstream ss(linea);
		string primo_token;
		if (ss>>primo_token) {
			if (primo_token == "Menu:")
			{
				to_save = false;
			}
			if (to_save){
				//primo_da_controllare.str(std::string());
				primo_da_controllare << ss.rdbuf()->str() <<" ";
				//cout<<ss.rdbuf()->str()<<endl;
			}
			if (primo_token == "Magazzino:") {
				prima_linea = true;
				to_save = true;
			}
		}
	}

	cout<<endl;
	if (!prima_linea) {
		cout<<"Non ho trovato nessuna riga di stampa dello stato!"<<endl;
		cout<<"Verifica la presenza di tali righe nell'output"<<endl
		    <<"e la correttezza del formato di tali righe"<<endl;
		return 1;
	}

	string buf_corretto, buf_da_controllare;

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
		cout<<buf_da_controllare<<endl;
		cout<<"Non coincide con la riga attesa, ossia con:"<<endl;
		//cout<<"Magazzino: "<<argv[1]<<endl;
		cout<<argv[1]<<endl;
		return 1;
	}


	cout<<"Test superato!!!"<<endl;
	cout<<"-------------------------------------------------------------"
	    <<endl;

	return 0;
}
EOF
    g++ -Wall singoli-test-prog-15Gen20.cc -o singoli-test-prog-15Gen20

    if [ $? -ne 0 ]; then
	echo Compilazione del tester fallita
	exit 1
    fi
}

stampa_msg_punto_insufficiente ()
{
    if [ "$1" != "" ]; then
	punto="punto $1"
    else
	punto="tuo programma"
    fi

    echo
    echo Per poter accedere alla correzione del $punto,
    echo devi prima correggere gli errori che fanno fallire questo test.
    echo
    echo Quando il tuo programma superera\' questo test, eseguiro\' anche i successivi.
    echo

    rm singoli-test-prog-15Gen20*
    exit 1
}

esegui_test ()
{
    echo
    echo ==== Inizio test $1 ====
    echo
    echo Eseguo il programma fornendo il seguente input: $2
    echo
    echo "$2" | ./a.out | ./singoli-test-prog-15Gen20 "$3"

    if [ $? -ne 0 ]; then
	stampa_msg_punto_insufficiente $4
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

esegui_test "di inizializzazione magazzino" "1 3 3 8" "0 1 2"

esegui_test "di inserimento 2 pacchi" "1 5 2 1 asd 2 1 qwe 3 8" "0 1 asd qwe 2 3 4"

esegui_test "di inserimento in scaffale non esistente" "1 5 2 5 asd 3 8" "0 1 2 3 4"

esegui_test "di inserimento di 6 pacchi per dimensione massima scaffale 5" \
		"1 5 2 1 asd 2 1 asd 2 1 asd 2 1 asd 2 1 asd 2 1 asd 3 8" "0 1 asd asd asd asd asd 2 3 4"

esegui_test "di reinizializzazione" "1 5 2 1 asd 1 2 3 8" "0 1"

# Dal precedente test superato in poi si è raggiunta la sufficienza

esegui_test "salvataggio" "1 2 2 0 asd 2 1 dsa 2 0 qwe 2 0 jkl 4 3 8" "0 asd qwe jkl 1 dsa" 5

esegui_test "caricamento" "5 3 8" "0 asd qwe jkl 1 dsa" 6

esegui_test "copia carico" "1 5 2 1 asd 2 1 qwe 6 1 2 3 8" "0 1 asd qwe 2 asd qwe 3 4" 7

esegui_test "fondi carico" "1 5 2 1 asd1 2 1 asd2 2 1 asd3 2 1 asd4 2 2 qwe1  2 2 qwe2 7 2 1 3 8" \
		"0 1 asd4 2 qwe1 qwe2 asd1 asd2 asd3 3 4" 8

echo
echo Complimenti, il tuo programma ha superato tutti i test!
echo

rm singoli-test-prog-15Gen20*
