/*
 * get_parameters.h
 *
 *  Created on: Feb 24, 2015
 *      Author: mconnolly
 */

#ifndef GET_PARAMETERS_H_
#define GET_PARAMETERS_H_

#include "functionsC.h"


void get_parameters(int model, POPULATION_PARAM *P);

int inter_ictal(POPULATION_PARAM *P);
int pre_ictal(POPULATION_PARAM *P);
int ictal(POPULATION_PARAM *P);

#endif /* GET_PARAMETERS_H_ */
