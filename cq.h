#ifndef _COMMON_CQ_H
#define _COMMON_CQ_H

int cq_index_i(int n,int ri,int wi);
float cq_access_i(float *s,int n,int ri,int wi);
void cq_increment_write_index(int n,int *wi);

#endif
