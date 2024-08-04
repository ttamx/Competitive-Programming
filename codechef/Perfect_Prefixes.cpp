#include "template.hpp"
#include "data-structure/fenwick-tree.hpp"

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n),val(n);
    for(auto &x:a)cin >> x,x--;
    Fenwick<int> f(n);
    int ans=0;
    for(int i=0;i<n;i++){
        f.update(a[i],1);
        val[i]=f.query(i);
        if(val[i]==i+1)ans++;
    }
    vector<int> b(n);
    for(int i=1;i<n;i++){
        int x=val[i-1];
        if(x==i)b[i]--;
        if(a[i-1]<=i-1)x--;
        if(a[i]<=i-1)x++;
        if(x==i)b[i]++;
    }
    int mx=0;
    for(int t=1;t<=2;t++){
        int mn=0;
        for(int i=t;i<n;i+=2){
            if(i>=2)b[i]+=b[i-2];
            mx=max(mx,b[i]-mn);
            mn=min(mn,b[i]);
        }
    }
    cout << ans+mx << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}