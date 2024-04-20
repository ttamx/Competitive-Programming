#include<bits/stdc++.h>
#define cerr if(0)cerr

using namespace std;

using ll = long long;

const int N=1e5+5;
const int Q=3e5+5;
const int LG=17;
const ll INF=1e18;

int n,t,q;
int m[N];
vector<int> a[N],b[N];
vector<pair<int,ll>> dp[LG][N];
vector<pair<int,ll>> cost[N];
vector<pair<int,int>> qr[N];
ll ans[Q];
int lg[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> t;
    for(int i=1;i<n;i++){
        int k;
        cin >> k;
        vector<pair<int,int>> res(k);
        for(auto &[l,r]:res)cin >> l >> r;
        sort(res.begin(),res.end(),[&](pair<int,int> x,pair<int,int> y){
            return x.first>y.first||(x.first==y.first&&y.second<x.second);
        });
        int mn=t;
        for(auto [l,r]:res){
            if(r>=mn)continue;
            mn=r;
            a[i].emplace_back(l);
            b[i].emplace_back(r);
            m[i]++;
        }
        reverse(a[i].begin(),a[i].end());
        reverse(b[i].begin(),b[i].end());
    }
    cin >> q;
    for(int i=1;i<=q;i++){
        int l,r;
        cin >> l >> r;
        qr[l].emplace_back(r,i);
        ans[i]=INF;
    }
    for(int i=1;i<n;i++){
        for(int j=0;j<LG;j++)dp[j][i].resize(m[i]);
        cost[i+1].resize(m[i]);
        for(int j=0;j<m[i];j++){
            dp[0][i][j]={j,b[i][j]-a[i][j]};
            cerr << i << "," << j << " : (" << j << "," << b[i][j]-a[i][j] << ")\n";
            if(i==n-1)continue;
            auto it=lower_bound(a[i+1].begin(),a[i+1].end(),b[i][j]);
            if(it==a[i+1].end()){
                cost[i+1][j]={0,a[i+1][0]+t-b[i][j]};
            }else{
                cost[i+1][j]={it-a[i+1].begin(),*it-b[i][j]};
            }
        }
    }
    for(int s=1;s<LG;s++){
        cerr << "--- " << (1<<s) << " ---\n";
        for(int i=1;i<n;i++){
            if(i+(1<<s)>n)break;
            for(int j=0;j<m[i];j++){
                auto [p,w]=dp[s-1][i][j];
                int x=i+(1<<(s-1));
                w+=cost[x][p].second;
                p=cost[x][p].first;
                w+=dp[s-1][x][p].second;
                p=dp[s-1][x][p].first;
                dp[s][i][j]={p,w};
                cerr << i << "," << j << " : (" << p << "," << w << ")\n";
            }
        }
    }
    lg[0]=-1,lg[1]=0;
    for(int i=2;i<=n;i++)lg[i]=lg[i/2]+1;
    for(int l=1;l<=n;l++){
        sort(qr[l].begin(),qr[l].end());
        unordered_map<int,ll> pt;
        ll res=INF;
        for(int j=0;j<m[l];j++){
            pt[dp[0][l][j].first]=dp[0][l][j].second;
            res=min(res,dp[0][l][j].second);
        }
        int pre=l+1;
        for(auto [r,i]:qr[l]){
            if(r>pre){
                res=INF;
                unordered_map<int,ll> npt;
                for(auto [_p,_w]:pt){
                    int x=pre,p=_p;
                    ll w=_w;
                    for(int s=lg[r-x];s>=0;s--){
                        int tar=x+(1<<s);
                        if(tar>r)continue;
                        cerr << x << "," << p << " -> ";
                        w+=cost[x][p].second;
                        p=cost[x][p].first;
                        w+=dp[s][x][p].second;
                        p=dp[s][x][p].first;
                        cerr << tar << "," << p << "\n";
                        x=tar;
                    }
                    auto it=npt.find(p);
                    if(it==npt.end())npt[p]=w;
                    else it->second=min(it->second,w);
                    res=min(res,w);
                }
                swap(pt,npt);
                pre=r;
            }
            ans[i]=min(ans[i],res);
        }
    }
    for(int i=1;i<=q;i++)cout << ans[i] << "\n";
}