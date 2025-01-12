/*
  Scrivere un programma che stampi i limiti dei tipi char, int, float e double.
  
  Esempio di output:

  int limits:
        dimensioni in byte: 4
        min: -2147483648
        max: 2147483647
        max cifre base 2: 31
        max cifre base 10: 9
        ha segno: 1
        e' intero: 1
        epsilon: 0
        errore arrotondamento: 0

  float limits:
        dimensioni in byte: 4
        min: 1.17549e-38
        max: 3.40282e+38
        max cifre base 2: 24
        max cifre base 10: 6
        ha segno: 1
        e' intero: 0
        epsilon: 1.19209e-07
        errore arrotondamento: 0.5
        esponente minimo in base 2: -125
        esponente minimo in base 10: -37
        esponente massimo in base 2: 128
        esponente massimo in base 10: 38

  double limits:
        dimensioni in bytes: 8
        min: 2.22507e-308
        max: 1.79769e+308
        max cifre base 2: 53
        max cifre base 10: 15
        ha segno: 1
        e' intero: 0
        epsilon: 2.22045e-16
        errore arrotondamento: 0.5
        esponente minimo in base 2: -1021
        esponente minimo in base 10: -307
        esponente massimo in base 2: 1024
        esponente massimo in base 10: 308
  char limits:
        dimensioni in bytes: 1
        min: -128
        max: 127
        max cifre base 2: 7
        max cifre base 10: 2
        ha segno: 1
        e' intero: 1
        epsilon: 
        errore arrotondamento: 
*/


#include <limits>
#include <iostream>

using namespace std ;

main()
{

	cout<<"int limits:"<<endl ;
	cout<<"\tdimensioni in bytes: "<<sizeof(int)<<endl ;
	cout<<"\tmin: "<<numeric_limits<int>::min()<<endl ;
	cout<<"\tmax: "<<numeric_limits<int>::max()<<endl ;
	cout<<"\tmax cifre base 2: "<<numeric_limits<int>::digits<<endl ;
	cout<<"\tmax cifre base 10: "<<numeric_limits<int>::digits10<<endl ;
	cout<<"\tha segno: "<<numeric_limits<int>::is_signed<<endl ;
	cout<<"\te' intero: "<<numeric_limits<int>::is_integer<<endl ;
	cout<<"\tepsilon: "<<numeric_limits<int>::epsilon()<<endl ;
	cout<<"\terrore arrotondamento: "
	    <<numeric_limits<int>::round_error()<<endl ;

	cout<<"float limits:"<<endl ;
	cout<<"\tdimensioni in bytes: "<<sizeof(float)<<endl ;
	cout<<"\tmin: "
	    <<numeric_limits<float>::min()<<endl ;
	cout<<"\tmax: "
	    <<numeric_limits<float>::max()<<endl ;
	cout<<"\tmax cifre base 2: "<<numeric_limits<float>::digits<<endl ;
	cout<<"\tmax cifre base 10: "<<numeric_limits<float>::digits10<<endl ;
	cout<<"\tha segno: "<<numeric_limits<float>::is_signed<<endl ;
	cout<<"\te' intero: "<<numeric_limits<float>::is_integer<<endl ;
	cout<<"\tepsilon: "<<numeric_limits<float>::epsilon()<<endl ;
	cout<<"\terrore arrotondamento: "
	    <<numeric_limits<float>::round_error()<<endl ;
	cout<<"\tesponente minimo in base 2: "
	    <<numeric_limits<float>::min_exponent<<endl ;
	cout<<"\tesponente minimo in base 10: "
	    <<numeric_limits<float>::min_exponent10<<endl ;
	cout<<"\tesponente massimo in base 2: "
	    <<numeric_limits<float>::max_exponent<<endl ;
	cout<<"\tesponente massimo in base 10: "
	    <<numeric_limits<float>::max_exponent10<<endl ;

	cout<<"double limits:"<<endl ;
	cout<<"\tdimensioni in bytes: "<<sizeof(double)<<endl ;
	cout<<"\tmin: "
	    <<numeric_limits<double>::min()<<endl ;
	cout<<"\tmax: "
	    <<numeric_limits<double>::max()<<endl ;
	cout<<"\tmax cifre base 2: "<<numeric_limits<double>::digits<<endl ;
	cout<<"\tmax cifre base 10: "<<numeric_limits<double>::digits10<<endl ;
	cout<<"\tha segno: "<<numeric_limits<double>::is_signed<<endl ;
	cout<<"\te' intero: "<<numeric_limits<double>::is_integer<<endl ;
	cout<<"\te' esatto: "<<numeric_limits<double>::is_integer<<endl ;
	cout<<"\tepsilon: "<<numeric_limits<double>::epsilon()<<endl ;
	cout<<"\terrore arrotondamento: "
	    <<numeric_limits<double>::round_error()<<endl ;
	cout<<"\tesponente minimo in base 2: "
	    <<numeric_limits<double>::min_exponent<<endl ;
	cout<<"\tesponente minimo in base 10: "
	    <<numeric_limits<double>::min_exponent10<<endl ;
	cout<<"\tesponente massimo in base 2: "
	    <<numeric_limits<double>::max_exponent<<endl ;
	cout<<"\tesponente massimo in base 10: "
	    <<numeric_limits<double>::max_exponent10<<endl ;

	cout<<"char limits:"<<endl ;
	cout<<"\tdimensioni in bytes: "<<sizeof(char)<<endl ;
	cout<<"\tmin: "<<static_cast<int>(numeric_limits<char>::min())<<endl ;
	cout<<"\tmax: "<<static_cast<int>(numeric_limits<char>::max())<<endl ;
	cout<<"\tmax cifre base 2: "<<numeric_limits<char>::digits<<endl ;
	cout<<"\tmax cifre base 10: "<<numeric_limits<char>::digits10<<endl ;
	cout<<"\tha segno: "<<numeric_limits<char>::is_signed<<endl ;
	cout<<"\te' intero: "<<numeric_limits<char>::is_integer<<endl ;
	cout<<"\tepsilon: "<<numeric_limits<char>::epsilon()<<endl ;
	cout<<"\terrore arrotondamento: "
	    <<numeric_limits<char>::round_error()<<endl ;

	cout<<endl ;


}
