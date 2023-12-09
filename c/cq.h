#ifndef _COMMON_CQ_H
#define _COMMON_CQ_H

float cq_index(int n, float ri, int wi);
int cq_index_i(int n, int ri, int wi);
float cq_access_i(float *s, int n, int ri, int wi);
float cq_access(float *s, int n, float ri, int wi);
void cq_increment_write_index(int n, int *wi);
float cq_update(float *s, int n, float i, int *wi);

#endif
