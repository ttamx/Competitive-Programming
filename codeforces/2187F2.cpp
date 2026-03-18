#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint998;

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n),b(n),pos(n);
    for(auto &x:a)cin >> x,x--;
    for(auto &x:b)cin >> x,x--;
    for(int i=0;i<n;i++)pos[b[i]]=i;
    vector<uint32_t> hsh(n);
    for(auto &x:hsh)x=rng();
    vector<uint32_t> f(n+1),g(n+1);
    for(int i=0;i<n;i++)f[i+1]=f[i]^hsh[a[i]];
    for(int i=0;i<n;i++)g[i+1]=g[i]^hsh[b[i]];
    mint ans=1;
    function<void(int,int,int,int,int)> rec=[&](int l1,int r1,int l2,int r2,int dep){
        if(l1==r1)return;
        if(a[l1]==b[l2]){
            ans*=dep;
            rec(l1+1,r1,l2+1,r2,dep+1);
            return;
        }
        for(int i=l1;i<r1;){
            int j=pos[a[i]];
            int p=0;
            for(int s=1;i+s<=r2;s++){
                if((f[i]^f[i+s])==(g[j]^g[j+s])){
                    p=s;
                }
            }
            rec(i,i+p,j,j+p,dep);
            i+=p;
        }
    };
    rec(0,n,0,n,1);
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}