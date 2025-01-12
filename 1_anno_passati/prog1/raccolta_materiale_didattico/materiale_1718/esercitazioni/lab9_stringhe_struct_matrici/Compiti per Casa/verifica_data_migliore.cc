Il sorgente verifica_data_peggiore.cc è scritto abbastanza male.
Questo file contiene una versione migliore della funzione data_valida

bool data_valida(const data_t &data)
{
    if (data.giorno == 0 || data.giorno > 31 
	|| data.mese == 0 || data.mese > 12)
	return false ;

    bool bisestile = !(data.anno % 400)
	|| 
	( !(data.anno % 4) && (data.anno % 100) ) ;

    switch (data.mese){
    case 2:
	if (data.giorno > 29 || (!bisestile && (data.giorno > 28)) ) 
	    return false ;
    case 4: case 6: case 9: case 11:
	if (data.giorno > 30) 
	    return false ;
    }
    return true ;
}  
