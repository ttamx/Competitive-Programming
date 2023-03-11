#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    long long s;
    cin >> n >> s;
    long long prev=1e9,pret;
    for(int i=1;i<=n;++i){
        long long v,t;
        cin >> t >> v;
        if(v<=prev){
            cout << 0 << '\n';
        }else{
            long long dist=prev*(t-pret);
            if(dist>=s){
                cout << 0 << '\n';
            }else{
                long long newv=prev+(dist*prev/(s-dist));
                newv=min(newv,v);
                cout << v-newv << '\n';
                v=newv;
            }
        }
        prev=v;
        pret=t;
    }
}