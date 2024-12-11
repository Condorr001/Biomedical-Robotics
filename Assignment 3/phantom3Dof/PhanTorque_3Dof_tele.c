/*PhanTorque_3Dof_tele.c. Code of the s-function part of Phan3DoF Library.
 *Copyright (C) <2013>  <Carlos Aldana carlos.aldana@upc.edu>
 *This program is free software: you can redistribute it and/or modify
 *it under the terms of the GNU General Public License as published by
 *the Free Software Foundation, either version 3 of the License, or
 *(at your option) any later version.
 
 *This program is distributed in the hope that it will be useful,
 *but WITHOUT ANY WARRANTY; without even the implied warranty of
 *MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *GNU General Public License for more details.
 
 *You should have received a copy of the GNU General Public License
 *along with this program.  If not, see <http://www.gnu.org/licenses/>.
 
 *You must specify the S_FUNCTION_NAME as the name of your S-function
 *(i.e. replace sfuntmpl_basic with the name of your S-function).
 */

#define S_FUNCTION_NAME  PhanTorque_3Dof_tele
#define S_FUNCTION_LEVEL 2

/*
 * Need to include simstruc.h for the definition of the SimStruct and
 * its associated macro definitions.
 */

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

#include "simstruc.h"

/*Open haptics libreries */

#include <HD/hd.h>
#include <HD/hdScheduler.h>
#include <HDU/hduError.h>
#include <HDU/hduVector.h>


/* PHANTOM name and variables declarations (Global Variables)*/

char *Haptic1_Name;
char *Haptic2_Name;

float tau1[3];
float tau2[3];

HDSchedulerHandle gCallbackHandle = 0;

HHD hHD1;
HHD hHD2;

/* Data Structure. */
struct Sensable{
    hduVector3Dd jointAngles;
    hduVector3Dd position;
    hduVector3Dd jointTorques; 
} Haptic1, Haptic2;

/*=============================================================================*/

/*====================*
 * S-function methods *
 *====================*/

/* Function: mdlInitializeSizes ===============================================
 * Abstract:
 *    The sizes information is used by Simulink to determine the S-function
 *    block's characteristics (number of inputs, outputs, states, etc.).
 */
static void mdlInitializeSizes(SimStruct *S)
{
    /*Parameters of the sfunction block (Name of Haptics)*/
    

    const mxArray* temp1 = ssGetSFcnParam(S,0);
    const mxArray* temp2 = ssGetSFcnParam(S,1);
    
    Haptic1_Name = mxArrayToString(temp1);
    Haptic2_Name = mxArrayToString(temp2);

    
    ssSetNumSFcnParams(S, 2);  /* Number of expected parameters */
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S))
    {
        return; /* Parameter mismatch will be reported by Simulink */
    }
    
    ssSetNumSampleTimes(S, 1);
    
    // Inputs of the sfunction block (Definition)
    
    ssSetNumInputPorts(S, 2);
    ssSetInputPortWidth(S, 0, 3);
    ssSetInputPortWidth(S, 1, 3);
    
    ssSetInputPortRequiredContiguous(S, 0, false);
    ssSetInputPortDirectFeedThrough(S, 0, 0);
    ssSetInputPortRequiredContiguous(S, 1, false);
    ssSetInputPortDirectFeedThrough(S, 1, 0);
    
    // Outputs of the sfunction block (Definition)
    
    ssSetNumOutputPorts(S, 4);
    ssSetOutputPortWidth(S, 0, 3);  //Haptic 1 Joints (q1)
    ssSetOutputPortWidth(S, 1, 3);  //Haptic 1 Position (x1,y1,z1)
    ssSetOutputPortWidth(S, 2, 3);  //Haptic 2 Joints (q2)
    ssSetOutputPortWidth(S, 3, 3);  //Haptic 2 Position (x2,y2,z2)
    
  
     /*Simulink */
    ssSetNumIWork(S, 0);
    ssSetNumRWork(S, 0);
    ssSetNumPWork(S, 0);
    ssSetNumModes(S, 0);
    ssSetNumNonsampledZCs(S, 0);
    ssSetOptions(S, 0);
}

/*=============================================================================*/
/* Functions for Phantom =========================================*/

/******************************************************************
 * Sets Force To Haptic.
 ******************************************************************/

HDCallbackCode HDCALLBACK SchedulerCallback(void *pUserData)
{
    float a;
    HDErrorInfo error;

    Haptic1.jointTorques[0] = 0;
    Haptic1.jointTorques[1] = 0;
    Haptic1.jointTorques[2] = 0;
    
    Haptic2.jointTorques[0] = 0;
    Haptic2.jointTorques[1] = 0;
    Haptic2.jointTorques[2] = 0;
    
    hdBeginFrame(hHD1);//-------------------------------------------------------
    
    //Read Haptic1 State
    hdGetDoublev(HD_CURRENT_JOINT_ANGLES, Haptic1.jointAngles);
    hdGetDoublev(HD_CURRENT_POSITION, Haptic1.position);
    
    hdBeginFrame(hHD2);//----------------------------------
    
    //Read Haptic2 State
    hdGetDoublev(HD_CURRENT_JOINT_ANGLES, Haptic2.jointAngles);
    hdGetDoublev(HD_CURRENT_POSITION, Haptic2.position);
   
    //Set Haptic2 torques (tau2)
    
    a=1000; //to convert from Nm to mNm
    Haptic2.jointTorques[0] = a*tau2[0];
    Haptic2.jointTorques[1] = a*tau2[1];
    Haptic2.jointTorques[2] = a*tau2[2];
        
    hdSetDoublev(HD_CURRENT_JOINT_TORQUE,Haptic2.jointTorques);
    
    hdEndFrame(hHD2);//------------------------------------
    
    hdMakeCurrentDevice(hHD1);
    
    //Set Haptic1 torques (tau1)
    
    a=1000; //to convert from Nm to mNm
    Haptic1.jointTorques[0] = a*tau1[0];
    Haptic1.jointTorques[1] = a*tau1[1];
    Haptic1.jointTorques[2] = a*tau1[2];
    
    hdSetDoublev(HD_CURRENT_JOINT_TORQUE,Haptic1.jointTorques);
    
    hdEndFrame(hHD1);//---------------------------------------------------------
    
    return HD_CALLBACK_CONTINUE;
    
    if (HD_DEVICE_ERROR(error = hdGetError()))
    {
        hduPrintError(stderr, &error, "Error while commanding control values");
        if (hduIsSchedulerError(&error))
        {
            return HD_CALLBACK_DONE;
        }
    }
    
    return HD_CALLBACK_CONTINUE;
} 

