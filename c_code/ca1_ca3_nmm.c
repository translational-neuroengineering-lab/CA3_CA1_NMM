#include "mex.h"
#include "EEGmodel.h"
void
mexFunction(int nlhs,mxArray *plhs[],int nrhs,const mxArray *prhs[])
{

	int 		i;
    float		A_CA3, B_CA3, G_CA3, A_CA1, B_CA1, G_CA1, C_schaffer, C_feedback;
    double 		*parameter_ptr;

    double 		*final_time_ptr;
    double 		final_time;
    double 		*fs_ptr;
    double 		fs;

    int 		n_frames;
    float		*simulated_lfp_ca3_ptr;
    float		*simulated_lfp_ca1_ptr;
    double 		*lfp_out_ca3;
    double 		*lfp_out_ca1;

    double 		*state;
//    parameter_ptr 	= mxGetPr(prhs[0]);
//
//    A_CA3 = parameter_ptr[0];
//    B_CA3 = parameter_ptr[1];
//    G_CA3 = parameter_ptr[2];
//
//    A_CA1 = parameter_ptr[3];
//    B_CA1 = parameter_ptr[4];
//    G_CA1 = parameter_ptr[5];
//
//    C_schaffer = parameter_ptr[6];
//    C_feedback = parameter_ptr[7];

//    printf("CA3_A = %f\n",A_CA3 );
//    printf("CA3_B = %f\n",B_CA3 );
//    printf("CA3_G = %f\n",G_CA3 );
//
//    printf("CA1_A = %f\n",A_CA1 );
//    printf("CA1_B = %f\n",B_CA1 );
//    printf("CA1_G = %f\n",G_CA1 );
//
//    printf("C_schaffer = %f\n",C_schaffer );
//    printf("C_feedback = %f\n",C_feedback );

    final_time_ptr 	= mxGetPr(prhs[0]);
    final_time 		= final_time_ptr[0];

    fs_ptr			= mxGetPr(prhs[1]);
    fs 				= fs_ptr[0];

    state 			= mxGetPr(prhs[2]);
    run_eeg_model(final_time, &simulated_lfp_ca3_ptr, &simulated_lfp_ca1_ptr,
    				&n_frames, fs, state);

	plhs[0]			= mxCreateDoubleMatrix(n_frames,1,mxREAL);
	plhs[1]			= mxCreateDoubleMatrix(n_frames,1,mxREAL);

	lfp_out_ca3		= mxGetPr(plhs[0]);
	lfp_out_ca1		= mxGetPr(plhs[1]);
	for ( i = 0; i < n_frames; i++){
		lfp_out_ca3[i]	= (double)simulated_lfp_ca3_ptr[i];
		lfp_out_ca1[i]	= (double)simulated_lfp_ca1_ptr[i];
	}
}
