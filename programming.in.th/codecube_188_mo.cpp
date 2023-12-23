#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;
const int K=350;

int n,q,k;
int a[N],l[N],r[N],c[N],cnt[N],ans[N];
vector<int> v[K];
map<int,int> mp;
int idx=0;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    k=sqrt(n)+1;
    for(int i=1;i<=n;i++)cin >> a[i],mp[a[i]]=0;
    for(auto &[x,y]:mp)y=++idx;
    for(int i=1;i<=n;i++)a[i]=mp[a[i]];
    for(int i=1;i<=q;i++){
        cin >> l[i] >> r[i] >> c[i];
        auto it=mp.find(c[i]);
        if(it==mp.end())continue;
        c[i]=it->second;
        v[r[i]/k].emplace_back(i);
    }
    int st=1,ed=0;
    for(int i=0;i<=k;i++){
        sort(v[i].begin(),v[i].end(),[&](int x,int y){
            return l[x]<l[y];
        });
        for(auto j:v[i]){
            while(st<l[j])cnt[a[st++]]--;
            while(st>l[j])cnt[a[--st]]++;
            while(ed<r[j])cnt[a[++ed]]++;
            while(ed>r[j])cnt[a[ed--]]--;
            ans[j]=cnt[c[j]];
        }
    }
    for(int i=1;i<=q;i++)cout << ans[i] << '\n';
}