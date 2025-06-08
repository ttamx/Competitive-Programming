#include "abcd.cpp"
#include <cassert>
#include <cstdio>
#include <vector>
using namespace std;

int _n;
vector<int>_answer_key;
int _exam_call = 0;

void _invalid_input(){
  printf("invalid_input!!!");
}

int exam(std::vector<char>_C){
  _exam_call++;
  if(_C.size() != _n) {
    _invalid_input();
    return -1;
  }

  int count = 0;
  for(int i = 0; i < _n; i++) {
    if(_C[i] == 'A' || _C[i] == 'B' || _C[i] == 'C' || _C[i] == 'D') {
      if(_C[i] == _answer_key[i])count++;
    }
    else {
      _invalid_input();
      return -1;
    }
  }
  return count;
}

int main(){

  assert(scanf("%d",&_n)==1);
  string s;
  cin >> s;
  assert(s.size()==_n);
  for(int i = 0; i < _n; i++) {
    _answer_key.push_back(s[i]);
  }

  vector<char> _ret = abcd(_n);
  bool all_correct = true;
  if(_ret.size() != _n) {
    printf("invalid return vector size\n");
    return 0;
  }
  for(int i = 0; i < _n; i++) {
    if(_ret[i] != _answer_key[i]) all_correct = false;
    printf("%c ",_ret[i]);
  }
  printf("\n");

  if(all_correct) {
    printf("Correct answer: You call function %d times.\n",_exam_call);
  }
  else {
    printf("incorrect answer\n");
  }
}
