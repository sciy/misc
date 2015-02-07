// What is it? //// GSL (ODE), gnuplot, fileIO... ////////////////////////////////////////////////////////{{{
// yapHHM ver 2.0
// Yet Another Program solves the Hodgkin-Huxley Model (HHM),
//     which describes how action potentials are initiated and propagated.
// HHM is a continuous time mathematical model includes a set of nonlinear differential equations (ODE):
//     dydt[0] = 0;// y[0] is the input (injection current) I. No evolution. Written as an equation for convenience.
//     dydt[1] = y[0]/C_m -g_Na*pow(y[2],3)*y[4]*(y[1]-E_Na)/C_m -g_K*pow(y[3],4)*(y[1]-E_K)/C_m -g_L*(y[1]-E_L)/C_m;// y[1] is u
//     dydt[2] = (2.5-0.1*y[1])    *(1-y[2])/(exp(2.5-0.1*y[1])-1) -4    *y[2]/exp(y[1]/18);// y[2] is m
//     dydt[3] = (0.1-0.01*y[1])   *(1-y[3])/(exp(1-0.1*y[1])-1)   -0.125*y[3]/exp(y[1]/80);// y[3] is n
//     dydt[4] = 0.07              *(1-y[4])/exp(y[1]/20)          -1    *y[4]/(exp(3-0.1*y[1])+1);// y[4] is h
// Parameters:     E_Na = 115, E_K = -12, E_L = 10.6, g_Na = 120, g_K = 36, g_L = 0.3, C_m = 1;//Mode 0
// Initialization: y[1] = 0, y[2] = 0, y[3] = 0, y[4] = 0;
// The above equations and parameters are taken from the book
//     Spiking Neuron Models: Single Neurons, Populations, Plasticity. W Gerstner, W M Kistler. Cambridge University Press, 2002
//     http://icwww.epfl.ch/~gerstner/SPNM/SPNM.html
//
// The GNU Scientific Library (GSL) is used to solve the HHM ODE, and the gnuplot is used to draw the figures.
// see http://www.gnu.org/software/gsl/manual/html_node/ODE-Example-programs.html#ODE-Example-programs
//     http://www.gnuplot.info/help.html
//     http://www.stahlke.org/dan/gnuplot-iostream/
//
// g++ -static yapHHM_mw.cpp -lm -lgsl -lgslcblas  -lboost_system -lboost_filesystem -lboost_iostreams  -o yapHHM2
//
// Mogei Wang (mogeiwang@gmail.com) on xUbuntu 14.04
// 2015-2-2 in Dalian, China
//////////////////////////////////////////////////////////////////////////////////////////////////////////}}}

#include <string>//{{{
#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>// for matrix used in solving ODE
#include <gsl/gsl_odeiv2.h>// for defining and solving ODE
#include <gnuplot-iostream.h>// the interface for controlling gnuplot from C++
using namespace std;

const int SystemDimension = 5;
const double Mode = 0;// Mode 0: E_x use HH 1952 parameters; Mode 1: E_x-65
Gnuplot plotter;
ifstream fin;
ofstream fout;//}}}

int func(double t, const double y[], double dydt[], void *params)// Defining functions for the derivatives of HHM{{{
{
    double C_m  = *(double *)(params+0*sizeof(double));
    double g_Na = *(double *)(params+1*sizeof(double));
    double E_Na = *(double *)(params+2*sizeof(double));
    double g_K  = *(double *)(params+3*sizeof(double));
    double E_K  = *(double *)(params+4*sizeof(double));
    double g_L  = *(double *)(params+5*sizeof(double));
    double E_L  = *(double *)(params+6*sizeof(double));

    dydt[0] = 0;// y[0] is the input current. No evolution. Written as an equation for convenience.
    dydt[1] = y[0]/C_m -g_Na*pow(y[2],3)*y[4]*(y[1]-E_Na)/C_m -g_K*pow(y[3],4)*(y[1]-E_K)/C_m -g_L*(y[1]-E_L)/C_m;// y[1] is u
    dydt[2] = (2.5-0.1*y[1])    *(1-y[2])/(exp(2.5-0.1*y[1])-1) -4    *y[2]/exp(y[1]/18);// y[2] is m
    dydt[3] = (0.1-0.01*y[1])   *(1-y[3])/(exp(1-0.1*y[1])-1)   -0.125*y[3]/exp(y[1]/80);// y[3] is n
    dydt[4] = 0.07              *(1-y[4])/exp(y[1]/20)          -1    *y[4]/(exp(3-0.1*y[1])+1);// y[4] is h
    return GSL_SUCCESS;
}//}}}

