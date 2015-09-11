/* Model described in
Authors: Wendling F, Hernandez A, Bellanger JJ, Chauvel P, Bartolomei F
Title: Interictal to ictal transition in human temporal lobe epilepsy:
insights from a computational model of intracerebral EEG.
Journal: J Clin Neurophysiol. 2005 Oct;22(5):343-56.
================================================
 Fabrice WENDLING
================================================
 Laboratoire Traitement du Signal et de L'Image
 INSERM U642 - UNIVERSITE DE RENNES 1
 Campus de Beaulieu
 35042 Rennes Cedex - France -
 http://perso.univ-rennes1.fr/fabrice.wendling/
================================================

fonctionsC. Written in ANSI C
All functions that actually define the model.
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "functionsC.h"
#include "stimulation.h"
#include "mex.h"

//-----------------------------------------------------------------------
//void saveAsBin(char *fileName, float *data, int nbL)
//{
//    FILE *fpBin;
//
//    fpBin = (FILE*)fopen(fileName,"wb");
//
//    fwrite(data, sizeof(float), nbL, fpBin);
//
//    fclose(fpBin);
//}
////-----------------------------------------------------------------------
//void saveAsTxt(char *fileName, float **data, int nbC, int nbL, float fEch, int withTime)
//{
//    int i,j;
//    FILE *fpTxt;
//
//    fpTxt = (FILE*)fopen(fileName,"wt");
//
//    for(i=0;i<nbL;i++){
//        if (withTime) fprintf(fpTxt,"%f",(float)i/fEch);
//        for(j=0;j<nbC;j++){
//            fprintf(fpTxt," %.6f",data[j][i]);
//        }
//        fprintf(fpTxt,"\n");
//    }
//    fclose(fpTxt);
//}


//------------------------------------------------------------------
float *vector(int n)
{
    float *v;
    v = (float*) malloc(n * sizeof(float) );
    return v;
}
//------------------------------------------------------------------
void free_vector(float *v)
{
    free (v);
}
//------------------------------------------------------------------
float sigm(float v, POPULATION_PARAM *P)
{
    float e0, v0, r;

    v0 = P->v0; e0 = P->e0; r = P->r;

    return 2*e0/(1+exp(r*(v0-v))) ;
}
//------------------------------------------------------------------
float p(POPULATION_PARAM *P)
{
    float x, coefMult, m, sigma;

    m = P->meanP; sigma = P->sigmaP;coefMult = P->coefMultP;

    x = coefMult * GaussianNoise(sigma,m);

    return x;
}
//----------------------------------------------------------------------
float GaussianNoise(float sigma,float m)
{
    float gauss;
    float rand1;
    float rand2;
    double pi = 3.141592653589793238462643383;

    rand1 = (float)rand()/(float)(RAND_MAX);
    rand2 = (float)rand()/(float)(RAND_MAX);
    gauss = sigma * sqrt(-2.0*log(1.0-rand1)) * cos(2.0*pi*rand2)+m;

    return(gauss);
}


//------------------------------------------------------------------
// Model ODEs
//------------------------------------------------------------------
void CA3_CA1_ODEs(float t, float *y, float *dydx, POPULATION_PARAM *P, float stimulation_CA3, float stimulation_CA1)
{
    float A_CA1;
    float B_CA1;
    float G_CA1;
    float C_CA1;
    float C1_CA1;
    float C2_CA1;
    float C3_CA1;
    float C4_CA1;
    float C5_CA1;
    float C6_CA1;
    float C7_CA1;
    float a_CA1;
    float b_CA1;
    float g_CA1;

    float A_CA3;
    float B_CA3;
    float G_CA3;
    float C_CA3;
    float C1_CA3;
    float C2_CA3;
    float C3_CA3;
    float C4_CA3;
    float C5_CA3;
    float C6_CA3;
    float C7_CA3;
    float a_CA3;
    float b_CA3;
    float g_CA3;

    float C_schaffer;
    float C_feedback;

    float v_CA3_Pyr;
    float i_CA3_Pyr;
    float v_CA3_E;
    float i_CA3_E;
    float v_CA3_IS1;
    float i_CA3_IS1;
    float v_CA3_IF1;
    float i_CA3_IF1;
    float v_CA3_IS2;
    float i_CA3_IS2;

    float v_CA1_Pyr;
    float i_CA1_Pyr;
    float v_CA1_E;
    float i_CA1_E;
    float v_CA1_IS1;
    float i_CA1_IS1;
    float v_CA1_IF1;
    float i_CA1_IF1;
    float v_CA1_IS2;
    float i_CA1_IS2;
    float v_CA1_IF2;
    float i_CA1_IF2;

    float dv_CA3_Pyr;
    float di_CA3_Pyr;
    float dv_CA3_E;
    float di_CA3_E;
    float dv_CA3_IS1;
    float di_CA3_IS1;
    float dv_CA3_IF1;
    float di_CA3_IF1;
    float dv_CA3_IS2;
    float di_CA3_IS2;

    float dv_CA1_Pyr;
    float di_CA1_Pyr;
    float dv_CA1_E;
    float di_CA1_E;
    float dv_CA1_IS1;
    float di_CA1_IS1;
    float dv_CA1_IF1;
    float di_CA1_IF1;
    float dv_CA1_IS2;
    float di_CA1_IS2;
    float dv_CA1_IF2;
    float di_CA1_IF2;

    float noise_CA3;
    float noise_CA1;

    // CA1
    A_CA1 	= P->A_CA1;
    B_CA1 	= P->B_CA1;
    G_CA1	= P->G_CA1;
    C_CA1	= P->C_CA1;
    C1_CA1 	= P->C1_CA1;
    C2_CA1 	= P->C2_CA1;
    C3_CA1 	= P->C3_CA1;
    C4_CA1 	= P->C4_CA1;
    C5_CA1 	= P->C5_CA1;
    C6_CA1 	= P->C5_CA1;
    C7_CA1 	= P->C7_CA1;
    a_CA1 	= P->a_CA1;
    b_CA1 	= P->b_CA1;
    g_CA1 	= P->g_CA1;

    // CA3
    A_CA3 	= P->A_CA3;
    B_CA3 	= P->B_CA3;
    G_CA3	= P->G_CA3;
    C_CA3	= P->C_CA3;
    C1_CA3 	= P->C1_CA3;
    C2_CA3 	= P->C2_CA3;
    C3_CA3 	= P->C3_CA3;
    C4_CA3 	= P->C4_CA3;
    C5_CA3 	= P->C5_CA3;
    C6_CA3 	= P->C5_CA3;
    C7_CA3 	= P->C7_CA3;
    a_CA3 	= P->a_CA3;
    b_CA3 	= P->b_CA3;
    g_CA3 	= P->g_CA3;

    C_schaffer = P->C_schaffer;
    C_feedback = P->C_feedback;


    v_CA3_Pyr 	= y[0];
    i_CA3_Pyr 	= y[1];
    v_CA3_E 	= y[2];
    i_CA3_E		= y[3];
    v_CA3_IS1	= y[4];
    i_CA3_IS1	= y[5];
    v_CA3_IF1  	= y[6];
    i_CA3_IF1 	= y[7];
    v_CA3_IS2 	= y[8];
    i_CA3_IS2 	= y[9];

    v_CA1_Pyr 	= y[10];
    i_CA1_Pyr 	= y[11];
    v_CA1_E 	= y[12];
    i_CA1_E		= y[13];
    v_CA1_IS1	= y[14];
    i_CA1_IS1	= y[15];
    v_CA1_IF1  	= y[16];
    i_CA1_IF1 	= y[17];
    v_CA1_IS2 	= y[18];
    i_CA1_IS2 	= y[19];
    v_CA1_IF2	= y[10];
    i_CA1_IF2	= y[21];

    /////////
    // CA3 //
    /////////

    noise_CA3   = p(P);
    dv_CA3_Pyr 	= i_CA3_Pyr;
    di_CA3_Pyr	= A_CA3*a_CA3*(sigm(v_CA3_E - v_CA3_IS1 - v_CA3_IF1 + stimulation_CA3, P)) - 2*a_CA3*i_CA3_Pyr - a_CA3*a_CA3*v_CA3_Pyr;

    dv_CA3_E 	= i_CA3_E;
    di_CA3_E 	= A_CA3*a_CA3*(noise_CA3 + C2_CA3*sigm(C1_CA3*v_CA3_Pyr - C_feedback*v_CA1_IF2  + stimulation_CA3, P) ) - 2*a_CA3*i_CA3_E - a_CA3*a_CA3*v_CA3_E;

    dv_CA3_IS1 	= i_CA3_IS1;
    di_CA3_IS1 	= B_CA3*b_CA3*C4_CA3*(sigm(C3_CA3*v_CA3_Pyr  + stimulation_CA3, P)) - 2*b_CA3*i_CA3_IS1 - b_CA3*b_CA3*v_CA3_IS1;

    dv_CA3_IF1 	= i_CA3_IF1;
    di_CA3_IF1 	= G_CA3*g_CA3*C7_CA3*(sigm(C5_CA3*v_CA3_Pyr - C6_CA3*v_CA3_IS2  + stimulation_CA3, P)) - 2*g_CA3*i_CA3_IF1 - g_CA3*g_CA3*v_CA3_IF1;

    dv_CA3_IS2 	= i_CA3_IS2;
    di_CA3_IS2 	= B_CA3*b_CA3*(sigm(C3_CA3*v_CA3_Pyr  + stimulation_CA3, P) ) - 2*b_CA3*i_CA3_IS2 - b_CA3*b_CA3*v_CA3_IS2;

    /////////
    // CA1 //
    /////////
    noise_CA1   = p(P);
    dv_CA1_Pyr 	= i_CA1_Pyr;
    di_CA1_Pyr 	= A_CA1*a_CA1*sigm(v_CA1_E - v_CA1_IS1 - v_CA1_IF1 + C_schaffer*v_CA3_Pyr + stimulation_CA1 , P) - 2*a_CA1*i_CA1_Pyr - a_CA1*a_CA1*v_CA1_Pyr;

    dv_CA1_E 	= i_CA1_E;
    di_CA1_E 	= A_CA1*a_CA1*(noise_CA1  + C2_CA1*sigm(C1_CA1*v_CA1_Pyr  + stimulation_CA1, P)) - 2*a_CA1*i_CA1_E - a_CA1*a_CA1*v_CA1_E;

    dv_CA1_IS1 	= i_CA1_IS1;
    di_CA1_IS1 	= B_CA1*b_CA1*C2_CA1*sigm(C2_CA1*v_CA1_Pyr + stimulation_CA1, P) - 2*b_CA1*i_CA1_IS1 - b_CA1*b_CA1*v_CA1_IS1;

    dv_CA1_IF1 	= i_CA1_IF1;
    di_CA1_IF1 	= G_CA1*g_CA1*C7_CA1*sigm(C5_CA1*v_CA1_Pyr - C6_CA1*v_CA1_IS2 + stimulation_CA1, P) - 2*g_CA1*i_CA1_IF1 - g_CA1*g_CA1*v_CA1_IF1;

    dv_CA1_IS2 	= i_CA1_IS2;
    di_CA1_IS2 	= B_CA1*b_CA1*sigm(C3_CA1*v_CA1_Pyr + stimulation_CA1, P) - 2*b_CA1*i_CA1_IS2 - b_CA1*b_CA1*v_CA1_IS2;

    dv_CA1_IF2 	= i_CA1_IF2;
    di_CA1_IF2 	= G_CA1*g_CA1*sigm(C5_CA1*v_CA1_Pyr + stimulation_CA1, P) - 2*g_CA1*i_CA1_IF2 - g_CA1*g_CA1*v_CA1_IF2;

    dydx[0] 	= dv_CA3_Pyr;
    dydx[1] 	= di_CA3_Pyr;
    dydx[2] 	= dv_CA3_E;
    dydx[3] 	= di_CA3_E;
    dydx[4] 	= dv_CA3_IS1;
    dydx[5] 	= di_CA3_IS1;
    dydx[6] 	= dv_CA3_IF1;
    dydx[7] 	= di_CA3_IF1;
    dydx[8] 	= dv_CA3_IS2;
    dydx[9] 	= di_CA3_IS2;

    dydx[10] 	= dv_CA1_Pyr;
    dydx[11] 	= di_CA1_Pyr;
    dydx[12] 	= dv_CA1_E;
    dydx[13] 	= di_CA1_E;
    dydx[14] 	= dv_CA1_IS1;
    dydx[15] 	= di_CA1_IS1;
    dydx[16] 	= dv_CA1_IF1;
    dydx[17] 	= di_CA1_IF1;
    dydx[18] 	= dv_CA1_IS2;
    dydx[19] 	= di_CA1_IS2;
    dydx[20] 	= dv_CA1_IF2;
    dydx[21] 	= di_CA1_IF2;

}
//------------------------------------------------------------------
/* Numerical Integration. Euler Method */
//------------------------------------------------------------------
void euler(float *y, float *dydx, int n, float x, float h, float *yout, POPULATION_PARAM *P, float stim_CA3, float stim_CA1 )
{
    int i;

    CA3_CA1_ODEs(x,y,dydx,P, stim_CA3, stim_CA1);

    // Update each ODE
    for (i=0;i<n;i++){
        yout[i]=y[i] + h * dydx[i];
    }
}
//------------------------------------------------------------------
void centre_signal(float *s,int Nbp)
{
    float Moy=0.0;
    int i;

    for(i=0; i < Nbp; i++)
        Moy += s[i];

    Moy /= Nbp;

    for(i=0; i < Nbp; i++)
        s[i] = s[i]-Moy;
}
