#include<bits/stdc++.h>

using namespace std;

using ull = uint64_t;

const int N=5e5+5;

mt19937_64 rng(time(0));

int q,cur;
ull dp[N];
map<int,ull> mp;
map<ull,int> inv;

ull my_hash(int x){
    if(mp.count(x))return mp[x];
    ull hsh=rng();
    mp[x]=hsh;
    inv[hsh]=x;
    return hsh;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> q;
    while(q--){
        int op;
        cin >> op;
        if(op==1){
            int m,k;
            cin >> m >> k;
            cur++;
            if(k&1){
                dp[cur]=my_hash(m);
            }
        }else if(op==2){
            int x,y;
            cin >> x >> y;
            dp[++cur]=dp[x]^dp[y];
        }else if(op==3){
            int x,m,k;
            cin >> x >> m >> k;
            dp[++cur]=dp[x];
            if(k&1){
                dp[cur]^=my_hash(m);
            }
        }else{
            int x;
            cin >> x;
            cout << inv[dp[x]] << "\n";
        }
    }
}