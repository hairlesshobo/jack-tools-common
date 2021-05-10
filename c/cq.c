#include "cq.h"
#include "signal-interpolate.h"

/* cq = circular queue
   n = buffer length
   ri = read index (float)
   wi = write index (int)
   ai = absolute index
   s = buffer */

float cq_index(int n,float ri,int wi)
{
  float ai = ((float)wi - 1.0) - ri;
  if(ai < 0.0) {
    ai += (float)n;
  }
  return ai ;
}

int cq_index_i(int n,int ri,int wi)
{
  int ai = (wi - 1) - ri;
  if(ai < 0) {
    ai += n;
  }
  return ai;
}

float cq_access_i(float *s,int n,int ri,int wi)
{
  int i = cq_index_i(n,ri,wi);
  return s[i];
}

float cq_access(float *s,int n,float ri,int wi)
{
  int i = cq_index(n,ri,wi);
  return signal_interpolate(s,n,i);
}

void cq_increment_write_index(int n,int *wi)
{
  *wi += 1;
  if(*wi >= n) {
    *wi = 0;
  }
}

float cq_update(float *s,int n,float i,int *wi)
{
  float j = s[*wi];
  s[*wi] = i;
  cq_increment_write_index(n,wi);
  return j;
}
