/*
 * get_parameters.c
 *
 *  Created on: Feb 24, 2015
 *      Author: mconnolly
 */

#include "get_parameters.h"

void get_parameters(int model, POPULATION_PARAM *P){
	switch(model){
	    case 1:
	    	inter_ictal(P);
	    	break;
	    case 2:
			pre_ictal(P);
			break;
	    case 3:
			ictal(P);
			break;
	}

}

int inter_ictal(POPULATION_PARAM *P) {
	P->A_CA3 	= 5;
	P->B_CA3 	= 40;
	P->G_CA3 	= 20;

	P->A_CA1 	= 5;
	P->B_CA1 	= 40;
	P->G_CA1 	= 20;

//	P->A_CA3 	= 6.9278;
//	P->B_CA3 	= 3.9451;
//	P->G_CA3 	= 14.874;
//
//	P->A_CA1 	= 6.9278;
//	P->B_CA1 	= 3.9451;
//	P->G_CA1 	= 14.874;

}

int pre_ictal(POPULATION_PARAM *P){
	P->A_CA3 	= 5.5;
	P->B_CA3 	= 7;
	P->G_CA3 	= 20;

	P->A_CA1 	= 5.5;
	P->B_CA1 	= 7;
	P->G_CA1 	= 20;

//	P->A_CA3 	= 5;
//	P->B_CA3 	= 9.6357;
//	P->G_CA3 	= 20.897;
//
//	P->A_CA1 	= 5;
//	P->B_CA1 	= 9.6357;
//	P->G_CA1 	= 20.897;

}

int ictal(POPULATION_PARAM *P){
	P->A_CA3 	= 9.4929;
	P->B_CA3 	= 10.279;
	P->G_CA3 	= 5.156;

	P->A_CA1 	= 9.4929;
	P->B_CA1 	= 10.279;
	P->G_CA1 	= 5.156;
}