/*=============================================================================*/

/* Function: mdlInitializeSampleTimes =========================================
 * Abstract:
 *    This function is used to specify the sample time(s) for your
 *    S-function. You must register the same number of sample times as
 *    specified in ssSetNumSampleTimes.
 */
static void mdlInitializeSampleTimes(SimStruct *S) 
{    
    ssSetSampleTime(S, 0, CONTINUOUS_SAMPLE_TIME);
    ssSetOffsetTime(S, 0, 0.0);
}

/*=============================================================================*/

/* Function: mdlStart ==================================================
 * Abstract:
 *    This function is called once at start of model execution. If you
 *    have states that should be initialized once, this is the place
 *    to do it.
 */

#define MDL_START

static void mdlStart(SimStruct *S)
{
    /*Initialize Device and Scheduler */
    
    mexPrintf("Local:\t");
    mexPrintf(Haptic1_Name);
    mexPrintf("\t Started \n");
    mexPrintf("Remote:\t");
    mexPrintf(Haptic2_Name);
    mexPrintf("\t Started \n");

    hHD1 = hdInitDevice(Haptic1_Name);
    hHD2 = hdInitDevice(Haptic2_Name);

    gCallbackHandle = hdScheduleAsynchronous(
            SchedulerCallback, 0, HD_MAX_SCHEDULER_PRIORITY);
    
    hdEnable(HD_FORCE_OUTPUT);
	hdMakeCurrentDevice(hHD1);
	hdEnable(HD_FORCE_OUTPUT);
    
    hdStartScheduler();
 
}

/*=============================================================================*/

/* Function: mdlUpdate ======================================================
 * Abstract:
 *    This function is called once for every major integration time step.
 *    Discrete states are typically updated here, but this function is useful
 *    for performing any tasks that should only take place once per
 *    integration step.
 */

#define MDL_UPDATE  /* Change to #undef to remove function */
#if defined(MDL_UPDATE)
static void mdlUpdate(SimStruct *S, int_T tid)
{
    InputRealPtrsType  u0 = ssGetInputPortRealSignalPtrs(S,0);
    InputRealPtrsType  u1 = ssGetInputPortRealSignalPtrs(S,1);

    tau1[0] = *u0[0];
    tau1[1] = *u0[1];
    tau1[2] = *u0[2];
    
    tau2[0] = *u1[0];
    tau2[1] = *u1[1];
    tau2[2] = *u1[2];

}
#endif /* MDL_UPDATE */

/*=============================================================================*/
/* Function: mdlDerivatives =================================================
 * Abstract:
 *    In this function, you compute the S-function block's derivatives.
 *    The derivatives are placed in the derivative vector, ssGetdX(S).
 */

#define MDL_DERIVATIVES  /* Change to #undef to remove function */
#if defined(MDL_DERIVATIVES)
static void mdlDerivatives(SimStruct *S)
{
}
#endif /* MDL_DERIVATIVES */

/*=============================================================================*/
/* Function: mdlOutputs =======================================================
 * Abstract:
 *    In this function, you compute the outputs of your S-function
 *    block.
 */

static void mdlOutputs(SimStruct *S, int_T tid)
{
    int i;
    
    real_T       *y1_joint_angle = ssGetOutputPortSignal(S, 0);
    real_T       *y1_position = ssGetOutputPortSignal(S, 1);
    real_T       *y2_joint_angle = ssGetOutputPortSignal(S, 2);
    real_T       *y2_position = ssGetOutputPortSignal(S, 3);
   
    
    for (i=0; i<3; i++)
    {
        y1_joint_angle[i] = Haptic1.jointAngles[i];
        y1_position[i] = Haptic1.position[i]*.001;
        y2_joint_angle[i] = Haptic2.jointAngles[i];
        y2_position[i] = Haptic2.position[i]*.001;
    }
    
}
/*=============================================================================*/

/* Function: mdlTerminate =====================================================
 * Abstract:
 *    In this function, you should perform any actions that are necessary
 *    at the termination of a simulation.  For example, if memory was
 *    allocated in mdlStart, this is the place to free it.
 */

static void mdlTerminate(SimStruct *S)
{
    hdStopScheduler();
    hdUnschedule(gCallbackHandle);
    hdDisableDevice(hHD1);
    hdDisableDevice(hHD2);
    mexPrintf("Local:\t");
    mexPrintf(Haptic1_Name);
    mexPrintf("\tStopped\n");
    mexPrintf("Remote:\t");
    mexPrintf(Haptic2_Name);
    mexPrintf("\tStopped\n");
}


/*=============================*
 * Required S-function trailer *
 *=============================*/

#ifdef  MATLAB_MEX_FILE    /* Is this file being compiled as a MEX-file? */
#include "simulink.c"      /* MEX-file interface mechanism */
#else
#include "cg_sfun.h"       /* Code generation registration function */
#endif
