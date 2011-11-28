#include "cq.h"

/* cq = circular queue
   n = buffer length
   ri = read index
   wi = write index
   ai = absolute index
   s = buffer */

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

void cq_increment_write_index(int n,int *wi)
{
  *wi += 1;
  if(*wi >= n) {
    *wi = 0;
  }
}
