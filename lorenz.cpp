// What is it? //// boost, gnuplot, fileIO... ////////////////////////////////////////////////////////////{{{
//
// use boost to solve the Lorenz system, use a file to save numerical solutions, use gnuplot to plot them.
//
// g++ -static lorenz.cpp -o lorenz -lboost_system -lboost_filesystem -lboost_iostreams
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

const int lorenzDimension = 3;
Gnuplot plotter;
ofstream fout;

typedef boost::array< double, lorenzDimension > state_type;

const double sigma = 10.0;
const double R = 28.0;
const double b = 2.33;//}}}

void lorenz(const state_type &x, state_type &dxdt, double t)//{{{
{
    dxdt[0] = sigma * (x[1] - x[0]);
    dxdt[1] = R * x[0] - x[1] - x[0] * x[2];
    dxdt[2] = -b * x[2] + x[0] * x[1];
}

void write_lorenz(const state_type &x, const double t)
{
    cout << t << '\t' << x[0] << '\t' << x[1] << '\t' << x[2] << endl;
    fout << t << '\t' << x[0] << '\t' << x[1] << '\t' << x[2] << endl;
}//}}}

int main(int argc, char **argv)
{

    fout.open("lorenz.txt",ios::out);//{{{
    if (! fout.is_open())
    {
        cout << "out file not opend!" << endl;
        return -1;
    }//}}}

    double t1 = 25.0;//{{{
    state_type x = { 10.0, 1.0, 1.0 }; // initial conditions
    odeinit::integrate(lorenz, x, 0.0, t1, 0.1, write_lorenz);//}}}

    plotter << "set terminal post enh" << endl;//enhanced PostScript{{{
    plotter << "set output \"lorenz.eps\"" << endl;
    plotter << "set xrange [0:" << t1 << "]" << endl;
    plotter << "set xtics 0,5," << t1 << endl;
    plotter << "unset key" << endl;
    plotter << "set title \"Lorenz System\"" << endl;

    plotter << "set yrange [" << -25 << ":" << 35 << "]" << endl;
    plotter << "set ytics -100,5,100" << endl;
    plotter << "plot \"lorenz.txt\" using 1:2 with line lc 1  lw 2  pt 1  ps 1 title \"I\"" << endl;

    plotter << "set yrange [" << -25 << ":" << 35 << "]" << endl;
    plotter << "set ytics -200,5,200" << endl;
    plotter << "plot \"lorenz.txt\" using 1:3 with line lc 2  lw 2  pt 2  ps 1 title \"u\"" << endl;//}}}

    plotter << "set output" << endl;//{{{
    plotter << "set term wxt" << endl;
    plotter << endl;

    fout.close();
    return 0;//}}}

}
