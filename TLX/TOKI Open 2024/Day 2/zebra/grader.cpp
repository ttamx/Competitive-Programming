#include "zebra.cpp"

#include <cassert>
#include <cstdio>
#include <string>
#include <utility>
#include <vector>

static void wrong_answer(std::string message) {
  printf("WA: %s\n", message.c_str());
  exit(0);
}

namespace tree_helper {

static int N;
static std::vector<std::vector<std::pair<int, int>>> adj;
static std::vector<int> colours;

static void dfs(int node, int parent, int depth) {
  for (auto [child, edge_idx] : adj[node]) {
    if (child == parent) {
      continue;
    }
    colours[edge_idx] = depth % 2;
    dfs(child, node, depth + 1);
  }
}

void find_colouring(int N, int R, std::vector<int> U, std::vector<int> V) {
  tree_helper::N = N;
  adj.assign(N, std::vector<std::pair<int, int>>());
  for (int i = 0; i < N - 1; ++i) {
    adj[U[i]].emplace_back(V[i], i);
    adj[V[i]].emplace_back(U[i], i);
  }

  colours.assign(N - 1, -1);
  dfs(R, -1, 0);
}

}  // namespace tree_helper

static int Q;

int is_zebra(std::vector<int> edges) {
  ++Q;
  if (Q > 500) {
    wrong_answer("Too many queries");
  }

  if (edges.empty()) {
    wrong_answer("No edges given");
  }

  int different = 0;
  for (int edge_idx : edges) {
    if (edge_idx < 0 || edge_idx >= tree_helper::N - 1) {
      wrong_answer("Edge index out of bounds");
    }
    if (tree_helper::colours[edge_idx] != tree_helper::colours[edges[0]]) {
      different = 1;
    }
  }

  return different;
}

int rnd(int x){
  return rand()%x;
}

int main() {
  srand(1928743);
  int tc=0;
  while(true){
  int N, R;
  // assert(2 == scanf("%d %d", &N, &R));
  N=4+rnd(10);
  R=rnd(N);
  printf("test %d\n",++tc);
  cerr << "test " << tc << "\n";
  cerr << N << " " << R << "\n";
  Q=0;

  std::vector<int> U(N - 1), V(N - 1);
  for (int i = 0; i < N - 1; ++i) {
    // assert(2 == scanf("%d %d", &U[i], &V[i]));
    U[i]=i+1,V[i]=rnd(i+1);
    cerr << U[i] << " - " << V[i] << "\n";
  }

  tree_helper::find_colouring(N, R, U, V);

  int guessed_root = find_root(N, U, V);

  printf("%d\n", guessed_root);
  printf("%d\n", Q);  // Number of queries used
  printf("-----\n");
  cerr << "-----\n";
  if(R != guessed_root){
    cerr << "WA\n";
    cerr << R << " != " << guessed_root << "\n";
    return 0;
  }
  }
  return 0;
}
