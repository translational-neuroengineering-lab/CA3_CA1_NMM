/*
 * stimulation.c
 *
 *  Created on: Feb 26, 2015
 *      Author: mconnolly
 */
#include <math.h>
#include <stdio.h>
#include "stimulation_biphasic.h"

float get_stimulation(float t, double *stimulation_ptr){
	float tick_b 	= 0;

	float fp		= stimulation_ptr[0];
	float amp_a		= stimulation_ptr[1];
	float dur_a		= stimulation_ptr[2];
	float amp_b		= stimulation_ptr[3];
	float dur_b		= stimulation_ptr[4];
	float gap_p 	= stimulation_ptr[5];

	tick_b =  fmod(t, 1/fp);

	if(tick_b < dur_a)
		return amp_a;
	else if(tick_b < dur_a + gap_p)
		return 0.0;
	else if(tick_b < dur_a + gap_p + dur_b)
		return amp_b;
	else
		return 0.;


}
