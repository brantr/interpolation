#include <stdio.h>
#include "interpolation.hpp"

/*! \fn Interpolation(void)
 *  \brief Constructor for Interpolation class */
Interpolation::Interpolation(void)
{
  //set the initialization flag =0 until 
  //initialization is called
  flag_init = 0;
}

/*! \fn Interpolation(void)
 *  \brief Destructor for Interpolation class */
Interpolation::~Interpolation(void)
{
  //free memory before we destroy the interpolation class
  FreeMemory();
}

/*! \fn double y(double x)
 *  \brief Returns y value interpolated at x */
double Interpolation::y(double x)
{
  //make sure we have initialized the interpolation first
  if(!flag_init)	
  {
    printf("ERROR! must initialize interpolant!\n");
    return 0;
  }

  //return the spline interpolant of y(x)
  return gsl_spline_eval(spline_x_y,x,acc_x_y);
}

/*! \fn void ShowTable(void)
 *  \brief Print table to screen */
void Interpolation::ShowTable(void)
{
  //print interpolation table to screen
  for(int i=0;i<n;i++)
    printf("x %e y %e\n",xt[i],yt[i]);
}

/*! \fn void Initialize(double *x_in, double *y_in, int n_in)
 *  \brief Initializes interpolation table */
void Interpolation::Initialize(double *x_in, double *y_in, int n_in)
{

  //remember the number of elements in
  //interpolation table
  n = n_in;

  //remember the x and y arrays
  xt = x_in;
  yt = y_in;

  //produce the gsl interpolations
  acc_x_y    = gsl_interp_accel_alloc();
  spline_x_y = gsl_spline_alloc(gsl_interp_cspline,n);
  gsl_spline_init(spline_x_y,xt,yt,n);
	
  //remember that we have initialized interpolant
  flag_init = 1;
}

/*! \fn void FreeMemory(void)
 *  \brief Frees memory*/
void Interpolation::FreeMemory(void)
{
  //If we have previously initialized,
  //free associated memory
  if(flag_init)
  {
    gsl_spline_free(spline_x_y);
    gsl_interp_accel_free(acc_x_y);
    flag_init = 0;
  }
}
