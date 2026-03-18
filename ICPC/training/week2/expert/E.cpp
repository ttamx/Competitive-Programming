#include<bits/stdc++.h>

using namespace std;

using ll = long long;

struct Query{
    int t,l,r;
    bool operator<(const Query &o)const{
        return t<o.t;
    }
};

void solve(){
    string s;
    cin >> s;
    int n=s.size();
    int q;
    cin >> q;
    vector<Query> qr(q);
    for(auto &x:qr){
        cin >> x.t >> x.l >> x.r;
        if(x.t>=n+1){
            if((x.t-n)%2==0){
                x.t=n;
            }else{
                x.t=n+1;
            }
        }
    }
    sort(qr.begin(),qr.end());
    vector<int> fa(n),l(n),r(n);
    for(int i=0;i<n;i++){
        fa[i]=l[i]=r[i]=i;
    }
    int cur=0;
    
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}