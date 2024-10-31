#ifndef __PARTICLE_H_INCLUDED__
#define __PARTICLE_H_INCLUDED__

void init(int N);
void generateParticle(int L,int R,int P);
long long countSize(int L,int R);
int bestPartition(int L,int R);

#endif