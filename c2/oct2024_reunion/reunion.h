#ifndef REUNION_H_INCLUDED
#define REUNION_H_INCLUDED

#include <vector>

namespace goat {
void goat_init(int N, int M, std::vector<int> U, std::vector<int> V,
               std::vector<int> W, int u);

int goat_move(int u);
} // namespace goat

namespace lemon {
void lemon_init(int N, int M, std::vector<int> U, std::vector<int> V,
                std::vector<int> W, int u);

int lemon_move(int u);
} // namespace lemon

#endif
