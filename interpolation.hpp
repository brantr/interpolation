#ifndef INTERPOLATION_H
#define INTERPOLATION_H
#include <gsl/gsl_spline.h>
class Interpolation
{
  public:
    //number of elements in table
    int n;

    //x-values for interpolation table
    double *xt; 

    //y-values for interpolation table
    double *yt; 

    //initialization flag
    int flag_init;

    //constructor
    Interpolation(void);

    //destructor
    ~Interpolation(void);

    //initializes look up table
    void Initialize(double *x_in, double *y_in, int n_in);

    //print initialization table to screen
    void ShowTable(void);

    //frees memory
    void FreeMemory(void);

    //gsl interpolation pointers
    gsl_spline *spline_x_y;
    gsl_interp_accel *acc_x_y;

    //return the interpolated value
    double y(double x);
};
#endif /*INTERPOLATION_H*/
