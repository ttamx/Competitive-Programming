#include "forbiddenwords.cpp"
#include <bits/stdc++.h>

unsigned int SEED = 1373858591;

mt19937 rng(SEED);

const int MAX_M = 100;

static int wmap[MAX_M];

static bool check_words(int M, int N, int K,
			std::vector<std::pair<int,int>> words,
			std::vector<std::pair<int,int>> F)
{
  std::set<std::pair<int,int>> Fset;
  std::set<std::pair<int,int>> used;

  if(words.size() > K) {
    std::cout << "Too many words (" << words.size() << ")\n";
    return false;
  }
  
  for(std::pair<int,int> fw : F) {
    Fset.insert(fw);
    Fset.insert(std::make_pair(fw.second, fw.first));
  }
  
  for(std::pair<int,int> w : words) {
    if(used.find(w) != used.end()) {
      std::cout << "Dupplicated words\n";
      std::cout << w.first << " " << w.second << std::endl;
      return false;
    }
    if(Fset.find(w) != Fset.end()) {
      std::cout << "Forbidden words\n";
      return false;
    }
    if((w.first < 0) || (w.first >= M) ||
       (w.second < 0) || (w.second >= M)) {
      std::cout << "Word out of range\n";
      return false;
    } else {
      used.insert(w);
      used.insert(std::make_pair(w.second, w.first));
    }
  }
  return true;
}

static void transform_words(int M, std::vector<std::pair<int,int>>& words, int is_permute)
{
  for(int w=0; w<M; w++) {
    wmap[w] = w;
  }
  
  if(is_permute) {
    std::shuffle(wmap, wmap+M,rng);
  }
  
  for(int i=0; i<words.size(); i++) {
    words[i].first = wmap[words[i].first];
    words[i].second = wmap[words[i].second];
    if(rng() % 2 == 0) {
      int tmp = words[i].first;
      words[i].first = words[i].second;
      words[i].second = tmp;
    }
  }

  std::shuffle(words.begin(), words.end(),rng);
}

int main()
{
  int R;
  int N, M, K;
  long long X;
  std::vector<std::pair<int,int>> F;

  std::srand(SEED);
  
  std::cin >> R;
  
  for(int rr = 0; rr < R; rr++) {
    std::cin >> M >> N >> K >> X;

    F.clear();
    for(int i=0; i<N; i++) {
      int a,b;
      std::cin >> a >> b;
      F.push_back(std::make_pair(a,b));
    }

    std::vector<std::pair<int,int>> words = alice(M,N,K,X,F);

    if(!check_words(M, N, K, words, F)) {
      std::cout << "Incorrect words\n";
      return 0;
    } 
  
    transform_words(M, words, true);

    long long output = bob(M, words);
    
    if(output != X) {
      std::cout << "Incorrect\n";
      return 0;
    }
  }

  std::cout << "Correct\n";
  return 0;
}
