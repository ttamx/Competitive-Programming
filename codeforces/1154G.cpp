#include<bits/stdc++.h>

using namespace std;

const int N=1e7+5;

int n;
vector<int> f[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++){
        int x;
        cin >> x;
        f[x].emplace_back(i);
    }
    long long ans=1e18;
    int u,v;
    for(int i=1;i<N;i++){
        int x=0,y=0,xi,yi;
        for(int j=i;j<N;j+=i){
            for(auto idx:f[j]){
                if(x==0){
                    x=j;
                    xi=idx;
                }else{
                    y=j;
                    yi=idx;
                    break;
                }
            }
            if(y>0)break;
        }
        if(y==0)continue;
        long long res=1ll*x*y/i;
        if(res<ans){
            ans=res;
            u=xi;
            v=yi;
        }
    }
    if(u>v)swap(u,v);
    cout << u << ' ' << v;
}