#include "template.hpp"
#include "data-structure/dsu.hpp"

void runcase(){
    int n,m;
    cin >> n >> m;
    DSU dsu(n);
    vector<vector<int>> f(11,vector<int>(n));
    while(m--){
        int a,d,k;
        cin >> a >> d >> k;
        a--;
        int l=a,r=a+d*k;
        f[d][l]++;
        f[d][r]--;
    }
    for(int d=1;d<=10;d++){
        for(int i=d;i<n;i++){
            f[d][i]+=f[d][i-d];
        }
        for(int i=0;i+d<n;i++){
            if(f[d][i]){
                dsu.merge(i,i+d);
            }
        }
    }
    int ans=0;
    for(int i=0;i<n;i++){
        if(i==dsu.find(i)){
            ans++;
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