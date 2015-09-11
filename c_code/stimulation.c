/*
 * stimulation.c
 *
 *  Created on: Feb 26, 2015
 *      Author: mconnolly
 */
#include <math.h>
#include <stdio.h>
#include "stimulation.h"

float get_stimulation(int model, float t, int tt, float *simulated_lfp_ca3, float *simulated_lfp_ca1){
    printf("ASDASDSDASDASD\n");

	float stim;
	stim = 0;
	switch(model){
		case 0:
			stim = stimulation_control(t, tt, simulated_lfp_ca3, simulated_lfp_ca1);
			break;
		case 1:
			stim = stimulation_electrical(t, tt, simulated_lfp_ca3, simulated_lfp_ca1);
			break;
		case 2:
			stim = stimulation_optical(t, tt, simulated_lfp_ca3, simulated_lfp_ca1);
			break;
	}
	return stim;
}

float stimulation_control(float t, int tt, float *simulated_lfp_ca3, float *simulated_lfp_ca1){
	return 0;
}
float stimulation_electrical(float t, int tt, float *simulated_lfp_ca3, float *simulated_lfp_ca1){
	float pw;
	float intensity;
	float stim_freq;

	pw 			= 0.01;
	intensity 	= 100;
	stim_freq 	= 35;

	if (t > 4 && t < 8){

		if(fmod(t,1./stim_freq) < pw){

			if(fmod(t,1./stim_freq) < pw/2){
				return -1*intensity;
			}else{
				return 1*intensity;
			}
		}else{
			return 0.0;
		}
	}
	return 0.0;
}



float stimulation_optical(float t, int tt, float *simulated_lfp_ca3, float *simulated_lfp_ca1){
	float pw;
	float intensity;
	float stim_freq = 35;

	pw 			= 0.01;
	intensity 	= 100;
	stim_freq 	= 35;

	if (t > 4 && t < 8){

		if(fmod(t,1./stim_freq) < pw){
			return -1*intensity;

		}else{
			return 0.0;
		}
	}
	return 0.0;
}
