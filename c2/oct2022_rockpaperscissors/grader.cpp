#include "rockpaperscissors.h"
#include <cassert>
#include <cstdio>
#include <vector>
#include <set>
using namespace std;
int n,t;
vector<int>person;
int tournament_call = 0, tournament_cost = 0;

void invalid_input(){
  printf("invalid_input!!!");
  cerr << "\n";
}

int tournament(std::vector<int>person_index){
  int count_rps[] = {0,0,0,0}, max_win = 0,num_person = 0;
  std::set<int>same_index_check;
  for(int i=0;i<person_index.size();i++){
    if(person_index[i] < 0 || person_index[i] > 3*n){
      for(auto x:person_index)cerr << x << " ";
      invalid_input();
      return -1;
    }
    same_index_check.insert(person_index[i]);
    count_rps[person[person_index[i]]]++;
    num_person++;
  }
  if(same_index_check.size() != person_index.size()){
      for(auto x:person_index)cerr << x << " ";
    invalid_input();
    return -1;
  }
  if(same_index_check.size()<3){
      for(auto x:person_index)cerr << x << " ";
    invalid_input();
    return -1;
  }
  tournament_call++;
  tournament_cost += person_index.size()*person_index.size();
  if(count_rps[0] >= 1)max_win = std::max(max_win, num_person-1);
  if(count_rps[1] >= 1)max_win = std::max(max_win, count_rps[3]);
  if(count_rps[2] >= 1)max_win = std::max(max_win, count_rps[1]);
  if(count_rps[3] >= 1)max_win = std::max(max_win, count_rps[2]);
  return max_win;
}

int main(){
  int q;
  assert(scanf("%d",&q)==1);
  while(q--){
    person.clear();
    bool isonecheater = false;
    tournament_call = 0, tournament_cost = 0;
    int count_rock = 0, count_paper = 0, count_scissors = 0, cheater_position = -1;
    int ans_cheater = 0;
    assert(scanf("%d %d", &n,&t) == 2);
    if(t==0){
      for(int i=0,x;i<(n*3)+1;i++){
        assert(scanf("%d", &x) == 1);
        person.push_back(x);
        if(x==0){
          if(isonecheater || i == 0){
            invalid_input();
            return 0;
          }
          isonecheater = true;
          cheater_position = i;
        }
        else if(x==1)count_rock++;
        else if(x==2)count_paper++;
        else if(x==3)count_scissors++;
        else{
          invalid_input();
          return 0;
        }
      }
      if(!isonecheater||count_paper!=n||count_rock!=n||count_scissors!=n){
        invalid_input();
        return 0;
      }
      ans_cheater=find_cheater1(n);
      if(ans_cheater != cheater_position)printf("Wrong Answer\n");
      else printf("Correct Answer: You call function %d times.\n",tournament_call);
    }
    else if(t==1){
      for(int i=0,x;i<(n*3)+1;i++){
        assert(scanf("%d", &x) == 1);
        person.push_back(x);
        if(x==0){
          if(isonecheater || i == 0){
            invalid_input();
            return 0;
          }
          isonecheater = true;
          cheater_position = i;
        }
        else if(x==1)count_rock++;
        else if(x==2)count_paper++;
        else if(x==3)count_scissors++;
        else{
          invalid_input();
          return 0;
        }
      }
      if(!isonecheater||count_paper!=n||count_rock!=n||count_scissors!=n){
        invalid_input();
        return 0;
      }
      ans_cheater=find_cheater2(n);
      cerr << ans_cheater;
      if(ans_cheater != cheater_position)printf("Wrong Answer\n");
      else printf("Correct Answer: Your total tournament cost is %d.\n",tournament_cost);
    }
  }
}
