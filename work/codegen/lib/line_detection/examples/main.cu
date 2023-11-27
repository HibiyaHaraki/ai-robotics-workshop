//
// File: main.cu
//
// GPU Coder version                    : 2.1
// CUDA/C/C++ source code generated on  : 11-Nov-2021 11:08:16
//

/*************************************************************************/
/* This automatically generated example CUDA main file shows how to call */
/* entry-point functions that MATLAB Coder generated. You must customize */
/* this file for your application. Do not modify this file directly.     */
/* Instead, make a copy of this file, modify it, and integrate it into   */
/* your development environment.                                         */
/*                                                                       */
/* This file initializes entry-point function arguments to a default     */
/* size and value before calling the entry-point functions. It does      */
/* not store or use any values returned from the entry-point functions.  */
/* If necessary, it does pre-allocate memory for returned values.        */
/* You can use this file as a starting point for a main function that    */
/* you can deploy in your application.                                   */
/*                                                                       */
/* After you copy the file, and before you deploy it, you must make the  */
/* following changes:                                                    */
/* * For variable-size function arguments, change the example sizes to   */
/* the sizes that your application requires.                             */
/* * Change the example values of function arguments to the values that  */
/* your application requires.                                            */
/* * If the entry-point functions return values, store these values or   */
/* otherwise use them as required by your application.                   */
/*                                                                       */
/*************************************************************************/

// Include Files
#include "main.h"
#include "line_detection.h"
#include "line_detection_terminate.h"

// Function Declarations
static void argInit_3xd1280xd720_uint8_T(unsigned char result_data[],
                                         int result_size[3]);

static unsigned char argInit_uint8_T();

static void main_line_detection();

// Function Definitions
//
// Arguments    : unsigned char result_data[]
//                int result_size[3]
// Return Type  : void
//
static void argInit_3xd1280xd720_uint8_T(unsigned char result_data[],
                                         int result_size[3])
{
  // Set the size of the array.
  // Change this size to the value that the application requires.
  result_size[0] = 3;
  result_size[1] = 2;
  result_size[2] = 2;
  // Loop over the array to initialize each element.
  for (int idx0{0}; idx0 < 3; idx0++) {
    for (int idx1{0}; idx1 < 2; idx1++) {
      for (int idx2{0}; idx2 < 2; idx2++) {
        // Set the value of the array element.
        // Change this value to the value that the application requires.
        result_data[(idx0 + 3 * idx1) + 6 * idx2] = argInit_uint8_T();
      }
    }
  }
}

//
// Arguments    : void
// Return Type  : unsigned char
//
static unsigned char argInit_uint8_T()
{
  return 0U;
}

//
// Arguments    : void
// Return Type  : void
//
static void main_line_detection()
{
  static unsigned char I_data[2764800];
  static unsigned char Iout_data[2764800];
  float predictedPosNorm[2];
  int I_size[3];
  int Iout_size[3];
  // Initialize function 'line_detection' input arguments.
  // Initialize function input argument 'I'.
  argInit_3xd1280xd720_uint8_T(I_data, I_size);
  // Call the entry-point 'line_detection'.
  line_detection(I_data, I_size, predictedPosNorm, Iout_data, Iout_size);
}

//
// Arguments    : int argc
//                char **argv
// Return Type  : int
//
int main(int, char **)
{
  // The initialize function is being called automatically from your entry-point
  // function. So, a call to initialize is not included here. Invoke the
  // entry-point functions.
  // You can call entry-point functions multiple times.
  main_line_detection();
  // Terminate the application.
  // You do not need to do this more than one time.
  line_detection_terminate();
  return 0;
}

//
// File trailer for main.cu
//
// [EOF]
//
