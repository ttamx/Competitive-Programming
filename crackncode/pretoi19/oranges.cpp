#include<bits/stdc++.h>

using namespace std;

typedef double db;

const int N=1e5+5;

int n;
map<db,vector<db>> res;
map<db,int> dp;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    for(int i=1;i<=n;i++){
        db a,b,c,d;
        cin >> a >> b >> c >> d;
        db l=a/b;
        db r=c/d;
        if(l>r)swap(l,r);
        res[r].emplace_back(l);
    }
    dp[-1]=0;
    for(auto [i,v]:res){
        dp[i]=prev(dp.lower_bound(i))->second;
        for(auto j:v){
            dp[i]=max(dp[i],prev(dp.lower_bound(j))->second+1);
        }
    }
    cout << n-dp.rbegin()->second;
}