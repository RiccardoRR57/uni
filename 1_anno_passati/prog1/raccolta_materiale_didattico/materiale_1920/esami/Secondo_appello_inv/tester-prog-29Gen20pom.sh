#!/bin/sh

crea_tester ()
{
    cat <<- EOF > righe_da_ultima_stampa.cc
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <cstdlib>

using namespace std;

void turn_lowercase(string &s)
{
	for (unsigned int i = 0 ; i < s.size() ; i++)
		s[i] = tolower(s[i]);
}

bool confronta_contenuto_linee(string linea1, string linea2)
{
	turn_lowercase(linea1);
	turn_lowercase(linea2);

	string buf1, buf2;
	stringstream stream1(linea1), stream2(linea2);

	// controllo prima riga della stampa
	while (true) {
		stream1>>buf1;
		stream2>>buf2;

		if (!stream1 || !stream2 || buf1 != buf2)
			break;
	}

	if (stream1 || stream2)
		return false;

	return true;
}

int main(int argc, char** argv)
{

	if (argc < 2) {
		cerr<<"Argomenti mancanti"<<endl;
		return 1;
	}
	vector<string> linee_output;

	string linea_aggancio(argv[1]);
	string linea;
	bool buffering = false;

	while (getline( cin, linea )) {
		if (confronta_contenuto_linee(linea, linea_aggancio)) {
			buffering = true;
			linee_output.clear();
		}
		if (buffering)
			linee_output.push_back(linea);
	}

	// stampa le ultime linee a partire dall'ultima stampa
	for (std::vector<string>::const_iterator i = linee_output.begin();
	     i != linee_output.end(); ++i)
		std::cout << *i<<endl;

	return 0;
}
EOF

    g++ -Wall righe_da_ultima_stampa.cc -o righe_da_ultima_stampa

    if [ $? -ne 0 ]; then
	echo Compilazione del filtro delle righe di output fallita
	exit 1
    fi

    cat <<- EOF > controlla_output.cc
#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>

using namespace std;

void turn_lowercase(string &s)
{
	for (unsigned int i = 0 ; i < s.size() ; i++)
		s[i] = tolower(s[i]);
}

bool confronta_contenuto_linee(string linea1, string linea2)
{
	turn_lowercase(linea1);
	turn_lowercase(linea2);

	string buf1, buf2;
	stringstream stream1(linea1), stream2(linea2);

	// controllo prima riga della stampa
	while (true) {
		stream1>>buf1;
		stream2>>buf2;

		if (!stream1 || !stream2 || buf1 != buf2)
			break;
	}

	if (stream1 || stream2)
		return false;

	return true;
}

int main(int argc, char** argv)
{
	if (argc < 3) {
		cout<<"Argomenti mancanti"<<endl;
		return 1;
	}

	int num_linee = atoi(argv[1]);

	cout<<"Ora leggo l'output del programma, e come ultima stampa dello stato"
	    <<endl<<"mi aspetto:"<<endl;

	for (int i = 0 ; i < num_linee ; i++)
		cout<<argv[i+2]<<endl;

	string linea;
	bool letta_una_linea = false;
	int indice_linea_corretta = 0;

	while (getline( cin, linea ) && indice_linea_corretta < num_linee) {
		letta_una_linea = true;
		string linea_corretta(argv[indice_linea_corretta+2]);

		if (!confronta_contenuto_linee(linea, linea_corretta)) {
			cout<<"La seguente riga:"<<endl;
			cout<<linea<<endl;
			cout<<"Non coincide con la riga attesa, ossia con:"
			    <<endl;
			cout<<linea_corretta<<endl;

			return 1;
		}
		indice_linea_corretta++;
	}

	cout<<endl;

	if (!letta_una_linea) {
		cout<<"Non ho trovato nessuna riga di stampa dello stato!"
		    <<endl;
		cout<<"Verifica la presenza di tali righe nell'output"<<endl
		    <<"e la correttezza del formato di tali righe"<<endl;

		return 1;
	}

	cout<<"Test superato!!!"<<endl;
	cout<<"-------------------------------------------------------------"
	    <<endl;

	return 0;
}
EOF

    g++ -Wall controlla_output.cc -o controlla_output

    if [ $? -ne 0 ]; then
	echo Compilazione del controllore dell\'ouput fallita
	exit 1
    fi
}

