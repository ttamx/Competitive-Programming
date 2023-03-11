#include <vector>
#include <algorithm>
#include <cstdio>
#include <set>
#include <utility>
#include "goatforget.cpp"

static int n, m, q;
static std::vector<int> g[128];
static int goat;
static int tcount;

int talk_tae(int x){
  if(x < 0 || x >= n){
    printf("Invalid talk\n");
    fflush(stdout);
    exit(0);
  }
  tcount++;
  if(tcount > q){
    printf("Too many talks\n");
    fflush(stdout);
    exit(0);
  }
  auto it = std::lower_bound(g[goat].begin(), g[goat].end(), x);
  int ylo = -1;
  int yhi = -1;
  if(it != g[goat].end()) yhi = *it;
  if(it != g[goat].begin()){
    it--;
    ylo = *it;
  }
  if(ylo != -1 && yhi != -1){
    if(abs(ylo - x) > abs(yhi - x)) return goat = yhi;
    else return goat = ylo;
  }else if(ylo != -1){
    return goat = ylo;
  }else{
    return goat = yhi;
  }
}

int main(){
  scanf("%d%d%d",&n,&m,&q);
  std::set<std::pair<int,int> > template_edges;
  for(int i = 0; i < m; i++){
    int u, v;
    scanf("%d%d",&u,&v);
    if(u > v) std::swap(u, v);
    g[u].push_back(v);
    g[v].push_back(u);
    template_edges.insert(std::make_pair(u, v));
  }
  for(int i = 0; i < n; i++){
    std::sort(g[i].begin(), g[i].end());
  }
  std::vector<std::vector<int> > raw_edges = recover_map(n, m, q);
  if(raw_edges.size() != m){
    printf("Invalid answer\n");
    fflush(stdout);
    exit(0);
  }
  std::set<std::pair<int,int> > edges;
  for(auto e : raw_edges){
    if(e.size() != 2){
      printf("Invalid answer\n");
      fflush(stdout);
      exit(0);
    }
    if(e[0] < 0 || e[0] >= n || e[1] < 0 || e[1] >= n || e[0] == e[1]){
      printf("Invalid answer\n");
      fflush(stdout);
      exit(0);
    }
    std::pair<int, int> edge = std::make_pair(e[0], e[1]);
    if(edge.first > edge.second) std::swap(edge.first, edge.second);
    if(edges.count(edge)){
      printf("Invalid answer\n");
      fflush(stdout);
      exit(0);
    }
    edges.insert(edge);
  }
  if(edges == template_edges){
    printf("Correct answer: %d\n", tcount);
  }else{
    printf("Wrong answer\n");
  }
  return 0;
}