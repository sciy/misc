// this program shows using self pointer to change vaule in function transferred in the whole struct {{{
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
#define StartFromXOS  int main(int argc, char * argv[]){ if (!initialization(argc, argv)) DebugError("program cannot be initializated!", false);
#define EndWithHonor  return deconstruction(); }
//}}}

typedef struct node_type
{
    integer ID;
    real t;
    real v[100];
    char *fileName;
    FILE *datahub;
    struct node_type *S; // thiS/Self pointer. can be used to change the vaule...
} Node;

boolean printID0(Node n)
{
    print("\t%ld", n.ID);
    n.ID = n.ID+100;
}

boolean printID1(Node n) //not same with printID0! will change value of Node!
{
    print("\t%ld", n.S->ID);
    n.S->ID = n.S->ID+100;
}

boolean printID2(Node n)
{
    print("\t%ld", n.ID);
}

boolean printID3(Node n) // same with printID2
{
    print("\t%ld", n.S->ID);
}

Node n[10];

boolean initialization(int user_command_number, char * user_commands[])/*{{{*/
{
    for (int i=0; i<10; i++)
    {
        n[i].ID = i;
        n[i].S = &n[i];
    }
    print("\nInitialization starts:\n");
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
for (int i=0; i<10; i++) printID0(n[i]);
print("\n");
for (int i=0; i<10; i++) printID2(n[i]);
print("\n");
for (int i=0; i<10; i++) printID3(n[i]);
print("\n");
for (int i=0; i<10; i++) printID1(n[i]);
print("\n");
for (int i=0; i<10; i++) printID2(n[i]);
print("\n");
for (int i=0; i<10; i++) printID3(n[i]);
EndWithHonor
