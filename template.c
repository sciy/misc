//=== README ===================================/*{{{*/
//·
//· Author: Mogei Wang
//·
//· MogeiWang@GMail.com
//·
//· Filename: template.c
//·
//· COPYRIGHT 2015
//·
//· Description:
//· gcc -std=gnu99 % -g -lm -lgsl -lgslcblas
//· gcc -std=gnu11 % -g -lm -lgsl -lgslcblas
//·
//==============================================/*}}}*/

#include <assert.h>//{{{ //checked
#include <ctype.h>
#include <errno.h>
#include <float.h>
#include <limits.h>
#include <locale.h>
#include <math.h> // tgmath.h
#include <setjmp.h>
#include <signal.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h> // unix.h :-)
#include <GL/freeglut.h> // openGL
#include <sys/stat.h> // unix files
#include <sys/types.h>

#define BEGIN {
#define END }
#define integer long int
#define boolean integer
#define real double
#define elif else if
#define true ((integer)(1==1))   // gcc: 1=true, 0=false
#define false ((integer)(!true))
#define EQ(f1, f2)          ( fabs((real)(f1)-(real)(f2))<(1e-13))

#define max(a,b)  ( ((a)>=(b)) ? (a):(b) )
#define min(a,b)  ( ((a)<=(b)) ? (a):(b) )
#define IdentifierLiteral(T) #T // return "T"
#define IdentifierJoint(T,x) T##x // return Tx
#define  print        printf
#define fprint       fprintf
#define pprint       fprintf
#define sprint       sprintf
#define  println()    print("\n")
#define fprintln(f)  fprint(f, "\n")
#define pprintln(p)  pprint(p, "\n")
#define sprintln(s)  sprint(s, "\n")
#define  printab()    print("\t")
#define fprintab(f)  fprint(f, "\t")
#define pprintab(p)  pprint(p, "\t")
#define sprintab(s)  sprint(s, "\t")
#define print_integer(pi)   print("\t%ld", pi)
#define print_real(pr)      print("\t%.15lf", pr)
#define print_boolean(pb)   if (EQ(pb,1)) print("\ttrue"); else print("\tfalse")
#define DebugWrong(s)           { print("\n[LINE %d] [FILE %s] [WRONG]: %s\n",__LINE__,__FILE__, s);}
#define DebugCheck(c, s)        { if (c) print("\n[LINE %d] [FILE %s] [CHECK]: %s\n",__LINE__,__FILE__, s);}
#define DebugW_T_F(s)           { print("\n[LINE %d] [FILE %s] [W-T-F]: %s\n",__LINE__,__FILE__, s);}
#define DebugPrint(s)           { print("\n[LINE %d] [FILE %s] [Print]: %s\n",__LINE__,__FILE__, s);}
#define DebugError(s, t)        { print("\n[LINE %d] [FILE %s] [ERROR]: %s\nreturning...\n",__LINE__,__FILE__, s); return t;}
#define Debug0_Div(divisor)     { if (EQ(divisor,0)) \
                                  print("\n[LINE %d] [FILE %s] [0_Div]: ATTEMPT TO USE 0 AS DENOMINATOR!\n",__LINE__,__FILE__);}
#define RandomSeed(s)            { if (s==0) srand(time(NULL)); else srand((int)s);}
#define string_to_integer(s,t)  t=strtol(s, NULL, 10)  // use this macro in this way:   string_to_integer(string, integer);
#define string_to_real(s,t)     t=strtod(s, NULL, 10)
#define integer_to_string(s, t) sprint(t, "%ld", s) // integer_to_string(integer, string); Reserve the memory for string first!
#define real_to_string(s, t)    sprint(t, "%lf", s)
#define BALL(x)                  typedef struct {x} // functions are threads, structs are balls ;-)
#define StartFromXOS   int main(int argc, char *argv[]) { if (!initialization(argc, argv)) DebugError("program cannot be initializated!", false);
#define EndWithHonor   return deconstruction(); }
#define array_size(a)  (sizeof((a)) / sizeof((a[0])))
#define iSwap(x,y)     { integer tmp; tmp=x; x=y; y=tmp; }
#define rSwap(x,y)     { real    tmp; tmp=x; x=y; y=tmp; }
//}}}

boolean initialization(int user_command_number, char * user_commands[])/*{{{*/
{
    // Command Line "test  a b c" /*{{{*/
    // argc   =   4            //argc is user_command_number
    // argv[0]   =   "test"    //argv is user_commands
    // argv[1]   =   "a"
    // argv[2]   =   "b"
    // argv[3]   =   "t"
    ///*}}}*/

    print("\nInitialization starts:\n");
    if (user_command_number <= 1)/*{{{*/
    {// use default
        print("using program default parameters, i.e.,\n");
        print("integer a = %ld\n", a_default);
        print("integer b = %ld\n", b_default);
        print("integer c = %ld\n", c_default);
    }
    elif (user_command_number != 4)
    {
        print("Usage: ...\n");
        return false;
    }
    else
    {// use user_commands: RK_order, adjust_mode, t_click_number
        a = atol(user_commands[1]); 
        b = atol(user_commands[2]) %2; 
        c = atol(user_commands[3]); 

        print("using user set parameters, i.e.,\n");
        print("integer a = %ld\n", a);
        print("integer b = %ld\n", b);
        print("integer c = %ld\n", c);
    }/*}}}*/
    // open files, etc.
    return true;
}/*}}}*/

boolean deconstruction()/*{{{*/
{
    // close files, etc.
    print("\nDeconstruction finished.\n");
    return true;
} /*}}}*/

StartFromXOS
// __main__
EndWithHonor
