/*
Scrivere un programma che stampi a video la tabella dei codici ASCII
dei soli caratteri stampabili.
Per ogni carattere si stampa il carattere stesso ed il codice ASCII.
Formattare la tabella in maniera tale che non occupi pi� di 25 righe.
Scrivere il programma supponendo di non conoscere a priori il codice ASCII
dei caratteri, ma di sapere solo che i codici dei caratteri stampabili 
appartengono all'intervallo che va dal codice del carattere ' ' (spazio) al 
codice del carattere '~'. Ovviamente non conosciamo neanche il codice dei due 
estremi, ossia dei caratteri ' ' e '~'.
Implementare la stampa sia mediante due cicli nidificati che mediante un solo 
ciclo.
Provare infine a scrivere due varianti del programma, utilizzando, 
rispettivamente una variabile di tipo int ed una variabile di tipo char per 
memorizzare i codici ASCII.

Esempio di output:

        32      33 !    34 "    35 #    36 $    37 %    38 &    39 '
        40 (    41 )    42 *    43 +    44 ,    45 -    46 .    47 /
        48 0    49 1    50 2    51 3    52 4    53 5    54 6    55 7
        56 8    57 9    58 :    59 ;    60 <    61 =    62 >    63 ?
        64 @    65 A    66 B    67 C    68 D    69 E    70 F    71 G
        72 H    73 I    74 J    75 K    76 L    77 M    78 N    79 O
        80 P    81 Q    82 R    83 S    84 T    85 U    86 V    87 W
        88 X    89 Y    90 Z    91 [    92 \    93 ]    94 ^    95 _
        96 `    97 a    98 b    99 c    100 d   101 e   102 f   103 g
        104 h   105 i   106 j   107 k   108 l   109 m   110 n   111 o
        112 p   113 q   114 r   115 s   116 t   117 u   118 v   119 w
        120 x   121 y   122 z   123 {   124 |   125 }   126 ~

*/

#include <iostream>

using namespace std ;

int main()
{
	int i = ' ' ;
	// soluzione con un solo ciclo
	while ( i <= '~' ) 
	{
	    if ( i % 8 == 0 )
		cout<<endl ;
	    cout<<"\t"<<i<<" "<<static_cast<char>(i) ;
	    i++ ;
	}
	cout<<endl ;

	return 0 ;
}
