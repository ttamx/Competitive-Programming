#include "template.hpp"
#include "data-structure/fenwick-tree.hpp"

struct Info{
    int x,y,z,i;
    bool operator<(const Info &o)const{
        if(x!=o.x)return x<o.x;
        if(y!=o.y)return y<o.y;
        if(z!=o.z)return z<o.z;
        return i<o.i;
    }
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    vector<int> p(n),s(n),b(n),inc(m),pref(m);
    for(auto &x:p)cin >> x;
    for(auto &x:s)cin >> x;
    for(auto &x:b)cin >> x;
    for(auto &x:inc)cin >> x;
    for(auto &x:pref)cin >> x;
    vector<Info> a;
    for(int i=0;i<n;i++){
        a.emplace_back(Info{p[i]+b[i],p[i]-b[i],-s[i],-1});
    }
    for(int i=0;i<m;i++){
        a.emplace_back(Info{inc[i]+pref[i],inc[i]-pref[i],-inc[i],i});
    }
    vector<int> vals;
    for(auto e:a){
        vals.emplace_back(e.z);
    }
    sort(vals.begin(),vals.end());
    vals.erase(unique(vals.begin(),vals.end()),vals.end());
    for(auto &e:a){
        e.z=lower_bound(vals.begin(),vals.end(),e.z)-vals.begin();
    }
    sort(a.begin(),a.end());
    auto aa=a;
    vector<int> ans(m);
    Fenwick<int> f(vals.size());
    auto rec=[&](auto &&self,int l,int r)->void {
        if(l==r)return;
        int m=(l+r)/2;
        self(self,l,m);
        self(self,m+1,r);
        vector<int> upd;
        for(int i=l,j=m+1,p=l;p<=r;p++){
            if(j>r|(i<=m&&a[i].y<=a[j].y)){
                if(a[i].i==-1){
                    f.update(a[i].z,+1);
                    upd.emplace_back(a[i].z);
                }
                aa[p]=a[i++];
            }else{
                if(a[j].i!=-1){
                    ans[a[j].i]+=f.query(a[j].z);
                }
                aa[p]=a[j++];
            }
        }
        for(int i=l;i<=r;i++){
            a[i]=aa[i];
        }
        for(auto i:upd){
            f.update(i,-1);
        }
    };
    rec(rec,0,a.size()-1);
    for(auto x:ans){
        cout << x << " ";
    }
    cout << "\n";
}