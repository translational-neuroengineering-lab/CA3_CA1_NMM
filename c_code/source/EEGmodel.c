#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "functionsC.h"
#include "stimulation.h"
#include "get_parameters.h"
#include "mex.h"

void run_eeg_model(double final_time,
		float **simulated_lfp_ca3_ptr, float **simulated_lfp_ca1_ptr,
		int *n_frames_ptr, double fs, double *state)

{
    /*-------------- Variables --------------------------*/
    int 	nb_fonc; // Number of ODEs
    float 	*y, *yout, *dydx; // State vector and derivatives
    float 	*simulated_lfp_ca3, *simulated_lfp_ca1, *simulated_lfp_ca3_clean, *simulated_lfp_ca1_clean;
    float 	SamplingFreq; // Text Field for sampling frequency
    int 	n_frames;
    float 	t = 0., dt; // time, time step
    int 	tt;
    float 	stimulation_CA3, stimulation_CA1;

    POPULATION_PARAM * P; // Vector of parameters

    // Initialization of the Vector of parameters
    nb_fonc = 22; // Number of ODEs
    y 		= (float *)calloc(nb_fonc, sizeof(float)); // State vector
    yout 	= (float *)calloc(nb_fonc, sizeof(float)); // State vector. Output
    dydx 	= (float *)calloc(nb_fonc, sizeof(float)); // Vector of derivatives
    P 		= (POPULATION_PARAM *)malloc(1 * sizeof(POPULATION_PARAM)); // Vector of parameters

    /////////
    // CA3 //
    /////////
//    P->A_CA3 	= A_CA3; // EXC Parameter (excitation)
//    P->B_CA3 	= B_CA3; // SDI Parameter (slow dendritic inhibition)
//    P->G_CA3 	= G_CA3; // FSI Parameter (fast somatic inhibition)

    // Non Dynamic model parameters. Default values
    P->a_CA3 	= 100.; // time constants of EPSPs and IPSPs
    P->b_CA3 	= 30.;
    P->g_CA3 	= 350.;

    P->C1_CA3 	= 1.; // Connectivity parameters (to be multiplied by P->C=135)
    P->C2_CA3 	= .8;
    P->C3_CA3 	= .25;
    P->C4_CA3 	= .25;
    P->C5_CA3 	= .3;
    P->C6_CA3 	= .1;
    P->C7_CA3 	= .8;

    P->C_CA3 	= 135.;

    P->C1_CA3 *= P->C_CA3;
    P->C2_CA3 *= P->C_CA3;
    P->C3_CA3 *= P->C_CA3;
    P->C4_CA3 *= P->C_CA3;
    P->C5_CA3 *= P->C_CA3;
    P->C6_CA3 *= P->C_CA3;
    P->C7_CA3 *= P->C_CA3;

    /////////
    // CA1 //
    /////////
//    P->A_CA1 	= A_CA1; // EXC Parameter (excitation)
//    P->B_CA1 	= B_CA1; // SDI Parameter (slow dendritic inhibition)
//    P->G_CA1 	= G_CA1; // FSI Parameter (fast somatic inhibition)

    // Non Dynamic model parameters. Default values
    P->a_CA1 	= 100.; // time constants of EPSPs and IPSPs
    P->b_CA1 	= 30.;
    P->g_CA1 	= 350.;

    P->C1_CA1 	= 1.; // Connectivity parameters (to be multiplied by P->C=135)
    P->C2_CA1 	= .8;
    P->C3_CA1 	= .25;
    P->C4_CA1 	= .25;
    P->C5_CA1 	= .3;
    P->C6_CA1 	= .1;
    P->C7_CA1 	= .8;

    P->C_CA1 	= 135.;

    P->C1_CA1 *= P->C_CA1;
    P->C2_CA1 *= P->C_CA1;
    P->C3_CA1 *= P->C_CA1;
    P->C4_CA1 *= P->C_CA1;
    P->C5_CA1 *= P->C_CA1;
    P->C6_CA1 *= P->C_CA1;
    P->C7_CA1 *= P->C_CA1;

    P->v0 	= 6.; // Sigmoid parameters
    P->e0 	= 2.5;
    P->r 	= 0.56;

    P->meanP 		= 3.; // Input noise parameters
    P->sigmaP 		= 1.;
    P->coefMultP 	= 30.;

    P->C_schaffer 	= 100;
    P->C_feedback 	= 100;

    // Simulation parameters
    final_time 		= final_time + 1; // result is shorted by 1 second at begining to eliminate simulation artifact
    SamplingFreq 	= fs; // user-defined (typical: 512 Hz)
    dt 				= 1./SamplingFreq; 	// period
    n_frames 		= final_time / dt; 	// number of samples

    // Allocation: the array for simulated EEG
    simulated_lfp_ca3 	= (float *)calloc(n_frames, sizeof(float));
    simulated_lfp_ca1 	= (float *)calloc(n_frames, sizeof(float));

    //////////////
    // This is the top level loop of the algorithm
    // The system state y is sent to euler() which updates
    // yout.
    //////////////

    for(tt=0;tt<n_frames;tt++){
//    	get_parameters(state[tt], P);
    	get_parameters(3, P);

    	stimulation_CA3 = 0;//get_stimulation(0, t, tt, simulated_lfp_ca3, simulated_lfp_ca1);
    	stimulation_CA1 = 0;//get_stimulation(0, t, tt, simulated_lfp_ca3, simulated_lfp_ca1);

    	euler(y,dydx,nb_fonc,t,dt,yout,P, stimulation_CA3, stimulation_CA1);
        y = yout;
        t += dt;
        simulated_lfp_ca3[tt] = y[2]-y[4]-y[6];
        simulated_lfp_ca1[tt] = y[12]-y[14]-y[16];


    }
//    centre_signal(simulated_lfp, n_frames); // remove DC offset as in actual EEG (hardware filter on Acquisition Systems)

    simulated_lfp_ca3_clean 	= (float *)calloc(n_frames-SamplingFreq, sizeof(float));
    simulated_lfp_ca1_clean 	= (float *)calloc(n_frames-SamplingFreq, sizeof(float));
    for(tt=SamplingFreq;tt<n_frames;tt++){
    	simulated_lfp_ca3_clean[tt-(int)SamplingFreq] = simulated_lfp_ca3[tt]; //Remove the simulation artifact at the beginning
    	simulated_lfp_ca1_clean[tt-(int)SamplingFreq] = simulated_lfp_ca1[tt]; //Remove the simulation artifact at the beginning
    }

    n_frames = n_frames - SamplingFreq;
    *simulated_lfp_ca3_ptr = simulated_lfp_ca3_clean;
    *simulated_lfp_ca1_ptr = simulated_lfp_ca1_clean;
    *n_frames_ptr = n_frames;

    // Free memory
    free(y);
//    free(yout);
    free(dydx);
//
//    free(simulated_lfp_ca3);
//    free(simulated_lfp_ca1);

//    free(simulated_lfp_ca3_clean);
//    free(simulated_lfp_ca1_clean);
//    sizeof(simulatedLFP);
}
