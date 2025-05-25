#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"
#include "data-structure/dsu.hpp"

using mint = mint107;

void runcase(){
    int n;
    cin >> n;
    DSU dsu(2*n);
    vector<int> nxt(2*n,-1);
    for(int i=0;i<n;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        nxt[u]=v;
        dsu.merge(u,v);
    }
    mint ans=1;
    vector<int> id(2*n,-1);
    for(int i=0;i<2*n;i++){
        if(nxt[i]==-1||id[i]!=-1)continue;
        int j=i;
        while(j!=-1&&id[j]==-1){
            id[j]=i;
            j=nxt[j];
        }
        if(j!=-1&&id[j]==i){
            int cnt=0;
            int st=j;
            do{
                cnt++;
                j=nxt[j];
            }while(j!=st);
            if(cnt>1){
                ans*=2;
            }
        }
    }
    for(int i=0;i<2*n;i++){
        if(nxt[i]==-1){
            ans*=dsu.size(i);
        }
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}