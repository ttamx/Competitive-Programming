#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int,int>;

const int N=2e5+5;

int n;
int p[N];
ll w[N],tot[N];
map<ll,ll> pq[N];
ll val[N];
vector<int> adj[N];
ll leaf=0;
bool sub4=true;

void init(vector<int> P,vector<int> W){
    n=P.size();
    for(int i=0;i<n;i++){
        p[i]=P[i];
        w[i]=W[i];
        if(w[i]!=1){
            sub4=false;
        }
        if(i>0){
            adj[p[i]].emplace_back(i);
        }
    }
    for(int i=0;i<n;i++){
        if(adj[i].empty()){
            leaf++;
        }
    }
}

ll query(int L,int R){
    if(sub4){
        ll ans=leaf*L;
        ans+=max(leaf*L-R,0LL);
        return ans;
    }
    ll ans=0;
    for(int i=n-1;i>=0;i--){
        pq[i].clear();
        val[i]=0;
        tot[i]=0;
        for(auto j:adj[i]){
            val[i]+=val[j];
            tot[i]+=tot[j];
            if(pq[j].size()>pq[i].size()){
                swap(pq[i],pq[j]);
            }
            for(auto &[x,y]:pq[j]){
                pq[i][x]+=y;
            }
        }
        if(val[i]==0){
            val[i]=L;
            ans+=L*w[i];
            continue;
        }
        pq[i][w[i]]+=val[i];
        tot[i]+=val[i];
        for(auto it=pq[i].begin();val[i]>R;){
            ll used=min(it->second,val[i]-R);
            val[i]-=used;
            tot[i]-=used;
            ans+=it->first*used;
            it->second-=used;
            if(it->second==0){
                it=pq[i].erase(it);
            }
        }
        ll can=val[i]-L;
        for(auto it=pq[i].end();tot[i]>can;){
            it--;
            ll used=min(it->second,tot[i]-can);
            tot[i]-=used;
            it->second-=used;
            if(it->second==0){
                it=pq[i].erase(it);
            }
        }
    }
    return ans;
}
