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

// --- includes and macros {{{
#include <stdio.h>
#include <math.h> //tgmath.h
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv2.h>
#include <GL/freeglut.h>
  
#define BEGIN {
#define END }
#define integer long int
#define boolean integer
#define real double
#define elif else if
#define true (1==1)   // gcc: 1=true, 0=false
#define false (!true)
#define IdentifierLiteral(T) #T // return "T"
#define IdentifierJoint(T,x) T##x // return Tx
#define print printf
#define fprint fprintf
#define pprint fprintf
#define DebugWrong(s)   {printf("\n[LINE %d] [FILe %s] [WRONG]: %s\n",__LINE__,__FILE__, s);}
#define DebugW_T_F(s)   {printf("\n[LINE %d] [FILe %s] [W-T-F]: %s\n",__LINE__,__FILE__, s);}
#define DebugError(s, t)  {printf("\n[LINE %d] [FILe %s] [ERROR]: %s\nreturning...\n",__LINE__,__FILE__, s); return t;}
#define Debug0_Div(divisor) {if(divisor==0) printf("\n[LINE %d] [FILe %s] [ERROR]: ATTEMPT TO USE 0 AS DENOMINATOR!\n",__LINE__,__FILE__);}
#define StartFromXOS  int main(int argc, char * argv[]){ if (!initialization(argc, argv)) ErrorReturn("program cannot be initializated!", false);
#define EndWithHonor  return deconstruction(); }
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
