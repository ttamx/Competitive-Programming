#include<bits/stdc++.h>

using namespace std;

const int N=2e5;

int n;
int l[N],r[N],k[N],vl[N],vr[N],ans[N];
map<int,vector<int>> mp;
vector<tuple<int,int,int>> vec;

struct Fenwick{
    int t[N];
    void update(int i,int v){
        for(;i<N;i+=i&-i)t[i]+=v;
    }
    int query(int i){
        int res=0;
        for(;i>0;i-=i&-i)res+=t[i];
        return res;
    }
    int query(int l,int r){
        return l<=r?query(r)-query(l-1):0;
    }
    void clear(){
        for(int i=1;i<=n;i++)t[i]=0;
    }
}f;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> l[i] >> r[i] >> k[i];
        vl[i]=l[i],vr[i]=r[i];
        mp[l[i]].emplace_back(i);
        vec.emplace_back(r[i]-l[i],1,i);
        vec.emplace_back(k[i],0,i);
    }
    sort(vl+1,vl+n+1);
    sort(vr+1,vr+n+1);
    sort(vec.rbegin(),vec.rend());
    for(auto &[key,val]:mp){
        for(auto i:val){
            int id=lower_bound(vr+1,vr+n+1,l[i]+k[i])-vr;
            ans[i]=f.query(id,n);
        }
        for(auto i:val){
            int id=lower_bound(vr+1,vr+n+1,r[i])-vr;
            f.update(id,1);
        }
    }
    f.clear();
    for(auto [s,t,i]:vec){
        if(t){
            int id=lower_bound(vl+1,vl+n+1,l[i])-vl;
            f.update(id,1);
        }else{
            int idl=lower_bound(vl+1,vl+n+1,l[i])-vl;
            int idr=upper_bound(vl+1,vl+n+1,r[i]-k[i])-vl-1;
            ans[i]+=f.query(idl,idr)-1;
        }
    }
    for(int i=1;i<=n;i++)cout << ans[i] << "\n";
}