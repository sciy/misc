// What is it? //// boost, gnuplot, fileIO... ////////////////////////////////////////////////////////////{{{
//
// using boost to solve the HHM system, use file to save the numerical solutions, and use gnuplot to plot.
//
// g++ -static HHM_mw.cpp -o HHM -lboost_system -lboost_filesystem -lboost_iostreams
//
// Mogei Wang (mogeiwang@gmail.com) on xUbuntu 14.04
// 2015-2-8 in Dalian, China
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////}}}

#include <iostream>//{{{
#include <fstream>
#include <boost/array.hpp>
#include <boost/numeric/odeint.hpp>
#include <gnuplot-iostream.h>
using namespace std;
namespace odeinit = boost::numeric::odeint;

const int HHMDimension = 5;
Gnuplot plotter;
ofstream fout;
typedef boost::array< double, HHMDimension > state_type;

const double Mode = 0;
const double C_m = 1.0, E_Na = 115 -Mode * 65, E_K = -12 -Mode * 65, E_L = 10.6 -Mode * 65, g_Na = 120, g_K = 36, g_L = 0.3;//}}}

void HHM(const state_type &x, state_type &dxdt, double t)//{{{
{
    double I_i = 0.0;// injection current set here!!!
    if (t >= 20) I_i = 6.0;

    dxdt[0] = I_i/C_m -g_Na*pow(x[1],3)*x[3]*(x[0]-E_Na)/C_m -g_K*pow(x[2],4)*(x[0]-E_K)/C_m -g_L*(x[0]-E_L)/C_m;// u
    dxdt[1] = (2.5-0.1*x[0])  *(1-x[1])/(exp(2.5-0.1*x[0])-1)  -4 *x[1]/exp(x[0]/18);// m
    dxdt[2] = (0.1-0.01*x[0]) *(1-x[2])/(exp(1-0.1*x[0])-1) -0.125*x[2]/exp(x[0]/80);// n
    dxdt[3] = 0.07            *(1-x[3])/exp(x[0]/20)           -1 *x[3]/(exp(3-0.1*x[0])+1);// h
}

void write_HHM(const state_type &x, const double t)
{
    cout << t << " " << x[0] << " " << x[1] << " " << x[2] << " " << x[3] << " " << g_Na*pow(x[1],3)*x[3] << " " << g_K*pow(x[2],4) << endl;
    fout << t << " " << x[0] << " " << x[1] << " " << x[2] << " " << x[3] << " " << g_Na*pow(x[1],3)*x[3] << " " << g_K*pow(x[2],4) << endl;
}//}}}

int main(int argc, char **argv)
{
    fout.open("HHM.txt",ios::out);//{{{
    if (! fout.is_open())
    {
        cout << "out file not opend!" << endl;
        return -1;
    }//}}}

    double t1 = 100.0;//{{{
    state_type x = { 0.0, 0.0, 0.0, 0.0 }; // initial conditions
    odeinit::integrate(HHM, x, 0.0, t1, 0.1, write_HHM);//}}}

    plotter << "set terminal post enh" << endl;//enhanced PostScript{{{ {{{
    plotter << "set output \"HHM.eps\"" << endl;
    plotter << "set xrange [0:" << t1 << "]" << endl;
    plotter << "set xtics 0,5," << t1 << endl;
    plotter << "unset key" << endl;
    plotter << "set title \"Hodgkin-Huxley Model\"" << endl;
    plotter << "set xlabel \"Time (mS)\"" << endl;//}}}

    plotter << "set ylabel \"Membrane Voltage (mV)\"" << endl;//{{{
    plotter << "set yrange [" << -20 - Mode * 65 << ":" << 110 - Mode * 65 << "]" << endl;
    plotter << "set ytics -200,5,200" << endl;
    plotter << "plot \"HHM.txt\" using 1:2 with line lc 2 lw 2 pt 2 ps 1 title \"u\"" << endl;
    plotter << "set key" << endl;
    plotter << "set ylabel \"Conductance of Na^{+} and K^{+} Channel ({/Symbol \\W}^{-1})\"" << endl;
    plotter << "set yrange [" << -5 << ":" << 35 << "]" << endl;
    plotter << "set ytics -100,1,100" << endl;
    plotter << "plot \"HHM.txt\" u 1:6 w l lc 7 lw 2 t \"Na^{+}\", \"HHM.txt\" u 1:7 w l lc 8 lw 2 t \"K^{+}\"" << endl;
    plotter << "set title \"u-n limit cycle\"" << endl;
    plotter << "set xlabel \"Membrane Voltage u (mV)\"" << endl;
    plotter << "set xrange [" << -20 - Mode * 65 << ":" << 110 - Mode * 65 << "]" << endl;
    plotter << "set xtics -200,5,200" << endl;
    plotter << "set ylabel \"n\"" << endl;
    plotter << "set yrange [" << -0.2 << ":" << 1.2 << "]" << endl;
    plotter << "set ytics -100,0.1,100" << endl;
    plotter << "unset key" << endl;
    plotter << "plot \"HHM.txt\" using 2:3 with line lc 9 lw 2 pt 9 ps 1 title \"un\"" << endl;//}}}

    plotter << "set output" << endl;//{{{
    plotter << "set term wxt" << endl;
    plotter << endl;

    fout.close();
    return 0;//}}}

}
