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
*/

#ifndef FUNCTIONSC_H_
#define FUNCTIONSC_H_

typedef struct
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

	float v0;
	float e0;
	float r;

	float meanP;
	float sigmaP;
	float coefMultP;

	float n_1;
	float n_2;

	float stim_freq;
}	POPULATION_PARAM; // Vector of model parameters

void saveAsTxt(char *fileName, float **data, int nbC, int nbL, float fEch, int withTime);
//------------------------------------------------------------------
void saveAsBin(char *fileName, float *data, int nbL);
//------------------------------------------------------------------
void euler(float *y, float *dydx, int n, float x, float h, float *yout, POPULATION_PARAM *P, float stimulation_CA3, float stimulation_CA1);
//------------------------------------------------------------------
float sigm(float v, POPULATION_PARAM *P);
//------------------------------------------------------------------
float p(POPULATION_PARAM *P);
//------------------------------------------------------------------
float GaussianNoise(float sigma,float m);
//------------------------------------------------------------------
void CA3_CA1_ODEs(float t, float *y, float *dydx, POPULATION_PARAM *P, float stimulation_CA3, float stimulation_CA1);
//------------------------------------------------------------------
float * vector(int n);
//------------------------------------------------------------------
void free_vector(float *v);
//------------------------------------------------------------------
void centre_signal(float *s,int Nbp);

#endif /* FUNCTIONSC.H */
