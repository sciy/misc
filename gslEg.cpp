//    $ g++ -Wall gslEg.cpp -o gslEg -lm -lgsl -lgslcblas
//    $ g++ -Wall gslEg.cpp -o gslEg -lm -lgsl -lcblas -latlas 
// see http://www.gnu.org/software/gsl/manual/html_node/Linking-with-an-alternative-BLAS-library.html#Linking-with-an-alternative-BLAS-library

// To compile a statically linked version of the program, use the -static flag in gcc,
//    $ gcc -static example.o -lgsl -lgslcblas -lm
// see http://www.gnu.org/software/gsl/manual/html_node/Shared-Libraries.html#Shared-Libraries

// To use C++ exception handling within user-defined functions passed to the library as parameters, the library must be built with the additional CFLAGS compilation option -fexceptions. 
// see http://www.gnu.org/software/gsl/manual/html_node/Compatibility-with-C_002b_002b.html#Compatibility-with-C_002b_002b

#include <gsl/gsl_sf.h>
#include <gsl/gsl_sf_bessel.h>
// #include <stdio.h>
#include <iostream>
using namespace std;

int main (int argc, char **argv)
{
    double x = 5.0;
    cout << gsl_sf_gamma_inc( 1.5, 0.5 ) << endl;
    cout << gsl_sf_gamma_inc_Q( 1.5, 0.5 ) << endl;
    cout << gsl_sf_gamma_inc_P( 1.5, 0.5 ) << endl;
    double y = gsl_sf_bessel_J0 (x);
    cout << "J0(" << x << ") =" << y << endl;
    return 0;
}
