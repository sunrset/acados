// system
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
// acados
#include "acados_c/ocp_nlp_interface.h"
#include "acados/utils/external_function_generic.h"
#include "acados_c/external_function_interface.h"
// mex
#include "mex.h"



// casadi functions for the model
#include "ocp_model.h"



void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
	{

//	mexPrintf("\nin sim_impl_ext_fun_create\n");

	// sizeof(long long) == sizeof(void *) = 64 !!!
	int ii;
	long long *ptr;



	/* RHS */

	// C_ocp

	// dims
	ptr = (long long *) mxGetData( mxGetField( prhs[0], 0, "dims" ) );
	ocp_nlp_dims *dims = (ocp_nlp_dims *) ptr[0];

	// C_ocp_ext_fun

	// model
	int np = 0;
	if(mxGetField( prhs[2], 0, "dim_np" )!=NULL) // TODO bool
		{
		np = mxGetScalar( mxGetField( prhs[2], 0, "dim_np" ) );
		}
	// TODO bool instead !!!
	char *param_phi = mxArrayToString( mxGetField( prhs[2], 0, "dyn_param_phi" ) );


	// opts

//	bool sens_forw = mxGetScalar( mxGetField( prhs[3], 0, "sens_forw" ) );
//	mexPrintf("\n%d\n", sens_forw);
	char *sim_method = mxArrayToString( mxGetField( prhs[3], 0, "sim_method" ) );
//	mexPrintf("\n%s\n", sim_method);


	int N = dims->N;



	/* LHS */

	/* copy existing fields */

//	plhs[0] = mxCreateSharedDataCopy(prhs[1]);
	plhs[0] = mxDuplicateArray(prhs[1]);



	/* populate new fields */

	external_function_casadi *ext_fun_ptr;
	external_function_param_casadi *ext_fun_param_ptr;

	mxArray *tmp_mat;

	// TODO templetize the casadi function names !!!
	if(!strcmp(param_phi, "true")) // TODO bool
		{
		// disc_phi_fun_jac
		ext_fun_param_ptr = (external_function_param_casadi *) malloc(N*sizeof(external_function_param_casadi));
		for(ii=0; ii<N; ii++)
			{
			external_function_param_casadi_set_fun(ext_fun_param_ptr+ii, &ocp_model_dyn_disc_phi_fun_jac);
			external_function_param_casadi_set_work(ext_fun_param_ptr+ii, &ocp_model_dyn_disc_phi_fun_jac_work);
			external_function_param_casadi_set_sparsity_in(ext_fun_param_ptr+ii, &ocp_model_dyn_disc_phi_fun_jac_sparsity_in);
			external_function_param_casadi_set_sparsity_out(ext_fun_param_ptr+ii, &ocp_model_dyn_disc_phi_fun_jac_sparsity_out);
			external_function_param_casadi_set_n_in(ext_fun_param_ptr+ii, &ocp_model_dyn_disc_phi_fun_jac_n_in);
			external_function_param_casadi_set_n_out(ext_fun_param_ptr+ii, &ocp_model_dyn_disc_phi_fun_jac_n_out);
			external_function_param_casadi_create(ext_fun_param_ptr+ii, np);
			}
		// populate output struct
		tmp_mat  = mxCreateNumericMatrix(1, 1, mxINT64_CLASS, mxREAL);
		ptr = mxGetData(tmp_mat);
		ptr[0] = (long long) ext_fun_param_ptr;
		mxSetField(plhs[0], 0, "dyn_disc_phi_fun_jac", tmp_mat);

		// disc_phi_fun_jac_hess
		ext_fun_param_ptr = (external_function_param_casadi *) malloc(N*sizeof(external_function_param_casadi));
		for(ii=0; ii<N; ii++)
			{
			external_function_param_casadi_set_fun(ext_fun_param_ptr+ii, &ocp_model_dyn_disc_phi_fun_jac_hess);
			external_function_param_casadi_set_work(ext_fun_param_ptr+ii, &ocp_model_dyn_disc_phi_fun_jac_hess_work);
			external_function_param_casadi_set_sparsity_in(ext_fun_param_ptr+ii, &ocp_model_dyn_disc_phi_fun_jac_hess_sparsity_in);
			external_function_param_casadi_set_sparsity_out(ext_fun_param_ptr+ii, &ocp_model_dyn_disc_phi_fun_jac_hess_sparsity_out);
			external_function_param_casadi_set_n_in(ext_fun_param_ptr+ii, &ocp_model_dyn_disc_phi_fun_jac_hess_n_in);
			external_function_param_casadi_set_n_out(ext_fun_param_ptr+ii, &ocp_model_dyn_disc_phi_fun_jac_hess_n_out);
			external_function_param_casadi_create(ext_fun_param_ptr+ii, np);
			}
		// populate output struct
		tmp_mat  = mxCreateNumericMatrix(1, 1, mxINT64_CLASS, mxREAL);
		ptr = mxGetData(tmp_mat);
		ptr[0] = (long long) ext_fun_param_ptr;
		mxSetField(plhs[0], 0, "dyn_disc_phi_fun_jac_hess", tmp_mat);
		}
	else
		{
		// disc_phi_fun_jac
		ext_fun_ptr = (external_function_casadi *) malloc(N*sizeof(external_function_casadi));
		for(ii=0; ii<N; ii++)
			{
			external_function_casadi_set_fun(ext_fun_ptr+ii, &ocp_model_dyn_disc_phi_fun_jac);
			external_function_casadi_set_work(ext_fun_ptr+ii, &ocp_model_dyn_disc_phi_fun_jac_work);
			external_function_casadi_set_sparsity_in(ext_fun_ptr+ii, &ocp_model_dyn_disc_phi_fun_jac_sparsity_in);
			external_function_casadi_set_sparsity_out(ext_fun_ptr+ii, &ocp_model_dyn_disc_phi_fun_jac_sparsity_out);
			external_function_casadi_set_n_in(ext_fun_ptr+ii, &ocp_model_dyn_disc_phi_fun_jac_n_in);
			external_function_casadi_set_n_out(ext_fun_ptr+ii, &ocp_model_dyn_disc_phi_fun_jac_n_out);
			external_function_casadi_create(ext_fun_ptr+ii);
			}
		// populate output struct
		tmp_mat  = mxCreateNumericMatrix(1, 1, mxINT64_CLASS, mxREAL);
		ptr = mxGetData(tmp_mat);
		ptr[0] = (long long) ext_fun_ptr;
		mxSetField(plhs[0], 0, "dyn_disc_phi_fun_jac", tmp_mat);

		// disc_phi_fun_jac_hess
		ext_fun_ptr = (external_function_casadi *) malloc(N*sizeof(external_function_casadi));
		for(ii=0; ii<N; ii++)
			{
			external_function_casadi_set_fun(ext_fun_ptr+ii, &ocp_model_dyn_disc_phi_fun_jac_hess);
			external_function_casadi_set_work(ext_fun_ptr+ii, &ocp_model_dyn_disc_phi_fun_jac_hess_work);
			external_function_casadi_set_sparsity_in(ext_fun_ptr+ii, &ocp_model_dyn_disc_phi_fun_jac_hess_sparsity_in);
			external_function_casadi_set_sparsity_out(ext_fun_ptr+ii, &ocp_model_dyn_disc_phi_fun_jac_hess_sparsity_out);
			external_function_casadi_set_n_in(ext_fun_ptr+ii, &ocp_model_dyn_disc_phi_fun_jac_hess_n_in);
			external_function_casadi_set_n_out(ext_fun_ptr+ii, &ocp_model_dyn_disc_phi_fun_jac_hess_n_out);
			external_function_casadi_create(ext_fun_ptr+ii);
			}
		// populate output struct
		tmp_mat  = mxCreateNumericMatrix(1, 1, mxINT64_CLASS, mxREAL);
		ptr = mxGetData(tmp_mat);
		ptr[0] = (long long) ext_fun_ptr;
		mxSetField(plhs[0], 0, "dyn_disc_phi_fun_jac_hess", tmp_mat);
		}
	
	return;

	}




