#ifndef _FFT_H
#include <complex.h>

void init_fft(void);

int get_result_size(int W1, int W2);

void cc_multiply(double complex *vals1,double complex *vals2, double complex *res,int size);
void c_add(double complex *vals1,double complex *vals2, double weight,int size);

void ifft_doubles(double complex *source, double *target, int size);

void fft1d(const double *row1,int ssize, double complex *result, int rsize);

void fft1d_ccm_ifft1d(double *row1,double *row2, double *result, int W1, int W2);

void fft2d_ccm_ifft2d(double **rows1,double **rows2, double **result, int W1, int W2, int H);

#endif 