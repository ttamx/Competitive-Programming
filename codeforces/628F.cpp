#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,b,q;
    cin >> n >> b >> q;
    vector<pair<int,int>> a(q);
    for(auto &[x,y]:a)cin >> x >> y;
    a.emplace_back(b,n);
    sort(a.begin(),a.end());
    auto calc=[&](int l,int r,int v){
        return (r-v+5)/5-(l-v+5)/5;
    };
    for(int mask=1;mask<32;mask++){
        int last=0,tot=0,cnt=0;
        for(auto [x,y]:a){
            int cur=0;
            for(int i=0;i<5;i++){
                if(mask>>i&1){
                    cur+=calc(last,x,i);
                }
            }
            cur=min(cur,y-cnt);
            if(cur<0){
                cout << "unfair\n";
                exit(0);
            }
            tot+=cur;
            last=x;
            cnt=y;
        }
        if(tot<__builtin_popcount(mask)*n/5){
            cout << "unfair\n";
            exit(0);    
        }
    }
    cout << "fair\n";
}