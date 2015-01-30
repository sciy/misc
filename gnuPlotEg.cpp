// g++ gnuPlotEg.cpp -o gnuPlotEg
// www.velocityreviews.com/forums/t278698-calling-gnuplot-from-a-c-program.html
#include<stdio.h>
#include <string>
#include <iostream>
using namespace std;

class GNUplot
{
    public:
    GNUplot() throw(string);
    ~GNUplot();
    void operator ()(const string & command); // send any command to gnuplot
    FILE *gnuplotpipe;
};

GNUplot::GNUplot() throw(string)
{
    // gnuplotpipe=popen("gnuplot -persist","w");
    gnuplotpipe=popen("gnuplot ","w");
    if (!gnuplotpipe)
    {
        throw("Gnuplot not found !");
    }
};

GNUplot::~GNUplot()
{
    fprintf(gnuplotpipe,"exit\n");
    pclose(gnuplotpipe);
}

void GNUplot::operator()(const string & command)
{
    fprintf(gnuplotpipe,"%s\n",command.c_str());
    fflush(gnuplotpipe); // flush is necessary, nothing gets plotted else
};

int main()
{
    GNUplot plotter;
    plotter("set terminal postscript eps");
    plotter("set output \"sin.eps\"");
    plotter("plot sin(x)");
    return 0;
}


// // http://dsec.pku.edu.cn/dsectest/dsec_cn/gnuplot/plot-b.html
// #include <sys/types.h>
// #include <sys/stat.h>
// #include <stdlib.h>
// #include <stdio.h>
// #include <math.h>
// #include <unistd.h>
//
// #define PANIC(a) do { \
//                 perror(a); \
//                 if (temp_name) unlink(temp_name);\
//                 exit(1);\
//         } while(0)
//
// int main() {
//     FILE *command,*data;
//     char *temp_name;
//     double a,b;
//     int i;
//
//     if ((temp_name = tmpnam((char *) 0)) == 0) PANIC("tmpnam failed");
//     if(mkfifo(temp_name, S_IRUSR | S_IWUSR) != 0) PANIC("mkfifo failed");
//     command = popen("gnuplot","w");
//     fprintf(command,"plot \"%s\" with lines\n",temp_name); fflush(command);
//     data = fopen(temp_name,"w");
//     for (i=0; i<20; i++) {
//         a = i/10.0;
//         b = sin(a);
//         fprintf(data,"%f %f\n",a,b);
//     }
//     fclose(data);
//     fprintf(stderr,"press enter to continue..."); fflush(stderr);
//     getchar();
//
//     fprintf(command,"plot \"%s\" with lines\n",temp_name); fflush(command);
//     data = fopen(temp_name,"w");
//     for (i=0; i<20; i++) {
//         a = i/10.0;
//         b = cos(a);
//         fprintf(data,"%f %f\n",a,b);
//     }
//     fclose(data);
//     fprintf(stderr,"press enter to continue..."); fflush(stderr);
//     getchar();
//     fclose(command);
//     unlink(temp_name);
//     return 0;
// }
//
