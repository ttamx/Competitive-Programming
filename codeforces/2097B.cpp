#include "template.hpp"
#include "data-structure/dsu.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint107;

void runcase(){
    int n,m,k;
    cin >> n >> m >> k;
    DSU dsu(n*m);
    vector<int> cnt(n*m),f(n*m);
    vector<pair<int,int>> a(k+1);
    for(auto &[x,y]:a){
        cin >> x >> y;
        x--,y--;
    }
    auto enc=[&](int x,int y){
        return x*m+y;
    };
    for(int i=0;i<k;i++){
        auto [x1,y1]=a[i];
        auto [x2,y2]=a[i+1];
        if(abs(x1-x2)+abs(y1-y2)!=2){
            cout << 0 << "\n";
            return;
        }
        if(x1==x2){
            int j=dsu.find(enc(x1,(y1+y2)/2));
            f[j]=1;
            cnt[j]++;
        }else if(y1==y2){
            int j=dsu.find(enc((x1+x2)/2,y1));
            f[j]=1;
            cnt[j]++;
        }else{
            int u=dsu.find(enc(x1,y2)),v=dsu.find(enc(x2,y1));
            if(dsu.merge(u,v)){
                f[u]|=f[v];
                cnt[u]+=cnt[v];
            }
            cnt[u]++;
        }
    }
    mint ans=1;
    for(int i=0;i<n*m;i++)if(dsu.find(i)==i){
        int s=dsu.size(i);
        if(cnt[i]>s){
            cout << 0 << "\n";
            return;
        }else if(cnt[i]==s){
            if(!f[i]){
                ans*=2;
            }
        }else{
            ans*=s;
        }
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}