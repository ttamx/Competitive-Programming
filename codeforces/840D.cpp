#include<bits/stdc++.h>

using namespace std;

const int N=300005;
const int K=5;

int n,q;
int a[N];
int ql[N],qr[N],qk[N];
int ans[N];
int cnt[N];
vector<int> pos[N];
array<pair<int,int>,K> suf[N],pre[N];

int query(int l,int r,int v){
    return upper_bound(pos[v].begin(),pos[v].end(),r)-lower_bound(pos[v].begin(),pos[v].end(),l);
}

void dnc(int l,int r,vector<int> qi){
    if(qi.empty())return;
    if(l==r){
        for(auto i:qi)ans[i]=a[l];
        return;
    }
    int m=(l+r)/2;
    {
        array<pair<int,int>,K> cur{};
        for(int i=m;i>=l;i--){
            cnt[a[i]]++;
            bool ok=false;
            for(int j=0;j<K;j++){
                if(cur[j].second==-a[i]){
                    cur[j].first++;
                    ok=true;
                    break;
                }
            }
            if(!ok)cur[K-1]=max(cur[K-1],{cnt[a[i]],-a[i]});
            sort(cur.rbegin(),cur.rend());
            suf[i]=cur;
        }
        for(int i=l;i<=m;i++)cnt[a[i]]=0;
    }
    {
        array<pair<int,int>,K> cur{};
        for(int i=m+1;i<=r;i++){
            cnt[a[i]]++;
            bool ok=false;
            for(int j=0;j<K;j++){
                if(cur[j].second==-a[i]){
                    cur[j].first++;
                    ok=true;
                    break;
                }
            }
            if(!ok)cur[K-1]=max(cur[K-1],{cnt[a[i]],-a[i]});
            sort(cur.rbegin(),cur.rend());
            pre[i]=cur;
        }
        for(int i=m+1;i<=r;i++)cnt[a[i]]=0;
    }
    vector<int> qli,qri;
    for(auto i:qi){
        if(qr[i]<=m)qli.emplace_back(i);
        else if(ql[i]>m)qri.emplace_back(i);
        else{
            ans[i]=n+1;
            int s=qr[i]-ql[i]+1;
            for(auto [c,v]:suf[ql[i]])if(query(ql[i],qr[i],-v)*qk[i]>s)ans[i]=min(ans[i],-v);
            for(auto [c,v]:pre[qr[i]])if(query(ql[i],qr[i],-v)*qk[i]>s)ans[i]=min(ans[i],-v);
        }
    }
    dnc(l,m,qli);
    dnc(m+1,r,qri);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    for(int i=1;i<=n;i++){
        cin >> a[i];
        pos[a[i]].emplace_back(i);
    }
    for(int i=1;i<=q;i++)cin >> ql[i] >> qr[i] >> qk[i];
    vector<int> qi(q);
    iota(qi.begin(),qi.end(),1);
    dnc(1,n,qi);
    for(int i=1;i<=q;i++)cout << (ans[i]>n?-1:ans[i]) << "\n";
}