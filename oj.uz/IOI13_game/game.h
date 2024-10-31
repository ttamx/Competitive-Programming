#ifndef __GAME_H__
#define __GAME_H__

#ifdef __cplusplus
extern "C" {
#endif

void init(int R, int C);
void update(int P, int Q, long long K);
long long calculate(int P, int Q, int U, int V);

#ifdef __cplusplus
}
#endif

#endif /* __GAME_H__ */
