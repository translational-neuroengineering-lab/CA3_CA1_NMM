/*
 * stimulation.h
 *
 *  Created on: Feb 26, 2015
 *      Author: mconnolly
 */

#ifndef STIMULATION_H_
#define STIMULATION_H_



float get_stimulation(int model, float t, int tt, float *simulated_lfp_ca3, float *simulated_lfp_ca1);
float stimulation_control(float t, int tt, float *simulated_lfp_ca3, float *simulated_lfp_ca1);
float stimulation_electrical(float t, int tt, float *simulated_lfp_ca3, float *simulated_lfp_ca1);
float stimulation_optical(float t, int tt, float *simulated_lfp_ca3, float *simulated_lfp_ca1);

#endif /* STIMULATION_H_ */
