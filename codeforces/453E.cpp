#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=1e5+5;
const int LG=17;
const int INF=INT_MAX/2;

int n,q;
int s[N],lim[N],rate[N],step[N];
map<int,pair<int,int>> mp;

struct WaveletTree{
    int m,log;
    int vals[N],mid[LG];
    pair<int,int> b[N];
    int cumsum[LG][N];
    ll sum_lim[LG][N],sum_rate[LG][N];
    void build(){
        for(int i=0;i<n;i++)vals[i]=step[i+1];
        sort(vals,vals+n);
        m=unique(vals,vals+n)-vals;
        for(int i=0;i<n;i++)b[i]={lower_bound(vals,vals+m,step[i+1])-vals,i+1};
        log=0;
        while((1<<log)<m)log++;
        for(int i=0;i<n;i++){
            sum_lim[log][i+1]=sum_lim[log][i]+lim[i+1];
            sum_rate[log][i+1]=sum_rate[log][i]+rate[i+1];
        }
        for(int d=log-1;d>=0;d--){
            auto f=[&](pair<int,int> x){return !(x.first>>d&1);};
            for(int i=0;i<n;i++)cumsum[d][i+1]=cumsum[d][i]+f(b[i]);
            mid[d]=stable_partition(b,b+n,f)-b;
            for(int i=0;i<n;i++){
                int j=b[i].second;
                sum_lim[d][i+1]=sum_lim[d][i]+lim[j];
                sum_rate[d][i+1]=sum_rate[d][i]+rate[j];
            }
        }
    }
    pair<ll,ll> query(int l,int r,int v){
        if(l>r)return {0,0};
        l--;
        v=upper_bound(vals,vals+m,v)-vals;
        if(v==0)return {0,0};
        if(v==m)return {sum_lim[log][r]-sum_lim[log][l],sum_rate[log][r]-sum_rate[log][l]};
        ll lim=0,rate=0;
        for(int d=log-1;d>=0;d--){
            int cl=cumsum[d][l],cr=cumsum[d][r];
            if(v>>d&1){
                lim+=sum_lim[d][cr]-sum_lim[d][cl];
                rate+=sum_rate[d][cr]-sum_rate[d][cl];
                l+=mid[d]-cl,r+=mid[d]-cr;
            }else l=cl,r=cr;
        }
        return {lim,rate};
    }
}wt;

ll calc(int l,int r,ll pt,ll t){
    ll res=0;
    if(pt==-1){
        for(int i=l;i<=r;i++)res+=min((ll)lim[i],s[i]+rate[i]*t);
        return res;
    }
    ll dt=t-pt;
    auto [lim1,rate1]=wt.query(l,r,dt); 
    auto [lim2,rate2]=wt.query(l,r,INF);
    return lim1+(rate2-rate1)*dt;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> s[i] >> lim[i] >> rate[i];
        step[i]=rate[i]?(lim[i]+rate[i]-1)/rate[i]:INF;
    }
    wt.build();
    cin >> q;
    mp[n]={1,-1};
    while(q--){
        int t,l,r;
        cin >> t >> l >> r;
        ll res=0;
        auto it=mp.lower_bound(l);
        assert(it!=mp.end());
        {
            int pr=it->first;
            auto &[pl,pt]=it->second;
            assert(pl<=l);
            if(pl<l){
                mp[l-1]=it->second;
                pl=l;
            }
        }
        for(;it!=mp.end()&&it->first<=r;it=mp.erase(it)){
            int pr=it->first;
            auto [pl,pt]=it->second;
            res+=calc(pl,pr,pt,t);
        }
        if(it!=mp.end()){
            int pr=it->first;
            auto &[pl,pt]=it->second;
            if(pl<=r){
                res+=calc(pl,r,pt,t);
                pl=r+1;
            }
        }
        mp[r]={l,t};
        cout << res << "\n";
    }
}