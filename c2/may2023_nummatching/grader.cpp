#include "nummatching.cpp"
#include <cstdio>
#include <cstdlib>

static const int MAX_N = 1010;
static int a[MAX_N];

static int used[MAX_N];
static int has_pair[MAX_N];
static int counter = 0;
static int N, Q;

bool can_match(std::vector<int> B)
{
  counter++;

  if(counter > Q) {
    cerr << counter << "\n";
    printf("too many queries\n");
    exit(0);
  }

  if(B.size() <= 1)
    return false;
  
  for(auto i = B.begin();
      i != B.end(); i++) {
    if((*i < 0) || (*i > N-1)) {
      printf("query set index error\n");
      exit(0);
    }
    
    if(used[*i] != counter) {
      used[*i] = counter;
      int val = a[*i];
      if(val == 0) {
	return true;
      }
      if(has_pair[val] == counter) {
	return true;
      } else {
	has_pair[val] = counter;
      }
    }
  }
  return false;
}

int main()
{
  int dummy;
  dummy = scanf("%d %d",&N, &Q);
  for(int i=0; i<N; i++) {
    dummy = scanf("%d",&a[i]);
    used[i] = has_pair[i] = 0;
  }

  counter = 0;
  auto output = find_matching(N);

  for(auto i = output.begin(); i != output.end(); i++) {
    printf("%d %d\n", (*i)[0], (*i)[1]);
  }

  bool is_correct = true;
  
  for(int i=0; i<N; i++) {
    used[i] = 0;
  }
  if(output.size()!=N/2) {
    printf("incorrect match\n");
    is_correct = false;
  } else {
    for(auto i = output.begin();
	i != output.end();
	i++) {
      if((*i).size() != 2) {
	printf("pair error\n");
	is_correct = false;
      }
      for(auto j = i->begin(); j != i->end(); j++) {
	if((*j < 0) || (*j > N-1)) {
	  printf("pair value error\n");
	  is_correct = false;
	} else {
	  if(used[*j] != 0) {
	    printf("not matching\n");
	    is_correct = false;
	  } else {
	    used[*j] = 1;
	  }
	}
      }
      int v1 = a[(*i)[0]];
      int v2 = a[(*i)[1]];
      if((v1 != 0) && (v2 != 0) && (v1 != v2)) {
	printf("incorrect match\n");
	is_correct = false;
      }
    }
  }
  if(is_correct) {
    printf("correct. %d queries\n", counter);
  }
}
