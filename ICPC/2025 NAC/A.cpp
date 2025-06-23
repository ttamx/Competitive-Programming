#include<bits/stdc++.h>
 
using namespace std;

using ll = long long;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int a,b;
    cin >> a >> b;
    int c=max(a,b);
    vector<int> fa(c+1),fb(c+1);
    auto upd=[&](vector<int> &f,int x){
        for(int i=2;i*i<=x;i++){
            while(x%i==0){
                f[i]++;
                x/=i;
            }
        }
        if(x>1)f[x]++;
    };
    auto pw=[&](ll x,int e){
        ll res=1;
        while(e--)res*=x;
        return res;
    };
    ll n=1,m=1;
    upd(fa,a);
    upd(fb,b);
    for(int v=c;v>=2;v--){
        int d=fa[v]-fb[v];
        if(d==0)continue;
        if(d>0){
            if(d%2){
                n*=pw(v,(d+1)/2);
                upd(fb,v-1);
            }else{
                n*=pw(v,d/2+1);
                m*=v;
            }
        }else{
            d=-d;
            if(d%2){
                m*=pw(v,(d+1)/2);
                upd(fa,v-1);
            }else{
                m*=pw(v,d/2+1);
                n*=v;
            }
        }
    }
    cout << n << " " << m << "\n";
}