stampa_msg_punto_insufficiente ()
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
    echo "di che test si tratta e qual'e' stato l'input dato al tuo programma."
    echo
    echo Per correggere gli errori, puoi provare ad eseguire il tuo programma
    echo manualmente, dando lo stesso input provato da me.
    echo
    echo Quando il tuo programma superera\' questo test, eseguiro\' anche i successivi.
    echo

    rm controlla_output* righe_da_ultima_stampa*

    exit 1
}

esegui_test ()
{
    nome_test="$1"
    punto=$2
    input_test="$3"
    num_linee_da_controllare=$4
    prima_linea_stampa="$5"

    echo
    echo ==== Inizio test $nome_test ====
    echo
    echo Eseguo il programma fornendo il seguente input: "$input_test"
    echo
    echo "$input_test" | ./$eseguibile > output_eseguibile.txt

    echo "Ecco l'output completo del programma (l'input non apparira'):"
    echo
    cat output_eseguibile.txt

    cat output_eseguibile.txt | ./righe_da_ultima_stampa "$prima_linea_stampa" \
	| ./controlla_output $num_linee_da_controllare "$prima_linea_stampa" \
			     "$6" "$7" "$8" "$9"

    if [ $? -ne 0 ]; then
	stampa_msg_punto_insufficiente $punto
    fi
}

esegui_tutti_test ()
{
    PRIMA="L M M G V Nome"

esegui_test "con insieme vuoto" "" "2 6" 1 "$PRIMA"

esegui_test "con un partecipante" "" "1 Marco *-**- 2 6" \
	    2 "$PRIMA" "* - * * - Marco"

esegui_test "con tre partecipanti" "" "1 Marco *-**- 1 Nicola --*-* 1 Andrea *-*** 2 6" \
	    4 "$PRIMA" "* - * * - Marco" "- - * - * Nicola" "* - * * * Andrea"

esegui_test "solo salvataggio" 3 "1 Marco *-**- 1 Nicola --*-* 1 Andrea *-*** 3 2 6" \
	    4 "$PRIMA" "* - * * - Marco" "- - * - * Nicola" "* - * * * Andrea"

esegui_test "caricamento da vuoto" 4 "4 2 6" \
	    4 "$PRIMA" "* - * * - Marco" "- - * - * Nicola" "* - * * * Andrea"

esegui_test "caricamento da meno partecipanti" 4 \
	    "1 Marco *-**- 1 Nicola --*-* 4 2 6" \
	    4 "$PRIMA" "* - * * - Marco" "- - * - * Nicola" "* - * * * Andrea"

esegui_test "caricamento da piu' partecipanti" 4 \
	    "1 Marco *-**- 1 Nicola --*-* 1 Giulio *-**- 1 Andrea *-*** 4 2 6 " \
	    4 "$PRIMA" "* - * * - Marco" "- - * - * Nicola" "* - * * * Andrea"

esegui_test "caricamento ed aggiunta di un partecipante " 4 \
	    "4 1 Giulio *-**- 2 6" \
	    5 "$PRIMA" "* - * * - Marco" "- - * - * Nicola" \
	    "* - * * * Andrea" "* - * * - Giulio"

esegui_test "trova giorno migliore" 5 \
	    "1 Marco *-**- 1 Nicola --*-* 1 Andrea *-*** 2 5 6" \
	    1 Mercoledi

esegui_test "trova giorno migliore senza partecipanti" 5 \
	    "5 6" \
	    1 nessuno

esegui_test "trova giorno migliore senza partecipanti disponibili" 5 \
	    "1 Marco ----- 1 Nicola ----- 5 6" \
	    1 nessuno

return

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

esegui_tutti_test

echo
echo Complimenti, il tuo programma ha superato tutti i test!
echo

rm controlla_output* righe_da_ultima_stampa*
