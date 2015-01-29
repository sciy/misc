//    g++ -Wall gsleg.c -o gsleg -lm -lgsl -lgslcblas

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
