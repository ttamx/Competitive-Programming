#include"trilib.h"
#include<bits/stdc++.h>

using namespace std;

int n;
vector<int> lower,upper;
deque<int> hull;

bool cmp(int x,int y){
    return is_clockwise(1,x,y);
}

void upd(int x){
    while(hull.size()>1&&!is_clockwise(hull.end()[-2],hull.back(),x))hull.pop_back();
    hull.emplace_back(x);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    n=get_n();
    for(int i=3;i<=n;i++){
        if(is_clockwise(1,2,i))upper.emplace_back(i);
        else lower.emplace_back(i);
    }
    sort(lower.begin(),lower.end(),cmp);
    sort(upper.begin(),upper.end(),cmp);
    upd(1);
    for(auto x:lower)upd(x);
    upd(2);
    for(auto x:upper)upd(x);
    int res=hull.size();
    for(int i=0;i<res;i++){
        upd(hull[0]);
        hull.pop_front();
    }
    give_answer(hull.size());
}