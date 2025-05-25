#include "template.hpp"
#include "data-structure/fenwick-tree.hpp"

struct Info{
    int i,x,y;
};

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
    }
    ll ans=0;
    for(int v=1;v<=10;v++){
        if(count(a.begin(),a.end(),v)==0)continue;
        vector<Info> b(n+1);
        int l=0,r=0;
        b[0]={0,0,0};
        for(int i=0;i<n;i++){
            if(a[i]<v)l--,r--;
            else if(a[i]>v)l++,r++;
            else l--,r++;
            b[i+1]={i,l,r};
        }
        auto c=b;
        Fenwick<int> f(2*n+1);
        function<void(int,int)> dnc=[&](int l,int r){
            if(l==r)return;
            int m=(l+r)/2;
            dnc(l,m);
            dnc(m+1,r);
            vector<int> upd;
            for(int i=l,j=m+1,p=l;p<=r;p++){
                if(j>r||(i<=m&&b[i].x>b[j].x)){
                    c[p]=b[i];
                    f.update(b[i].y+n,+1);
                    upd.emplace_back(b[i].y+n);
                    i++;
                }else{
                    c[p]=b[j];
                    ans+=f.query(b[j].y+n-1);
                    j++;
                }
            }
            for(int i=l;i<=r;i++){
                b[i]=c[i];
            }
            for(auto i:upd){
                f.update(i,-1);
            }
        };
        dnc(0,n);
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}