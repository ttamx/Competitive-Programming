#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=5e5+5;

struct DS{
    map<ll,ll> mp;
    void update(ll i,ll v){
        auto it=mp.upper_bound(i);
        if(it==mp.begin()){
            mp[i]=v;
            return;
        }
        it--;
        if(it->second<v){
            mp[i]=v;
            it=mp.find(i);
            auto it2=next(it);
            while(it2!=mp.end()&&it->second>=it2->second){
                it2=mp.erase(it2);
            }
        }
    }
    ll query(ll i){
        auto it=mp.upper_bound(i);
        if(it==mp.begin()){
            return -1;
        }
        return prev(it)->second;
    }
}ds;

int n,c;
ll p,q;
ll dp[N],val[N];
string s;
int cur=0;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> c >> p >> q;
    cin >> s;
    for(int i=1;i<=n;i++){
        if(i>=c)ds.update(val[i-c],dp[i-c]);
        if(s[i-1]=='Y')cur++;
        val[i]=cur*q-i*p;
        dp[i]=max(dp[i-1],ds.query(val[i])+1);
    }
    cout << dp[n];
}