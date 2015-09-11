/*
 * EEGmodel.h
 *
 *  Created on: Jan 30, 2015
 *      Author: mconnolly
 */

#ifndef EEGMODEL_H_
#define EEGMODEL_H_


void run_eeg_model(double final_time,
		float **simulated_lfp_ca3_ptr, float **simulated_lfp_ca1_ptr,
		int *n_frames_ptr, double fs, double *state);

#endif /* EEGMODEL_H_ */