int jac(double t, const double y[], double *dfdy, double dfdt[], void *params)// the Jacobian matrix of HHM{{{
{
    gsl_matrix_view dfdy_mat = gsl_matrix_view_array(dfdy, SystemDimension, SystemDimension);
    gsl_matrix * m = &dfdy_mat.matrix;
//     gsl_matrix_set(m, 0 ..i. 3, 0 ..j. 3,  df[i]/dy[j]);// Jacobian matrix not set!!!
//     For some stepper algorithms of gsl_odeiv2, it is necessary to provide this Jacobian matrix!
//     http://www.gnu.org/software/gsl/manual/html_node/Stepping-Functions.html#Stepping-Functions

    dfdt[0] = 0.0;// df[0]/dt; df[0] is dydt[0].
    dfdt[1] = 0.0;// df[1]/dt
    dfdt[2] = 0.0;
    dfdt[3] = 0.0;
    dfdt[4] = 0.0;

    return GSL_SUCCESS;
}//}}}

int main(void)
{

    fout.open("yapHHM_MembraneVoltage.txt",ios::out);//|ios::binary);{{{
    if (! fout.is_open() )
    {
        cout << "out file not opend!" << endl;
        return -1;
    }//}}}

    double C_m = 1.0, E_Na = 115 -Mode * 65, E_K = -12 -Mode * 65, E_L = 10.6 -Mode * 65, g_Na = 120, g_K = 36, g_L = 0.3;//{{{
    double params[] = {C_m, g_Na, E_Na, g_K, E_K, g_L, E_L};
    gsl_odeiv2_system sys = {func, jac, SystemDimension, params};// build the sys for evolution.
    gsl_odeiv2_driver * d = gsl_odeiv2_driver_alloc_y_new(&sys, gsl_odeiv2_step_rk8pd, 1e-6, 1e-6, 0.0);
//  gsl_odeiv2_driver * d = gsl_odeiv2_driver_alloc_y_new(&sys, gsl_odeiv2_step_rk4,   1e-3, 1e-8, 1e-8);

    double t = 0.0, t1 = 100.0, tsfactor = 10.0, ts = tsfactor * t1;// t: current time, from 0 to t1; ts: how many time steps
    double y[SystemDimension] = { 0.0, 0.0, 0.0, 0.0, 0.0 };
    cout << "#t  " << "input   " << "y[1]   " << "y[2]   " << "y[3]   " << "y[4]   " << "Na+   " << "K+   " << endl;
    fout << "#t  " << "input   " << "y[1]   " << "y[2]   " << "y[3]   " << "y[4]   " << "Na+   " << "K+   " << endl;
    cout << t << "  " << y[0] << "  " << y[1] << "  " << y[2] << "  " << y[3] << "  " << y[4] <<  "  " << g_Na*pow(y[2],3)*y[4] << "  " << g_K*pow(y[3],4) << endl;
    fout << t << "  " << y[0] << "  " << y[1] << "  " << y[2] << "  " << y[3] << "  " << y[4] <<  "  " << g_Na*pow(y[2],3)*y[4] << "  " << g_K*pow(y[3],4) << endl;//}}}

    for (int i = 1; i <= round(ts); i++)// i is the number of current time step{{{
    {
        double ti = i / tsfactor;
        if (i == (30 * tsfactor    )) y[0] = 7.3; else// i == x*tsfactor: y[0]=y: turn the input voltage to y at time x
        if (i == (31 * tsfactor    )) y[0] = 0  ;     // i == zzz       : y[0]=0: turn the input voltage to 0 at time step zzz

        int status = gsl_odeiv2_driver_apply(d, &t, ti, y);// The step-size is automatically adjusted.
//         int status = gsl_odeiv2_driver_apply_fixed_step(d, &t, 1e-3, 1000, y);// Fixed step.
// //      gsl_odeiv2_driver_apply( d,  t, t1, y[]) evolves the driver system d from t to t1.
// //      gsl_odeiv2_driver_apply_fixed_step( d,  t, h, n, y[]) evolves the driver system d from t with n steps of size h.

        if (status != GSL_SUCCESS)
        {
            cout << "error, return value= " << status << endl;
            break;
        }

        cout << t << "  " << y[0] << "  " << y[1] << "  " << y[2] << "  " << y[3] << "  " << y[4] <<  "  " << g_Na*pow(y[2],3)*y[4] << "  " << g_K*pow(y[3],4) << endl;
        fout << t << "  " << y[0] << "  " << y[1] << "  " << y[2] << "  " << y[3] << "  " << y[4] <<  "  " << g_Na*pow(y[2],3)*y[4] << "  " << g_K*pow(y[3],4) << endl;
    }//}}}

    plotter << "set terminal post enh" << endl;//enhanced PostScript{{{ {{{
    plotter << "set output \"yapHHM_MembraneVoltage.eps\"" << endl;
    plotter << "set xrange [0:" << t1 << "]" << endl;
    plotter << "set xtics 0,5," << t1 << endl;
    plotter << "unset key" << endl;
    plotter << "set title \"Hodgkin-Huxley Model\"" << endl;
    plotter << "set xlabel \"Time (mS)\"" << endl;//}}}

    plotter << "set ylabel \"Input Current per unit area ({/Symbol \\m}A/cm^{2})\"" << endl;//{{{
    plotter << "set yrange [" << -2 << ":" << 12 << "]" << endl;
    plotter << "set ytics -100,1,100" << endl;
    plotter << "plot \"yapHHM_MembraneVoltage.txt\" using 1:2 with line lc 1  lw 2  pt 1  ps 1 title \"I\"" << endl;

    plotter << "set ylabel \"Membrane Voltage (mV)\"" << endl;
    plotter << "set yrange [" << -20 - Mode * 65 << ":" << 110 - Mode * 65 << "]" << endl;
    plotter << "set ytics -200,5,200" << endl;
    plotter << "plot \"yapHHM_MembraneVoltage.txt\" using 1:3 with line lc 2  lw 2  pt 2  ps 1 title \"u\"" << endl;

    plotter << "set key" << endl;
    plotter << "set ylabel \"Conductance of Na^{+} and K^{+} Channel ({/Symbol \\W}^{-1})\"" << endl;
    plotter << "set yrange [" << -5 << ":" << 30 << "]" << endl;
    plotter << "set ytics -100,1,100" << endl;
    plotter << "plot \"yapHHM_MembraneVoltage.txt\" u 1:7 w l lc 7  lw 2  pt 7  ps 1 t \"Na^{+}\", \"yapHHM_MembraneVoltage.txt\" u 1:8 w l lc 8  lw 2  pt 8  ps 1 t \"K^{+}\"" << endl;

    plotter << "set title \"u-n limit cycle\"" << endl;
    plotter << "set xlabel \"Membrane Voltage u (mV)\"" << endl;
    plotter << "set xrange [" << -20 - Mode * 65 << ":" << 110 - Mode * 65 << "]" << endl;
    plotter << "set xtics -200,5,200" << endl;
    plotter << "set ylabel \"n\"" << endl;
    plotter << "set yrange [" << -0.2 << ":" << 1.2 << "]" << endl;
    plotter << "set ytics -100,0.1,100" << endl;
    plotter << "unset key" << endl;
    plotter << "plot \"yapHHM_MembraneVoltage.txt\" using 3:4 with line lc 9  lw 2  pt 9  ps 1 title \"un\"" << endl;
    //}}}

    plotter << "set output" << endl;//{{{
    plotter << "set term wxt" << endl;
    plotter << endl;//}}} }}}

    fout.close();//{{{
    gsl_odeiv2_driver_free(d);
    return 0;//}}}

}
