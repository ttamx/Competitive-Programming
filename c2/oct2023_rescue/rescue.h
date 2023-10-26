#ifndef RESCUE_H_INCLUDED
#define RESCUE_H_INCLUDED

#include <vector>

void init_rescue(int N, int Q, std::vector<int> X, std::vector<int> Y);
int answer_query(int A, int B, int C, int D);
void cancel_request(int R);

#endif
