#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int n;

bool ask(int p,int r){
    p=min(p,n);
    if(r>=p)return false;
    cout << "? " << p << " " << r << endl;
    int res;
    cin >> res;
    return res;
}

int solve1(int mask,ll cur){
    if(mask+cur>=n)return mask;
    if(ask(cur*2,mask+cur))return solve1(mask+cur,cur*2);
    else return solve1(mask,cur*2);
}

pair<int,int> solve2(int mask,ll cur){
    bool q0=ask(cur*2,mask);
    bool q1=ask(cur*2,mask+cur);
    if(q0&&q1)return {solve1(mask,cur*2),solve1(mask+cur,cur*2)};
    if(q0)return solve2(mask,cur*2);
    if(q1)return solve2(mask+cur,cur*2);
    assert(false);
    return {-1,-1};
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--){
        cin >> n;
        auto [x,y]=solve2(0,1);
        cout << "! " << x << " " << y << endl;
    }
}