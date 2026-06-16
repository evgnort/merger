#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>

#define PI 3.14159265358979323846
#define MAX_LOG2 16

static double complex fwlens[MAX_LOG2];
static double complex rwlens[MAX_LOG2];
static double complex *wlens[2] = {fwlens,rwlens};
static uint8_t brlut[256];

void init_fft(void)
   {
   uint8_t pos,targ = 128,mask;

   brlut[0] = 0;
   brlut[255] = 255;
   for (pos = 1 ; pos < 255; pos++) 
      {
      brlut[pos] = targ;

      for (mask = 128 ; targ & mask ; mask >>= 1) // 0x80, 0x40 ..
         targ ^= mask; // Проходим по всем установленным битам слева до первого не установленного, сбрасывая их
      targ |= mask; // Устанавливаем первый не установленный
      }

   int len,wnnum;
   for (len = 2,wnnum = 0; wnnum < MAX_LOG2; len <<= 1, wnnum++)
      {
      double angle = 2.0 * PI / len;
      fwlens[wnnum] = cexp(I * -angle);
      rwlens[wnnum] = cexp(I * angle);
      }
   }

static void _shuffle_doubles(const double *source, double complex *target, int size, int ssize)
   {
   int shift = 16 - __builtin_ctz(size);

   int pos;
   for (pos = 0; pos < ssize; pos++) 
      {
      int targ = (brlut[pos & 0xFF] << 8) + brlut[(pos >> 8) & 0xFF];
      target[targ >> shift] = CMPLX(source[pos],0);
      }
   for (; pos < size; pos++) 
      {
      int targ = (brlut[pos & 0xFF] << 8) + brlut[(pos >> 8) & 0xFF];
      target[targ >> shift] = 0;
      }
   }

static void _shuffle_in_place(double complex *target, int size) 
   {
   int shift = 16 - __builtin_ctz(size);

   int pos;
   for (pos = 1; pos < size - 1; pos++) 
      {
      int targ = (brlut[pos & 0xFF] << 8) + brlut[(pos >> 8) & 0xFF];
      targ >>= shift;
      if (pos < targ) 
         {
         double complex temp = target[pos];
         target[pos] = target[targ];
         target[targ] = temp;
         }
      }
   }

static void _fft(double complex *target, int size, int reverse)
   {
   int i,j,step,wnnum;
   for (step = 2,wnnum = 0; step <= size; step <<= 1,wnnum++) 
      {
      double complex wn = wlens[reverse][wnnum];
      for (i = 0; i < size; i += step) 
         {
         double complex w = 1.0;
         for (j = 0; j < step / 2; j++) 
            {
            double complex u = target[i + j];
            double complex t = w * target[i + j + step / 2];
                
            target[i + j] = u + t;
            target[i + j + step / 2] = u - t;
            w *= wn;
            }
         }
      }
   }

void fft_doubles(const double *source, double complex *target, int size, int ssize) 
   {
   _shuffle_doubles(source, target, size, ssize);
   _fft(target, size,0);
   }

void fft_in_place(double complex *target, int size) 
   {
   _shuffle_in_place(target, size);
   _fft(target, size,0);
   }

void ifft_in_place(double complex *target, int size)
   {
   _shuffle_in_place(target, size);
   _fft(target, size,1);
   int i;
   for (i = 0; i < size; i++)
      target[i] /= size;
   }

void ifft_doubles(double complex *source, double *target, int size)
   {
   _shuffle_in_place(source, size);
   _fft(source, size,1);
   int i;
   for (i = 0; i < size; i++)
      target[i] = creal(source[i]) / size;
   }

void cc_multiply(double complex *vals1,double complex *vals2, double complex *res,int size)
   {
   int i;
   for (i = 0; i < size; i++)
      res[i] = vals1[i] * conj(vals2[i]);
   }

void c_add(double complex *vals1,double complex *vals2, double weight,int size)
   {
   int i;
   for (i = 0; i < size; i++)
      vals1[i] = vals1[i] + vals2[i] * weight;
   }

int get_result_size(int W1, int W2)
   {
   int W = (W1 > W2) ? W1 : W2;

   // Ближайшая степень двойки >= запрошенного размера оси времени * 2
   int lzW = __builtin_clz(W) + (__builtin_popcount(W) == 1);
   return 2 << (32 - lzW);
   }

void fft1d(const double *row1,int ssize, double complex *result, int rsize)
   {
   fft_doubles(row1,result, rsize, ssize);
   }

void fft1d_ccm_ifft1d(double *row1,double *row2, double *result, int W1, int W2)
   {
   int tpsizeW = get_result_size(W1,W2);

   double complex *row1c = (double complex *)calloc(tpsizeW,sizeof(double complex));
   double complex *row2c = (double complex *)calloc(tpsizeW,sizeof(double complex));

   fft_doubles(row1,row1c, tpsizeW, W1);
   fft_doubles(row2,row2c, tpsizeW, W2);

   cc_multiply(row1c,row2c,row1c,tpsizeW);

   ifft_doubles(row1c, result, tpsizeW);

   free(row1c);
   free(row2c);
   }

void fft2d_ccm_ifft2d(double **rows1,double **rows2, double **result, int W1, int W2, int H)
   {
   int i,j;

   int tpsizeW = get_result_size(W1,W2);

   // Ближайшая степень двойки >= запрошенного размера по вертикали
   int lzH = __builtin_clz(H) + (__builtin_popcount(H) == 1);
   int tpsizeH = 1 << (32 - lzH);

   double complex *rows1c[tpsizeH];
   double complex *rows2c[tpsizeH];

   for (i = 0; i < H; i++)
      {   
      rows1c[i] = (double complex *)calloc(tpsizeW,sizeof(double complex));
      rows2c[i] = (double complex *)calloc(tpsizeW,sizeof(double complex));

      fft_doubles(rows1[i],rows1c[i], tpsizeW, W1);
      fft_doubles(rows2[i],rows2c[i], tpsizeW, W2);
      }

   for (; i < tpsizeH; i++)
      {   
      rows1c[i] = (double complex *)calloc(tpsizeW,sizeof(double complex));
      rows2c[i] = (double complex *)calloc(tpsizeW,sizeof(double complex));
      }

   double complex *res1 = (double complex *)calloc(tpsizeH * tpsizeW,sizeof(double complex));
   double complex *res2 = (double complex *)calloc(tpsizeH * tpsizeW,sizeof(double complex));

   double complex *res = (double complex *)calloc(tpsizeH * tpsizeW,sizeof(double complex));

   for (j = 0; j < tpsizeW; j++)
      {
      for (i = 0; i < H; i++)
         {
         res1[j * tpsizeH + i] = rows1c[i][j];
         res2[j * tpsizeH + i] = rows2c[i][j];
         }

      fft_in_place(&res1[j*tpsizeH], tpsizeH);
      fft_in_place(&res2[j*tpsizeH], tpsizeH);
      }

   cc_multiply(res1,res2,res,tpsizeH * tpsizeW);

   for (j = 0; j < tpsizeW; j++)
      ifft_in_place(&res[j * tpsizeH], tpsizeH);
    
   for (i = 0; i < tpsizeH; i++)
      {
      for (j = 0; j < tpsizeW; j++)
         rows1c[i][j] = res[j*tpsizeH + i];

      ifft_doubles(rows1c[i], result[i], tpsizeW);
      free(rows1c[i]);
      free(rows2c[i]);
      }
      
   free(res1);
   free(res2);
   free(res);
   }


